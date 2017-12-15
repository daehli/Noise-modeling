//
//  image.cpp
//  tp-P4y
//
//  Created by Benoit Naegel on 25/01/2016.
//  Copyright © 2016 Benoit Naegel. All rights reserved.
//

#include <iostream>
#include <cstring> // memcpy

    template<class T>
Image<T>::Image(int dx, int dy, T *data):dx(0),dy(0),data(0)
{
    if(dx>=0 && dy>=0) {
        this->dx=dx;
        this->dy=dy;
        this->size=dx*dy;
        this->data=new T[this->size];
        if(data != 0) {
            memcpy(this->data, data, size*sizeof(T));
        }
    }
}

    template<class T>
Image<T>::Image(const Image<T> &image)
{
    this->dx=image.dx;
    this->dy=image.dy;
    this->size=image.size;
    this->data=new T[dx*dy];
    for(int i=0; i<dx*dy; ++i) {
        this->data[i]=image.data[i];
    }

}

    template<class T>
Image<T> &Image<T>::operator=(const Image<T> &image)
{
    if(this!=&image)
    {
        if(this->data!=0) {
            delete[] data;
            data=0;
        }
        this->dx=image.dx;
        this->dy=image.dy;
        this->size=dx*dy;
        this->data=new T[dx*dy];
        for(int i=0; i<this->size; i++) {
            this->data[i]=image.data[i];
        }
    }
    return *this;
}

    template<class T>
Image<T>::~Image()
{
    if(data!=0)
    {
        delete[] data;
    }
}

template<class T>
int Image<T>::getDx() const
{
    return dx;
}

template<class T>
int Image<T>::getDy() const
{
    return dy;
}

template<class T>
int Image<T>::getSize() const
{
    return size;
}

template<class T>
T* Image<T>::getData() const
{
    return data;
}

template<class T>
void Image<T>::print() const
{

    for(int x=0; x<dx; x++) {
        std::cout.width(3);
        std::cout << "----";
    }
    std::cout << "\n";

    for(int y=0; y<dy; y++) {
        for(int x=0; x<dx; x++) {
            std::cout.width(3);
            std::cout << (double)(*this)(x,y) << "|";
        }
        std::cout << "\n";
        for(int x=0; x<dx; x++) {
            std::cout.width(3);
            std::cout << "----";
        }
        std::cout << "\n";
    }
}

    template<class T>
T &Image<T>::operator()(const int &x, const int &y)
{
    return data[y*dx+x];
}

template<class T>
T Image<T>::operator() (const int &x, const int &y) const
{
    return data[y*dx+x];
}
