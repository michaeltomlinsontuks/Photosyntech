#include "FlyweightFactory.h"
template <class ID, class T>
FlyweightFactory<ID, T>::FlyweightFactory()
{
    cache = new unordered_map<ID, Flyweight<T> *>;
}

template <class ID, class T>
Flyweight<T> *FlyweightFactory<ID, T>::getFlyweight(ID id, T *data)
{

    if (cache->find(id) != cache->end())
    {
        return (*cache)[id];
    }
    else
    {

        if (data == NULL)
        {

            throw "Data given for flyweight is NULL";
            return nullptr;
        }
        else
        {
            (*cache)[id] = new Flyweight<T>(data);
        }

        return (*cache)[id];
    }
}

template <class ID, class T>
FlyweightFactory<ID, T>::~FlyweightFactory()
{
    auto itr = cache->begin();
    while (itr != cache->end())
    {
        if (itr->second)
        {
            delete itr->second;
        }
        itr++;
    }
    cache->clear();
    delete cache;
}