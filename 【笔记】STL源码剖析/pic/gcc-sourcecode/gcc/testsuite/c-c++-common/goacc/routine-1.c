/* { dg-additional-options "-Wopenacc-parallelism" } for testing/documenting
   aspects of that functionality.  */

#pragma acc routine gang
/* { dg-warning "region is gang partitioned but does not contain gang partitioned code" "" { target *-*-* } .+3 }
   { dg-warning "region is worker partitioned but does not contain worker partitioned code" "" { target *-*-* } .+2 }
   { dg-warning "region is vector partitioned but does not contain vector partitioned code" "" { target *-*-* } .+1 } */
void gang (void)
{
}

#pragma acc routine worker
/* { dg-warning "region is worker partitioned but does not contain worker partitioned code" "" { target *-*-* } .+2 }
   { dg-warning "region is vector partitioned but does not contain vector partitioned code" "" { target *-*-* } .+1 } */
void worker (void)
{
}

#pragma acc routine vector
/* { dg-warning "region is vector partitioned but does not contain vector partitioned code" "" { target *-*-* } .+1 } */
void vector (void)
{
}

#pragma acc routine seq
void seq (void)
{
}

int main ()
{
#pragma acc kernels num_gangs (32) num_workers (32) vector_length (32)
  {
    gang ();
    worker ();
    vector ();
    seq ();
  }

#pragma acc parallel num_gangs (32) num_workers (32) vector_length (32)
  {
    gang ();
    worker ();
    vector ();
    seq ();
  }

  return 0;
}
