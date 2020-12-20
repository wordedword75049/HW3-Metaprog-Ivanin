#pragma once

#include <memory>
#include "TypeList.h"

template<class TVertices>
struct MetaGraphVertices;

template<size_t idx>
struct MatrixGraphVerticesGet;

template<size_t idx>
struct MatrixGraphVerticesSet;

template<typename ...Args>
struct MetaGraphVertices<typelist::TypeList < Args...>>
{
  using Head = typename typelist::TypeList<Args...>::Head;
  using Tail = typename typelist::TypeList<Args...>::Tail;

  MetaGraphVertices ()
    : upVertex(std::make_unique<Head>()) {}

  std::unique_ptr<Head> upVertex{};
  MetaGraphVertices<Tail> verticesTail;
};

template<>
struct MetaGraphVertices<typelist::NullType> {};

template<>
struct MetaGraphVertices<typelist::EmptyTypeList> {};

template<size_t idx>
struct MatrixGraphVerticesGet
{
  template<typename VerticesStorage>
  static decltype(auto) Get (VerticesStorage &verticesStorage)
  {
    return MatrixGraphVerticesGet<idx - 1>
      ::Get(verticesStorage.verticesTail);
  }
};

template<>
struct MatrixGraphVerticesGet<0>
{
  template<typename VerticesStorage>
  static std::unique_ptr<typename VerticesStorage::Head> &Get (VerticesStorage &verticesStorage)
  {
    return verticesStorage.upVertex;
  }
};

template<size_t idx>
struct MatrixGraphVerticesSet
{
  template<typename T, typename VerticesStorage>
  static void Set (VerticesStorage &verticesStorage, T &&obj)
  {
    MatrixGraphVerticesSet<idx - 1>
      ::Set(verticesStorage.verticesTail, std::forward<T>(obj));
  }
};

template<>
struct MatrixGraphVerticesSet<0>
{
  template<typename T, typename VerticesStorage>
  static void Set (VerticesStorage &verticesStorage, T &&obj)
  {
    verticesStorage.upVertex = std::make_unique<typename VerticesStorage::Head>(obj);
  }
};
