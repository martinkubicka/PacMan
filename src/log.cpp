/**
 * @file log.cpp
 *
 * @author  Martin Kubička (xkubic45@stud.fit.vutbr.cz)
 * @author  Matěj Macek (xmacek27@stud.fit.vutbr.cz)
 *
 * @date 2023-05-08
 * @brief Definitions of functions declared in log.h file.
 */

#include "log.h"

void openLogRead(string path, ifstream& file) {
    file.open(path + "/log/log.txt", std::ios::in);

    if (!file.is_open()) {
        cerr << "ERROR: Opening file!" << endl;
        exit(EXIT_FAILURE);
    }
}

void openLogWrite(string path, ofstream& file) {
    file.open(path + "/log/log.txt", ios::trunc);

    if (!file.is_open()) {
        cerr << "ERROR: Opening file!" << endl;
        exit(EXIT_FAILURE);
    }
}

void closeLog(std::ifstream& file) {
    if (file.is_open()) {
        file.close();
    }
}

void closeLog(std::ofstream& file) {
    if (file.is_open()) {
        file.close();
    }
}

void writeToLog(string str, ofstream& file) {
   file << str << endl;
}

Instruction* getInstruction(ifstream& file) {
    string word;
    Instruction *inst = new Instruction;

    while (file >> word && word != "MAP" && word != "GS" && word != "PCM" && word != "GM" && word != "KEYL" && word != "KILL" && word != "GE") {}

    if (word == "MAP") {
        inst->type = MAP;
        file >> inst->arg1;
    } else if (word == "GS") {
        inst->type = GS;
    } else if (word == "PCM") {
        inst->type = PCM;
        file >> inst->arg1;
        file >> inst->arg2;
    } else if (word == "GM") {
        inst->type = GM;
        file >> inst->arg1;
        file >> inst->arg2;
        file >> inst->arg3;
    } else if (word == "KEYL") {
        inst->type = KEYL;
        file >> inst->arg1;
    } else if (word == "KILL") {
        inst->type = KILL;
    } else if (word == "GE") {
        inst->type = GE;
    } else {
        inst->type = NONE;
    }

    return inst;
}

/*** End of log.cpp ***/
