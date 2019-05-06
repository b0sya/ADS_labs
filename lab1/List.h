//
//  Header.h
//  template class list
//
//  Created by b0ysa on 19/02/2019.
//  Copyright © 2019 b0ysa. All rights reserved.
//

#ifndef List_h
#define List_h
#include <stdexcept>
#include <iostream>

using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node *next;
    Node(T data = T(), Node *next = nullptr) {
        this->data = data;
        this->next = next;
    }
};

template <typename T>
class List {
private:
    size_t size = 0;
    Node< T > *head;
public:

    List();

    ~List();

    void push_back(T data);

    void push_front(T data);

    void pop_back();

    void pop_front();

    void insert(T data, size_t index);

    T at (size_t index);

    void remove(size_t index);

    void clear();

    void set (T data, size_t index);

    int getSize() { return size;}

    T getHeadData() { return head->data;}

    bool isEmpty();

    template <typename T1> friend ostream& operator<< (ostream &out, List<T1> list);



};

template <typename T>
List< T > :: List() {
    size = 0;
    head = nullptr;
}

template <typename T>
void List< T > :: push_back(T data) {
    if (head) {
        Node< T > *current = this -> head;
        while (current -> next) {
            current = current -> next;
        }
        current -> next = new Node< T >(data);
    } else {
        head = new Node< T >(data);
    }
    size++;
}

template <typename T>
void List< T > :: push_front(T data) {
    head = new Node< T >(data, head);
    size++;
}

template <typename T>
void List< T > :: pop_back(){
    remove(size - 1);
}

template <typename T>
void List< T > :: pop_front() {
    Node< T > *buffer = this->head;
    if (head != NULL){
        head = head -> next;
    }
    delete buffer;
    size--;
}

template <typename T>
bool List< T > :: isEmpty() {
    return size!= 0 ? false : true;
}

template <typename T>
void List< T > :: clear() {
    while (size) {
        pop_front();
    }
}

template <typename T>
List< T > :: ~List() {
    clear();
}

template <typename T>
void List< T > :: insert(T data, size_t index){

    if (index > size)
        throw out_of_range ("The index is greater then list size");

    if (!index) {
        push_front(data);
    }else{
        Node< T > *prev = this->head;

        for (int i = 0; i <index - 1; i++){
            prev = prev -> next;
        }
        Node< T > *newNode = new Node< T > (data, prev -> next);
        prev -> next = newNode;
        size++;
    }

}

template <typename T>
void List< T > :: remove(size_t index){
    if (index > size)
        throw out_of_range ("The index is greater then list size");

    if (!index) {
        pop_front();
    }else{
        Node< T > *prev = this->head;

        for (int i = 0; i <index - 1; i++){
            prev = prev -> next;
        }
        Node< T > *buffer = prev -> next;
        prev -> next = buffer -> next;
        delete buffer;
        size--;
    }
}

template <typename T>
void List< T > :: set(T data, size_t index){

    if (index > size)
        throw out_of_range ("The index is greater then list size");

    Node< T > *prev = this->head;
    for (int i = 0; i <index; i++){
        prev = prev -> next;
    }
    prev ->data = data;

}

template <typename T>
T List< T > :: at(size_t index) {

    if (index > size)
        throw out_of_range ("The index is greater then list size");

    Node< T > *search = this -> head;
    int current = 0;

    while (search != nullptr) {
        if (current == index)
            return search -> data;
        search = search -> next;
        current++;
    }
    return 0;
}

template<class T> ostream &operator<<(ostream &out, List<T> list){
    for (int i = 0; i < list.getSize(); i++){
        cout << i << " element is [" << list.at(i) << "]" << endl;
    }
    return out;
}

#endif /* List_h */
