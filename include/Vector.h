#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <string>
#include <cstddef>

/**
 *
 *  A class representing an n-dimensional vector of doubles (n >= 1). Common
 *  vector operations are implemented in a loop-free manner to encourage use of
 *  functors and STL algorithms.
 *
 *  Since no dynamic memory is used, destructor, copy constructor, and an
 *  assignment operator are not necessary.
 */
template <size_t DIM>
class Vector {
public:
    /**
     *  Creates the zero vector.
     */
    Vector();

    /**
     *  Creates a vector using the first DIM values starting at ptr.
     */
    explicit Vector(const double *ptr);

    /***************************************************************************
    *                                                                          *
    *                      S P A C E   O P E R A T I O N S                     *
    *                                                                          *
    ***************************************************************************/

    /**
     *  Returns the sum of this vector and rhs.
     */
    const Vector<DIM> add(const Vector<DIM> &rhs) const;

    /**
     *  Returns the additive inverse of this vector.
     */
    const Vector<DIM> invert() const;

    /**
     *  Scales a copy of this vector by rhs and returns the result.
     */
    const Vector<DIM> scale(const double &rhs) const;

    /**
     *  Returns the dot (inner) product of this vector and rhs.
     */
    double dot(const Vector<DIM> &rhs) const;

    /**
     *  Returns the square of the magnitude of this vector.
     */
    double normSq() const;

    /**
     *  Returns the magnitude of this vector.
     */
    double norm() const;

    /**
     *  Scales this vector such that its magnitude is 1 and returns the result
     *  for chaining.
     */
    Vector<DIM> & normalize();

    /**
     *  Returns the cross product of this and rhs if called on a 3D vector.
     *  throws an std::domain_error otherwise.
     */
    const Vector<DIM> cross(const Vector<DIM> &v) const;

    /**
     *  Returns a human readable representation of this vector.
     *  Ex. [1 2 3]
     */
    std::string toString() const;

    /***************************************************************************
    *                                                                          *
    *                  O V E R L O A D E D   O P E R A T O R S                 *
    *                                                                          *
    ***************************************************************************/

    /**
     *  Returns true if this vector equals rhs.
     */
    bool operator==(const Vector<DIM> &rhs) const;

    /**
     *  Returns true if this vector differs from rhs.
     */
    bool operator!=(const Vector<DIM> &rhs) const;

    /**
     *  Returns a reference to the index-th component of this vector. Not range
     *  checked.
     */
    double& operator[](size_t index);

    /**
     *  Returns a reference to the index-th component of this vector. Not range
     *  checked.
     */
    const double& operator[](size_t index) const;

    /**
     *  Returns the sum of this vector and rhs.
     */
    Vector<DIM> operator+(const Vector<DIM> &rhs) const;

    /**
     *  Increments this vector by rhs and returns the result for chaining.
     */
    Vector<DIM> & operator+=(const Vector<DIM> &rhs);

    /**
     *  Returns the additive inverse of this vector.
     */
    Vector<DIM> operator-() const;

    /**
     *  Returns the difference between this vector and rhs.
     */
    Vector<DIM> operator-(const Vector<DIM> &rhs) const;

    /**
     *  Decrements this vector by rhs and returns the result for chaining.
     */
    Vector<DIM> & operator-=(const Vector<DIM> &v);

    /**
     *  Scales this vector by rhs and returns the result for chaining.
     */
    Vector<DIM> & operator*=(const double &rhs);

    /**
     *  Scales this vector by 1.0 / rhs and returns the result for chaining.
     */
    Vector<DIM> & operator/=(const double &rhs);

    /**
     *  Scales a copy of this vector by rhs and returns the result.
     */
    Vector<DIM> operator*(const double &rhs) const;

    /**
     *  Scales a copy of this vector by 1.0 / rhs and returns the result.
     */
    Vector<DIM> operator/(const double &rhs) const;

    /**
     *  Returns the dot (inner) product of this vector and rhs.
     */
    double operator*(const Vector<DIM> &rhs) const;

    /**
     *  Returns the cross product of this and rhs if called on a 3D vector.
     *  throws an std::domain_error otherwise.
     */
    Vector<DIM> operator^(const Vector<DIM> &v) const;

private:

    /**
     *  Private iterator methods.
     */
    double* begin();

    const double* begin() const;

    double* end();

    const double* end() const;

    /**
     *  Statically allocated storage space.
     */
    double data_[DIM];
};

/**
 *  Returns the result of scaling a copy of v by scale. This free function
 *  guarantees that vector scaling is commutative.
 */
template <size_t DIM>
const Vector<DIM> operator*(const double &scale, const Vector<DIM> &v);

typedef Vector<2> vector2;
typedef Vector<3> vector3;
typedef Vector<4> vector4;

#include "../src/Vector.cpp"
#endif
