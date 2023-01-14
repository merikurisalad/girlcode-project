#include "decoder.h"
#include "queue.h"
#include "stack.h"
#include <bits/stdc++.h>
using namespace std;

// need to populate vector<pair<int,int>> pathPts
decoder::decoder(const PNG & tm, pair<int,int> s)
   :start(s),mapImg(tm) {

    int height = (int) mapImg.height();
    int width = (int) mapImg.width();

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

    // path coord table
    // 2D vector array
    // values are pair<int,int> that store the coordinate from which
    // the current location was discovered
    pair<int,int> defaultCoord(0,0);
    vector<vector<pair<int,int>>> pathCoords(width, vector<pair<int,int>>(height,defaultCoord));

    // list of coordinates that correspond to the maze
    Queue <pair<int,int>> mazeList;

    // initialize variables in while loop
    pair<int,int> curr = start;
    v[curr.first][curr.second] = true;
    shortestPaths[curr.first][curr.second] = 0;
    pathCoords[curr.first][curr.second] = curr;
    mazeList.enqueue(curr);

    // iterate over mapImg until mazeList is empty
    // adding each neighbor to mazeList if it meets criteria
    while (!mazeList.isEmpty()){
       curr = mazeList.dequeue();
       vector<pair<int,int>> neighborList = neighbors(curr);

       // for each neighbor, if it meets criteria for maze, add it to mazeList
        for (int i = 0; i < 4 ; i++ ){
            int dist = shortestPaths[curr.first][curr.second];
            dist += 1;
            if (good(v, shortestPaths, curr, neighborList[i])) {
               v[neighborList[i].first][neighborList[i].second] = true;
               shortestPaths[neighborList[i].first][neighborList[i].second] = dist;
               pathCoords[neighborList[i].first][neighborList[i].second] = curr;
               mazeList.enqueue(neighborList[i]);
            }
        }
    }

    // at this point we have table shortestPaths
    // we need to find the largest value in shortestPaths
    pair<int,int> treasure = findSpot(shortestPaths);

    // NOTE TO LINDA: probs need to make a list of all 
    // possible paths to treasure from start
    // and then pick the shortest one to be pathPts
    // for now, just pick the path using the pathCoords list
    // this should work for snake
    curr = treasure;
    pair<int,int> next;
    while (curr.first != start.first || curr.second != start.second) {
        pathPts.push_back(curr);
        next = pathCoords[curr.first][curr.second];
        curr = next;
    }
    pathPts.push_back(start);
    // reverse pathPts
    reverse(pathPts.begin(), pathPts.end());
    cout << "pathPts[0]: " << pathPts[0].first << " , " << pathPts[0].second << endl;
    cout << "pathPts[1]: " << pathPts[1].first << " , " << pathPts[1].second << endl;
    cout << "pathPts[2]: " << pathPts[2].first << " , " << pathPts[2].second << endl;
    cout << "pathPts[3]: " << pathPts[3].first << " , " << pathPts[3].second << endl;
}

PNG decoder::renderSolution(){
    // creates a copy of the base map
    PNG map = PNG(mapImg);
    int length = (int) pathPts.size();
    for (int i = 0; i < length; i++){
        setRed(map, pathPts[i]);
    }
    return map;
}

PNG decoder::renderMaze(){
    // created a copy of the base map
    PNG map = PNG(mapImg);
    int height = (int) map.height();
    int width = (int) map.width();

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
   setGrey(map, curr);
   mazeList.enqueue(curr);

   // iterate over mapImg until mazeList is empty
   // adding each neighbor to mazeList if it meets criteria
   while (!mazeList.isEmpty()){ 
      curr = mazeList.dequeue();
      vector<pair<int,int>> neighborList = neighbors(curr);

      // for each neighbor, if it meets criteria for maze, add it to mazeList
      // and darken it on mapImg

      for (int i = 0; i < 4 ; i++ ){
         int dist = shortestPaths[curr.first][curr.second];
         dist += 1;
         if (good(v, shortestPaths, curr, neighborList[i])) {
            v[neighborList[i].first][neighborList[i].second] = true;
            shortestPaths[neighborList[i].first][neighborList[i].second] = dist;
            setGrey(map, neighborList[i]);
            mazeList.enqueue(neighborList[i]);
         }
      }
   }

   // draw 7x7 red square around start
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

void decoder::setGrey(PNG & im, pair<int,int> loc){
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

void decoder::setRed(PNG & im, pair<int,int> loc){
    unsigned int x = (unsigned int) loc.first;
    unsigned int y = (unsigned int) loc.second;
    // pixel at loc coordinates
    RGBAPixel* pixel = im.getPixel(x,y);

    // set colour channel values to new values
    pixel->r = 255;
    pixel->g = 0;
    pixel->b = 0;
}

// returns last coordinate pair from pathPts
pair<int,int> decoder::findSpot(){
    int size = pathPts.size();
    return pathPts[size-1];
}

// finds largest value in d
// returns coordinate that corresponds to that value
pair<int,int> decoder::findSpot(vector<vector<int>> & d){
    int height = (int) mapImg.height();
    int width = (int) mapImg.width();
    pair<int,int> result(0,0);
    int maxValue = 0;
    for (int x = 0; x < width; x++){
        for (int y = 0; y < height; y++){
            if (d[x][y] > maxValue){
                maxValue = d[x][y];
                result.first = x;
                result.second = y; 
            }
        }
    }
    return result;
}

int decoder::pathLength(){
    return pathPts.size();
}

bool decoder::good(vector<vector<bool>> & v, vector<vector<int>> & d, pair<int,int> curr, pair<int,int> next){
unsigned int imageWidth = mapImg.width();
unsigned int imageHeight = mapImg.height();
unsigned int nextX = (unsigned int) next.first;
unsigned int nextY = (unsigned int) next.second;
RGBAPixel* nextPix;
bool nextV;

// checks that nextPix we are getting is within image height and width
if (nextX < imageWidth && nextY < imageHeight){
    nextPix = mapImg.getPixel(nextX, nextY);
    nextV = v[next.first][next.second];
} else {
    // pixel not within image bounds, break and return false
    return false;
}

// other criteria for if next is "good" (AKA - it's part of the maze path)
if (nextV == false &&
   compare(nextPix, d[curr.first][curr.second])) {
      return true;
}

return false;

}

vector<pair<int,int>> decoder::neighbors(pair<int,int> curr) {
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

// tests whether p's lower order bits, when interpreted as a
// number, is d+1 (mod 64).
bool decoder::compare(RGBAPixel* p, int d){
// get two lowest order bits of each color channel and shift appropriately
unsigned int b1b2 = (p->r & 0b00000011) << 4;      // red channel
unsigned int b3b4 = (p->g & 0b00000011) << 2;      // green channel
unsigned int b5b6 = p->b & 0b00000011;              // blue channel

// create one cohesive maze value
unsigned int mazeValue = b1b2 | b3b4 | b5b6;

// do comparison
d = (d+1)%64;
if (d == (int) mazeValue) {
   return true;
}
return false;

}
