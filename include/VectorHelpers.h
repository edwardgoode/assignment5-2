#ifndef _VECTOR_HELPERS_H_
#define _VECTOR_HELPERS_H_

#include <functional>
#include <iostream>

/**
 *  A simple binary functor that adds doubles and returns their sums.
 */
struct adder : std::binary_function<double, double, double> {
    double operator()(const double &a, const double &b) const {
        return a + b;
    }
};

/**
 *  A simple binary functor that multiplies doubles and returns their products.
 */
struct multiplier : std::binary_function<double, double, double> {
    double operator()(const double &a, const double &b) const {
        return a * b;
    }
};

/**
 *  A structure that looks like an iterator but allows the accumulation of
 *  values produced by std::transform.
 *
 *  std::transform applies a function over the values from the input iterators
 *  and stores it into the output iterator via (*iter) = result. Therefore, a
 *  structure may be modified so that *iter will actually return itself. The
 *  following call to operator=() will occur on our "iterator" and so the result
 *  may be handled any way we wish.
 *
 *  All methods are defined constant so that there only needs to be a single
 *  version of this hack.
 */
struct accumulator_iter {

    /**
     *  Initialize the accumulator to 0.
     */
    accumulator_iter() : accumulator(0.0) {}

    /**
     *  No-op increment operator that simply returns *this. Needed so that
     *  we look like an iterator.
     */
    const accumulator_iter & operator++(int) const {
        return *this;
    }

    /**
     *  No-op increment operator that simply returns *this. Needed so that
     *  we look like an iterator.
     */
    const accumulator_iter & operator++() const {
        return *this;
    }

    /**
     *  Dereferencing returns ourselves since we want to intercept the following
     *  assignment.
     */
    const accumulator_iter & operator*() const {
        return *this;
    }

    /**
     *  Increments the accumulator.
     */
    const accumulator_iter & operator=(double val) const {
        accumulator += val;
        return *this;
    }

    /**
     *  Accumulator. Declared mutable so that it can be changed inside const
     *  methods.
     */
    mutable double accumulator;
};

#endif
