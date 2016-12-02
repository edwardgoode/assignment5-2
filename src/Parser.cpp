/**
 * @class Parser.cpp
 * @brief Parser for graduate portion
 * @details Needed to implement loadFile in order for tests to run
 *
 * I affirm that this work is my own
 * 2016-11-30
 * @author Edward Goode
 * VuID: goodees
 * Email: edward.s.goode@vanderbilt.edu
 */

#ifndef _PARSER_CPP_
#define _PARSER_CPP_

#include "../include/Parser.h"
#include <iostream>
#include <fstream>

/**
 *  Loads the script file and configures the Universe. Consult the
 *  assignment PDF for the syntax of the scripts.
 */
void Parser::loadFile(char const* filename){
    std::ifstream myfile(filename);
    if(myfile.is_open())
        myfile.close();
}

#endif
