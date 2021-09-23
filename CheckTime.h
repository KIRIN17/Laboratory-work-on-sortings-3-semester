#pragma once
#include <time.h>
#include <fstream>

template<typename T>
void ARRAY_STRESS_TEST_Merge_Sort_special(bool(*cmp)(const T&,const T&)){
    int size = 10000;
    std::ofstream out;
    out.open("ArrayOnlyMergeSort.txt");
    for (int i = 1; i <= 10; ++i) {

        int current_size = size * i;
        int array[current_size];
        for (int j = 0; j < current_size; ++j) {
            array[j] = rand() % 1000;
        }

        ArraySequence<int> arrSeq(array,current_size);
        unsigned int start_time = clock();
        MergeSort(&arrSeq,cmp);
        unsigned int end_time = clock();
        unsigned int search_time = end_time - start_time;
        out << search_time << ' ';
    }
}
template<typename T>
void ARRAY_STRESS_TEST_Merge_Sort(bool(*cmp)(const T&,const T&)){
    int size = 1000;
    std::ofstream out;
    out.open("ArrayMergeSort.txt");
    for (int i = 1; i <= 10; ++i) {

        int current_size = size * i;
        int array[current_size];
        for (int j = 0; j < current_size; ++j) {
            array[j] = rand() % 1000;
        }

        ArraySequence<int> arrSeq(array,current_size);
        unsigned int start_time = clock();
        MergeSort(&arrSeq,cmp);
        unsigned int end_time = clock();
        unsigned int search_time = end_time - start_time;
        out << search_time << ' ';
    }
}
template<typename T>
void ARRAY_STRESS_TEST_ShellSort(bool(*cmp)(const T&,const T&)){
    int size = 1000;
    std::ofstream out;
    out.open("ArrayShellSort.txt");
    for (int i = 1; i <= 10; ++i) {

        int current_size = size * i;
        int array[current_size];
        for (int j = 0; j < current_size; ++j) {
            array[j] = rand() % 1000;
        }
        ArraySequence<int> arrSeq(array,current_size);
        unsigned int start_time = clock();
        ShellSort(&arrSeq,cmp);
        unsigned int end_time = clock();
        unsigned int search_time = end_time - start_time;
        out << search_time << ' ';
    }
}
template<typename T>
void ARRAY_STRESS_TEST_QuickSort(bool(*cmp)(const T&,const T&),bool(*pred)(const T&,const T&)){
    int size = 1000;
    std::ofstream out;
    out.open("ArrayQuickSort.txt");
    for (int i = 1; i <= 10; ++i) {
        int current_size = size * i;
        int array[current_size];
        for (int j = 0; j < current_size; ++j) {
            array[j] = rand() % 1000;
        }
        ArraySequence<int> arrSeq(array,current_size);

        unsigned int start_time = clock();
        QuickSort(&arrSeq,cmp,pred);
        unsigned int end_time = clock();
        unsigned int search_time = end_time - start_time;

        out << search_time << ' ';
    }
}

//=======================================================================================================//
template<typename T>
void LIST_STRESS_TEST_Merge_Sort_special(bool(*cmp)(const T&,const T&)){
    int size = 10000;
    std::cout << "kek";
    std::ofstream out;
    out.open("ListOnlyMergeSort.txt");
    for (int i = 1; i <= 10; ++i) {
        std::cout << i << std::endl;
        int current_size = size * i;
        int array[current_size];
        for (int j = 0; j < current_size; ++j) {
            array[j] = rand() % 1000;
        }
        LinkedListSequence<int> arrSeq(array,current_size);
        unsigned int start_time = clock();
        MergeSort(&arrSeq,cmp);
        unsigned int end_time = clock();
        unsigned int search_time = end_time - start_time;
        out << search_time << ' ';

    }
}
template<typename T>
void LIST_STRESS_TEST_Merge_Sort(bool(*cmp)(const T&,const T&)){
    int size = 1000;
    std::ofstream out;
    out.open("ListMergeSort.txt");
    for (int i = 1; i <= 10; ++i) {

        int current_size = size * i;
        int array[current_size];
        for (int j = 0; j < current_size; ++j) {
            array[j] = rand() % 1000;
        }

        LinkedListSequence<int> arrSeq(array,current_size);
        unsigned int start_time = clock();
        MergeSort(&arrSeq,cmp);
        unsigned int end_time = clock();
        unsigned int search_time = end_time - start_time;
        out << search_time << ' ';
    }
}
template<typename T>
void LIST_STRESS_TEST_ShellSort(bool(*cmp)(const T&,const T&)){
    int size = 1000;
    std::ofstream out;
    out.open("ListShellSort.txt");
    for (int i = 1; i <= 10; ++i) {

        int current_size = size * i;
        int array[current_size];
        for (int j = 0; j < current_size; ++j) {
            array[j] = rand() % 1000;
        }
        LinkedListSequence<int> arrSeq(array,current_size);
        unsigned int start_time = clock();
        ShellSort(&arrSeq,cmp);
        unsigned int end_time = clock();
        unsigned int search_time = end_time - start_time;
        out << search_time << ' ';
    }
}
template<typename T>
void LIST_STRESS_TEST_QuickSort(bool(*cmp)(const T&,const T&),bool(*pred)(const T&,const T&)){
    int size = 1000;
    std::ofstream out;
    out.open("ListQuickSort.txt");
    for (int i = 1; i <= 10; ++i) {
        int current_size = size * i;
        int array[current_size];
        for (int j = 0; j < current_size; ++j) {
            array[j] = rand() % 1000;
        }
        LinkedListSequence<int> arrSeq(array,current_size);

        unsigned int start_time = clock();
        QuickSort(&arrSeq,cmp,pred);
        unsigned int end_time = clock();
        unsigned int search_time = end_time - start_time;

        out << search_time << ' ';
    }
}