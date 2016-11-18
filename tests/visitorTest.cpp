/*
 * G. Hemingway @2016
 */
#include <memory>
#include <gtest/gtest.h>
#include "../include/Visitor.h"
#include "../include/Object.h"
#include "../include/ObjectFactory.h"
#include "../include/Universe.h"
#include "./testHelper.h"
#include "../include/Parser.h"


// The fixture for testing the Visitor class.
class VisitorTest : public ::testing::Test {};

TEST_F(VisitorTest, SimpleVisitor) {
    std::stringstream stream;
    std::unique_ptr<Universe> univ(Universe::instance());
#ifdef GRADUATE
    Parser parser;
    parser.loadFile("../tests/visitorTest.txt");
#else
    ObjectFactory factory;
    univ->addObject(factory.makeObject("H"));
    univ->addObject(factory.makeObject("e"));
    univ->addObject(factory.makeObject("l"));
    univ->addObject(factory.makeObject("l"));
    univ->addObject(factory.makeObject("o"));
#endif

    PrintVisitor printer(stream);
    for (Universe::iterator i = univ->begin(); i != univ->end(); ++i)
        (*i)->accept(printer);

    stream.flush();
    EXPECT_EQ(stream.str(), "Hello");
}
