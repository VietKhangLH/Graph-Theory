#include "Graph.h"
#include "cassert"

using namespace std;

Graph::Graph()
{}

const Vertex & Graph::addVertex()
{
    Vertex toAdd {true};
    _vertices.insert(toAdd);
    _incidents[toAdd] = {};

    return *_vertices.find(toAdd);
}

const Edge & Graph::addEdge(const Vertex & source, const Vertex & destination)
{
    assert(_vertices.find(source) != _vertices.end() &&
           _vertices.find(destination) != _vertices.end());
    Edge toAdd {true};
    _edges.insert(toAdd);
    _extremities[toAdd] = make_pair(source, destination);
    _incidents[source].insert(toAdd);
    _incidents[destination].insert(toAdd);

    return *_edges.find(toAdd);
}

bool Graph::removeEdge(const Edge & toRemove)
{
    if(_edges.find(toRemove) != _edges.end())
        return false;

    _edges.erase(toRemove);
    _incidents.at(_extremities.at(toRemove).first).erase(toRemove);
    _incidents.at(_extremities.at(toRemove).second).erase(toRemove);
    _extremities.erase(toRemove);
    return true;
}

bool Graph::removeVertex(const Vertex & toRemove)
{
    if(_vertices.find(toRemove) != _vertices.end())
        return false;

    _vertices.erase(toRemove);
    for(auto it = _incidents.at(toRemove).begin() ; it != _incidents.at(toRemove).end() ; ++it)
        _extremities.erase(*it);
    _incidents.at(toRemove).clear();
    _incidents.erase(toRemove);
    return true;
}

const std::set <Vertex> & Graph::getVertices() const
{
    return _vertices;
}

const std::set <Edge> & Graph::getEdges() const
{
    return _edges;
}

const std::set <Edge > & Graph::getIncidents(const Vertex & v) const
{
    assert(_incidents.find(v) != _incidents.end());

    return _incidents.at(v);
}

const Vertex & Graph::source(const Edge & e) const
{
    return _extremities.at(e).first;
}

const Vertex & Graph::destination(const Edge & e) const
{
    return _extremities.at(e).second;
}

int Graph::degre(const Vertex & v) const
{
    return _incidents.at(v).size();
}

int Graph::VertexCount() const
{
    return _vertices.size();
}

int Graph::edgeCount() const
{
    return _edges.size();
}


