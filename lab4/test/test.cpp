//
// Created by b0sya on 2019-04-08.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include "../FindShortWayService.h"
using namespace std;

using testing::Eq;

namespace {
    class ClassDeclaration: public testing::Test{
    public:
        //initialization of object that will be used in test

        ifstream input;
        ClassDeclaration(){
            input.open("inputForTest.txt");
        }
    };
}

TEST_F(ClassDeclaration, test_createTripTable){
    FindShortWayService service(input);
    ASSERT_EQ(service.getNumOfCities(), 3);
}
TEST_F(ClassDeclaration, test_createArrWithDefoultVal){
    FindShortWayService service(input);
    int**tripArr = new int*[service.getNumOfCities()];
    for (size_t i = 0; i < service.getNumOfCities(); i++)
        tripArr[i] = new int[service.getNumOfCities()];
    service.createArrWithDefaultVal(tripArr);
    for(int i = 0; i < service.getNumOfCities(); i++){
        for(int j = 0; j < service.getNumOfCities(); j++){
            ASSERT_EQ(tripArr[i][j],1000000);
        }
    }
    input.close();
}

TEST_F(ClassDeclaration, test_createAssociativeArray){
    FindShortWayService service(input);
    int**tripArr = new int*[service.getNumOfCities()];
    for (size_t i = 0; i < service.getNumOfCities(); i++)
        tripArr[i] = new int[service.getNumOfCities()];
    service.createArrWithDefaultVal(tripArr);
    service.createAssociativeArray(tripArr);
    ASSERT_EQ(tripArr[0][0],1000000);
    ASSERT_EQ(tripArr[0][1],20);
    ASSERT_EQ(tripArr[0][2],40);
    ASSERT_EQ(tripArr[1][0],10);
    ASSERT_EQ(tripArr[1][1],1000000);
    ASSERT_EQ(tripArr[1][2],14);
    ASSERT_EQ(tripArr[2][0],35);
    ASSERT_EQ(tripArr[2][1],1000000);
    ASSERT_EQ(tripArr[2][2],1000000);

}

TEST_F(ClassDeclaration, test_determinateCityIndex){
    FindShortWayService service(input);
    ASSERT_EQ(service.determinateCityIndex("Москва"), 0);
    ASSERT_EQ(service.determinateCityIndex("Санкт-Петербург"), 1);
    ASSERT_EQ(service.determinateCityIndex("Хабаровск"), 2);
    EXPECT_THROW(service.determinateCityIndex("Супер-Пупербург"), out_of_range);
}

TEST_F(ClassDeclaration, test_fordBellmanAlgorithm){
    FindShortWayService service(input);
    int**tripArr = new int*[service.getNumOfCities()];
    for (size_t i = 0; i < service.getNumOfCities(); i++)
        tripArr[i] = new int[service.getNumOfCities()];
    service.createArrWithDefaultVal(tripArr);
    service.createAssociativeArray(tripArr);
    string way = "";
    int* distancesFromTheStart = service.fordBellmanAlgorithm(tripArr,service.determinateCityIndex("Москва"),service.determinateCityIndex("Cанкт-Петербург"),&way);
    ASSERT_EQ(distancesFromTheStart[0], 0);
    ASSERT_EQ(distancesFromTheStart[1], 20);
    ASSERT_EQ(distancesFromTheStart[2], 34);
}
