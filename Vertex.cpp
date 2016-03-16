#include "Vertex.h"

int Vertex::_currentId = 0;
constexpr int FALSE_ID = -1;

Vertex::Vertex(bool valid) :
    _id(valid ? _currentId++ : FALSE_ID)
{}

int Vertex::id() const
{
    return _id;
}

bool Vertex::valid() const
{
    return id() != FALSE_ID;
}

bool Vertex::operator<(const Vertex & v) const
{
    return id() < v.id();
}
