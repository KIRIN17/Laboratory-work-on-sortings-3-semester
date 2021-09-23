#pragma once

#include "DynamicArray.h"
#include "LinkedList.h"

template<typename T>
class Sequence {
public:
    virtual Sequence<T> *CreateSequence(Iterator<T> *begin, Iterator<T> *end) = 0;

    virtual Sequence<T> *GetSubsequence(int startIndex, int endIndex) = 0;

    virtual Sequence<T> *Concat(Sequence<T> *list) = 0;

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

template<typename T>
class ArraySequence : public Sequence<T> {
public:
    void Swap(int i,int j) override{
        data.Swap(i,j);
    }
    ArraySequence<T> *Clone() override { return new ArraySequence<T>(); }

    ArraySequence<T> *CreateSequence(Iterator<T> *begin, Iterator<T> *end) override {
        return new ArraySequence<T>(begin, end);
    }

    Cell<T>* Get_Elem(int index) override{//работает
        return data.Get_Elem(index);
    }

    ArrayIt<T> *Begin() override {
        return data.Begin();
    }

    ArrayIt<T> *End() override {
        return data.End();
    }

    ArraySequence() : data() {}

    ArraySequence(Iterator<T> *begin, Iterator<T> *end) : data(begin, end) {}

    ArraySequence(T *item, int count) : data(item, count) {}

    ArraySequence(ArraySequence<T> &array) : data(array.data) {}

    ArraySequence(LinkedList<T> &list) {//копиконструктор для параметра LinkedList
        T *items;
        items = (T *) malloc(sizeof(T) * (list.GetLength()));
        for (int i = 0; i < list.GetLength(); ++i) {
            items[i] = list.Get(i);
        }
        data = DynamicArray<T>(items, list.GetLength());
    }

    int GetLength() {
        return data.GetSize();
    }

    T& Get(int index) {
        return data.Get(index);
    }

    T& GetFirst() {
        return data.Get(0);
    }

    T& GetLast() {
        return data.Get(data.GetSize() - 1);
    }

    void Append(T item) {
        data.Append(item);
    }

    void Prepend(T item) {
        data.Prepend(item);
    }

    void InsertAt(T item, int index) {//void Set(int index,T value)
        if (index >= data.GetSize() || index < 0)
            throw "\nInsertAt Message : Index Out Of Range";
        data.Resize(data.GetSize() + 1);
        for (int i = data.GetSize() - 2; i >= index; --i) {
            data.Set(i + 1, data.Get(i));
        }
        data.Set(index, item);
    }

    void Print() {
        data.Print();
    }

    ArraySequence<T> *GetSubsequence(int startIndex, int endIndex) {
        T *items = (T *) malloc(sizeof(T) * (endIndex - startIndex));
        for (int i = startIndex; i < endIndex; ++i) {
            items[i - startIndex] = data.Get(i);
        }
        ArraySequence<T> *result = new ArraySequence<T>(items, endIndex - startIndex);
        return result;
    }

    ArraySequence<T> *Concat(Sequence<T> *list) {
        if (list->GetLength() != 0) {
            T *items = (T *) malloc(sizeof(T) * (data.GetSize() + list->GetLength()));
            for (int i = 0; i < data.GetSize(); ++i) {
                items[i] = data.Get(i);
            }
            for (int i = 0; i < list->GetLength(); ++i) {
                items[i + data.GetSize()] = list->Get(i);
            }
            ArraySequence<T> *result = new ArraySequence<T>(items, data.GetSize() + list->GetLength());

            return result;
        } else {
            ArraySequence<T> *result = new ArraySequence<T>(*this);
            return result;
        }

    }

private:
    DynamicArray<T> data;

};

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

private:
    LinkedList<T> data;
};
