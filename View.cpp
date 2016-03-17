#include "View.h"

#include <sstream>
#include <iostream>

using namespace std;
using namespace sf;

constexpr int VERTEX_RADIUS = 20;

//=======================================
// Constructeur
//=======================================
SFMLView::SFMLView(int w, int h): // On affecte la valeur des dimensions (width et height) directement a la construction de l'objet
    _w(w),
    _h(h),
    _vertexShape{20, VERTEX_RADIUS}
{
    _window = new RenderWindow(VideoMode(w, h, 32), "Graph Theory", Style::Close);
    _window->setFramerateLimit(FRAME_LIMIT);
    _vertexShape.setOrigin(VERTEX_RADIUS, VERTEX_RADIUS);
    _vertexShape.setFillColor(Color::White);
    _vertexShape.setOutlineThickness(2);
    _vertexShape.setOutlineColor(Color::Black);
    for(int i = 0 ; i < 2 ; ++i)
    {
        _linePreview[i].color = Color::Transparent;
        _edgeShape[i].color = Color::Black;
    }
}

//=======================================
// Destructeur
//=======================================
SFMLView::~SFMLView()
{
    if(_window != nullptr)
        delete _window;
}

//=======================================
// Accesseurs en écriture
//=======================================
void SFMLView::setGraph(Graph & graph)
{
    _graph = graph;
}
//=======================================
// Fonction de dessin
//=======================================
void SFMLView::draw()
{
    _window->clear(Color::White);

    _window->draw(_linePreview, 2, Lines);

    for(auto i = _edges.begin() ; i != _edges.end() ; ++i)
    {
        _edgeShape[0].position = Vector2f ((float)i->second.first.x, (float)i->second.first.y);
        _edgeShape[1].position = Vector2f ((float)i->second.second.x, (float)i->second.second.y);
        _window->draw(_edgeShape, 2, Lines);
    }
    for(auto i = _vertices.begin() ; i != _vertices.end() ; ++i)
    {
        _vertexShape.setPosition((float)i->second.x, (float)i->second.y);
        _window->draw(_vertexShape);
    }

    _window->display(); // On affiche ce qu'il y a a afficher (dans l'ordre d'appels des draw)
}

//=======================================
// Traitement des evenements
//=======================================
bool SFMLView::treatEvents() // Cette methode gere les evenements clavier, elle renvoie vrai tant qu'il faut continuer a gerer ces evenements
{
    bool quit = false; // On ne veut pas quitter de base
    if(_window->isOpen()) // Si la fenetre est ouverte
    {
        Event event;
        while (_window->pollEvent(event)) // Tant qu'il y a un evenement utilisateur dans la file d'attente
        {
            // On regarde si cet evenement correspond a :
            // - d'une part la fermeture de la fenetre
            // - la touche echap est appuyee
            // Dans ces deux cas on ferme la fenetre, et on retourne faux, ce qui va faire sortir de la boucle du main
            if ((event.type == Event::Closed) ||
                    ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape)))
            {
                _window->close();
                quit = true;
            }
            else
            {
                switch(event.type)
                {
                case Event::MouseButtonPressed:
                {
                    switch(event.mouseButton.button)
                    {
                    case Mouse::Left:
                    {
                        bool collision = false;
                        auto i = _vertices.begin();
                        while(!collision && i != _vertices.end())
                        {
                            collision = (Mouse::getPosition(*_window).x - i->second.x) * (Mouse::getPosition(*_window).x - i->second.x)
                                        + (Mouse::getPosition(*_window).y - i->second.y) * (Mouse::getPosition(*_window).y - i->second.y)
                                        <= (VERTEX_RADIUS * VERTEX_RADIUS * 4 + VERTEX_RADIUS);
                            i++;
                        }
                        if(!collision)
                            _vertices[_graph.addVertex()] = {(float)Mouse::getPosition(*_window).x, (float)Mouse::getPosition(*_window).y};
                        break;
                    }
                    case Mouse::Middle:
                    {
                        bool collision = false;
                        auto i = _vertices.begin();
                        while(!collision && i != _vertices.end())
                        {
                            collision = (Mouse::getPosition(*_window).x - i->second.x) * (Mouse::getPosition(*_window).x - i->second.x)
                                        + (Mouse::getPosition(*_window).y - i->second.y) * (Mouse::getPosition(*_window).y - i->second.y)
                                        <= VERTEX_RADIUS * VERTEX_RADIUS;
                            if(collision)
                            {
                                _graph.removeVertex(i->first);
                                for(auto j = _graph.getIncidents(i->first).begin() ; j != _graph.getIncidents(i->first).end() ; ++j)
                                {
                                    _edges.erase(*j);
                                }
                                _vertices.erase(i);
                            }
                            else i++;
                        }
                    }
                    case Mouse::Right:
                    {
                        bool collision = false;
                        auto i = _vertices.begin();
                        while(!collision && i != _vertices.end())
                        {
                            collision = (Mouse::getPosition(*_window).x - i->second.x) * (Mouse::getPosition(*_window).x - i->second.x)
                                        + (Mouse::getPosition(*_window).y - i->second.y) * (Mouse::getPosition(*_window).y - i->second.y)
                                        <= VERTEX_RADIUS * VERTEX_RADIUS;
                            if(collision)
                            {
                                for(int j = 0 ; j < 2 ; ++j)
                                {
                                    _linePreview[j].position = Vector2f {(float)i->second.x, (float)i->second.y};
                                    _linePreview[j].color = Color::Black;
                                }
                            }
                            else i++;
                        }
                    }
                    break;
                    default:
                        break;
                    }
                }
                break;
                case Event::MouseMoved:
                    if(_linePreview[0].color != Color::Transparent)
                        _linePreview[1].position = Vector2f {(float)Mouse::getPosition(*_window).x, (float)Mouse::getPosition(*_window).y};
                    break;
                case Event::MouseButtonReleased:
                    if(event.mouseButton.button == Mouse::Right && _linePreview[0].color != Color::Transparent)
                    {
                        for(int i = 0 ; i < 2 ; ++i)
                            _linePreview[i].color = Color::Transparent;

                        bool collision = false;
                        auto i = _vertices.begin();
                        while(!collision && i != _vertices.end())
                        {
                            collision = (Mouse::getPosition(*_window).x - i->second.x) * (Mouse::getPosition(*_window).x - i->second.x)
                                        + (Mouse::getPosition(*_window).y - i->second.y) * (Mouse::getPosition(*_window).y - i->second.y)
                                        <= VERTEX_RADIUS * VERTEX_RADIUS;
                            if(collision)
                            {
                                bool sourceTrouve = false;
                                auto j = _vertices.begin();
                                while(!sourceTrouve && j != _vertices.end())
                                {
                                    sourceTrouve = Vector2f {(float)j->second.x, (float)j->second.y} ==_linePreview[0].position;
                                    if(sourceTrouve)
                                        _edges[_graph.addEdge(i->first, j->first)] = make_pair(_linePreview[0].position, i->second);
                                    else j++;
                                }
                            }
                            else i++;
                        }
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }
    return !quit;
}

void SFMLView::synchronize()
{

}

