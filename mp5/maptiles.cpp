/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

Point<3> convertToLAB(HSLAPixel pixel) {
    Point<3> result(pixel.h/360, pixel.s, pixel.l);
    return result;
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
     MosaicCanvas * canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
     vector<Point<3>> points;
     std::map<Point<3>, int> tilemap;
     //Get array of points based off HSLAPixel
     for(unsigned long it = 0; it < theTiles.size(); it++){
       HSLAPixel avg_color = theTiles[it].getAverageColor();
       points.push_back(Point<3>(convertToLAB(avg_color)));
       tilemap.insert(std::make_pair(points[it], it));
     }
     //Make tree of points
     KDTree<3> myTree = KDTree<3>(points);
     //Set canvas to each point
     for(int i =0; i< canvas->getRows(); i++){
       for(int j=0; j< canvas->getColumns(); j++){
         canvas->setTile(i, j, get_match_at_idx(myTree, tilemap, theTiles, theSource, i, j));
       }
     }
    return canvas;
}

TileImage* get_match_at_idx(const KDTree<3>& tree,
                                  map<Point<3>, int> tile_avg_map,
                                  vector<TileImage>& theTiles,
                                  const SourceImage& theSource, int row,
                                  int col)
{
    // Create a tile which accurately represents the source region we'll be
    // using
    HSLAPixel avg = theSource.getRegionColor(row, col);
    Point<3> avgPoint = convertToLAB(avg);
    Point<3> nearestPoint = tree.findNearestNeighbor(avgPoint);

    // Check to ensure the point exists in the map
    map< Point<3>, int >::iterator it = tile_avg_map.find(nearestPoint);
    if (it == tile_avg_map.end())
        cerr << "Didn't find " << avgPoint << " / " << nearestPoint << endl;

    // Find the index
    int index = tile_avg_map[nearestPoint];
    return &theTiles[index];

}
