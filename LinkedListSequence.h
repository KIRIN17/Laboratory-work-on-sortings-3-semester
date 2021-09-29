#pragma once
#include "Sequences.h"

template<typename T>
class LinkedListSequence : public Sequence<T> {
public:
    LinkedListSequence<T> *Clone() override { return new LinkedListSequence<T>(); }

    LinkedListSequence<T> *CreateSequence(Iterator<T> *begin, Iterator<T> *end) override {
        return new LinkedListSequence<T>(begin, end);
    }

    Node<T>* Get_Elem(int index) override{
        return data.Get_Elem(index);
    }


    ListIt<T> *Begin() override {
        return data.Begin();
    }

    ListIt<T> *End() override {
        return data.End();
    }
    void Swap(int i,int j) override{
        data.Swap(i,j);
    }
    LinkedListSequence() : data(){}

    LinkedListSequence(Iterator<T> *begin, Iterator<T> *end) : data(begin,end){}

    LinkedListSequence(T *items, int count) : data(items,count){}

    LinkedListSequence(int count) : data(count){}

    //переопределение не охватывает соответствующую функцию из LinkedList,
    // так как требуется общность первого параметра,вследствие чего нет возможности получить данные
    LinkedListSequence<T> *Concat(Sequence<T> *list) {
        for (int i = 0; i < list->GetLength(); ++i) {//добавляю в data все элементы из list,её Size увеличивается
            data.Append(list->Get(i));
        }
        T *items;
        items = (T *) malloc(sizeof(T *) * (data.GetLength() + list->GetLength()));
        for (int i = 0; i < data.GetLength(); ++i) {//записываю все элементы из data  в массив
            items[i] = data.Get(i);
        }

        LinkedListSequence<T> *result = new LinkedListSequence<T>(items, data.GetLength());//создание нового экземпляра
        return result;
    }

    LinkedListSequence(const LinkedList<T> &list) {//конструктор по объекту
        LinkedList<T> *tmp = new LinkedList<T>(list);
        std::cout << "Constructor by object . . .\n";
        data = *tmp;
    }

    LinkedListSequence<T> *GetSubsequence(int startIndex, int endIndex) {//вернуть Sequence<T>*
        LinkedList<T> *tmp = data.GetSubLinkedList(startIndex, endIndex);//создаем экземляр с указанными индексами
        T *items;
        items = (T *) malloc(sizeof(T *) * (endIndex - startIndex));
        for (int i = 0; i < endIndex - startIndex; ++i) {
            items[i] = tmp->Get(i);
        }

        LinkedListSequence<T> *result = new LinkedListSequence<T>(items, endIndex - startIndex);

        return result;
    }

    int GetLength() {
        return data.GetLength();
    }

    T& GetFirst() {
        return data.GetFirst();
    }

    T& GetLast() {
        return data.GetLast();
    }


    T& Get(int index) {
        return data.Get(index);
    }

    void Append(T item) {
        data.Append(item);
    }

    void Prepend(T item) {
        data.Prepend(item);
    }

    void InsertAt(T item, int index) {
        data.InsertAt(item, index);
    }

    void removeAt(int index) {
        data.removeAt(index);
    }

    void Print() {
        data.print_from_begin();
    }

    void ShellSort(bool(*cmp)(const T&,const T&)) override{
        IShellSort<T> obj;
        obj.Sort(this,cmp);
    }
    void MergeSort(bool(*cmp)(const T&,const T&)) override{
        IMergeSort<T> obj;
        obj.Sort(this,cmp);
    }
    void QuickSort(bool(*cmp)(const T&,const T&),bool(*pred)(const T&,const T&)) override{
        IMergeSort<T> obj;
        obj.Sort(this,cmp,pred);
    }
private:
    LinkedList<T> data;
};
