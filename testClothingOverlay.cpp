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

TEST_CASE("test")
{

    // clothing overlay
    PNG item;
	item.readFromFile("images/bodysuit.png");

    PNG basecloth;
    basecloth.readFromFile("images/modelresized.png");

    clothingoverlay C(basecloth, item);

    PNG clothingImage = C.renderImage();
	clothingImage.writeToFile("images/clothingoutput.png");
    PNG treasuremazeans1;
	treasuremazeans1.readFromFile("images/greyedsnake.png");
    REQUIRE( clothingImage == treasuremazeans1 );
 

}