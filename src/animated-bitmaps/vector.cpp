#include "vector.h"
#include <string.h>

template<class Data>
Vector<Data>::Vector() : d_size(0), d_capacity(0), d_data(0) {};

template<class Data>
    Vector<Data>::Vector(Vector const &other) : d_size(other.d_size), d_capacity(other.d_capacity), d_data(0) //for when you set 1 vector = to another
    {
        d_data = (Data *)malloc(d_capacity*sizeof(Data));
        memcpy(d_data, other.d_data, d_size*sizeof(Data));
    }; // Copy constuctor

template<class Data>
Vector<Data>::Vector(Data d) : d_size(0), d_capacity(0), d_data(0) {
  
}

//template<class Data>
//    Vector<Data>::Vector(Data a, Data b, Data c, Data d) {
//        push_back(a);
//        push_back(b);
//        push_back(c);
//        push_back(d);
//    }

template<class Data>
    Vector<Data>::~Vector()
    {
        free(d_data);
    }; // Destructor

template<class Data>
    Vector<Data>& Vector<Data>::operator=(Vector<Data> const &other)
    {
        free(d_data);
        d_size = other.d_size;
        d_capacity = other.d_capacity;
        d_data = (Data *)malloc(d_capacity*sizeof(Data));
        memcpy(d_data, other.d_data, d_size*sizeof(Data));
        return *this;
    }; // Needed for memory management

template<class Data>
    void Vector<Data>::push_back(Data const &x)
    {
        if (d_capacity == d_size) //when he pushes data onto the heap, he checks to see if the storage is full
            resize();  //if full - resize

        d_data[d_size++] = x;
    }; // Adds new value. If needed, allocates more space

template<class Data>
    void Vector<Data>::Clear() //here
    {
        memset(d_data, 0, d_size);
        d_capacity = 0;
        d_size = 0;
        free(d_data);
    }

//template<class Data>
//    size_t Vector<Data>::size() const { return d_size; }; // Size getter

//    Data const &Vector<Data>::operator[](size_t idx) const { return d_data[idx]; }; // Const getter

//    Data &Vector<Data>::operator[](size_t idx) { return d_data[idx]; }; // Changeable getter

//    Data *Vector<Data>::pData() { return (Data*)d_data; }

//private:
template<class Data>
    void Vector<Data>::resize()
    {
        d_capacity = d_capacity ? d_capacity * 2 : 1;
        Data *newdata = (Data *)malloc(d_capacity*sizeof(Data)); //allocates new memory
        memcpy(newdata, d_data, d_size * sizeof(Data));  //copies all the old memory over
        free(d_data);                                          //free old
        d_data = newdata;
    };// Allocates double the old space

template class Vector<int>;

