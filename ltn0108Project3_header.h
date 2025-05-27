#ifndef ltn0108Project3_HEADER_H
#define ltn0108Project3_HEADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

// Global constant
const int NUM_TESTS = 5;

// Enumeration for menu choices
enum Menu { Add = 1, Remove, Display, Search, Results, Quit };

// Structure for student data
struct Student {
    string name;
    int studentID;
    int numTests;
    int* testScores;
    double average;
};

// Function declarations
void addStudent();
void removeStudent(int id);
void display();
void search(int id);
void exportResults();
int findMinimum(int arr[], int size);
int getNumber(); 

#endif
