/*
 * G. Hemingway @2016
 */
#include <cstdlib>          // for std::rand()
#include <cmath>            // for std::pow()
#include <gtest/gtest.h>
#include "../include/Vector.h"

const double data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

// The fixture for testing the Vector class
class VectorTest : public ::testing::Test {};


TEST_F(VectorTest, ToString) {
    const vector3 v1;
    EXPECT_EQ(v1.toString(), "[0 0 0]");

    vector3 v2(data);
    EXPECT_EQ(v2.toString(), "[0 1 2]");

    vector3 v3(data + 1);
    EXPECT_EQ(v3.toString(), "[1 2 3]");

    vector3 v4(data + 7);
    EXPECT_EQ(v4.toString(), "[7 8 9]");

    vector3 v5(v4);
    EXPECT_EQ(v5.toString(), "[7 8 9]");

    v5 = v1;
    EXPECT_EQ(v5.toString(), "[0 0 0]");
}


TEST_F(VectorTest, Subscript) {
    vector3 v1;
    v1[1] = 1;
    v1[2] = 2;
    EXPECT_EQ(v1.toString(), "[0 1 2]");

    vector3 v2(v1);
    EXPECT_DOUBLE_EQ(v2[0], 0);
    EXPECT_DOUBLE_EQ(v2[1], 1);
    EXPECT_DOUBLE_EQ(v2[2], 2);

    v2[0]++;
    v2[1]++;
    v2[2]++;
    EXPECT_DOUBLE_EQ(v2[0], 1);
    EXPECT_DOUBLE_EQ(v2[1], 2);
    EXPECT_DOUBLE_EQ(v2[2], 3);
    EXPECT_DOUBLE_EQ(v1[0], 0);
    EXPECT_DOUBLE_EQ(v1[1], 1);
    EXPECT_DOUBLE_EQ(v1[2], 2);

    const vector3 v3(v2);
    EXPECT_DOUBLE_EQ(v3[0], 1);
    EXPECT_DOUBLE_EQ(v3[1], 2);
    EXPECT_DOUBLE_EQ(v3[2], 3);
}


TEST_F(VectorTest, Equality) {
    vector3 v1;
    EXPECT_TRUE(v1 == v1);
    EXPECT_FALSE(v1 != v1);

    const vector3 v2(v1);
    EXPECT_TRUE(v1 == v2);

    v1[3] = 0;  // Note: this corrupts memory but should not be range-checked.
    EXPECT_TRUE(v1 == v2);

    v1[0] = 1;
    EXPECT_TRUE(v1 != v2);

    v1 = v2;
    EXPECT_TRUE(v1 == v2);
}

TEST_F(VectorTest, SpaceOps) {
    const double basis[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    const vector3 zero;
    const vector3 x(basis);
    const vector3 y(basis + 3);
    const vector3 z(basis + 6);

    vector3 v1 = -x;
    EXPECT_EQ(v1.toString(), "[-1 -0 -0]");

    EXPECT_EQ((v1 + -v1),  zero); // Tests additive inverse.

    double a = 1, b = 2.5, c = 3;
    vector3 combo1 = x * a + y * b + z * c;
    EXPECT_EQ(combo1.toString(), "[1 2.5 3]");

    vector3 combo2 = a * x + b * y + c * z; // Tests commutativity
    EXPECT_EQ(combo2, combo1);

    vector3 sum = combo1 + combo2;
    EXPECT_EQ(sum, 2 * combo1);
    EXPECT_EQ(sum, combo2 * 2);
    EXPECT_EQ(combo1 - combo2, zero);

    for (double scale = 0; scale < 2.0; scale += 0.2) {
        EXPECT_EQ(scale * sum, sum * scale);
    }

    v1 = zero;
    for (int i = 1; i < 5; ++i) {
        EXPECT_EQ((v1 += x), i * x);
    }
    ((v1 -= x) -= x) -= x;
    EXPECT_EQ(v1, x);

    for (int i = 1; i < 5; ++i)
        EXPECT_EQ((v1 *= 2.0), std::pow(2.0, i) * x);

    v1 = v1 / 2;
    EXPECT_EQ(v1, x * 8);

    (((v1 /= 2) /= 2) /= 2) /= 2;
    EXPECT_EQ(v1, 0.5 * x);
}


template <size_t DIM>
double correctDotProduct(const Vector<DIM>& v1, const Vector<DIM>& v2) {
    double sum = 0;
    for (size_t i = 0; i < DIM; ++i)
        sum += v1[i] * v2[i];
    return sum;
}

// Returns a random double between 0 and max that can be represented exactly via
// IEE 754
double getRandom(int max) {
    int whole = std::rand() % max;
    double fraction = 1.0 / std::pow(2.0, (double) (std::rand() % 10));
    return whole + fraction;
}


TEST_F(VectorTest, DotProduct) {
    const std::string str[] = {"[0 1 2 3]", "[1 2 3 4]", "[2 3 4 5]",
                               "[3 4 5 6]", "[4 5 6 7]", "[5 6 7 8]",
                               "[6 7 8 9]"};

    vector4 vArray[7];
    for (int i = 0; i < 7; ++i) {
        vArray[i] = vector4(data + i);
        EXPECT_EQ(vArray[i].toString(), str[i]);
    }
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            vector4& a = vArray[i];
            vector4& b = vArray[j];
            double dot = correctDotProduct(a, b);
            double leftDot = a.dot(b);
            double rightDot = b.dot(a);
            EXPECT_DOUBLE_EQ(dot, leftDot);
            EXPECT_DOUBLE_EQ(leftDot, rightDot);
            EXPECT_DOUBLE_EQ(dot, a * b);
            EXPECT_DOUBLE_EQ(dot, b * a);
        }
    }
    // Property tests.
    // 1. Commutativity was tested above
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            for (int k = 0; k < 7; ++k) {
                vector4& a = vArray[i];
                vector4& b = vArray[j];
                vector4& c = vArray[k];
                // 2. Distributivity
                EXPECT_EQ((a * (b + c)), (a * b + a * c));
                // 3. Bilinearity (part 1)
                double c1 = getRandom(10);
                EXPECT_EQ((a * ((c1 * b) + c)), ((c1 * (a * b)) + (a * c)));
                // 4. Bilinearity (part 2)
                double c2 = getRandom(10);
                EXPECT_EQ((c1 * a) * (c2 * b), (c1 * c2) * (a * b));
            }
        }
    }
}


template <size_t DIM>
void createBasis(Vector<DIM>* array) {
    for (size_t v = 0; v < DIM; ++v)
        for (size_t comp = 0; comp < DIM; ++comp)
            array[v][comp] = v == comp ? 1 : 0;
}

template <size_t DIM>
Vector<DIM> createVector() {
    Vector<DIM> basis[DIM];
    createBasis(basis);

    Vector<DIM> combo;

    for (size_t i = 0; i < DIM; ++i)
        combo += basis[i] * getRandom(10);
    return combo;
}

template <size_t DIM>
double normSq(const Vector<DIM>& v) {
    double acc = 0;
    for (size_t i = 0; i < DIM; ++i)
        acc += v[i] * v[i];
    return acc;
}

template <size_t DIM>
void testNorm() {
    const vector3 zero;
    assert(zero.norm() == 0);

    Vector<DIM> basis[DIM];
    createBasis(basis);

    for (size_t i = 0; i < DIM; ++i)
        EXPECT_EQ(basis[i].norm(), 1);

    for (int i = 0; i < 100; ++i) {
        Vector<DIM> v = createVector<DIM>();

        double n2 = v.normSq();
        EXPECT_EQ(n2, v * v);
        EXPECT_EQ(n2, normSq(v));
        EXPECT_TRUE(std::abs(v.normalize().norm() - 1) < 0.001);
    }
}

TEST_F(VectorTest, Norm) {
    testNorm<1>();
    testNorm<2>();
    testNorm<3>();
    testNorm<10>();
}

TEST_F(VectorTest, CrossProduct) {
    vector4 v4, v5;
    v4[0] = 1;
    v5[1] = 1;
    EXPECT_THROW({
        v5.cross(v5);
        assert(!"The above should have thrown an exception");
    }, std::domain_error);

    vector3 basis[3];
    createBasis(basis);
    const vector3 zero;
    const vector3 x = basis[0];
    const vector3 y = basis[1];
    const vector3 z = basis[2];
    EXPECT_EQ(x.cross(y), z);

    for (int i = 0; i < 100; ++i) {
        double a1 = getRandom(10);
        double b1 = getRandom(10);
        double c1 = getRandom(10);
        double a2 = getRandom(10);
        double b2 = getRandom(10);
        double c2 = getRandom(10);
        double a3 = getRandom(10);
        double b3 = getRandom(10);
        double c3 = getRandom(10);
        vector3 u = a1 * x + b1 * y + c1 * z;
        vector3 v = a2 * x + b2 * y + c2 * z;
        vector3 w = a3 * x + b3 * y + c3 * z;
        EXPECT_EQ(u.cross(v), (u ^ v));
        EXPECT_EQ((u ^ v), -(v ^ u));
        // Jacobi identity
        EXPECT_EQ((u ^ (v ^ w)) + (v ^ (w ^ u)) + (w ^ (u ^ v)), zero);
    }
}