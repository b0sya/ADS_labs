//
// Created by b0sya on 2019-04-08.
//

#include "../main.cpp"

using testing::Eq;

namespace {
    class ClassDeclaration: public testing::Test{
    public:
        //initialization of object that will be used in test
        MyNode *p;
        MyNode *leftSon;
        MyNode *rightSon;

        ClassDeclaration(){
            p;
            leftSon;
            rightSon;
        }
    };
}

TEST_F(ClassDeclaration, test_leftSonSymbol){
    leftSon = new MyNode();
    leftSon->symbol = 'C';
    leftSon->freq = 1;
    rightSon = new MyNode();
    rightSon->symbol = 'a';
    rightSon->freq = 5;
    p = new MyNode(leftSon, rightSon);

    ASSERT_EQ(p->left->symbol,'C');

}

TEST_F(ClassDeclaration, test_rightSonSymbol){
    leftSon = new MyNode();
    leftSon->symbol = 'C';
    leftSon->freq = 1;
    rightSon = new MyNode();
    rightSon->symbol = 'a';
    rightSon->freq = 5;
    p = new MyNode(leftSon, rightSon);

    ASSERT_EQ(p->right->symbol,'a');

}

TEST_F(ClassDeclaration, test_rightSonFreq){
    leftSon = new MyNode();
    leftSon->symbol = 'C';
    leftSon->freq = 1;
    rightSon = new MyNode();
    rightSon->symbol = 'a';
    rightSon->freq = 5;
    p = new MyNode(leftSon, rightSon);

    ASSERT_EQ(p->left->freq,1);

}

TEST_F(ClassDeclaration, test_leftSonFreq){
    leftSon = new MyNode();
    leftSon->symbol = 'C';
    leftSon->freq = 1;
    rightSon = new MyNode();
    rightSon->symbol = 'a';
    rightSon->freq = 5;
    p = new MyNode(leftSon, rightSon);

    ASSERT_EQ(p->right->freq,5);

}
TEST_F(ClassDeclaration, test_parentFreq){
    leftSon = new MyNode();
    leftSon->symbol = 'C';
    leftSon->freq = 1;
    rightSon = new MyNode();
    rightSon->symbol = 'a';
    rightSon->freq = 5;
    p = new MyNode(leftSon, rightSon);

    ASSERT_EQ(p->freq,6);

}

TEST_F(ClassDeclaration, test_BuildTable){
    leftSon = new MyNode();
    leftSon->symbol = 'C';
    leftSon->freq = 1;
    rightSon = new MyNode();
    rightSon->symbol = 'a';
    rightSon->freq = 5;
    p = new MyNode(leftSon, rightSon);

    BuildTable(p);

    List< char > showKey = table.get_keys();
    List< string > showCode = table.get_data();

    ASSERT_EQ(showKey.at(0),'C');
    ASSERT_EQ(showKey.at(1),'a');
    ASSERT_EQ(showCode.at(0),"0");
    ASSERT_EQ(showCode.at(1),"1");

}