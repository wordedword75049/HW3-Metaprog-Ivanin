#pragma once

#include "../MetaGraphVertices.h"
#include "../TypeList.h"

template<class TEdges>
struct MatrixGraphComponents;

template<size_t fromId, size_t dstId>
struct MatrixGraphComponentsGet;

template<size_t fromId, size_t dstId>
struct MatrixGraphComponentsSet;

template<typename ...E>
struct MatrixGraphComponents<typelist::TypeList < E...>>
{
  MatrixGraphComponents () = default;

  MetaGraphVertices<typename typelist::TypeList<E...>::Head>         edgesHead; // ~ edge attr as vertex
  MatrixGraphComponents<typename typelist::TypeList<E...>::Tail> edgesTail;
};

template<>
struct MatrixGraphComponents<typelist::EmptyTypeList> {};

template<>
struct MatrixGraphComponents<typelist::NullType> {};

template<size_t fromId, size_t dstId>
struct MatrixGraphComponentsGet
{
  template<typename EdgesStorage>
  static decltype(auto) Get (EdgesStorage &edgesStorage)
  {
    return MatrixGraphComponentsGet<fromId - 1, dstId>
      ::Get(edgesStorage.edgesTail);
  }
};

template<size_t dstId>
struct MatrixGraphComponentsGet<0, dstId>
{
  template<typename EdgesStorage>
  static decltype(auto) Get (EdgesStorage &edgesStorage)
  {
    return MatrixGraphVerticesGet<dstId>
      ::Get(edgesStorage.edgesHead);
  }
};

template<size_t fromId, size_t dstId>
struct MatrixGraphComponentsSet
{
  template<typename T, typename EdgesStorage>
  static void Set (EdgesStorage &edgesStorage, T &&obj)
  {
    MatrixGraphComponentsSet<fromId - 1, dstId>
      ::Set(edgesStorage.edgesTail, std::forward<T>(obj));
  }
};

template<size_t dstId>
struct MatrixGraphComponentsSet<0, dstId>
{
  template<typename T, typename EdgesStorage>
  static void Set (EdgesStorage &edgesStorage, T &&obj)
  {
    MatrixGraphVerticesSet<dstId>
      ::Set(edgesStorage.edgesHead, std::forward<T>(obj));
  }
};
