/* This program is meant to create a hashtable that can store,delete,print, and generate student information
 * Date: 5/1/2021
 * Author: Pujan Patel
 */
#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>
#include <string>
#include <fstream>
using namespace std;
//create structs
struct Student {
    string firstName;
    string lastName;
    int studentID = 0;
    float GPA = 0;
};
struct Node {
    Student * student = NULL;
    Node * next = NULL; 
};
//declare methods
void hashMethod(Node * LLList[], int arraySize);
void printList(Node * LLList[], int arraySize);
void rehash(Node * LLList[], int & arraySize);
void createStudents(Node * LLList[], int arraySize, int numberGenerated);
void deleteEntry(Node * LLList[], int arraySize);
//main method
int main() {
    //initialize defaults
    int arraySize = 100;
    Node * LLList[arraySize];
    for(int i = 0; i < arraySize; i++) {
        LLList[i] = NULL;
    }
    bool running = true;
    char userCommand[80];
    //while running, ask for input and run respective function
    while(running) {
        cout << "ADD, PRINT, GENERATE, DELETE, or QUIT" << endl;
        cin >> userCommand;
        if(strcmp("ADD", userCommand) == 0) {
            hashMethod(LLList, arraySize);
            rehash(LLList, arraySize);
        }
        else if(strcmp("PRINT", userCommand) == 0) {
            printList(LLList, arraySize);
        }
        else if(strcmp("GENERATE", userCommand) == 0) {
            int generateNum;
            cout << "How many students?" << endl;
            cin >> generateNum;
            createStudents(LLList, arraySize, generateNum);
        }
        else if(strcmp("DELETE", userCommand) == 0) {
            deleteEntry(LLList, arraySize);
        }
        else if(strcmp("QUIT", userCommand) == 0) {
            running = false;
        }
    }   
    return 0;
}
//store through hashing
void hashMethod(Node * LLList[], int arraySize) {
    Student * tempStudent = new Student();
    Node * tempNode = new Node();
    int hashValue;
    cout << "First Name" << endl;
    cin >> tempStudent->firstName;
    cout << "Last Name" << endl;
    cin >> tempStudent->lastName;
    cout << "Student ID" << endl;
    cin >> tempStudent->studentID;
    cout << "Student GPA" << endl;
    cin >> tempStudent->GPA;
    hashValue = tempStudent->studentID % arraySize;
    tempNode->student = tempStudent;
    if(LLList[hashValue] == NULL) {
        LLList[hashValue] = tempNode;
    }
    else {
        Node * headNode = LLList[hashValue];
        Node * current = headNode;
        while(current->next != NULL) {
            current = current->next;
        }
        current->next = tempNode;
        LLList[hashValue] = headNode;
    }
}
//print hashed array
void printList(Node * LLList[], int arraySize) {
    for(int i = 0; i < arraySize; i++) {
        if(LLList[i] != NULL) {
            Node * headNode = LLList[i];
            if(headNode -> next != NULL) {
                while(headNode->next != NULL) {
                    cout << headNode->student->firstName << " " <<headNode->student->lastName << ", " 
                    << headNode->student->studentID << ", " << setprecision(2) << fixed 
                    << headNode->student->GPA << endl;
                    headNode = headNode->next;
                }
            }
            cout << headNode->student->firstName << " " <<headNode->student->lastName << ", " 
                << headNode->student->studentID << ", " << setprecision(2) << fixed 
                << headNode->student->GPA << endl;
        }
    }
}
//rehash if needed with bigger array 
void rehash(Node * LLList[], int & arraySize) {
    bool needRehash = false;
    int repeat = 0;
    for(int i = 0; i < arraySize; i++) {
        repeat = 0;
        if(LLList[i] != NULL) {
            repeat = 1;
            Node * headNode = LLList[i];
            while(headNode->next != NULL) {
                repeat++;
                headNode = headNode->next;
                if(repeat >= 3) {
                    cout << "REHASHING" << endl;
                    //needRehash = true;
                    repeat = 0;
                }
            }
        }
    }
    if(needRehash) {
        srand(time(NULL));
        int hashValue;
        arraySize *=2;
        Node * newLLList[arraySize];
        for(int i = 0; i < arraySize; i++) {
            newLLList[i] = NULL;
        }
        for(int i = 0; i < arraySize/2; i++) {
            if(LLList[i] != NULL) {
                Node * nodeHead = LLList[i];
                Node * current = nodeHead;
                Node * previous = current;
                while(current->next != NULL) {
                    previous = current;
                    current = current->next;
                }
                hashValue = rand() % arraySize/2+arraySize/2;
                previous->next = NULL;
                if(newLLList[hashValue] == NULL) {
                    newLLList[hashValue] = current;
                }
                else {
                    Node * newNodeHead = LLList[hashValue];
                    Node * newCurrent = newNodeHead;
                    while(newCurrent->next != NULL) {
                        newCurrent = newCurrent->next;
                    }
                    newCurrent->next = current;
                    newLLList[hashValue] = newNodeHead;
                }
            }


        }
        for(int i = 0; i < arraySize/2; i++) {
            newLLList[i] = LLList[i];
        }
        LLList = newLLList;
    } 
}
//generate using txt files
void createStudents(Node * LLList[], int arraySize, int numberGenerated) {
    srand(time(NULL));
    for(int i = 0; i < numberGenerated; i++) {    
        int lineNum = rand() % 50 + 1;
        string lineF;
        string lineL;
        int generatedID = i; 
        float generatedGPA = (rand() % 500)/100;
        int hashValue;
        ifstream fNameFile ("firstName.txt");
        ifstream lNameFile ("lastName.txt");
        if(fNameFile.is_open()) {
            for(int i = 0; i < lineNum; i++) {
                getline(fNameFile, lineF);
            }
            fNameFile.close();
        }
        if(lNameFile.is_open()) {
            for(int i = 0; i < lineNum; i++) {
                getline(lNameFile, lineL);
            }
            lNameFile.close();
        }
        char firstGenerated[80];
        char lastGenerated[80];
        for(int i = 0; i < sizeof(firstGenerated); i++) {
            firstGenerated[i] = lineF[i];
        }
        for(int i = 0; i < sizeof(lastGenerated); i++) {
            lastGenerated[i] = lineL[i];
        }
        Student * tempStudent = new Student();
        Node * tempNode = new Node();
        tempNode->student = tempStudent;
        tempStudent->firstName = lineF;
        tempStudent->lastName = lineL;
        tempStudent->studentID = generatedID;
        tempStudent->GPA = generatedGPA;
        hashValue = tempStudent->studentID % arraySize;
        tempNode->student = tempStudent; 
        if(LLList[hashValue] == NULL) {
            LLList[hashValue] = tempNode;
        }
        else {
            Node * headNode = LLList[hashValue];
            Node * current = headNode;
            while(current->next != NULL) {
                current = current->next;
            }
            current->next = tempNode;
            LLList[hashValue] = headNode;
        }
    }
}
//delete specifc ID entry
void deleteEntry(Node * LLList[], int arraySize) {
    int studentIDRemove;
    cout << "ID of student you would like to remove" << endl;
    cin >> studentIDRemove;
    for(int i = 0; i < arraySize; i++) {
        if(LLList[i] != NULL) {
            Node * headNode = LLList[i];
            Node * current = headNode;
            if(headNode -> next != NULL) {
                while(headNode->next != NULL) {
                    current = headNode;
                    headNode = headNode->next;
                    if(headNode->student->studentID == studentIDRemove) {
                        Node * skip = headNode->next;
                        current->next = skip;
                    }
                }
            }
            if(headNode->student->studentID == studentIDRemove) {
                LLList[i] = NULL;
            }
        }   
    }
}
