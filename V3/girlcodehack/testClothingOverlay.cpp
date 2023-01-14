#define CATCH_CONFIG_MAIN

#include <iostream>
#include <limits.h>
#include <sys/stat.h>
#include <vector>

#include "cs221util/RGBAPixel.h"
#include "cs221util/PNG.h"
#include "cs221util/catch.hpp"

#include "clothingoverlay.h"

using namespace std;
using namespace cs221util;


#define IMAGEDIR "images/"
#define SOLNIMGDIR "soln_images/"

/**
 * Test Cases
 * these are just examples of a logical flow similar to 
 * that of main.cpp. We suggest decoupling the embedding
 * tests from the decoding tests, but we leave it to you
 * to do so.
 */

TEST_CASE("test body suit")
{

    // clothing overlay
    PNG item;
	item.readFromFile("images/bodysuit.png");

    PNG basecloth;
    basecloth.readFromFile("images/modelresizednotop.png");

    clothingoverlay C(basecloth, item);

    PNG clothingImage = C.renderImage(120, 0);
	clothingImage.writeToFile("images/outbodysuit.png");
    PNG treasuremazeans1;
	treasuremazeans1.readFromFile("images/greyedsnake.png");
    REQUIRE( clothingImage == treasuremazeans1 );
 

}

TEST_CASE("test crop top")
{
    // clothing overlay
    PNG item;
	item.readFromFile("images/shirt.png");

    PNG basecloth;
    basecloth.readFromFile("images/modelresizednotop.png");

    clothingoverlay C(basecloth, item);

    PNG clothingImage = C.renderImage(221, 98);
	clothingImage.writeToFile("images/outtop.png");
    PNG treasuremazeans1;
	treasuremazeans1.readFromFile("images/greyedsnake.png");
    REQUIRE( clothingImage == treasuremazeans1 );
}

TEST_CASE("test full outfit")
{
    // clothing overlay
    PNG item;
	item.readFromFile("images/pants.png");

    PNG basecloth;
    basecloth.readFromFile("images/outtop.png");

    clothingoverlay C(basecloth, item);

    PNG clothingImage = C.renderImage(163, 295);
	clothingImage.writeToFile("images/outfulloutfit.png");
    PNG treasuremazeans1;
	treasuremazeans1.readFromFile("images/greyedsnake.png");
    REQUIRE( clothingImage == treasuremazeans1 );
}

TEST_CASE("test dress")
{
    PNG item;
	item.readFromFile("images/dress.png");

    PNG basecloth;
    basecloth.readFromFile("images/modelresizednotop.png");

    clothingoverlay C(basecloth, item);

    PNG clothingImage = C.renderImage(120, 120);
	clothingImage.writeToFile("images/outdress.png");
    PNG treasuremazeans1;
	treasuremazeans1.readFromFile("images/greyedsnake.png");
    REQUIRE( clothingImage == treasuremazeans1 );
}