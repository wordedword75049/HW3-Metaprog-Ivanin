#pragma once

#include <memory>
#include "MatrixGraphComponents.h"
#include "../MetaGraphVertices.h"
#include "../TypeList.h"

template<typename V, typename E>
struct MatrixGraph {};

template<typename ...TVertices, typename ...TEdges>
struct MatrixGraph<typelist::TypeList <TVertices...>, typelist::TypeList<TEdges...>>
{
  using Vertices = typename typelist::TypeList<TVertices...>;
  using Edges = typename typelist::TypeList<TEdges...>;

  static constexpr size_t nVertices = typelist::Length<Vertices>::val;
  static_assert(nVertices != 0, "No vertices");

  MatrixGraph () :
      vertices(),
      edges()
  {}

  template<size_t idx>
  decltype(auto) GetVertex()
  {
    static_assert(
        0 <= idx && idx < nVertices,
        "No such vertex index"
    );
    return MatrixGraphVerticesGet<idx>
      ::Get(vertices);
  }

  template<size_t idx, typename T>
  void SetVertex(T&& obj)
  {
    static_assert(
        0 <= idx && idx < nVertices,
        "No such vertex index"
    );
    static_assert(
        std::is_same<
            typename std::remove_reference<T>::type,
            typename typelist::TypeAt<idx, Vertices>::res
        >::value,
        "Wrong type for vertex"
    );
    MatrixGraphVerticesSet<idx>
      ::Set(vertices, std::forward<T>(obj));
  }

  template<size_t fromId, size_t dstId>
  decltype(auto) GetEdge()
  {
    static_assert(
        0 <= fromId && fromId < nVertices,
        "From index does not exist"
    );
    static_assert(
        0 <= dstId && dstId < nVertices,
        "To index does not exist"
    );
    return MatrixGraphComponentsGet<fromId, dstId>
      ::Get(edges);
  }

  template<size_t fromId, size_t dstId, typename T>
  void SetEdge(T&& obj)
  {
    static_assert(
        0 <= fromId && fromId < nVertices,
        "From index does not exist"
    );
    static_assert(
        0 <= dstId && dstId < nVertices,
        "To index does not exist"
    );
    static_assert(
        std::is_same<
            typename std::remove_reference<T>::type,
            typename typelist::TypeAt<
                dstId,
                typename typelist::TypeAt<fromId, Edges>::res
            >::res
        >::value,
        "Wrong type for edge"
    );
    MatrixGraphComponentsSet<fromId, dstId>
      ::Set(edges, std::forward<T>(obj));
  }

  MatrixGraphComponents<Edges> edges;
  MetaGraphVertices<Vertices>      vertices;
};
