 #include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Map.h"
#include <iostream>
using namespace std;

int main() {
    Map <int, int> map;
    map.insert(1,2);
    map.insert(3,4);
    map.deleteNode(1);
    cout << map.get_data();
    testing::InitGoogleTest();
    int b = RUN_ALL_TESTS();
    return 0;
}
