#include <iostream>
#include "lib/EmptyEdge.h"
#include "lib/TypeList.h"
#include "lib/graphBymatrix/MatrixGraph.h"

using namespace typelist;

class TestingVertex {};

class TestingEdge1 {};

class TestingEdge2 {};

std::ostream& operator<<(std::ostream& os, const TestingVertex& test1)
{
    os << "This is testing of vertex class";
    return os;
}

std::ostream& operator<<(std::ostream& os, const TestingEdge1& test2)
{
    os << "This is testing of edge class 1";
    return os;
}

std::ostream& operator<<(std::ostream& os, const TestingEdge2& test3)
{
    os << "This is testing of edge class 2";
    return os;
}



int main ()
{
  {
    MatrixGraph<
            TypeList<int, float, TestingVertex, int>,
            TypeList<
            TypeList<EmptyEdge, int,  TestingEdge2, float>,
            TypeList<TestingEdge1, EmptyEdge, std::string, EmptyEdge>,
            TypeList<int, float, EmptyEdge,  int>,
            TypeList<TestingEdge2,  std::string, EmptyEdge,  EmptyEdge>
        >
    > matrixGraph;

    matrixGraph.SetVertex<0>((int)75049);
    matrixGraph.SetVertex<1>((float) 4.529);
    matrixGraph.SetVertex<2>(TestingVertex());
    matrixGraph.SetVertex<3>((int)23);

    matrixGraph.SetEdge<0, 1>((int) 5);
    matrixGraph.SetEdge<0, 2>(TestingEdge2());
    matrixGraph.SetEdge<0, 3>((float)7.13);
    matrixGraph.SetEdge<1, 0>(TestingEdge1());
    std::string s1 = "Edged string";
    matrixGraph.SetEdge<1, 2>(s1);
    matrixGraph.SetEdge<2, 0>((int)3);
    matrixGraph.SetEdge<2, 1>((float) 42.1);
    matrixGraph.SetEdge<2, 3>((int)912);
    matrixGraph.SetEdge<3, 0>(TestingEdge2());
    std::string s2 = "Edge 3-1";
    matrixGraph.SetEdge<3, 1>(s2);


    std::cout << "Vertex number = " << 0 << " = " << *matrixGraph.GetVertex<0>()
        << std::endl;
    std::cout << "Vertex number = " << 1 << " = " << *matrixGraph.GetVertex<1>()
        << std::endl;
    std::cout << "Vertex number = " << 2 << " = " << *matrixGraph.GetVertex<2>()
        << std::endl;
    std::cout << "Vertex number = " << 3 << " = " << *matrixGraph.GetVertex<3>()
        << std::endl;
    std::cout << "Edge<0, 2> = " << *matrixGraph.GetEdge<0, 2>()
        << std::endl;
    std::cout << "Edge<2, 1> = " << *matrixGraph.GetEdge<2, 1>()
        << std::endl;
    std::cout << "Edge<1, 2> = " << *matrixGraph.GetEdge<1, 2>()
        << std::endl;


    
  }
  return 0;
}
