 
#include "SmartPointer.h"
#include <iostream>
using namespace std;

template<typename T>
SP<T>::SP():pData(0), reference(0)
{
    //Create a new reference counter
    reference = new RC();
    //Increment the reference counter
    reference -> AddRef();
}
template<typename T>
SP<T>::SP(const T &pValue)
{
    reference = new RC();
    pData = new T(pValue);
    reference -> AddRef();
}
template<typename T>
SP<T>::SP(T* pValue) : pData(pValue), reference(0)
{
    //Create a new reference counter
    reference = new RC();
    //Increment reference counter
    reference->AddRef();
}

template<typename T>
SP<T>::SP(const SP<T> & sp) : pData(sp.pData), reference(sp.reference)
{
    //Copy constructor, copies data and reference pointer
    //Increment ref counter
    reference->AddRef();
}

template<typename T>
SP<T>::~SP()
{
    cout<<"Destroyed pointer with ref nr : "<< (reference->getCount()) <<endl;
    if(reference->Release() == 0)
    {
        delete pData;
        delete reference;
    }
}