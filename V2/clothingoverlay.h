
#ifndef _CLOTHINGOVERLAY_H
#define _CLOTHINGOVERLAY_H

#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
#include <utility>
#include <vector>
using namespace std;
using namespace cs221util;

class clothingoverlay {

public:

    // Simply initializes member variables. Assumes: 
    //      base and item have the same dimensions.
    //      center is a position on the item.
    //      the item is defined by a collection of 
    //          same-coloured pixels as that of the center.
	clothingoverlay(const PNG & baseim, const PNG & itemim);

	// draws the entire item on a copy of the base image by changing the pixels
    // in the base image to match that of the item image, so that the item appears
    // overtop of the base.
	PNG renderImage();


private:

// changes the colour of the pixel in the baseIm to match that of the pixel
// in the itemIm, at the location loc
void changeColor(PNG & baseIm, PNG & itemIm, pair<int,int> loc);

// ========= private member variables ================

	PNG base; // you can assume that these two images have the same dimensions, and that
	PNG item; // position i,j in one corresponds to position i,j in the other.

};

#endif
