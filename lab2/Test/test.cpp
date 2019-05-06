#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include "../List.h"
#include "../Map.h"
using testing::Eq;

namespace {
    class ClassDeclaration: public testing::Test{
    public:
        //initialization of object that will be used in test
        Map<int, int> lst;
        NodeForMap<int, int> *root;

        ClassDeclaration(){
            lst;
            root;
        }
    };
}

TEST_F(ClassDeclaration, test_insert){
    lst.insert(13, 1);
    lst.insert(8, 2);

    root = lst.get_root();

    //check keys
    ASSERT_EQ(root->key, 13);
    ASSERT_EQ(root->left->key, 8);

    //check values
    ASSERT_EQ(root->data, 1);
    ASSERT_EQ(root->left->data, 2);

    //check colors
    ASSERT_EQ(root->color, 0);
    ASSERT_EQ(root->left->color, 1);

    //check that these are all nodes of tree
    ASSERT_EQ(root->left->left, nullptr);
    ASSERT_EQ(root->left->right, nullptr);

}


TEST_F(ClassDeclaration, test_remove){
    lst.insert(13, 1);
    lst.insert(8, 2);
    lst.insert(17, 3);

    lst.deleteNode(13);
    root = lst.get_root();

    //check keys
    ASSERT_EQ(root->key, 17);
    ASSERT_EQ(root->left->key, 8);

    //check values
    ASSERT_EQ(root->data, 3);

    //check colors
    ASSERT_EQ(root->color, 0);
    ASSERT_EQ(root->left->color, 1);

    //check that these are all nodes of tree
    ASSERT_EQ(root->right, nullptr);
    ASSERT_EQ(root->left->left, nullptr);
    ASSERT_EQ(root->left->right, nullptr);
}

TEST_F(ClassDeclaration, test_find){
    lst.insert(13, 1);
    lst.insert(8, 2);
    lst.insert(17, 3);

    root = lst.get_root();
    NodeForMap<int, int> *forFind = lst.find(8);

    //check keys
    ASSERT_EQ(forFind, root->left);
}

TEST_F(ClassDeclaration, test_clear){
    lst.insert(13, 1);
    lst.insert(8, 2);
    lst.insert(17, 3);

    root = lst.get_root();
    ASSERT_EQ(root != nullptr, true);
    lst.clear();
    root = lst.get_root();
    ASSERT_EQ(root == nullptr, true);
}

TEST_F(ClassDeclaration, test_getKeys){
    lst.insert(1, 4);
    lst.insert(2, 5);
    lst.insert(3, 6);

    List<int> listOfKeys = lst.get_keys();

    for (int i = 1; i < 4; i++){
        ASSERT_EQ(i, listOfKeys.at(i-1));
    }

    ASSERT_EQ(3, listOfKeys.getSize());
}

TEST_F(ClassDeclaration, test_getData){
    lst.insert(1, 4);
    lst.insert(2, 5);
    lst.insert(3, 6);

    List<int> listOfValues = lst.get_data();

    for (int i = 1; i < 4; i++){
        ASSERT_EQ(i+3, listOfValues.at(i-1));
    }

    ASSERT_EQ(3, listOfValues.getSize());
}
