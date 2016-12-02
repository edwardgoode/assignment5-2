/* -*- C++ -*- */
#ifndef _VISITOR_CPP_
#define _VISITOR_CPP_

#include "Visitor.h"

Visitor::~Visitor() {}

PrintVisitor::PrintVisitor(std::ostream &os){
    os_ = os;
}

void PrintVisitor::visit(object &obj){
    os << obj.getName();
}
#endif /* _VISITOR_CPP_ */

