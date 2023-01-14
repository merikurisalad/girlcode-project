#include "treasureMap.h"
#include "queue.h"
using namespace std;

treasureMap::treasureMap(const PNG & baseim, const PNG & mazeim, pair<int,int> s)
{
    base = baseim;
    maze = mazeim;
    start = s;

}

void treasureMap::setGrey(PNG & im, pair<int,int> loc){
    unsigned int x = (unsigned int) loc.first;
    unsigned int y = (unsigned int) loc.second;
    // pixel at loc coordinates
    RGBAPixel* pixel = im.getPixel(x,y);

    // new colour channel values
    int newR = 2*(pixel->r /4);
    int newG = 2*(pixel->g /4);
    int newB = 2*(pixel->b /4);

    // set colour channel values to new values
    pixel->r = newR;
    pixel->g = newG;
    pixel->b = newB;

}

void treasureMap::setLOB(PNG & im, pair<int,int> loc, int d){
// get pixel
unsigned int x = (unsigned int) loc.first;
unsigned int y = (unsigned int) loc.second;
RGBAPixel* pixel = im.getPixel (x,y);

d = (unsigned int) d%64;
// get individual bits of maze value for each colour channel 
unsigned int b1b2 = (d & 0b00110000) >> 4;           // red channel
unsigned int b3b4 = (d & 0b00001100) >> 2;           // green channel
unsigned int b5b6 = d & 0b00000011;                  // blue channel

// set two lowest order bits for each color channel to 0
pixel->r = pixel->r & 0b0011111100;
pixel->g = pixel->g & 0b0011111100;
pixel->b = pixel->b & 0b0011111100;

// set two lowest order bits for each colour channel
// to appropriate maze value
pixel->r = pixel->r | b1b2;
pixel->g = pixel->g | b3b4;
pixel->b = pixel->b | b5b6;
}

PNG treasureMap::renderMap(){
    // creates a copy of the base map
    PNG map = PNG(base);
    int height = (int) maze.height();
    int width = (int) maze.width();

    // visited table
    // 2D vector array
    //  - value is false if coordinate has not yet been visited
    //  - value is true if coordinate has been visited already (maze has made a loop)
    vector<vector<bool>> v;
    v.resize(width);
    for (int x = 0; x <  width; x++){
        v[x].resize(height);
        for (int y = 0; y < height; y++) {
            v[x][y] = false;
        }
    }

    // shortest path table
    // 2D vector array
    // values are integers that store the length of the shortest path
    // between current location and the start location
    vector<vector<int>> shortestPaths(width, vector<int>(height,0));

    // list of coordinates that correspond to the maze
    Queue <pair<int,int>> mazeList;

    // initialize variables in while loop
    pair<int,int> curr = start;
    v[curr.first][curr.second] = true;
    shortestPaths[curr.first][curr.second] = 0;
    setLOB(map, curr, 0);
    mazeList.enqueue(curr);

    // iterate over map until mazeList is empty
    // adding each neighbor to mazeList if it meets criteria
    while (!mazeList.isEmpty()){
        curr = mazeList.dequeue();
        vector<pair<int,int>> neighborList = neighbors(curr);

        // for each neighbor, if it meets criteria for maze, add it to mazeList
        // and darken it on map
        for (int i = 0; i < 4 ; i++ ){
            if (good(v, curr, neighborList[i])) {
                v[neighborList[i].first][neighborList[i].second] = true;
                int d = shortestPaths[curr.first][curr.second];
                d += 1;
                shortestPaths[neighborList[i].first][neighborList[i].second] = d;
                setLOB(map, neighborList[i], d);
                mazeList.enqueue(neighborList[i]);
            }
        }
    }

    return map;
}

PNG treasureMap::renderMaze(){
    // creates a copy of the base map
    PNG map = PNG(base);
    int height = (int) map.height();
    int width = (int) map.width();

    // list of coordinates that correspond to the maze
    Queue <pair<int,int>> mazeList;

    // visited table
    // 2D vector array
    //  - value is false if coordinate has not yet been visited
    //  - value is true if coordinate has been visited already (maze has made a loop)
    vector<vector<bool>> v;
    v.resize(width);
    for (int x = 0; x <  width; x++){
        v[x].resize(height);
        for (int y = 0; y < height; y++) {
            v[x][y] = false;
        }
    }

    // initialize variables in while loop
    pair<int,int> curr = start;
    mazeList.enqueue(curr);
    // iterate over maze map until mazeList is empty
    // adding each neighbor to mazeList if it meets criteria
    while (!mazeList.isEmpty()){
        curr = mazeList.dequeue();
        vector<pair<int,int>> neighborList = neighbors(curr);

        // for each neighbor, if it meets criteria for maze, add it to mazeList
        // and darken it on map
        for (int i = 0; i < 4 ; i++ ){
            if (good(v, curr, neighborList[i])) {
                v[neighborList[i].first][neighborList[i].second] = true;
                mazeList.enqueue(neighborList[i]);
                setGrey(map, neighborList[i]);
            }
        }
    }

    // draw 7x7 red square around start
    Queue <pair<int,int>> redSquare;
    curr = start;
    pair <int, int> topLeft (curr.first - 3, curr.second - 3);
    pair <int, int> topRight (curr.first + 3, curr.second - 3);
    pair <int, int> bottomLeft (curr.first - 3, curr.second + 3);
    pair <int, int> bottomRight (curr.first + 3, curr.second + 3);

    for (int y = topLeft.second; y <= bottomRight.second; y++){
        for (int x = topLeft.first; x <= topRight.first; x++){
            if (x >= 0 && y >= 0){
                RGBAPixel* pixel = map.getPixel(x,y);
                pixel->r = 255;
                pixel->g = 0;
                pixel->b = 0;
            }
        }
    }

    return map;
}

bool treasureMap::good(vector<vector<bool>> & v, pair<int,int> curr, pair<int,int> next){

unsigned int imageWidth = maze.width();
unsigned int imageHeight = maze.height();
unsigned int nextX = (unsigned int) next.first;
unsigned int nextY = (unsigned int) next.second;
unsigned int currX = (unsigned int) curr.first;
unsigned int currY = (unsigned int) curr.second;
RGBAPixel* currPix = maze.getPixel(currX, currY);
RGBAPixel* nextPix;
bool nextV;

// checks that nextPix we are getting is within image height and width
if (nextX < imageWidth && nextY < imageHeight){
    nextPix = maze.getPixel(nextX, nextY);
    nextV = v[next.first][next.second];
} else {
    // pixel not within image bounds, break and return false
    return false;
}

bool result = false;

// other criteria for if next is "good" (AKA- it should be explored)
if (currPix->a == nextPix->a &&
    currPix->r == nextPix->r &&
    currPix->g == nextPix->g &&
    currPix->b == nextPix->b &&
    nextV == false) {
        result = true;
    }

return result;

}

vector<pair<int,int>> treasureMap::neighbors(pair<int,int> curr) {
    int x = curr.first;
    int y = curr.second;

    // left
    pair<int,int> left;
    left.first = x - 1;
    left.second = y;

    // below
    pair<int,int> below;
    below.first = x;
    below.second = y + 1;

    // right
    pair<int,int> right;
    right.first = x + 1;
    right.second = y;

    // above
    pair<int,int> above;
    above.first = x;
    above.second = y - 1;

    vector<pair<int,int>> result;
    result.push_back(left);
    result.push_back(below);
    result.push_back(right);
    result.push_back(above);
    
    return result;
}

