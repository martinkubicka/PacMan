#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <string>
#include <iostream>

using namespace std;

enum instructionEnum {
    MAP,
    GS,
    GE,
    PCM,
    GM,
    KEYL,
    KILL,
    NONE
};

// struktura
struct Instruction {
    instructionEnum type;
    string arg1;
    string arg2;
    string arg3;
};

void openLogRead(string path, ifstream& file);

void openLogWrite(string path, ofstream& file);

void writeToLog(string str, ofstream& file);

Instruction* getInstruction(ifstream &file);

void closeLog(ifstream& file);

void closeLog(ofstream& file);

#endif // LOG_H
