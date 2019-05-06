//
// Created by b0ysa on 2019-04-24.
//

#ifndef LAB4_FINDSHORTWAYSERVICE_H
#define LAB4_FINDSHORTWAYSERVICE_H
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
using namespace std;

struct Destination {
    string finish;
    int price;
};

class FindShortWayService {
//private:
public:
    map <string, vector<Destination> > tripTable;
    const int INF = 1000000;
    int numOfCities;
    map<string, vector<Destination> >:: iterator mapCursor;

    void createTripTable(ifstream& file);

    void createArrWithDefaultVal(int **arr);

    void createAssociativeArray(int **arr);

    void showAssociativeArray(int **arr);

    int determinateCityIndex(string nameOfCity);

    int* fordBellmanAlgorithm(int **associativeArr, int startIndex, int endIndex, string *way);

    void showShortWay(int* distanceArr, string start, string end, int endIndex, string way);

    void showDistanceArr(int* distandeArr);

    void showCitiesIndexes(string start, string end, int startIndex, int endIndex){
        cout << "The index of " << start << " = " << startIndex <<endl << "The index of " << end << " = " << endIndex << endl;
    }

    string findCityByIndex(int index);

//public:
    void showTripTable();

    void findShortWay(string start, string end);

    FindShortWayService(ifstream& file){
        createTripTable(file);
        showTripTable();
    }

    unsigned long getNumOfCities(){
        return numOfCities;
    }

};

void FindShortWayService :: createTripTable(ifstream& file) {
    while (file){

        string bufferStr;
        int numOfSeparator = 0;
        string strElem = "";
        string startPoint;
        string endPoint;
        Destination route1;
        Destination route2;

        getline(file, bufferStr);
        if (bufferStr == "") {
            getline(file, bufferStr);
        } else {
            for (int i = 0; i < bufferStr.size(); i++) {
                if (bufferStr[i] == ';') {
                    numOfSeparator++;
                    switch (numOfSeparator) {
                        case 1:
                            startPoint = strElem;
                            route2.finish = startPoint;
                            strElem.clear();
                            i++;
                            break;
                        case 2:
                            route1.finish = strElem;
                            endPoint = strElem;
                            strElem.clear();
                            i++;
                            break;
                        case 3:
                            if (strElem == "N/A" || strElem == ""){
                                route1.price = INF;
                            }else{
                                route1.price = atoi(strElem.c_str());
                            }
                            strElem.clear();
                            i++;
                            break;
                        case 4:
                            if (strElem == "N/A" || strElem == ""){
                                route2.price = INF;
                            }else{
                                route2.price = atoi(strElem.c_str());
                            }
                            strElem.clear();
                            i++;
                            break;
                        default:
                            break;
                    }
                }
                strElem += bufferStr[i];
            }
            tripTable[startPoint].push_back(route1);
            tripTable[endPoint].push_back(route2);
        }
    }
    numOfCities = tripTable.size();
}

void FindShortWayService :: findShortWay(string start, string end){
    const unsigned long numOfCities = getNumOfCities();

    int**tripArr = new int*[numOfCities];
    for (size_t i = 0; i < numOfCities; i++)
        tripArr[i] = new int[numOfCities];
    string way;

    createArrWithDefaultVal(tripArr);

    createAssociativeArray(tripArr);

    int startIndex = determinateCityIndex(start);
    int endIndex = determinateCityIndex(end);

    int* distancesFromTheStart = fordBellmanAlgorithm(tripArr,startIndex, endIndex, &way);

    showShortWay(distancesFromTheStart, start, end, endIndex, way);
}

void FindShortWayService :: createArrWithDefaultVal(int **arr) {
    for (int i = 0; i < numOfCities; i++) {
        for (int j = 0; j < numOfCities; j++){
            arr[i][j] = INF;
        }
    }
}

void FindShortWayService :: createAssociativeArray(int **arr){
    map<string, vector<Destination> >:: iterator mapCursor2;
    int i;
    for (mapCursor = tripTable.begin(),i = 0; i < numOfCities ; ++mapCursor, i++){
        vector<Destination>& vec = mapCursor->second;
        vector<Destination>::iterator it;
        for (it = vec.begin(); it != vec.end(); ++it) {
            mapCursor2 = tripTable.begin();
            int count = 0;
            while (mapCursor2->first != it->finish){
                count++;
                mapCursor2++;
            }
            arr[i][count] = it->price;
        }
    }
}

void FindShortWayService :: showAssociativeArray(int **arr){
    cout << "||";
    for (mapCursor = tripTable.begin(); mapCursor!= tripTable.end(); ++mapCursor){
        cout << mapCursor->first << " || ";
    }
    cout << endl;
    for (int i = 0; i < numOfCities; i++) {
        for (int j = 0; j < numOfCities; j++){
            if (arr[i][j] == INF)
                cout << "∞" << " ";
            else
                cout << "" << arr[i][j] << "";
        }
        cout << endl;
    }
}

void FindShortWayService :: showTripTable(){
    for (mapCursor = tripTable.begin(); mapCursor != tripTable.end() ; ++mapCursor) {
        vector<Destination>& vec = mapCursor->second;
        vector<Destination>::iterator it;
        for (it = vec.begin(); it != vec.end(); ++it){
            cout << mapCursor -> first << " -> ";
            if (it->price == INF)
                cout << it->finish << " = " << "N/A" << endl;
            else
                cout << it->finish << " = " << it->price << endl;
        }
        cout << endl;
    }
}

int FindShortWayService :: determinateCityIndex(string nameOfCity){
    int index = 0;
    mapCursor = tripTable.begin();
    while (mapCursor -> first != nameOfCity){
        index++;
        if (index > numOfCities){
            throw out_of_range ("Incorrect city! Program stopped!");
        }
        mapCursor++;
    }
    return index;
}

int* FindShortWayService :: fordBellmanAlgorithm(int **associativeArr, int startIndex, int endIndex, string *way){

    *way += to_string(startIndex);
    string *ways = new string[numOfCities];
    int *distanceArray = new int[numOfCities];
    for (int i=0; i<numOfCities; i++)
        distanceArray[i] = INF;
    distanceArray[startIndex] = 0;
    for (size_t k = 0; k < numOfCities; k++)
        for (size_t i = 0; i < numOfCities; i++)
            for (size_t j = 0; j < numOfCities; j++)
                if (distanceArray[i] + associativeArr[i][j] < distanceArray[j]){
                    distanceArray[j] = distanceArray[i] + associativeArr[i][j];
                    ways[j] = ways[i] + '-' + to_string(j);
                }
    *way += ways[endIndex];
    return distanceArray;
}

void FindShortWayService :: showShortWay(int* distanceArr, string start, string end, int endIndex, string way){
    if (distanceArr[endIndex] == INF){
        cout << "Between this cities there is no way!" << endl;
    }else{
        size_t i = 0;
        string newWay;
        string finding, finded;
        char c;
        size_t j;
        bool flag = false;
        int check;
        while (i < way.length())
        {
            finding.clear();
            c = way[i];
            while ((c != '-') && (i < way.length()))
            {
                finding += c;
                i++;
                c = way[i];
            }
            j = 0;
            while (finding != to_string(j))
                j++;
            finded = findCityByIndex(j);
            if (!flag){
                newWay += finded;
                flag = true;
            }else {
                newWay += " -> ";
                newWay += finded;
            }
            i++;
        }
        cout << "The cheapest way: " << newWay << " by price =  " << distanceArr[endIndex] << "$";
    }
}

void FindShortWayService ::showDistanceArr(int *distanceArr) {
    cout << "Матрица расстояний: " << endl;
    for (int i=0; i < numOfCities; i++)
        cout << distanceArr[i] << " ";
    cout << endl;
}

string FindShortWayService ::findCityByIndex(int index) {
    if (index < numOfCities){
        int i = 0;
        for (mapCursor = tripTable.begin(); i!= index; i++){
            mapCursor++;
        }
        return mapCursor->first;
    }
    return "";
}

#endif //LAB4_FINDSHORTWAYSERVICE_H
