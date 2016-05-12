#include <iostream>
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "catch.hpp"
#include "../src/PictureDatabase.h"


TEST_CASE("Testing database")
{
    PictureInformation pi1("home/name1");
    pi1.add(2.3);
    pi1.add(2.1);
    pi1.add(2.2);

    PictureInformation pi2("home/name2");
    pi2.add(1.3);
    pi2.add(1.1);
    pi2.add(1.2);

    PictureDatabase db;
    db.addPicture(pi1);
    db.addPicture(pi2);

    std::ofstream ofs("/home/konrad/Dokumenty/CLionProjects/BagOfWords/output");

    boost::archive::text_oarchive oa(ofs);
    oa << db;
    oa.end_preamble();
    ofs.close();

    PictureDatabase db2;
    // create and open an archive for input
    std::ifstream ifs("/home/konrad/Dokumenty/CLionProjects/BagOfWords/output");
    boost::archive::text_iarchive ia(ifs);
    // read class state from archive
    ia >> db2;
    ia.delete_created_pointers();
    ifs.close();

    REQUIRE(db2.getPicture(0).getName() == "home/name1");
    REQUIRE(db2.getPicture(1).getName() == "home/name2");
    REQUIRE(db2.getPicture(0).getElement(0) == 2.3);
    REQUIRE(db2.getPicture(0).getElement(1) == 2.1);
    REQUIRE(db2.getPicture(0).getElement(2) == 2.2);
    REQUIRE(db2.getPicture(1).getElement(0) == 1.3);
    REQUIRE(db2.getPicture(1).getElement(1) == 1.1);
    REQUIRE(db2.getPicture(1).getElement(2) == 1.2);
}

