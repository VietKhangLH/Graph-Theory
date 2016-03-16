#ifndef _SFMLView_
#define _SFMLView_

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Graph.h"

constexpr int FRAME_LIMIT = 60;

class SFMLView
{
private:
    int _w, _h;

    sf::RenderWindow * _window;
    Graph _graph;

    sf::CircleShape _vertexShape;

    std::map<Vertex, sf::Vector2i > _vertices;
   // std::map<Edge, sf::RectangleShape > _edges;
public:
    SFMLView(int w, int h);
    ~SFMLView();

    void setGraph(Graph & graph);

    bool treatEvents();
    void synchronize();
    void draw();
};
#endif
