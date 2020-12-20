#pragma once 
namespace typelist {


  class NullType {
  };

  class __NonExistentType {
  };

  template<typename ...Args>
  struct TypeList {
    using Head = NullType;
    using Tail = NullType;
  };

  template<typename H, typename ...T>
  struct TypeList<H, T...> {
    using Head = H;
    using Tail = TypeList<T...>;
  };

  typedef TypeList<> EmptyTypeList;

  template<typename H>
  struct TypeList<H> {
    using Head = H;
    using Tail = EmptyTypeList;
  };


  template<typename T>
  struct Length {
    static const size_t val = 1 + Length<typename T::Tail>::val;
  };

  template<>
  struct Length<NullType> {
    static const size_t val = 0;
  };


  template<size_t idx, typename ...T>
  struct TypeAt {
    using res = NullType;
  };

  template<size_t idx, typename ...T>
  struct TypeAt<idx, TypeList<T...>> {
    using res = typename TypeAt<idx - 1, typename TypeList<T...>::Tail>::res;
  };

  template<size_t idx>
  struct TypeAt<idx, NullType> {
    using res = NullType;
  };

  template<typename ...T>
  struct TypeAt<0, TypeList<T...>> {
    using res = typename TypeList<T...>::Head;
  };


  template<typename U, typename ...T>
  struct IndexOf {
    static const size_t val = 1;
  };

  template<typename ...K, typename U>
  struct IndexOf<U, TypeList<K...>> {
    static const size_t val = 1 + IndexOf<U, typename TypeList<K...>::Tail>::val;
  };

  template<typename T, typename ...K>
  struct IndexOf<TypeList<T, K...>, T> {
    static const size_t val = 0;
  };

};
