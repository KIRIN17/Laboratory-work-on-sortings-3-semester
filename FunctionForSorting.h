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
