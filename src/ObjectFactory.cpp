/**
 * @class ObjectFactory.cpp
 * @brief Creates an object with the provided parameters
 * @details used to construct objects easier
 *
 * I affirm that this work is my own
 * 2016-11-30
 * @author Edward Goode
 * VuID: goodees
 * Email: edward.s.goode@vanderbilt.edu
 */

#ifndef _OBJECT_FACTORY_CPP
#define _OBJECT_FACTORY_CPP

#include "../include/ObjectFactory.h"
#include "../include/Object.h"

/**
 *  Creates an object with the provided parameters. Default values of zero
 *  will be assigned to everything except for name.
 */
Object* ObjectFactory::makeObject(std::string name, double mass, const vector2 &pos, const vector2 &vel){
    return new Object(name, mass, pos, vel);
}
#endif