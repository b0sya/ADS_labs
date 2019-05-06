//
// Created by b0ysa on 04/03/2019.
//

#ifndef LAB2_MAP_H
#define LAB2_MAP_H
#include "List.h"
#include <stdexcept>
#include <iostream>

using namespace std;

template <typename T, typename T1>
class NodeForMap {
public:
    T key;
    T1 data;
    NodeForMap *left;
    NodeForMap *right;
    NodeForMap *parent;
    bool color;//black - false; red - true
    NodeForMap(T key, T1 data) {
        this->key = key;
        this->data = data;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        color = true;
    }
    ~NodeForMap();
};

template<typename T, typename T1>
NodeForMap<T, T1>::~NodeForMap() {
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

template <typename T, typename T1>
class Map {
private:
    NodeForMap< T, T1 > *root;
    void rightRotation(NodeForMap< T, T1 > *elemX);

    void leftRotation(NodeForMap< T, T1 > *elemX);

    void fixInsert (NodeForMap< T, T1 > *current);

    void fixDeleting(NodeForMap<T, T1> *son);
public:

    Map();

    ~Map();

    void insert (T key, T1 data);

    void addForData(T key, T num);

    void deleteNode(T key);

    void show();

    void clear();

    void showTable();

    NodeForMap< T, T1 >* get_root() {
        return root;
    }

    void helpClear(NodeForMap<T, T1> *currentNode);

    NodeForMap<T, T1>* find(T key);

    List<T> get_keys();

    void creatingListOfKeys(NodeForMap<T, T1> *currentNode, List<T> &keysList);

    List<T1> get_data();

    void creatingListOfData(NodeForMap<T, T1> *currentNode, List<T1> &listOfData);

    List<T>  createFrecList(List<T> list);

    void helpCreateFrecList(NodeForMap<T, T1> *currentNode, List<T> &listOfData);




};

template <typename T, typename T1>
Map<T, T1>::Map() {
    root = nullptr;
}

template <typename T, typename T1>
void Map<T, T1>::insert(T key1, T1 value1) {

    NodeForMap<T, T1> *newElem = new NodeForMap<T, T1>(key1, value1);

    if (root == nullptr){
        root = newElem;
    } else {
        NodeForMap<T, T1> *current = root;
        NodeForMap<T, T1> *parent = nullptr;

        while (current!= nullptr){
            parent = current;
            if (current->key < newElem -> key){
                current = current -> right;
            }else if (current -> key > newElem -> key) {
                current = current -> left;
            } else {
                throw invalid_argument ("This is key in a tree");
            }

        }

        // now we have found the place where new ell will be added

        newElem->parent = parent;
        newElem->color = true;

        if (parent->key < newElem->key)
            parent->right = newElem;
        else
            parent->left = newElem;
    }
    fixInsert(newElem);
}

template <typename T, typename T1>
void Map<T, T1>::fixInsert (NodeForMap <T, T1> *current){

    while (current!= root && current->parent->color){ // while p red
        // if p node is left son
        if (current->parent == current->parent->parent->left){
            NodeForMap<T, T1> *uncle = current->parent->parent->right;
            if (uncle!= nullptr && uncle->color){ //uncle red
                current->parent->color = false;
                uncle->color = false;
                current->parent->parent->color = true;
                current = current->parent->parent;
            } else { //uncle black or don't exist
                if (current == current->parent->right){
                    current = current->parent;

                    leftRotation(current);
                }

                current->parent->color = false;
                current->parent->parent->color = true;
                rightRotation(current->parent->parent);
            }

        } else {

            NodeForMap<T, T1> *uncle = current->parent->parent->left;
            if (uncle!= nullptr && uncle->color) { //uncle red
                current->parent->color = false;
                uncle->color = false;
                current->parent->parent->color = true;
                current = current->parent->parent;
            } else {
                if (current == current->parent->left){
                    current = current->parent;
                    rightRotation(current);
                }

                current->parent->color = false;
                current->parent->parent->color = true;
                leftRotation(current->parent->parent);
            }
        }
    }
    root->color = false;
}

template<typename T, typename T1>
void Map<T, T1>::rightRotation(NodeForMap<T, T1> *elemX) {

    NodeForMap<T, T1> *elemY = elemX->left;

    elemX->left = elemY->right;
    if (elemY->right != nullptr) elemY->right->parent = elemX;


    if (elemY != nullptr) elemY->parent = elemX->parent;
    if (elemX->parent) {
        if (elemX == elemX->parent->right)
            elemX->parent->right = elemY;
        else
            elemX->parent->left= elemY;
    } else {
        root = elemY;
    }

    elemY->right = elemX;
    if (elemX != nullptr) elemX->parent = elemY;
}

template<typename T, typename T1>
void Map<T, T1>::leftRotation(NodeForMap<T, T1> *elemX) {

    NodeForMap<T, T1> *elemY = elemX->right;

    elemX->right = elemY->left;
    if (elemY->left != nullptr) elemY->left->parent = elemX;

    if (elemY != nullptr) elemY->parent = elemX->parent;
    if (elemX->parent) {
        if (elemX == elemX->parent->left)
            elemX->parent->left = elemY;
        else
            elemX->parent->right = elemY;
    } else {
        root = elemY;
    }

    elemY->left = elemX;
    if (elemX != nullptr) elemX->parent = elemY;
}

template<typename T, typename T1>
void Map<T, T1>::deleteNode(T key) {

    NodeForMap<T, T1> *deleted = find(key);

    // if its list
    if ((deleted->left == nullptr)&&(deleted->right == nullptr)){
        if (deleted == root) {
            root = nullptr;
            delete deleted;
        } else {

            if (deleted == deleted->parent->left)
                deleted->parent->left = nullptr;
            else
                deleted->parent->right = nullptr;

            if (!deleted->color) fixDeleting(deleted->parent);
            delete deleted;
        }
    }

    //if one son
    if ((deleted->left == nullptr) != (deleted->right == nullptr)){

        if (deleted == root){
            if (deleted->left != nullptr)
                root = deleted->left;
            else if (deleted->right != nullptr)
                root = deleted->right;
        } else {
            NodeForMap<T, T1> *sonOfDeleted;

            if (deleted->left != nullptr)
                sonOfDeleted = deleted->left;
            else
                sonOfDeleted = deleted->right;

            sonOfDeleted->parent = deleted->parent;

            if (deleted == deleted->parent->left)
                deleted->parent->left = sonOfDeleted;
            else
                deleted->parent->right = sonOfDeleted;

            if (!deleted->color) fixDeleting(sonOfDeleted);
            delete deleted;

        }
    }

    //if two sons
    if ((deleted->left != nullptr) && (deleted->right != nullptr)){
        NodeForMap<T, T1> *temporaryNode = deleted->right;
        while (temporaryNode->left != nullptr) temporaryNode = temporaryNode->left;

        if (temporaryNode->right == nullptr){
            if (temporaryNode == temporaryNode->parent->left)
                temporaryNode->parent->left = nullptr;
            else
                temporaryNode->parent->right = nullptr;

            deleted->key = temporaryNode->key;
            deleted->data = temporaryNode->data;
            if (!temporaryNode->color) fixDeleting (temporaryNode->parent);
        } else {
            NodeForMap<T, T1> *sonOfTemporary = temporaryNode->right;
            temporaryNode->parent->left = sonOfTemporary;
            sonOfTemporary->parent = temporaryNode->parent;
            deleted->key = temporaryNode->key;
            deleted->data = temporaryNode->data;
            if (!temporaryNode->color) fixDeleting (sonOfTemporary);
        }
        delete temporaryNode;
    }
}

template<typename T, typename T1>
void Map<T, T1>::fixDeleting(NodeForMap<T, T1> *son){
    while ((!son->color)&&(son!=root)){
        if (son == son->parent->left){
            if (son->parent->right->color){
                son->parent->right->color = false;
                son->parent->color = true;
                leftRotation (son->parent);
            }
            if ((!son->parent->right->left->color) &&(!son->parent->right->right->color)){
                son->parent->right->color = true;
            }else{
                if (!son->parent->right->right->color){
                    son->parent->right->left->color = false;
                    son->parent->right->color = true;
                    rightRotation(son->parent->right);
                }
                son->parent->right->color = son->parent->color;
                son->parent->color = false;
                son->parent->right->right->color = false;
                leftRotation (son->parent);
                son = root;
            }
        }else{
            if (son->parent->left->color){
                son->parent->left->color = false;
                son->parent->color = true;
                rightRotation(son->parent);
            }
            if ((!son->parent->left->left->color) && (!son->parent->left->right->color)){
                son->parent->left->color = true;
            }else{
                if (!son->parent->left->left){
                    son->parent->left->right->color = false;
                    son->parent->left->color = true;
                    leftRotation(son->parent->left);
                }
                son->parent->left = son->parent;
                son->parent->color = false;
                son->parent->left->left->color = false;
                rightRotation(son->parent);
                son = root;
            }
        }
    }
    son->color = false;
    root->color = false;
}

template<typename T, typename T1>
NodeForMap<T, T1> *Map<T, T1>::find(T key) {
    NodeForMap<T, T1> *current = root;

    while (current != nullptr){
        if (current->key == key){
            return current;
        }
        else {
            current =  (current->key < key)? current->right : current->left;
        }
    }
    return nullptr;
}

template<typename T, typename T1>
void Map<T, T1>::show() {
    if (root == nullptr) {
        cout << "Empty map";
        return;
    }
    NodeForMap<T, T1> *currentNode = root;
    helpShow(currentNode, 0);
}

template<typename T, typename T1>
void helpShow(NodeForMap<T, T1> *node, int level) {
    if (node) {
        helpShow(node->right, level+1);
        for(int i = 0; i < 3*level; i++) cout << ".";
        char color = (node->color)? 'r' : 'b';
        cout << node->key << "(" << color << ")" << endl;
        helpShow(node->left, level+1);
    }
}

template<typename T, typename T1>
void Map<T, T1>::clear() {
    NodeForMap<T, T1> *currentNode = root;
    helpClear(currentNode);
}

template<typename T, typename T1>
void Map<T,T1>::helpClear(NodeForMap<T, T1> *currentNode){
    if (currentNode == root) root = nullptr;
    if(currentNode){
        helpClear(currentNode->left);
        helpClear(currentNode->right);
        delete currentNode;
    }
}

template<typename T, typename T1>
List<T> Map<T, T1>::get_keys() {
    List<T> keysList;
    creatingListOfKeys(root, keysList);
    return keysList;
}

template<typename T, typename T1>
void Map<T, T1>::creatingListOfKeys(NodeForMap<T, T1> *node, List<T> &keysList) {
    if(node){
        creatingListOfKeys(node->left, keysList);
        keysList.push_back(node->key);
        creatingListOfKeys(node->right, keysList);
    }
}

template<typename T, typename T1>
List<T1> Map<T, T1>::get_data() {
    List<T1> dataList;
    creatingListOfData(root, dataList);
    return dataList;
}

template<typename T, typename T1>
void Map<T, T1>::creatingListOfData(NodeForMap<T, T1> *node, List<T1> &dataList) {
    if(node){
        creatingListOfData(node->left, dataList);
        dataList.push_back(node->data);
        creatingListOfData(node->right, dataList);
    }
}

template<typename T, typename T1>
Map<T, T1>::~Map() {
    clear();
}

template<typename T, typename T1>
List<T> Map<T, T1>::createFrecList(List<T> list) {
    helpCreateFrectList(root, list);
    return list;
}

template<typename T, typename T1>
void Map<T, T1>::helpCreateFrecList(NodeForMap<T, T1> *node, List<T> &dataList) {
    if(node){
        helpCreateFrectList(node->left, dataList);
        //dataList.push_back(node->key, node->data);
        helpCreateFrectList(node->right, dataList);
    }
}

template<typename T, typename T1>
void Map<T, T1>::addForData(T key, T num) {
    NodeForMap<T, T1> *m = find(key);
    if (m){
        m->data += num;
    }else{
        insert(key, num);
    }
}
template<typename T, typename T1>
void Map<T, T1>:: showTable(){

}
#endif //LAB2_MAP_H

