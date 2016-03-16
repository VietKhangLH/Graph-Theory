#ifndef Vertex_H
#define Vertex_H

class Vertex
{
    private:
        int _id;
        static int _currentId;
    public:
        Vertex(bool valid = false);
        int id() const;
        bool valid() const;
        bool operator<(const Vertex & v) const;
};

#endif // Vertex_H
