/**
 * @class Universe.cpp
 * @brief A singleton universe to simulate planetary ineraction
 * @details Holds a vector with objects
 *
 * I affirm that this work is my own
 * 2016-11-30
 * @author Edward Goode
 * VuID: goodees
 * Email: edward.s.goode@vanderbilt.edu
 */

#ifndef _UNIVERSE_CPP_
#define _UNIVERSE_CPP_

#include "../include/Universe.h"
#include "../include/Object.h"
#include <cmath>

Universe *Universe::instance_ = nullptr;

/**
 *  Returns the only instance of the Universe
 */
Universe* Universe::instance(){
    if (instance_ == nullptr)
        instance_ = new Universe();

    return instance_;
}

/**
 *  Calculates the force vector between obj1 and obj2. The direction of the
 *  result is as experienced by obj1. Negate the result to obtain force
 *  experienced by obj2.
 */
vector2 Universe::getForce(const Object &obj1, const Object &obj2){
    double numerator = G * obj1.getMass() * obj2.getMass();
    double denominator = (obj1.getPosition() - obj2.getPosition()).normSq();
    double operation = numerator/denominator;
    vector2 direction = (obj1.getPosition() - obj2.getPosition()).normalize();
    vector2 zero;

    if(obj2.getName() == obj1.getName())
        return zero;

    return operation * direction;
}

/**
 *  Releases all the dynamic objects still registered with the Universe.
 */
Universe::~Universe(){
    release(objects_);
    instance_ = nullptr;
}

/**
 *  Registers an Object with the universe. The Universe will clean up this
 *  object when it deems necessary.
 */
void Universe::addObject(Object *ptr){
    objects_.push_back(ptr);
}

/**
 *  Returns the begin iterator to the actual Objects. The order of itetarion
 *  will be the same as that over getSnapshot()'s result as long as no new
 *  objects are added to either of the containers.
 */
std::vector<Object*>::iterator Universe::begin(){
    return objects_.begin();
}

/**
 *  Returns the begin iterator to the actual Objects. The order of itetarion
 *  will be the same as that over getSnapshot()'s result as long as no new
 *  objects are added to either of the containers.
 */
std::vector<Object*>::const_iterator Universe::begin() const{
    return objects_.begin();
}

/**
 *  Returns the end iterator to the actual Objects. The order of itetarion
 *  will be the same as that over getSnapshot()'s result as long as no new
 *  objects are added to either of the containers.
 */
std::vector<Object*>::iterator Universe::end(){
    return objects_.end();
}

/**
 *  Returns the end iterator to the actual Objects. The order of itetarion
 *  will be the same as that over getSnapshot()'s result as long as no new
 *  objects are added to either of the containers.
 */
std::vector<Object*>::const_iterator Universe::end() const{
    return objects_.end();
}

/**
 *  Returns a container of copies of all the Objects registered with the
 *  Universe. This should be used as the source of data for computing the
 *  next step in the simulation
 */
std::vector<Object*> Universe::getSnapshot() const{
    std::vector<Object*> copyVector;
    for (Object *obj : objects_){
        copyVector.push_back((*obj).clone());
    }

    return copyVector;
}

/**
 *  Advances the simulation by the provided time step. For this assignment,
 *  you may assume that the first registered object is a "sun" and its
 *  position should not be affected by any of the other objects.
 */
void Universe::stepSimulation(const double &timeSec){
    std::vector<Object*> newVector = getSnapshot();

    for(size_t i = 1; i < objects_.size(); i++){
        vector2 forceOnObj;

        for(Object *obj: objects_)
            forceOnObj += getForce(*obj, *newVector[i]);

        vector2 acceleration = forceOnObj / (*newVector[i]).getMass();
        vector2 deltaVelocity = acceleration * timeSec;
        vector2 velocity = (*newVector[i]).getVelocity() + deltaVelocity;
        vector2 deltaPosition = velocity * timeSec;
        vector2 position = (*newVector[i]).getPosition() + deltaPosition;
        (*newVector[i]).setPosition(position);
        (*newVector[i]).setVelocity(velocity);

    }

    swap(newVector);
}

/**
 *  Swaps the constants of the provided container with the Universe's Object
 *  store and releases the old Objects.
 */
void Universe::swap(std::vector<Object*> &snapshot){
    objects_.swap(snapshot);
    release(snapshot);
}

/**
 *  Calls delete on each pointer and removes it from the container.
 */
void Universe::release(std::vector<Object*> &objects){
    for (Object *obj : objects)
        delete obj;

    objects.clear();
}

Universe::Universe(){
}

#endif