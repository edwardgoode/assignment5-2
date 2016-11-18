#ifndef _VECTOR_CPP_
#define _VECTOR_CPP_

#include "../include/Vector.h"
#include "../include/VectorHelpers.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <cmath>
#include <stdexcept>
#include <functional>

/**
 *  Creates the zero vector.
 */
template <size_t DIM>
Vector<DIM>::Vector() {
    std::fill(begin(), end(), 0.0);
}

/**
 *  Creates a vector using the first DIM values starting at ptr.
 */
template <size_t DIM>
Vector<DIM>::Vector(const double *ptr) {
    std::copy(ptr, ptr + DIM, begin());
}

/*******************************************************************************
*                                                                              *
*                        S P A C E   O P E R A T I O N S                       *
*                                                                              *
*******************************************************************************/

/**
 *  Returns the sum of this vector and rhs.
 */
template <size_t DIM>
const Vector<DIM> Vector<DIM>::add(const Vector<DIM> &rhs) const {
    Vector<DIM> sum;
    std::transform(begin(), end(), rhs.begin(), sum.begin(), adder());
    return sum;
}

/**
 *  Returns the additive inverse of this vector.
 */
template <size_t DIM>
const Vector<DIM> Vector<DIM>::invert() const {
    return scale(-1.0);
}

/**
 *  Scales a copy of this vector by rhs and returns the result.
 */
template <size_t DIM>
const Vector<DIM> Vector<DIM>::scale(const double &rhs) const{
    Vector<DIM> s;
    // Via a binder, we can reuse multiplier with a transform
    std::transform(begin(), end(), s.begin(), std::bind2nd(multiplier(), rhs));
    return s;
}

/**
 *  Returns the dot (inner) product of this vector and rhs.
 */
template <size_t DIM>
double Vector<DIM>::dot(const Vector<DIM> &rhs) const {
    // transform will return the output iterator. Therefore, I hacked together
    // an iterator that will actually accumulate the values that are "assigned
    // to its content."
    return std::transform(begin(), end(), rhs.begin(), accumulator_iter(),
                          multiplier()).accumulator;
}

/**
 *  Returns the square of the magnitude of this vector.
 */
template <size_t DIM>
double Vector<DIM>::normSq() const {
    // Dot product of a vector with itself yields the square of the norm.
    return dot(*this);
}

/**
 *  Returns the magnitude of this vector.
 */
template <size_t DIM>
double Vector<DIM>::norm() const {
    return std::sqrt(normSq());
}

/**
 *  Scales this vector such that its magnitude is 1 and returns the result
 *  for chaining.
 */
template <size_t DIM>
Vector<DIM> & Vector<DIM>::normalize() {
    return *this /= norm();
}

/**
 *  Returns the cross product of this and rhs if called on a 3D vector.
 *  throws an std::domain_error otherwise.
 */
template <size_t DIM>
const Vector<DIM> Vector<DIM>::cross(const Vector<DIM> &v) const {
    (void)(v);
    throw std::domain_error("Operation not supported");
}

template <>
inline const Vector<3> Vector<3>::cross(const Vector<3> &v) const {
    Vector<3> c;
    c[0] = (*this)[1] * v[2] - (*this)[2] * v[1];
    c[1] = (*this)[2] * v[0] - (*this)[0] * v[2];
    c[2] = (*this)[0] * v[1] - (*this)[1] * v[0];
    return c;
}

/**
 *  Returns a human readable representation of this vector.
 *  Ex. [1 2 3]
 */
template <size_t DIM>
std::string Vector<DIM>::toString() const {
    std::stringstream str;
    str << "[";
    // We know that DIM is at least 1 so the following is safe and lets us
    // avoid substringing to erase the final space that the naive approach would
    // produce.
    std::copy(begin(), end() - 1, std::ostream_iterator<double>(str, " "));
    str << (*this)[DIM - 1] << "]";
    return str.str();
}

/***************************************************************************
*                                                                          *
*                  O V E R L O A D E D   O P E R A T O R S                 *
*                                                                          *
***************************************************************************/

/**
 *  Returns true if this vector equals rhs.
 */
template <size_t DIM>
bool Vector<DIM>::operator==(const Vector<DIM> &rhs) const {
    return std::equal(begin(), end(), rhs.begin());
}

/**
 *  Returns true if this vector differs from rhs.
 */
template <size_t DIM>
bool Vector<DIM>::operator!=(const Vector<DIM> &rhs) const {
    return !(*this == rhs);
}

/**
 *  Returns a reference to the index-th component of this vector. Not range
 *  checked.
 */
template <size_t DIM>
double & Vector<DIM>::operator[](size_t index) {
    return data_[index];
}

/**
 *  Returns a reference to the index-th component of this vector. Not range
 *  checked.
 */
template <size_t DIM>
const double & Vector<DIM>::operator[](size_t index) const {
    return data_[index];
}

/**
 *  Returns the sum of this vector and rhs.
 */
template <size_t DIM>
Vector<DIM> Vector<DIM>::operator+(const Vector<DIM> &rhs) const {
    return add(rhs);
}

/**
 *  Increments this vector by rhs and returns the result for chaining.
 */
template <size_t DIM>
Vector<DIM> & Vector<DIM>::operator+=(const Vector<DIM> &rhs) {
    return *this = *this + rhs;
}

/**
 *  Returns the additive inverse of this vector.
 */
template <size_t DIM>
Vector<DIM> Vector<DIM>::operator-() const {
    return scale(-1.0);
}

/**
 *  Returns the difference between this vector and rhs.
 */
template <size_t DIM>
Vector<DIM> Vector<DIM>::operator-(const Vector<DIM> &rhs) const {
    return *this + -rhs;
}

/**
 *  Decrements this vector by rhs and returns the result for chaining.
 */
template <size_t DIM>
Vector<DIM> & Vector<DIM>::operator-=(const Vector<DIM> &v) {
    return *this += -v;
}

/**
 *  Scales this vector by rhs and returns the result for chaining.
 */
template <size_t DIM>
Vector<DIM> & Vector<DIM>::operator*=(const double &rhs) {
    return *this = scale(rhs);
}

/**
 *  Scales this vector by 1.0 / rhs and returns the result for chaining.
 */
template <size_t DIM>
Vector<DIM>& Vector<DIM>::operator/=(const double& rhs) {
    return *this *= (1.0 / rhs);
}

/**
 *  Scales a copy of this vector by rhs and returns the result.
 */
template <size_t DIM>
Vector<DIM> Vector<DIM>::operator*(const double &rhs) const {
    return scale(rhs);
}

/**
 *  Scales a copy of this vector by 1.0 / rhs and returns the result.
 */
template <size_t DIM>
Vector<DIM> Vector<DIM>::operator/(const double &rhs) const {
    return scale(1.0 / rhs);
}

/**
 *  Returns the dot (inner) product of this vector and rhs.
 */
template <size_t DIM>
double Vector<DIM>::operator*(const Vector<DIM> &rhs) const {
    return dot(rhs);
}

/**
 *  Returns the cross product of this and rhs if called on a 3D vector.
 *  throws an std::domain_error otherwise.
 */
template <size_t DIM>
Vector<DIM> Vector<DIM>::operator^(const Vector<DIM> &v) const {
    return cross(v);
}

template <size_t DIM>
double* Vector<DIM>::begin() {
    return data_;
}

template <size_t DIM>
const double* Vector<DIM>::begin() const {
    return data_;
}

template <size_t DIM>
double* Vector<DIM>::end() {
    return data_ + DIM;
}

template <size_t DIM>
const double* Vector<DIM>::end() const {
    return data_ + DIM;
}


/**
 *  Returns the result of scaling a copy of v by scale. This free function
 *  guarantees that vector scaling is commutative.
 */
template <size_t DIM>
const Vector<DIM> operator*(const double &scale, const Vector<DIM> &v) {
    return v * scale;
}


#endif
