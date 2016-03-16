#include "Edge.h"

int Edge::_currentId = 0;
constexpr int FALSE_ID = -1;

Edge::Edge(bool valid) :
    _id(valid ? _currentId++ : FALSE_ID)
{}

int Edge::id() const
{
    return _id;
}

bool Edge::valid() const
{
    return id() != FALSE_ID;
}

bool Edge::operator<(const Edge & e) const
{
    return id() < e.id();
}
