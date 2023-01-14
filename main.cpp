
// File:        main.cpp
// Author:      cheeren
// Date:        2021-02-20
// Description: Partial test of PA2 functionality
//


#include "clothingoverlay.h"
#include "cs221util/RGBAPixel.h"
#include "cs221util/PNG.h"

using namespace cs221util;
using namespace std;

int main()
{

	PNG item;
	item.readFromFile("images/shirt.png");

    PNG base;
    base.readFromFile("images/woman.png");

    clothingoverlay M(base, item);

    PNG finalImage = M.renderImage();
	finalImage.writeToFile("images/hacktestim1.png");

  return 0;
}
