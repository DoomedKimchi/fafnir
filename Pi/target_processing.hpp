#ifndef __target_processing_hpp__
#define __target_processing_hpp__
#include "vision_includes.hpp"

/* This function finds targets by looking for rectangles
   inside other rectangles */
void find_targets(YAML::Node *config,
		  vector<vector<Point> > &rectangles,
		  vector<vector<Point> > &targets);


/* This function draws rectangles to an image */
void draw_targets(YAML::Node *config,
		  vector<vector<Point> > &rectangles,
		  vector<vector<Point> > &targets,
		  Mat &image);

#endif
