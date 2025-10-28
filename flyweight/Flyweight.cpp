#include "Flyweight.h"
template <class T>
Flyweight<T>::Flyweight(T* data)
{
    this->data = data;
}
template <class T>
T* Flyweight<T>::getState()
{
    return data;
}
template <class T>
Flyweight<T>::~Flyweight()
{
    if (data)
        delete this->data;
}