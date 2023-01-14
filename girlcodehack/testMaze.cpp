#define CATCH_CONFIG_MAIN

#include <iostream>
#include <limits.h>
#include <sys/stat.h>
#include <vector>

#include "cs221util/RGBAPixel.h"
#include "cs221util/PNG.h"
#include "cs221util/catch.hpp"

#include "decoder.h"
#include "treasureMap.h"
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

TEST_CASE("treasureMap::basic no cycles", "[weight=1][part=treasureMap]")
{

	PNG maze;
	maze.readFromFile("images/snake.png");
	pair<int,int> start(1,1);

    PNG base;
    base.readFromFile("images/sunshine.png");

    treasureMap M(base, maze, start);

    PNG treasuremaze = M.renderMaze();
	treasuremaze.writeToFile("images/greyedsnakeMYIMAGE.png");
    PNG treasuremazeans;
	treasuremazeans.readFromFile("images/greyedsnake.png");
    REQUIRE( treasuremaze == treasuremazeans );

    PNG treasure = M.renderMap();
	treasure.writeToFile("images/embeddedsnakeMYIMAGE.png");
    PNG treasureans;
    treasureans.readFromFile("images/embeddedsnake.png");
    REQUIRE( treasure == treasureans );


    decoder dec(treasure,start);

    PNG soln = dec.renderSolution();
    soln.writeToFile("images/solnsnakeMYSOLN.png");
    PNG solnans;
    solnans.readFromFile("images/solnsnake.png");
    REQUIRE( soln == solnans );

    PNG solnmaze = dec.renderMaze();
    solnmaze.writeToFile("images/solnsnakemazeMYSOLNTEST.png");
    PNG solnmazeans;
    solnmazeans.readFromFile("images/solnsnakemaze.png");
    REQUIRE( solnmaze == solnmazeans );

    // clothing overlay
    PNG item;
	item.readFromFile("images/shirt.png");

    PNG basecloth;
    basecloth.readFromFile("images/sunshine.png");

    clothingoverlay C(basecloth, item);

    PNG clothingImage = C.renderImage();
	clothingImage.writeToFile("images/clothingoutput.png");
    PNG treasuremazeans1;
	treasuremazeans1.readFromFile("images/greyedsnake.png");
    REQUIRE( clothingImage == treasuremazeans1 );
 

}

TEST_CASE("decoder::basic cycles", "[weight=1][part=decoder]")
{
	PNG maze;
	maze.readFromFile("images/maze.png");
	pair<int,int> start(1,1);

    PNG base;
    base.readFromFile("images/sunshine.png");

    treasureMap M(base, maze, start);

    PNG treasure = M.renderMap();
	//treasure.writeToFile("images/embeddedmaze.png");
    PNG treasureans;
    treasureans.readFromFile("images/embeddedmaze.png");
    REQUIRE( treasure == treasureans );

    PNG treasuremaze = M.renderMaze();
	//treasuremaze.writeToFile("images/greyedmaze.png");
    PNG treasuremazeans;
	treasuremazeans.readFromFile("images/greyedmaze.png");
    REQUIRE( treasuremaze == treasuremazeans );

    decoder dec(treasure,start);

    PNG soln = dec.renderSolution();
    soln.writeToFile("images/solnmazeMYSOLN.png");
    PNG solnans;
    solnans.readFromFile("images/solnmaze.png");
    REQUIRE( soln == solnans );

    PNG solnmaze = dec.renderMaze();
    solnmaze.writeToFile("images/solnmazemazeMYSOLN.png");
    PNG solnmazeans;
    solnmazeans.readFromFile("images/solnmazemaze.png");
    REQUIRE( solnmaze == solnmazeans );

}

