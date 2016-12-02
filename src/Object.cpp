#ifndef _OBJECT_CPP_
#define _OBJECT_CPP_

#include "../include/Object.h"

/**
 *  Destroys this object.
 */
Object::~Object();

/**
 *  An entry point for a visitor.
 */
void Object::accept(Visitor &visitor){
    visitor.visit(this);
}

/**
 *  Implementation of the prototype. Returns a dynamically allocated deep
 *  copy of this object.
 */
Object::Object* clone() const;

/**
 *  Returns the mass.
 */
double Object::getMass() const;

/**
 *  Returns the name.
 */
std::string Object::getName() const;

/**
 *  Returns the position vector.
 */
vector2 Object::getPosition() const;

/**
 *  Returns the velocity vector.
 */
vector2 Object::getVelocity() const;

/**
 *  Sets the position vector.
 */
void Object::setPosition(const vector2 &pos);

/**
 *  Sets the velocity vector.
 */
void Object::setVelocity(const vector2 &vel);

/**
 *  Returns true if this object is member-wise equal to rhs.
 */
bool Object::operator==(const Object &rhs) const;

/**
 *  Returns !(*this == rhs).
 */
bool Object::operator!=(const Object &rhs) const;


#endif