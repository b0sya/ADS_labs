#include <iostream>
#include "List.h"
#include "Map.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class MyNode {
public:
    int freq;
    char symbol;
    MyNode *left, *right;

    MyNode(){
        left=right=nullptr;
    }

    MyNode(MyNode *L, MyNode *R){
        left =  L;
        right = R;
        freq = L->freq + R->freq;
    }
};

string code = "";
Map<char, string > table;

void BuildTable(MyNode *root)
{
    if (root->left!=NULL){
        code+="0";
        BuildTable(root->left);
    }

    if (root->right!=NULL){
        code+="1";
        BuildTable(root->right);
    }

    if (root->left==NULL && root->right==NULL) {
        table.insert(root->symbol, code);

    }
    code = code.substr(0, code.size()-1);

}

template <typename T, typename T1>
void show(List<T> showK, List<T1> showS){
    for (int i = 0; i < showS.getSize(); i++){
        cout << showK.at(i) << " : " << showS.at(i) << endl;
    }
}

void printTree(MyNode *root, unsigned k = 0){
    if (root != nullptr){
        printTree(root->left, k+3);
        for (unsigned i = 0; i < k; i++){
            cout << "   ";
        }
        if (root->symbol)
            cout << root->freq << "(" << root->symbol <<") " << endl;
        else
            cout << root->freq << endl;
        printTree(root->right, k + 3);
    }
}

int main() {

    string input;
    cout << "Enter your string: ";
    getline(cin, input);
    cout << "Input string: "<< input << " | " << input.size() * 8 << " bits" << endl;

    Map< char, int> frequencies;

    //create map with frequencies
    for (int i = 0; i < input.length(); i++){
        char symbol = input[i];
        frequencies.addForData(symbol, 1);
    }

    List<char> keyList = frequencies.get_keys();
    List<int> dataList = frequencies.get_data();

    cout << keyList << endl;
    cout << dataList << endl << endl;

    List <MyNode*> tree;
    //creating list with frequencies (Future tree leaves)
    for (int i = 0; i < dataList.getSize(); i++){
        MyNode *node = new MyNode();
        node->symbol = keyList.at(i);
        node->freq = dataList.at(i);
        tree.push_back(node);
    }
    //creating tree
    while (tree.getSize() != 1){
        tree.sort();

        MyNode *sonL = tree.getHead()->data;
        tree.pop_front();
        MyNode *sonR = tree.getHead()->data;
        tree.pop_front();

        MyNode *parent = new MyNode(sonR,sonL);
        tree.push_back(parent);

    }



    MyNode *root = tree.getHead()->data;
    //printTree(root);
    //Create a table with encoded characters
    BuildTable(root);

    List< char > showKey = table.get_keys();
    List< string > showCode = table.get_data();

    show(showKey, showCode);

    cout << endl;

    //encoding a string
    string coded = "";
    for (int i = 0; i < input.length(); i++){
        char c = input[i];
         coded += table.find(c)->data;
    }

    cout << "Encrypted string: " << coded <<" | " << coded.size() << " bits" << endl << "Compression ratio: " << (double)input.size()*8/(double)coded.size() << endl;

    cout << "Decrypted string: ";
    //Decode string using tree
    MyNode *cursor = root;
    for (int i = 0; i < coded.size(); i++){
        if (coded[i] == '1')
            cursor=cursor->right;
        else
            cursor= cursor->left;
        if (cursor->symbol) {
            cout << cursor->symbol;
            cursor = root;
        }
    }

    /*testing::InitGoogleTest();
    int b = RUN_ALL_TESTS();*/
    return 0;
}