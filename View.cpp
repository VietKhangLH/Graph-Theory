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
    _vertexShape.setFillColor(Color::Transparent);
    _vertexShape.setOutlineThickness(2);
    _vertexShape.setOutlineColor(Color::Black);
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
                        _vertices[_graph.addVertex()] = Mouse::getPosition(*_window);
                        break;
                    case Mouse::Middle:
                    {
                        // Soit C un cercle de centre Ω(a;b) et de rayon r. Un point M de coordonnées (x;y) appartient à C si et seulement si
                        // (x–a)²+(y–b)²=r²
                        // ssi x² - 2xa + a² + y² - 2yb + b² = r²

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
                                _vertices.erase(i);
                            }
                            else i++;
                        }
                    }
                    default:
                        break;
                    }
                }
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

