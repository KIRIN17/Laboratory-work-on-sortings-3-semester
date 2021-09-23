#pragma once
#include <tuple>

template<typename T>
class TemplateElem{
public:
    virtual T& operator *() = 0;

    virtual TemplateElem<T>* operator ++() = 0;

    virtual TemplateElem<T>* operator --() = 0;

    virtual TemplateElem<T>* Move_Prev(int count) = 0;
};

template<typename T>
class Cell : public TemplateElem<T>{
public:
    Cell(){ptr_ = nullptr;}
    Cell(T* ptr) : ptr_(ptr){}

    T* ptr_;
    Cell<T>* operator ++() override{
        ++ptr_;
        return this;
    }
    Cell<T>* operator --() override{
        --ptr_;
        return this;
    }
    T& operator *() override{
        return *ptr_;
    }

    Cell<T>* Move_Prev(int count) override{
        for (int i = 0; i < count; ++i) {
            --ptr_;
        }
        return this;
    }
};
template<typename T>
class Node : public TemplateElem<T>{
public:

    Node* pNext;
    Node* pPrev;

    T data;
    int number;

    Node(T data = T(),Node* pPrev = nullptr,Node* pNext = nullptr,int number = 0){
        this->data = data;
        this->pPrev = pPrev;
        this->pNext = pNext;
        this->number = number;
    }
    Node<T>* Move_Prev(int count) override{
        Node<T>* curr = pPrev;
        for (int i = 0; i < count - 1; ++i) {
            if(curr)
                curr = curr->pPrev;
            else
                break;
        }
        return curr;
    }
    Node<T>* operator ++() override{
        return pNext;
    }
    Node<T>* operator --() override{
        return pPrev;
    }

    T& operator *() override{
        return data;
    }
};

template<typename T>
bool operator != (Node<T>& lhs,Node<T>& rhs){
    return std::make_tuple(lhs.pNext,lhs.pPrev,lhs.data) != std::make_tuple(nullptr, nullptr,0);
}

template<typename T>
std::ostream& operator << (std::ostream& output, const Node<T>& node){
    return output << node.data;
}

template<typename T>
bool operator <=(Node<T>& lhs,Node<T>& rhs){
    return lhs.data <= rhs.data;
}
