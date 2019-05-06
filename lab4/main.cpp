#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "FindShortWayService.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace std;

int main() {

    setlocale(LC_ALL, "rus");
    ifstream file("inputForTest.txt");
    string start;
    string end;

    FindShortWayService searchEngine(file);

    cout << "Enter your start city: ";
    cin >> start;
    cout << "Enter your destination city: ";
    cin >> end;
    
    searchEngine.findShortWay(start,end);

    file.close();

    testing::InitGoogleTest();
    int b = RUN_ALL_TESTS();
    return 0;
}