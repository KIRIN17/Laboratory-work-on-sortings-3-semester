#pragma once

#include "TemplateElem.h"

template<typename T>
class Iterator {
public:
    virtual T &operator*() = 0;

    virtual Iterator<T> *operator++() = 0;

    virtual Iterator<T> *operator--() = 0;

    virtual Iterator<T> *Clone() = 0;

    virtual Iterator<T> *get_next() = 0;

    virtual Iterator<T> *get_prev() = 0;

    virtual int get_number() const = 0;
};

template<typename T>
class ListIt : public Iterator<T> {
public:
    ListIt() { ptr_ = nullptr; };

    ListIt<T> *Clone() override { return new ListIt<T>(); }

    ListIt(Node<T> *ptr, int number) : ptr_(ptr), number_(number) {};

    T &operator*() override {
        return **ptr_;
    }

    ListIt<T> *operator++() override {
        ptr_ = ptr_->pNext;
        return new ListIt<T>(ptr_, ++number_);
    }

    ListIt<T> *operator--() override {
        ptr_ = ptr_->pPrev;
        return new ListIt<T>(ptr_, --number_);
    }

    ListIt<T> *get_next() override {
        return new ListIt<T>(ptr_->pNext, number_ + 1);
    }

    ListIt<T> *get_prev() override {
        return new ListIt<T>(ptr_->pPrev, number_ - 1);
    }

    int get_number() const override {
        return number_;
    }

private:
    int number_;
    Node<T> *ptr_;

};


template<typename T>
class ArrayIt : public Iterator<T> {
public:
    ArrayIt() { ptr_ = nullptr; }

    ArrayIt<T> *Clone() override { return new ArrayIt<T>(); }

    ArrayIt(T *ptr, int number) : ptr_(ptr), number_(number) {};

    T &operator*() override {
        return *ptr_;
    }

    ArrayIt<T> *operator++() override {
        return new ArrayIt<T>(++ptr_, ++number_);
    };

    ArrayIt<T> *operator--() override {
        return new ArrayIt<T>(--ptr_, --number_);
    };

    ArrayIt<T> *get_next() override {
        return new ArrayIt<T>(ptr_ + 1, number_ + 1);
    }

    ArrayIt<T> *get_prev() override {
        return new ArrayIt<T>(ptr_ - 1, number_ - 1);
    }

    int get_number() const override {
        return number_;
    }

private:
    T *ptr_;
    int number_;
};

//============================================================================================================//
template<typename T>
bool operator!=(const Iterator<T> &lhs, const Iterator<T> &rhs) {
    return lhs.get_number() != rhs.get_number();
}

template<typename T>
bool operator==(const Iterator<T> &lhs, const Iterator<T> &rhs) {
    return lhs.get_number() == rhs.get_number();
}

template<typename T>
int operator-(const Iterator<T> &lhs, const Iterator<T> &rhs) {
    return lhs.get_number() - rhs.get_number();
}

template<typename T>
Iterator<T> *operator+(Iterator<T> &lhs, int rhs) {
    if (rhs == 0)
        return &lhs;
    Iterator<T> *tmp = lhs.get_next();
    for (int i = 0; i < rhs - 1; ++i) {
        tmp = tmp->get_next();
    }
    return tmp;
}

template<typename T>
Iterator<T> *operator-(Iterator<T> &lhs, int rhs) {
    if (rhs == 0)
        return &lhs;
    Iterator<T> *tmp = lhs.get_prev();
    for (int i = 0; i < rhs - 1; ++i) {
        tmp = tmp->get_prev();
    }
    return tmp;
}
//============================================================================================================//