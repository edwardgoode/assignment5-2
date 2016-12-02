/**
 * @class Visitor.cpp
 * @brief Visitor class to print Objects
 * @details Object has an entry point
 *
 * I affirm that this work is my own
 * 2016-11-30
 * @author Edward Goode
 * VuID: goodees
 * Email: edward.s.goode@vanderbilt.edu
 */
#ifndef _VISITOR_CPP_
#define _VISITOR_CPP_

#include "../include/Visitor.h"
#include "../include/Object.h"

Visitor::~Visitor() {}

PrintVisitor::PrintVisitor(std::ostream &os) : os_(os){
}

void PrintVisitor::visit(Object &object){
    os_ << object.getName();
}
#endif

