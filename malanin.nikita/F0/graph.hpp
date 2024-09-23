#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <tree.hpp>
#include <list.hpp>
#include <iostream>

namespace malanin
{
  class Graph
  {
  public:
    Graph() = default;

    void addNode(int name);
    void addEdge(int lnode, int rnode, size_t weight = 1);
    void rmNode(int name);
    void rmEdge(int lnode, int rnode);

    struct Path;
    bool pathExists(int start, int finish) const;
    size_t countPaths(int start, int finish) const;
    Path findAnyPath(int start, int finish) const;
    void printAnyPath(int start, int finish, std::ostream&) const;
    List< Path > findAllPaths(int start, int finish) const;
    void printAllPaths(int start, int finish, std::ostream&) const;

    std::ostream& printNodes(std::ostream& = std::cout) const;
    std::ostream& printAllEdges(std::ostream& = std::cout) const;
    bool contains(int nodeName) const;

    std::string name;
    std::string filename;
  private:
    struct Node;
    Tree< int, Node > nodes_;

    struct Edge;
    struct DeepDetourer;
    struct Printer;
    struct Dextra;

    size_t calcPathLength(const List< int >& path) const;
    void printPath(const Path&, std::ostream&) const;
  };

  struct Graph::Path
  {
    size_t lenght;
    List< int > path;
  };

  struct Graph::Printer
  {
    std::ostream& printUniqueEdges(const Node&, std::ostream&);
    bool hasUniqueEdges(const Node&) const;
    List< int > visitedNodes;
  };

  struct Graph::Dextra
  {
    Dextra(const Graph&);

    Path operator()(int begin, int end);

    void calcMinTimeToEach();
    int getNodeWithMinimumTimeToIt();
    void recalculateTimeToNeighboursOfTheNode(const Node&);
    List< int > findShortestPath(int start, int finish);

    void updateNodeState(int node, size_t timeToNode, int parrentNode = -1);

    const Graph& graph;
    List< int > unprocessedNodes;
    Tree <int, int> nodesParrents;
    Tree< int, size_t > timeToNodes;
  };

  struct Graph::DeepDetourer
  {
    using Path = List< int >;

    DeepDetourer(const Graph&);

    bool checkPathExistance(int begin, int end);
    size_t countPaths(int begin, int end);
    Path findAnyPath(int begin, int end);
    List< Path > findAllPaths(int begin, int end);

    bool getPath(int begin, int end, Path& path);
    void getAllPaths(int begin, int end, List< Path >& paths, Path curPath);
    bool doPathContainsNode(int node, const Path& path);

    List< int > passedNodes_;
    const Graph& graph_;
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
    List< Edge > edges;
    Tree< int, Edge > backLinks;
  };
  std::istream& operator>>(std::istream&, Graph&);
}

#endif

