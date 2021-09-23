#include <iostream>
#include "UnitTests.h"
#include "CheckTime.h"
template<typename InputIt>
void Print(InputIt* begin,InputIt* end){
    for(auto i = begin;*i!=*end;++*i){
        std::cout << **i << ' ';
    }
    std::cout <<std::endl;
}


void TestAll(){
    TestRunner tr;
    tr.RunTest(TestMergeSort,"Test MergeSort");
    tr.RunTest(TestShellSort,"Test ShellSort");
    tr.RunTest(TestQuickSort,"Test QuickSort");
}

int main() {
    TestAll();
    std::cout << "Start stress - tests ? (y/n)" << std::endl;
    char answer;
    std::cin >> answer;
    if (answer == 'y') {
        std::cout << "ArraySequence - 1, LinkedListSequence - 2" << std::endl;
        std::cin >> answer;
        if (answer == '1') {
            ARRAY_STRESS_TEST_Merge_Sort(cmp<int>);
            ARRAY_STRESS_TEST_ShellSort(cmp<int>);
            ARRAY_STRESS_TEST_QuickSort(cmp<int>, pred<int>);
        }
        if (answer == '2') {
            LIST_STRESS_TEST_Merge_Sort(cmp<int>);
            LIST_STRESS_TEST_ShellSort(cmp<int>);
            LIST_STRESS_TEST_QuickSort(cmp<int>, pred<int>);
        }
    }
    std::cout << "Start special - tests ? (y/n)" << std::endl;
    std::cin >> answer;
    if (answer == 'y') {
        ARRAY_STRESS_TEST_Merge_Sort_special(cmp<int>);
        LIST_STRESS_TEST_Merge_Sort_special(cmp<int>);
    } else {
        std::cout << "Want to enter a sequence to sort it ?(y/n)" << std::endl;
        std::cin >> answer;
        if (answer == 'y') {
            std::cout << "Enter the number of elements in the sequence :" << std::endl;
            int N;
            std::cin >> N;
            int tmp[N];
            std::cout << "Generate a random sequence ? (y/n)" << std::endl;
            std::cin >> answer;
            if (answer == 'y') {
                for (int i = 0; i < N; ++i) {
                    tmp[i] = rand() % 1000;
                }
            } else {
                std::cout << "Enter " << N << " sequence items :" << std::endl;
                for (int i = 0; i < N; ++i) {
                    int value;
                    std::cin >> value;
                    tmp[i] = value;
                }
            }
            std::cout << "Select the type of sequence:\n"
                         "1 - dynamic array\n"
                         "2 - linked list" << std::endl;
            std::cin >> answer;
            Sequence<int> *seq;
            if (answer == '1')
                seq = new ArraySequence<int>(tmp, N);
            if (answer == '2')
                seq = new LinkedListSequence<int>(tmp, N);
            std::cout << "Your sequence : ";
            Print(seq->Begin(), seq->End());
            std::cout << "Select sorting type :\n"
                         "1 - merge sort\n"
                         "2 - Shell sort\n"
                         "3 - quick sort" << std::endl;
            std::cin >> answer;
            if (answer == '1')
                MergeSort(seq, cmp);
            if (answer == '2')
                ShellSort(seq, cmp);
            if (answer == '3')
                QuickSort(seq, cmp, pred);
            std::cout << "Your sorted sequence : ";
            Print(seq->Begin(), seq->End());

        }
    }


    return 0;
}
