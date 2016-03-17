#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <set>
#include <utility>

#include "Vertex.h"
#include "Edge.h"

class Graph
{
    private:
        std::set<Vertex > _vertices;
        std::set<Edge > _edges;

        std::map<Vertex, std::set<Edge > > _incidents;
        std::map<Edge, std::pair<Vertex, Vertex > > _extremities;

    public:
        Graph();
        const Vertex & addVertex();
        const Edge & addEdge(const Vertex & source, const Vertex & destination);
        bool removeEdge(const Edge & toRemove);
        bool removeVertex(const Vertex & toRemove);
        const std::set <Vertex> & getVertices() const;
        const std::set <Edge> & getEdges() const;
        const std::set <Edge > & getIncidents(const Vertex & v) const;
        const Vertex & source(const Edge & e) const;
        const Vertex & destination(const Edge & e) const;
        int degre(const Vertex & v) const;
        int VertexCount() const;
        int edgeCount() const;
};

#endif // GRAPH_H
