#include "clothingoverlay.h"
using namespace std;

clothingoverlay::clothingoverlay(const PNG & baseim, const PNG & itemim)
{
    base = baseim;
    item = itemim;
}

PNG clothingoverlay::renderImage(int xStart, int yStart){
    // creates a copy of the base image
    PNG baseImage = PNG(base);
    int baseHeight = (int) baseImage.height();
    int baseWidth = (int) baseImage.width();

    // creates a copy of the item image
    PNG itemImage = PNG(item);
    int itemHeight = (int) itemImage.height();
    int itemWidth = (int) itemImage.width();

    // determine starting point for overlay
    // based on dimensions of item compared to base image
    // int xStart = ((baseWidth - itemWidth) / 2) - 3;
    // cout << xStart << endl;

    // iterate over all pixels in image,
    // changing pixels in base image to match those of item,
    // for any pixels in item that are not transparent
    for (int i = 0; i < itemWidth; i++){
        for (int j = 0; j < itemHeight; j++){
            pair<int,int> loc;
            loc.first = i + xStart;
            loc.second = j + yStart;
            changeColor(baseImage, itemImage, loc, xStart, yStart);
        }
    }
    
    return baseImage;
}

// change colour of pixel in base image to match that in item image
// at loc, if the alpha value for the pixel in the item is not 0 (transparent)
void clothingoverlay::changeColor(PNG & baseIm, PNG & itemIm, pair<int,int> loc, int xStart, int yStart){
    unsigned int x = (unsigned int) loc.first;
    unsigned int y = (unsigned int) loc.second;
    
    // get baseIm pixel
    RGBAPixel* basePixel = baseIm.getPixel (x,y);

    // get itemIm pixel
    int itemX = x - xStart;
    int itemY = y - yStart;
    RGBAPixel* itemPixel = itemIm.getPixel (itemX,itemY);

    // set basePixel values to itemPixel values
    if (itemPixel->a != 0){
        basePixel->r = itemPixel->r;
        basePixel->g = itemPixel->g;
        basePixel->b = itemPixel->b;
    }
}





