
#ifndef CIRCLE_LIST_H
#define CIRCLE_LIST_H

#include <iostream>
using namespace std;

template <class T> class CircleList;

template <class T>
class CircleListElem {
private:
    T data;
    CircleListElem* next;
    CircleListElem* prev;
public:
    CircleListElem(const T& adata, CircleListElem* anext = NULL, CircleListElem* aprev = NULL);
    const T& getData() const;
    CircleListElem* getNext();
    CircleListElem* getPrev();
    template <class U> friend class CircleList;
};

template <class T>
class CircleList {
private:
    CircleListElem<T>* current;
    int count;
    CircleList(const CircleList& list);
    CircleList& operator=(const CircleList& list);
public:
    CircleList();
    ~CircleList();
    CircleListElem<T>* getCurrent();
    int getCount() const;
    bool isEmpty() const;
    void insertFirst(const T& data);
    void moveToNext();
    T removeCurrent();
    void clear();
};

template <class T>
CircleListElem<T>::CircleListElem(const T& adata, CircleListElem<T>* anext, CircleListElem<T>* aprev)
    : data(adata), next(anext), prev(aprev) {}

template <class T>
const T& CircleListElem<T>::getData() const {
    return data;
}

template <class T>
CircleListElem<T>* CircleListElem<T>::getNext() {
    return next;
}

template <class T>
CircleListElem<T>* CircleListElem<T>::getPrev() {
    return prev;
}

template <class T>
CircleList<T>::CircleList() : current(NULL), count(0) {}

template <class T>
CircleList<T>::~CircleList() {
    clear();
}

template <class T>
CircleListElem<T>* CircleList<T>::getCurrent() {
    return current;
}

template <class T>
int CircleList<T>::getCount() const {
    return count;
}

template <class T>
bool CircleList<T>::isEmpty() const {
    return count == 0;
}

template <class T>
void CircleList<T>::insertFirst(const T& data) {
    CircleListElem<T>* newElem = new CircleListElem<T>(data);
    if (isEmpty()) {
        current = newElem;
        newElem->next = newElem;
        newElem->prev = newElem;
    } else {
        CircleListElem<T>* last = current->prev;
        newElem->next = current;
        newElem->prev = last;
        current->prev = newElem;
        last->next = newElem;
        current = newElem;
    }
    count++;
}

template <class T>
void CircleList<T>::moveToNext() {
    if (!isEmpty()) {
        current = current->next;
    }
}

template <class T>
T CircleList<T>::removeCurrent() {
    T result = current->data;
    CircleListElem<T>* toDelete = current;
    if (count == 1) {
        current = NULL;
    } else {
        CircleListElem<T>* nextElem = current->next;
        CircleListElem<T>* prevElem = current->prev;
        prevElem->next = nextElem;
        nextElem->prev = prevElem;
        current = nextElem;
    }
    delete toDelete;
    count--;
    return result;
}

template <class T>
void CircleList<T>::clear() {
    while (!isEmpty()) {
        removeCurrent();
    }
}

#endif
