
struct __waiters
{
  __waiters() noexcept;
  ~__waiters () noexcept;

  static __waiters &_S_for()
  {
    static __waiters w;
    
    return w;
  }
};
