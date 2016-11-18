/*
 * G. Hemingway @2016
 */
#include <fstream>
#include <memory>
#include <gtest/gtest.h>
#include "../include/Visitor.h"
#include "../include/Object.h"
#include "../include/ObjectFactory.h"
#include "../include/Universe.h"
#include "./testHelper.h"
#include "../include/Parser.h"


/**
 *  Returns the next vector in the file.
 */
vector2 getNextVector(std::ifstream &is) {
    vector2 v;
    is >> v[0] >> v[1];
    return v;
}


// The fixture for testing Uniform Circular Motion math.
class UMCTest : public ::testing::Test {};

TEST_F(UMCTest, YearlongTest) {
    std::ifstream file("../tests/testData.txt", std::ifstream::in);
    if (file.fail()) {
        std::cout << "UMCTest not able to open file: ../tests/testData.txt." << std::endl;
        exit(-1);
    } else {
        std::cout << "UMCTest opened file." << std::endl;
    }

    FileCloser closer(file);    // closer will automatically close our file
    const double step = 1;
    const int io = 100;
    std::unique_ptr<Universe> u(Universe::instance());

#ifdef GRADUATE
    Parser parser;
    parser.loadFile("../tests/UCMtest.txt");
#else
    Object* sun = ObjectFactory::makeObject("sun", 1.98892e30);
    vector2 position = makeVector2(149597870700.0, 0);
    vector2 velocity = makeVector2(0, 29788.4676);
    Object* obj = ObjectFactory::makeObject("earth", 5.9742e24, position, velocity);
    u->addObject(sun);
    u->addObject(obj);
#endif

    const double year_s = 31554195.932106005998594489072144;

    int ioCount = 0;
    for (double time = 0; time < year_s; time += step) {
        if (ioCount == io) {
            Object& object = **(++(u->begin()));
            vector2 pos = object.getPosition();
            vector2 check = getNextVector(file);
            assertVector(pos, check, 1000000.0);
            ioCount = 0;
        }
        ioCount++;

        u->stepSimulation(step);
    }
}
