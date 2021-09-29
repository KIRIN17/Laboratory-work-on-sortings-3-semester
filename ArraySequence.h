#include "Sequences.h"
#include "ISorter.h"

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
    DynamicArray<T> data;

};