/*
 * G. Hemingway @2016
 */
#include <memory>
#include <gtest/gtest.h>
#include "../include/Visitor.h"
#include "../include/Object.h"
#include "../include/Universe.h"
#include "../include/ObjectFactory.h"
#include "./testHelper.h"
#include "../include/Parser.h"


// The fixture for testing the Inertia math.
class InertiaTest : public ::testing::Test {};

TEST_F(InertiaTest, FreeBodyTest) {
    std::unique_ptr<Universe> univ(Universe::instance());
#ifdef GRADUATE
    Parser parser;
    parser.loadFile("../tests/inertiaTest.txt");
    vector2 velocity = (**(++(univ->begin()))).getVelocity();
    vector2 position = (**(++(univ->begin()))).getPosition();
#else
    // Create a sun with zero mass, stationary at origin
    Object* sun = ObjectFactory::makeObject("sun", 0);
    // Make an object with mass=100, positioned at 100,100, with a velocity of 100,0
    vector2 velocity = makeVector2(100, 0);
    vector2 position = makeVector2(100, 100);
    Object* body = ObjectFactory::makeObject("obj", 100, position, velocity);
    univ->addObject(sun);
    univ->addObject(body);
#endif
    // Lets run the simulation forward 50 time steps
    for(int step = 0; step < 50; ++step) {
        const Object &obj = **(++(univ->begin()));
        assertVector(obj.getPosition(), position);
        univ->stepSimulation(1);
        position += velocity;
    }
}
