//
// Created by b0ysa on 23/02/2019.
//

#include "../List.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

using testing :: Eq;
namespace {
    class ClassDeclaration : public testing:: Test {
    public:
        List<int> objInt;
        List<char> objChar;
        List<double> objDouble;
        List<string> objString;
        ClassDeclaration(){
            objInt;
            objChar;
            objDouble;
            objString;
        }
    };
}

TEST_F(ClassDeclaration, Test_get_size_method_with_double){
    objDouble.push_back(1.0);
    objDouble.push_front(0.9);
    EXPECT_DOUBLE_EQ(2,objDouble.getSize());
}

TEST_F(ClassDeclaration, Test_push_back_method_with_int) {
    objInt.push_back(5);
    objInt.push_back(1);
    EXPECT_EQ(5,objInt.at(0));
}
TEST_F(ClassDeclaration, Test_push_back_method_with_double) {
    objDouble.push_back(5.0);
    EXPECT_DOUBLE_EQ(5.0,objDouble.at(0));
}
TEST_F(ClassDeclaration, Test_push_back_method_with_char) {
    objChar.push_back('a');
    EXPECT_EQ('a',objChar.at(0));
}
TEST_F(ClassDeclaration, Test_push_back_method_with_string) {
    objString.push_back("apple");
    EXPECT_EQ("apple",objString.at(0));
}
TEST_F(ClassDeclaration, Test_push_front_method_with_int) {
    objInt.push_back(1);
    objInt.push_front(0);
    EXPECT_EQ(0,objInt.at(0));
}

TEST_F(ClassDeclaration, Test_push_front_method_with_double) {
    objDouble.push_back(1.0);
    objDouble.push_front(0.9);
    EXPECT_DOUBLE_EQ(0.9,objDouble.at(0));
}
TEST_F(ClassDeclaration, Test_pop_back_method_with_double) {
    objDouble.push_back(1.0);
    objDouble.push_front(0.9);
    objDouble.pop_back();
    EXPECT_DOUBLE_EQ(1,objDouble.getSize());
    EXPECT_DOUBLE_EQ(0.9,objDouble.at(0));
}
TEST_F(ClassDeclaration, Test_pop_front_method_with_double){
    objDouble.push_back(1.0);
    objDouble.push_front(0.9);
    objDouble.pop_front();
    EXPECT_DOUBLE_EQ(1,objDouble.getSize());
    EXPECT_DOUBLE_EQ(1.0,objDouble.at(0));
}
TEST_F(ClassDeclaration, Test_remove_method_with_double){
    objDouble.push_back(1.0);
    objDouble.push_front(0.9);
    objDouble.insert(5.6,1);
    objDouble.remove(1);
    EXPECT_DOUBLE_EQ(2,objDouble.getSize());
    EXPECT_DOUBLE_EQ(1.0,objDouble.at(1));
}
TEST_F(ClassDeclaration, Test_remove_method_with_first_element){
    objDouble.push_back(1.0);
    objDouble.push_front(0.9);
    objDouble.insert(5.6,1);
    objDouble.remove(0);
    EXPECT_DOUBLE_EQ(2,objDouble.getSize());
    EXPECT_DOUBLE_EQ(1.0,objDouble.at(1));
    EXPECT_DOUBLE_EQ(5.6,objDouble.at(0));
    EXPECT_DOUBLE_EQ(5.6,objDouble.getHeadData());
}
TEST_F(ClassDeclaration, Test_clear_method_with_double){
    objDouble.push_back(1.0);
    objDouble.push_front(0.9);
    objDouble.insert(5.6,1);
    objDouble.clear();
    EXPECT_DOUBLE_EQ(0,objDouble.getSize());
}
TEST_F(ClassDeclaration, Test_set_method_with_double){
    objDouble.push_back(1.0);
    objDouble.push_front(0.9);
    objDouble.insert(5.6,1);
    objDouble.set(99.9,0);
    EXPECT_DOUBLE_EQ(3,objDouble.getSize());
    EXPECT_DOUBLE_EQ(99.9,objDouble.at(0));
}
TEST_F(ClassDeclaration, Test_set_method_with_double_and_out_of_range){
    objDouble.push_back(1.0);
    objDouble.push_front(0.9);
    objDouble.insert(5.6,1);
    EXPECT_THROW(objDouble.set(99.9,99), out_of_range);
}
TEST_F(ClassDeclaration, Test_isEmpty_method_with_double){
    objDouble.push_back(1.0);
    objDouble.push_front(0.9);
    objDouble.insert(5.6,1);
    EXPECT_DOUBLE_EQ(false,objDouble.isEmpty());
}
TEST_F(ClassDeclaration, Test_insert_method_with_double){
    objDouble.push_back(1.0);
    objDouble.push_front(0.9);
    objDouble.insert(5.6,1);
    EXPECT_DOUBLE_EQ(5.6,objDouble.at(1));
}
TEST_F(ClassDeclaration, Test_insert_method_with_first_element){
    objDouble.push_back(1.0);
    objDouble.push_front(0.9);
    objDouble.insert(5.6,0);
    EXPECT_DOUBLE_EQ(5.6,objDouble.getHeadData());
}
