#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <string>
#include "Vector.h"

// Forward declaration.
class Visitor;
class ObjectFactory;

/**
 *  Representation of objects suitable for use in the simulation. For this
 *  assignment, this will be the only allowable type. In the future, however,
 *  this class will serve as the abstract base class of the composite pattern.
 *
 *  Krzysztof Zienkiewicz
 */
class Object {
public:
    /**
     *  Destroys this object.
     */
    virtual ~Object();

    /**
     *  An entry point for a visitor.
     */
    virtual void accept(Visitor &visitor);

    /**
     *  Implementation of the prototype. Returns a dynamically allocated deep
     *  copy of this object.
     */
    virtual Object* clone() const;

    /**
     *  Returns the mass.
     */
    virtual double getMass() const;

    /**
     *  Returns the name.
     */
    virtual std::string getName() const;

    /**
     *  Returns the position vector.
     */
    virtual vector2 getPosition() const;

    /**
     *  Returns the velocity vector.
     */
    virtual vector2 getVelocity() const;

    /**
     *  Sets the position vector.
     */
    virtual void setPosition(const vector2 &pos);

    /**
     *  Sets the velocity vector.
     */
    virtual void setVelocity(const vector2 &vel);

    /**
     *  Returns true if this object is member-wise equal to rhs.
     */
    bool operator==(const Object &rhs) const;

    /**
     *  Returns !(*this == rhs).
     */
    bool operator!=(const Object &rhs) const;

private:
    friend class ObjectFactory;
    /**
     *  Initializes an object with the provided properties - really only called by the ObjectFactory
     */
    Object(const std::string &name, double mass, const vector2 &pos, const vector2 &vel);

    /**
     *  Name of the object.
     */
    std::string name_;

    /**
     *  Mass of the object in kilograms.
     */
    double mass_;

    /**
     *  Position vector of the object in meters.
     */
    vector2 position_;

    /**
     *  Velocity vector of the object in meters/second.
     */
    vector2 velocity_;
};

#endif
