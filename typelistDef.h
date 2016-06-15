
  template<class T, class U>
  struct Typelist
  {
  };

  class NullType
  {
  };

  template<class TList1, class TList2> struct CONCAT;

  template<class T1, class U1, class TList2>
  struct CONCAT<Typelist<T1, U1>, TList2>
  {
    typedef Typelist<T1, typename CONCAT<U1, TList2>::type> type;
  };

  template<class TList1>
  struct CONCAT<TList1, NullType>
  {
    typedef TList1 type;
  };
  template<class TList2>
  struct CONCAT<NullType, TList2>
  {
    typedef TList2 type;
  };

  template<class TList> struct MAX_SIZE_OF;
  template<> struct MAX_SIZE_OF< NullType >
  {
    enum { value = 0 };
  };
  template<class T, class U>
  struct MAX_SIZE_OF< Typelist<T, U> >
  {
    enum { value = sizeof(T) > MAX_SIZE_OF<U>::value ?  sizeof(T): MAX_SIZE_OF<U>::value };
  };

  template<class TList> struct TYPE_COUNT;
  template<> struct TYPE_COUNT< NullType >
  {
    enum { value = 0 };
  };
  template<class T, class U>
  struct TYPE_COUNT< Typelist<T, U> >
  {
    enum { value = 1 + TYPE_COUNT<U>::value };
  };




