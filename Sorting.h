#pragma once
#include "Sequences.h"
template<typename T>
bool cmp_(const T& a,const T& b){
    return a <= b;
}
template<typename T>
bool cmp(const T& a,const T& b){
    return a < b;
}
template<typename T>
bool pred(const T& a,const T& b){
    return a > b;
}

template<typename T>
void ShellSort(Sequence<T>* seq,bool(*cmp)(const T&,const T&)){
    int size = seq->GetLength();
    int gap = size / 2;

    while (gap > 0){
        for (int i = gap; i < size; ++i) {
            TemplateElem<T>* current = seq->Get_Elem(i);
            T current_value = **current;//seq->Get(i);
            int position = i;
            current = current->Move_Prev(gap);
            while (position >= gap && !cmp(**current , current_value)){//по сути seq->Get(position - gap) - значит отступить от прошлого узла на gap
                seq->Swap(position,position - gap);
                //seq->Get(position) = seq->Get(position - gap);
                position -= gap;
                current = current->Move_Prev(gap);
                //seq->Get(position) = current_value;
            }
        }
        gap /= 2;
    }

}
template <typename T>
Iterator<T>* Copy(Iterator<T>* begin,Iterator<T>* end,Iterator<T>* first_in_new){
    while(*begin != *end){
        **first_in_new = **begin;//присваивание и инкремент
        ++*first_in_new;
        ++*begin;
    }
    return first_in_new;
}

template <typename T>
Iterator<T>* Merge(Iterator<T>* begin1,Iterator<T>* end1,Iterator<T>* begin2,Iterator<T>* end2,Iterator<T>* first_in_new,bool(*cmp)(const T&,const T&)){
    for(;*begin1 != *end1;){
        if(*begin2 == *end2)
            return Copy(begin1,end1,first_in_new);
        if(cmp(**begin1 , **begin2)){
            **first_in_new = **begin1;
            ++*begin1;
        }else{
            **first_in_new = **begin2;
            ++*begin2;
        }
        ++*first_in_new;
    }
    return Copy(begin2,end2,first_in_new);

}
template<typename T>
Sequence<T>* SEQ_MALLOC(Sequence<T>* tmp){
    return tmp->Clone();
}
template<typename T>
Iterator<T>* ITER_MALLOC(Iterator<T>* tmp){
    return tmp->Clone();
}
template<typename T>
void MergeSort(Sequence<T>* a,bool(*cmp)(const T&,const T&)){

    if(*a->End() - *a->Begin() < 2)
        return;

    Sequence<T>* elements = SEQ_MALLOC(a);
    elements = elements->CreateSequence(a->Begin(),a->End());

    Sequence<T>* elements1 = SEQ_MALLOC(a);
    elements1 = elements1->CreateSequence(elements->Begin(),*elements->Begin() + elements->GetLength()/2);

    Sequence<T>* elements2 = SEQ_MALLOC(a);
    elements2 = elements2->CreateSequence(*elements->Begin() + elements->GetLength()/2,elements->End());

    MergeSort(elements1,cmp);
    MergeSort(elements2,cmp);


    Merge(elements1->Begin(),elements1->End(),elements2->Begin(),elements2->End(),a->Begin(),cmp);


}


template <typename T>
void QuickSort(Sequence<T>* seq,bool(*cmp)(const T&,const T&),bool(*pred)(const T&,const T&)){
    int i = 0, j = 0;
    int left = 0, right = 0;

    LinkedList<int> stack;
    stack.Append(left);
    stack.Append(seq->GetLength() - 1);

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
        tmp_i = seq->Get_Elem(i);
        tmp_j = seq->Get_Elem(j);


        T pivot_value = seq->Get(pivot);
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
