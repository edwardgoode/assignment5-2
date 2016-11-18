#ifndef _OBJECT_FACTORY_H_
#define _OBJECT_FACTORY_H_

#include "Vector.h"

// Forward declaration.
class Object;

/**
 *  A factory class used to make Object creation easier.
 *  Krzysztof Zienkiewicz
 */
class ObjectFactory {
public:
    /**
     *  Creates an object with the provided parameters. Default values of zero
     *  will be assigned to everything except for name.
     */
    static Object* makeObject(std::string name, double mass=0, const vector2 &pos=vector2(), const vector2 &vel=vector2());
};

#endif
