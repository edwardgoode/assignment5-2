/**
 * @class Object.cpp
 * @brief Representation of objects suitable for use in the simulation.
 * @details Creates object with physical attributes to be used for physics simulator
 *
 * I affirm that this work is my own
 * 2016-11-30
 * @author Edward Goode
 * VuID: goodees
 * Email: edward.s.goode@vanderbilt.edu
 */

#ifndef _OBJECT_CPP_
#define _OBJECT_CPP_

#include "../include/Object.h"
#include "../include/Visitor.h"

/**
 *  Destroys this object.
 */
Object::~Object(){
}

/**
 *  An entry point for a visitor.
 */
void Object::accept(Visitor &visitor){
    visitor.visit(*this);
}

/**
 *  Implementation of the prototype. Returns a dynamically allocated deep
 *  copy of this object.
 */
Object* Object::clone() const{
    Object *copy = new Object(name_, mass_, position_, velocity_);
    return copy;
}

/**
 *  Returns the mass.
 */
double Object::getMass() const{
    return mass_;
}

/**
 *  Returns the name.
 */
std::string Object::getName() const{
    return name_;
}

/**
 *  Returns the position vector.
 */
vector2 Object::getPosition() const{
    return position_;
}

/**
 *  Returns the velocity vector.
 */
vector2 Object::getVelocity() const{
    return velocity_;
}

/**
 *  Sets the position vector.
 */
void Object::setPosition(const vector2 &pos){
    position_ = pos;
}

/**
 *  Sets the velocity vector.
 */
void Object::setVelocity(const vector2 &vel){
    velocity_ = vel;
}

/**
 *  Returns true if this object is member-wise equal to rhs.
 */
bool Object::operator==(const Object &rhs) const{
    return name_ == rhs.name_ && mass_ == rhs.mass_
           && position_ == rhs.position_ && velocity_ == rhs.velocity_;
}

/**
 *  Returns !(*this == rhs).
 */
bool Object::operator!=(const Object &rhs) const{
    return !(*this == rhs);
}

Object::Object(const std::string &name, double mass, const vector2 &pos, const vector2 &vel) :
        name_(name), mass_(mass), position_(pos), velocity_(vel) {
}


#endif