#include <cstdlib>
#include <iostream>

#include "View.h"

using namespace std;

int main()
{
    cout << "Hello World !" << endl;
    Graph graph;
    SFMLView view(500, 500);
    view.setGraph(graph);

    while(view.treatEvents())
    {
        view.draw();
    }

    return EXIT_SUCCESS;
}
