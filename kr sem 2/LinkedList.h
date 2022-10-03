#pragma once

#include <iostream>
#include <cassert>

using namespace std;

template<typename T>
class LinkedList {
private:
    struct Node {
        T value;
        Node *next;

        Node(T value, Node *next) {
            this->value = value;
            this->next = next;
        };
    };

    int size = 0;
    Node *first;
    Node *last;
public:
    //~LinkedList();

    int getSize();

    void addFirst(T value);

    void add(T value);

    void add(T value, int ind);

    void remove(int ind);

    void set(T value, int ind);

    T get(int ind);

    LinkedList<T> copy();

    void clear();

    void print();

    T *toArray();

    void insertList(LinkedList<T> a, int ind);
};

template<typename T>
int LinkedList<T>::getSize() {
    return size;
}

template<typename T>
void LinkedList<T>::addFirst(T value) {
    if (size > 0) {
        first = new Node(value, first);
    } else {
        first = new Node(value, nullptr);
        last = first;
    }
    size++;
}

template<typename T>
void LinkedList<T>::add(T value) {
    if (size > 0) {
        last->next = new Node(value, nullptr);
        last = last->next;
    } else {
        first = new Node(value, nullptr);
        last = first;
    }
    size++;
}

template<typename T>
void LinkedList<T>::add(T value, int ind) {
    assert(ind <= size && ind > -1);
    if (ind == 0) {
        addFirst(value);
        return;
    }
    if (ind == size) {
        add(value);
        return;
    }
    Node *req = first;
    for (int i = 0; i < ind - 1; i++) {
        req = req->next;
    }
    Node *temp = new Node(value, req->next);
    req->next = temp;
    size++;

}

template<typename T>
void LinkedList<T>::set(T value, int ind) {
    assert(ind < size && ind > -1);
    Node *req = first;
    for (int i = 0; i < ind; i++) {
        req = req->next;
    }
    req->value = value;
}

template<typename T>
T LinkedList<T>::get(int ind) {
    assert(ind < size && ind > -1);
    Node *req = first;
    for (int i = 0; i < ind; i++) {
        req = req->next;
    }
    return req->value;
}

template<typename T>
LinkedList<T> LinkedList<T>::copy() {
    LinkedList<T> b;
    Node *req = first;
    for (int i = 0; i < size; i++) {
        b.add(req->value);
        req = req->next;
    }
    return b;
}

template<typename T>
void LinkedList<T>::clear() {
    while (size > 0) {
        Node *second = first->next;
        delete first;
        first = second;
        size--;
    }
}

template<typename T>
void LinkedList<T>::print() {
    Node *req = first;
    for (int i = 0; i < size; i++) {
        cout << (req->value);
        req = req->next;
    }
}

template<typename T>
T *LinkedList<T>::toArray() {
    T *a = new T[getSize()];
    Node *req = first;
    for (int i = 0; i < size; i++) {
        a[i] = (req->value);
        req = req->next;
    }
    return a;
}

/*
template<typename T>
LinkedList<T>::~LinkedList() {
    clear();
}
*/
template<typename T>
void LinkedList<T>::remove(int ind) {
    //cout << ind << "\n";
    assert(ind < size && ind > -1);
    if (ind == 0) {
        Node *tmp = first;
        first = first->next;
        delete tmp;
    }
    if (ind > 0) {
        Node *req = first;
        for (int i = 0; i < ind - 1; i++) {
            req = req->next;
        }
        if (ind == size - 1) {
            last = req;
            delete req->next;
        } else {
            Node *tmp = req->next;
            req->next = req->next->next;
            delete tmp;
        }
    }
    size--;
}

template<typename T>
void LinkedList<T>::insertList(LinkedList<T> a, int ind) {
    assert(ind <= size && ind > -1);
    LinkedList<T> b = a.copy();
    if (size == 0) {
        first = b.first;
        last = b.last;
        size = b.size;
    } else {
        if (ind == 0) {
            first = b.first;
            b.last->next = first;
        } else if (ind == size) {
            last->next = b.first;
            last = b.last;
        } else {
            Node *req = first;
            for (int i = 0; i < ind - 1; i++) {
                req = req->next;
            }
            b.last->next = req->next;
            req->next = b.first;
        }
        size += b.size;
    }
}