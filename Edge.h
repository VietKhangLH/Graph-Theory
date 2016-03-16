#ifndef EDGE_H
#define EDGE_H

class Edge
{
    private:
        int _id;
        static int _currentId;
    public:
        Edge(bool valid = false);
        int id() const;
        bool valid() const;
        bool operator<(const Edge & e) const;
};

#endif // EDGE_H
