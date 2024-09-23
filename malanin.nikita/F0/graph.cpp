#include "graph.hpp"
#include <delimiters.hpp>
#include <algorithm>
#include <utility>
#include <limits>
#include <iterator>
#include <iomanip>

void malanin::Graph::addNode(int name)
{
  if (contains(name))
  {
    throw std::invalid_argument("[ERROR](insertion): the node you want to add already exists");
  }
  nodes_.insert({name, Node{name}});
}

void malanin::Graph::rmNode(int name)
{
  Node& node = nodes_.at(name);
  auto iter(node.edges.begin());
  for (auto iter(node.edges.begin()); !node.edges.empty(); iter = node.edges.begin())
  {
    int neighbourName = iter->dest;
    rmEdge(name, neighbourName);
    rmEdge(neighbourName, name);
  }
  nodes_.erase(name);
}

void malanin::Graph::addEdge(int lnode, int rnode, size_t weight)
{
  if (!contains(lnode))
  {
    throw std::invalid_argument("[ERROR](connection): no node named " + std::to_string(lnode));
  }
  if (!contains(rnode))
  {
    throw std::invalid_argument("[ERROR](connection): no node named " + std::to_string(rnode));
  }
  Node& leftNode = nodes_[lnode];
  Node& rightNode = nodes_[rnode];

  Edge fromLeftToRight{rightNode.name, weight};

  leftNode.edges.pushBack(fromLeftToRight);
  rightNode.backLinks.insert({lnode, fromLeftToRight});
}

void malanin::Graph::rmEdge(int lnode, int rnode)
{
  if (!contains(lnode))
  {
    throw std::invalid_argument("[ERROR](disconnection): node names" + std::to_string(lnode) + " doesn't exist");
  }
  if (!contains(rnode))
  {
    throw std::invalid_argument("[ERROR](disconnection): node names" + std::to_string(rnode) + " doesn't exist");
  }

  Node& leftNode = nodes_[lnode];
  Node& rightNode = nodes_[rnode];

  leftNode.edges.remove(rightNode.backLinks[lnode]);
  rightNode.backLinks.erase(lnode);
}

bool malanin::Graph::pathExists(int start, int finish) const
{
  DeepDetourer dd(*this);
  return dd.checkPathExistance(start, finish);
}

size_t malanin::Graph::countPaths(int start, int finish) const
{
  DeepDetourer dd(*this);
  return dd.countPaths(start, finish);
}

size_t malanin::Graph::calcPathLength(const List< int >& path) const
{
  size_t length = 0;
  if (path.empty())
  {
    return length;
  }
  auto prev = path.cbegin();
  auto cur = ++path.cbegin();
  while (cur != path.cend())
  {
    auto& backlinks = nodes_.at(*cur).backLinks;
    length += backlinks.at(*prev).weight;
    prev = cur;
    ++cur;
  }
  return length;
}

malanin::Graph::Path malanin::Graph::findAnyPath(int start, int finish) const
{
  DeepDetourer dd(*this);
  List< int > path = dd.findAnyPath(start, finish);
  return Path{calcPathLength(path), path};
}

void malanin::Graph::printPath(const Path& path, std::ostream& out) const
{
  out << "Path nodes: ";
  for (auto iter(path.path.cbegin()); iter != path.path.cend(); ++iter)
  {
    out << *iter << ' ';
  }
  out << "\b; cumulative length: " << path.lenght << '\n';
}

void malanin::Graph::printAnyPath(int start, int finish, std::ostream& out) const
{
  DeepDetourer dd(*this);
  Path path = findAnyPath(start, finish);
  printPath(path, out);
}

malanin::List< malanin::Graph::Path > malanin::Graph::findAllPaths(int start, int finish) const
{
  DeepDetourer dd(*this);
  List< Path > result;
  List< List< int > > paths = dd.findAllPaths(start, finish);
  for (List< int > rawPath : paths)
  {
    result.push_front(Path {calcPathLength(rawPath), rawPath});
  }
  return result;
}

void malanin::Graph::printAllPaths(int start, int finish, std::ostream& out) const
{
  List< Path > paths = findAllPaths(start, finish);
  for (Path path : paths)
  {
    printPath(path, out);
  }
}


std::ostream& malanin::Graph::printNodes(std::ostream& out) const
{
  for (auto cIter(nodes_.cbegin()); cIter != nodes_.cend();)
  {
    out << cIter->first;
    if (++cIter != nodes_.cend())
    {
      out << ' ';
    }
  }
  out << '\n';
  return out;
}

std::ostream& malanin::Graph::printAllEdges(std::ostream& out) const
{
  Printer printer;
  for (auto cIter(nodes_.cbegin()); cIter != nodes_.cend();)
  {
    printer.printUniqueEdges(cIter->second, out);
    if (++cIter == nodes_.cend())
    {
      return out << '\n';
    }
    const Node& nextNode = cIter->second;
    if (printer.hasUniqueEdges(nextNode))
    {
      out << ' ';
    }
  }
  return out << '\n';
}

std::ostream& malanin::Graph::Printer::printUniqueEdges(const Node& node, std::ostream& out)
{
  visitedNodes.pushBack(node.name);
  for (auto cIter(node.edges.cbegin()); cIter != node.edges.cend(); cIter++)
  {
    int destinationName = cIter->dest;
    size_t weight = cIter -> weight;
    bool edgeIsUnique = !visitedNodes.contains(destinationName);
    if (edgeIsUnique)
    {
      if (cIter != node.edges.cbegin())
      {
        out << ' ';
      }
      out << node.name << '-' << destinationName << ':' << weight;
    }
  }
  return out;
}

bool malanin::Graph::Printer::hasUniqueEdges(const Node& node) const
{
  for (auto cIter(node.edges.cbegin()); cIter != node.edges.cend(); cIter++)
  {
    int destName = cIter->dest;
    bool isUnique = !visitedNodes.contains(destName);
    if (isUnique)
    {
      return true;
    }
  }
  return false;
}

size_t malanin::Graph::Edge::HashFunction::operator()(const Edge& rhs) const
{
  size_t ptrHash = std::hash< int >()(rhs.dest);
  size_t weightHash = std::hash< size_t >()(rhs.weight) << 1;
  return ptrHash ^ weightHash;
}

bool malanin::Graph::Edge::operator==(const Edge& rhs) const
{
  return dest == rhs.dest && weight == rhs.weight;
}

malanin::Graph::Dextra::Dextra(const Graph& curGraph):
  graph(curGraph)
{
  for (auto cIter(curGraph.nodes_.cbegin()); cIter != curGraph.nodes_.cend(); cIter++)
  {
    const Node& node = cIter->second;
    unprocessedNodes.pushBack(node.name);
    timeToNodes.insert({node.name, std::numeric_limits< size_t >::max()});
  }
}

malanin::Graph::Path malanin::Graph::Dextra::operator()(int start, int finish)
{
  if (!graph.contains(start))
  {
    throw std::invalid_argument("[ERROR](navigation): no node " + std::to_string(start));
  }
  if (!graph.contains(finish))
  {
    throw std::invalid_argument("[ERROR](navigation): no node " + std::to_string(finish));
  }
  updateNodeState(start, 0);
  calcMinTimeToEach();
  Path path;
  path.lenght = timeToNodes.at(finish);
  path.path = findShortestPath(start, finish);
  return path;
}

void malanin::Graph::Dextra::calcMinTimeToEach()
{
  while(!unprocessedNodes.empty())
  {
    int nameOfNodeWithMinimumTime = getNodeWithMinimumTimeToIt();
    if (timeToNodes.at(nameOfNodeWithMinimumTime) == std::numeric_limits< size_t >::max())
    {
      return;
    }
    const Node& node = graph.nodes_.at(nameOfNodeWithMinimumTime);
    recalculateTimeToNeighboursOfTheNode(node);
    unprocessedNodes.remove(node.name);
  }
}

void malanin::Graph::Dextra::recalculateTimeToNeighboursOfTheNode(const Node& node)
{
  for (auto iter(node.edges.cbegin()); iter != node.edges.cend(); iter++)
  {
    int neighbourName = iter->dest;
    bool neighbourIsUnprocessed = unprocessedNodes.contains(neighbourName);
    if (neighbourIsUnprocessed)
    {
      size_t timeToNeighbour = timeToNodes.at(node.name) + iter->weight;
      if (timeToNeighbour < timeToNodes.at(neighbourName))
      {
        updateNodeState(neighbourName, timeToNeighbour, node.name);
      }
    }
  }
}

int malanin::Graph::Dextra::getNodeWithMinimumTimeToIt()
{
  size_t minTime = std::numeric_limits< size_t >::max();
  int node = -1;
  for (auto iter(unprocessedNodes.cbegin()); iter != unprocessedNodes.cend(); iter++)
  {
    size_t curTime = timeToNodes.at(*iter);
    if (curTime <= minTime)
    {
      node = *iter;
      minTime = curTime;
    }
  }
  return node;
}

malanin::List< int > malanin::Graph::Dextra::findShortestPath(int start, int finish)
{
  if (timeToNodes.at(finish) == std::numeric_limits< size_t >::max())
  {
    std::invalid_argument("[ERROR](navigation): no path exists from node " + std::to_string(start)
     + " to node " + std::to_string(finish) + '\n');
  }
  malanin::List< int > path;
  path.pushFront(finish);
  do
  {
    int parentNode = nodesParrents.at(finish);
    path.pushFront(parentNode);
    finish = parentNode;
  } while (finish != start);
  return path;
}

void malanin::Graph::Dextra::updateNodeState(int node, size_t timeToNode, int parrentNode)
{
  timeToNodes[node] = timeToNode;
  nodesParrents[node] = parrentNode;
}

bool isNewLine(std::istream& in)
{
  in >> std::noskipws;
  char peek = in.peek();
  in >> std::skipws;
  return peek == '\n';
}

std::istream& malanin::operator>>(std::istream& in, Graph& graph)
{
  using del = DelimiterIO;

  int lnode = -1, rnode = -1;
  size_t weight;

  while(!(in.eof() || isNewLine(in)))
  {
    in >> lnode >> del{'-'} >> rnode >> del{':'} >> weight;
    if (in.fail() && !in.eof())
    {
      std::cerr << "Warning: failed to read one of the nodes\n";
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), ' ');
      continue;
    }
    if (!graph.contains(lnode))
    {
      graph.addNode(lnode);
    }
    if (!graph.contains(rnode))
    {
      graph.addNode(rnode);
    }
    graph.addEdge(lnode, rnode, weight);
  }
  return in;
}

bool malanin::Graph::contains(int nodeName) const
{
  return nodes_.contains(nodeName);
}

malanin::Graph::DeepDetourer::DeepDetourer(const Graph& curGraph):
  graph_(curGraph)
{}

bool malanin::Graph::DeepDetourer::checkPathExistance(int begin, int end)
{
  return !findAnyPath(begin, end).empty();
}

size_t malanin::Graph::DeepDetourer::countPaths(int begin, int end)
{
  List< Path > paths = findAllPaths(begin, end);
  return std::distance(paths.begin(), paths.end());
}

bool malanin::Graph::DeepDetourer::getPath(int begin, int end, Path& path)
{
  if (begin == end)
  {
    path.push_front(begin);
    return true;
  }
  passedNodes_.push_back(begin);
  auto& edges = graph_.nodes_.at(begin).edges;
  for (auto edgeIter(edges.cbegin()); edgeIter != edges.cend(); ++ edgeIter)
  {
    if (!passedNodes_.contains(edgeIter->dest))
    {
      if (getPath(edgeIter->dest, end, path))
      {
        path.push_front(begin);
        return true;
      }
    }
  }
  return false;
}

malanin::Graph::DeepDetourer::Path malanin::Graph::DeepDetourer::findAnyPath(int begin, int end)
{
  Path path;
  getPath(begin, end, path);
  return path;
}

bool malanin::Graph::DeepDetourer::doPathContainsNode(int node, const Path& path)
{
  for (auto iter(path.cbegin()); iter != path.cend(); ++iter)
  {
    if (*iter == node)
    {
      return true;
    }
  }
  return false;
}

void malanin::Graph::DeepDetourer::getAllPaths(int begin, int end, List< Path >& paths, Path curPath)
{
  if (begin == end)
  {
    Path pathCopy = curPath;
    pathCopy.push_back(end);
    paths.push_front(pathCopy);
  }
  curPath.push_back(begin);
  auto& edges = graph_.nodes_.at(begin).edges;
  for (auto edgeIter(edges.cbegin()); edgeIter != edges.cend(); ++ edgeIter)
  {
    if (!doPathContainsNode(edgeIter->dest, curPath))
    {
      getAllPaths(edgeIter->dest, end, paths, curPath);
    }
  }
  passedNodes_.remove(begin);
}

malanin::List< malanin::Graph::DeepDetourer::Path > malanin::Graph::DeepDetourer::findAllPaths(int begin, int end)
{
  List< Path > paths;
  getAllPaths(begin, end, paths, Path());
  return paths;
}
