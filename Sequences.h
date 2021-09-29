#pragma once
#include "DynamicArray.h"
#include "LinkedList.h"

template<typename T>
class Sequence {
public:
    virtual Sequence<T> *CreateSequence(Iterator<T> *begin, Iterator<T> *end) = 0;

    virtual Sequence<T> *GetSubsequence(int startIndex, int endIndex) = 0;

    virtual Sequence<T> *Concat(Sequence<T> *list) = 0;

    virtual void MergeSort(bool(*cmp)(const T&,const T&)) = 0;

    virtual void ShellSort(bool(*cmp)(const T&,const T&)) = 0;

    virtual void QuickSort(bool(*cmp)(const T&,const T&),bool(*pred)(const T&,const T&)) = 0;

    virtual Sequence<T> *Clone() = 0;

    virtual T& GetFirst() = 0;

    virtual T& GetLast() = 0;

    virtual T& Get(int index) = 0;

    virtual TemplateElem<T>* Get_Elem(int index) = 0;

    virtual int GetLength() = 0;

    virtual void Append(T item) = 0;

    virtual void Prepend(T item) = 0;

    virtual void InsertAt(T item, int index) = 0;

    virtual void Swap(int i,int j) = 0;
    virtual Iterator<T> *Begin() = 0;

    virtual Iterator<T> *End() = 0;

    virtual void Print() = 0;
};

