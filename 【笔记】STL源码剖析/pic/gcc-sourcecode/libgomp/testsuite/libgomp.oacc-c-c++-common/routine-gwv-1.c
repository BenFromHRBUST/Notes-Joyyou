#include <stdio.h>
#include <openacc.h>
#include <gomp-constants.h>

#define N (32*32*32+17)

#pragma acc routine gang
void __attribute__ ((noinline)) gang (int ary[N])
{
#pragma acc loop gang worker vector
  for (unsigned ix = 0; ix < N; ix++)
    {
      if (acc_on_device (acc_device_not_host))
	{
	  int g, w, v;

	  g = __builtin_goacc_parlevel_id (GOMP_DIM_GANG);
	  w = __builtin_goacc_parlevel_id (GOMP_DIM_WORKER);
	  v = __builtin_goacc_parlevel_id (GOMP_DIM_VECTOR);
	  ary[ix] = (g << 16) | (w << 8) | v;
	}
      else
	ary[ix] = ix;
    }
}

int main ()
{
  int ary[N];
  int ix;
  int exit = 0;
  int ondev = 0;
  int gangsize, workersize, vectorsize;

  for (ix = 0; ix < N;ix++)
    ary[ix] = -1;
  
#define NG 32
#define NW 32
#define VL 32
#pragma acc parallel num_gangs(NG) num_workers(NW) vector_length(VL) \
  copy(ary) copy(ondev)
  {
    ondev = acc_on_device (acc_device_not_host);
    gang (ary);
  }
  gangsize = NG;
  workersize = NW;
  vectorsize = VL;
#ifdef ACC_DEVICE_TYPE_radeon
  /* AMD GCN has an upper limit of 'num_workers(16)'.  */
  if (workersize > 16)
    workersize = 16;
  /* AMD GCN uses the autovectorizer for the vector dimension: the use
     of a function call in vector-partitioned code in this test is not
     currently supported.  */
  vectorsize = 1;
#endif

  for (ix = 0; ix < N; ix++)
    {
      int expected = ix;
      if(ondev)
	{
	  int chunk_size = (N + gangsize * workersize * vectorsize - 1)
			   / (gangsize * workersize * vectorsize);
	  
	  int g = ix / (chunk_size * vectorsize * workersize);
	  int w = (ix / vectorsize) % workersize;
	  int v = ix % vectorsize;

	  expected = (g << 16) | (w << 8) | v;
	}
      
      if (ary[ix] != expected)
	{
	  exit = 1;
	  printf ("ary[%d]=%x expected %x\n", ix, ary[ix], expected);
	}
    }
  
  return exit;
}
