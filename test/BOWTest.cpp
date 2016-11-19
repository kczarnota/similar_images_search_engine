#include "catch.hpp"
#include "../src/Model/BOW.hpp"


TEST_CASE("Testing visual dictionary")
{
    BOW bow(1000, "/home/konrad/Pulpit/testc++/images", "db");

    REQUIRE(bow.getDatabasePath() == "/home/konrad/Pulpit/testc++/db");
    REQUIRE(bow.getDictionaryPath() == "/home/konrad/Pulpit/testc++/db_dictionary.xml");
}