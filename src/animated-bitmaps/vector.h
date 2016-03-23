#include <stdlib.h>

template<class Data>
class Vector {
    size_t d_size; // Stores no. of actually stored objects
    size_t d_capacity; // Stores allocated capacity
    Data *d_data; // Stores data this is this "heap" we need a function that returns a pointer to this value, to print it
public:
//    Vector() : d_size(0), d_capacity(0), d_data(0) {}; // Default constructor
    Vector();

    Vector(Vector const &other); 
    Vector(Data a);  

//    Vector(Data a, Data b, Data c, Data d);
    
    ~Vector();

    Vector &operator=(Vector const &other);

    void push_back(Data const &x);

    void Clear();

    size_t size() const { return d_size; }; // Size getter

    Data const &operator[](size_t idx) const { return d_data[idx]; }; // Const getter

    Data &operator[](size_t idx) { return d_data[idx]; }; // Changeable getter

    Data *pData() { return (Data*)d_data; }

private:
    void resize();

};
