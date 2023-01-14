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

TEST_CASE("clothingoverlay")
{

	PNG base;
	base.readFromFile("images/woman.png");

    PNG item;
    item.readFromFile("images/shirt.png");

    clothingoverlay M(base, item);

    PNG finalImage = M.renderImage();
	finalImage.writeToFile("images/greyedsnakeMYIMAGE.png");
    PNG finalImageans;
	finalImageans.readFromFile("images/greyedsnake.png");
    REQUIRE( finalImage == finalImageans );


}