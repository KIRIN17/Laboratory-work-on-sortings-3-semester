#pragma once
#include "FunctionForSorting.h"

template<typename T>
class ISorter{
public:
    virtual void Sort(Sequence<T>* sequence,bool(*cmp)(const T&,const T&),bool(*pred)(const T&,const T&)) = 0;
};

template<typename T>
class IMergeSort : public ISorter<T>{
public:
    void Sort(Sequence<T>* sequence,bool(*cmp)(const T&,const T&),bool(*pred)(const T&,const T&) = nullptr) override{

        if(*sequence->End() - *sequence->Begin() < 2)
            return;

        Sequence<T>* elements = SEQ_MALLOC(sequence);
        elements = elements->CreateSequence(sequence->Begin(),sequence->End());

        Sequence<T>* elements1 = SEQ_MALLOC(sequence);
        elements1 = elements1->CreateSequence(elements->Begin(),*elements->Begin() + elements->GetLength()/2);

        Sequence<T>* elements2 = SEQ_MALLOC(sequence);
        elements2 = elements2->CreateSequence(*elements->Begin() + elements->GetLength()/2,elements->End());



        MergeSort(elements1,cmp);
        MergeSort(elements2,cmp);

        Merge(elements1->Begin(),elements1->End(),elements2->Begin(),elements2->End(),sequence->Begin(),cmp);
    }
};

template<typename T>
class IShellSort : public ISorter<T>{
public:
    void Sort(Sequence<T>* sequence,bool(*cmp)(const T&,const T&),bool(*pred)(const T&,const T&) = nullptr) override{
        int size = sequence->GetLength();
        int gap = size / 2;

        while (gap > 0){
            for (int i = gap; i < size; ++i) {
                TemplateElem<T>* current = sequence->Get_Elem(i);
                T current_value = **current;//seq->Get(i);
                int position = i;
                current = current->Move_Prev(gap);
                while (position >= gap && !cmp(**current , current_value)){
                    sequence->Swap(position,position - gap);
                    position -= gap;
                    current = current->Move_Prev(gap);
                }
            }
            gap /= 2;
        }
    }
};

template<typename T>
class IQuickSort : public ISorter<T>{
public:
    void Sort(Sequence<T>* sequence,bool(*cmp)(const T&,const T&),bool(*pred)(const T&,const T&)){
        int i = 0, j = 0;
        int left = 0, right = 0;

        LinkedList<int> stack;
        stack.Append(left);
        stack.Append(sequence->GetLength() - 1);

        TemplateElem<T>* tmp_i;
        TemplateElem<T>* tmp_j;

        do{
            right = stack.GetLast();
            stack.pop_back();
            left = stack.GetLast();
            stack.pop_back();

            i = left;
            j = right;

            int pivot = (left + right) / 2;
            tmp_i = sequence->Get_Elem(i);
            tmp_j = sequence->Get_Elem(j);


            T pivot_value = sequence->Get(pivot);
            do {

                while(cmp(**tmp_i , pivot_value)){
                    ++i;
                    tmp_i = ++*tmp_i;
                }
                while(pred(**tmp_j , pivot_value)){
                    --j;
                    tmp_j = --*tmp_j;
                }
                if(i <= j){
                    T tmp = **tmp_i;
                    **tmp_i = **tmp_j;
                    **tmp_j = tmp;

                    tmp_i = ++*tmp_i;
                    tmp_j = --*tmp_j;

                    ++i;
                    --j;
                }
            }while(i <= j);

            if (i < right){
                stack.Append(i);
                stack.Append(right);
            }
            if (left < j){
                stack.Append(left);
                stack.Append(j);
            }
        } while (stack.GetLength());
    }
};