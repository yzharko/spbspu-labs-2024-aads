#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <tree.hpp>
#include <list.hpp>
#include <iostream>

namespace miheev
{
  class Graph
  {
  private:
    struct Node;
    struct Edge;

  public:
    Graph() = default;

    void addNode(int name);
    void addEdge(int lnode, int rnode, size_t weight = 1);
    void rmNode(int name);
    void rmEdge(int lnode, int rnode);

    struct Path;
    Path navigate(int start, int finish) const;

    std::ostream& printNodes(std::ostream& = std::cout) const;
    std::ostream& printAllEdges(std::ostream& = std::cout) const;
    bool contains(int nodeName) const;

    std::string name;
    std::string filename;
  private:
    Tree< int, Node > nodes_;

    struct Printer;
    struct Dextra;
  };

  struct Graph::Path
  {
    size_t lenght;
    miheev::List< int > path;
  };

  struct Graph::Printer
  {
    std::ostream& printUniqueEdges(const Node&, std::ostream&);
    bool hasUniqueEdges(const Node&) const;
    miheev::List< int > visitedNodes;
  };

  struct Graph::Dextra
  {
    Dextra(const Graph&);

    Path operator()(int begin, int end);

    void calcMinTimeToEach();
    int getNodeWithMinimumTimeToIt();
    void recalculateTimeToNeighboursOfTheNode(const Node&);
    miheev::List< int > findShortestPath(int start, int finish);

    void updateNodeState(int node, size_t timeToNode, int parrentNode = -1);

    const Graph& graph;
    miheev::List< int > unprocessedNodes;
    Tree <int, int> nodesParrents;
    Tree< int, size_t > timeToNodes;
  };

  struct Graph::Edge
  {
    int dest;
    size_t weight;
    struct HashFunction;
    bool operator==(const Edge&) const;
  };

  struct Graph::Edge::HashFunction
  {
    size_t operator()(const Edge& rhs) const;
  };

  struct Graph::Node
  {
    int name;
    miheev::List< Edge > edges;
    Tree< int, Edge > backLinks;
  };
  std::istream& operator>>(std::istream&, Graph&);
}

#endif