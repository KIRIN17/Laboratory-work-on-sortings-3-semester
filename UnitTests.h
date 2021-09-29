#pragma once
#include <sstream>
#include <exception>
#include <iostream>
#include "ArraySequence.h"
#include "LinkedListSequence.h"
#include "FunctionForSorting.h"

template<class T, class U>
void AssertEqual(const T& t, const U& u,
                 const std::string& hint)
{
    if (t != u) {
        std::ostringstream os;
        os << "Assertion failed: " << t << " != " << u
           << " hint: " << hint;
        throw std::runtime_error(os.str());
    }
}

inline void Assert(bool b, const std::string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const std::string& test_name) {
        try {
            func();
            std::cerr << test_name << " OK" << std::endl;
        } catch (std::runtime_error& e) {
            ++fail_count;
            std::cerr << test_name << " fail: " << e.what() << std::endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            std::cerr << fail_count << " unit tests failed. Terminate" << std::endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

template<typename T>
bool IsSorted(Iterator<T>* begin,Iterator<T>* end,bool(*cmp)(const T&,const T&)){
    for(auto i = begin;*i != *(*end - 1);++*i){
        if(!cmp(**i,**(*i + 1)))
            return false;
    }
    return true;
}

void TestMergeSort(){
    {
        int data[5] = {1, -1, 100, 40, 14};
        LinkedListSequence<int> a(data, 5);
        a.MergeSort(cmp);
        Assert(IsSorted(a.Begin(), a.End(), cmp), "");
    }
    {
        int data[5] = {1, -1, 100, 40, 14};
        ArraySequence<int> b(data,5);
        b.MergeSort(cmp);
        Assert(IsSorted(b.Begin(),b.End(),cmp),"");
    }
}

void TestShellSort(){
    {
        int data[5] = {1, -1, 100, 40, 14};
        LinkedListSequence<int> a(data, 5);
        a.ShellSort(cmp);
        Assert(IsSorted(a.Begin(), a.End(), cmp), "");
    }
    {
        int data[5] = {1, -1, 100, 40, 14};
        ArraySequence<int> b(data,5);
        b.ShellSort(cmp);
        Assert(IsSorted(b.Begin(),b.End(),cmp),"");
    }
}

void TestQuickSort(){
    {
        int data[5] = {1, -1, 100, 40, 14};
        LinkedListSequence<int> a(data, 5);
        a.QuickSort(cmp,pred);
        Assert(IsSorted(a.Begin(), a.End(), cmp), "");
    }
    {
        int data[5] = {1, -1, 100, 40, 14};
        ArraySequence<int> b(data,5);
        b.QuickSort(cmp,pred);
        Assert(IsSorted(b.Begin(),b.End(),cmp),"");
    }
}