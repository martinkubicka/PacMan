/**
 * @file log.h
 *
 * @author  Martin Kubička (xkubic45@stud.fit.vutbr.cz)
 * @author  Matěj Macek (xmacek27@stud.fit.vutbr.cz)
 *
 * @date 2023-05-08
 * @brief Declarations of functions which are used for creating and writing to log.
 */

#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <string>
#include <iostream>

using namespace std;

/** Enum which help us to know which instruction was read from log when replaying game */
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

/** Struct which represents read instruction from log file - there can be max 3 arguments */
struct Instruction {
    instructionEnum type;
    string arg1;
    string arg2;
    string arg3;
};

/**
 * @brief Function which opens log for reading.
 *
 * @param path path to log file
 * @param file file
 */
void openLogRead(string path, ifstream& file);

/**
 * @brief Function which opens log for writing.
 *
 * @param path path to log file
 * @param file file
 */
void openLogWrite(string path, ofstream& file);

/**
 * @brief Function which writes string to log file.
 *
 * @param str string which will be written
 * @param file file
 */
void writeToLog(string str, ofstream& file);

/**
 * @brief Function which reads log file and returns recognized instruction.
 *
 * @param file file
 *
 * @return Instruction struct pointer.
 */
Instruction* getInstruction(ifstream &file);

/**
 * @brief Function for closing log opened as ifstream.
 *
 * @param file ifstream file
 */
void closeLog(ifstream& file);

/**
 * @brief Function for closing log opened as ofstream.
 *
 * @param file ofstream file
 */
void closeLog(ofstream& file);

#endif // LOG_H

/*** End of log.h ***/
