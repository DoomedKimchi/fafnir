#include "vision_includes.hpp"
#include "target_processing.hpp"

/* Utility functions only used here */

vector<Point> order_vertices(vector<Point> rect) {
  vector<Point> output;
  Point rect_tl, rect_tr, rect_bl, rect_br;

  // find which vertex is the top left one
  // this means the vertex with the smallest sum
  // of coordinates
  size_t minindex = 0;
  int minsum = rect[0].x+rect[0].y;
  for (size_t i = 1; i < rect.size(); i++) {
    if (rect[i].x+rect[i].y < minsum) {
      minindex = i;
      minsum = rect[i].x+rect[i].y;
    }
  }
  rect_tl = rect[minindex];
  // now find bottom right vertex with same procedure
  size_t maxindex = 0;
  int maxsum = rect[0].x+rect[0].y;
  for (size_t i = 1; i < rect.size(); i++) {
    if (rect[i].x+rect[i].y > maxsum) {
      maxindex = i;
      maxsum = rect[i].x+rect[i].y;
    }
  }
  rect_br = rect[maxindex];
  // now we only have two left, so we can
  // tell which one is which by which is
  // higher
  vector<size_t> remaining_indicies;
  // figure out which indicies are remaining
  for (size_t i = 0; i < 4; i++) {
    if (i != minindex && i != maxindex)
      remaining_indicies.push_back(i);
  }
  // there should be two
  assert(remaining_indicies.size() == 2);
  if (rect[remaining_indicies[0]].y > rect[remaining_indicies[1]].y) {
    rect_bl = rect[remaining_indicies[0]];
    rect_tr = rect[remaining_indicies[1]];
  } else {
    rect_bl = rect[remaining_indicies[1]];
    rect_tr = rect[remaining_indicies[0]];
  }
  output.push_back(rect_tl);
  output.push_back(rect_tr);
  output.push_back(rect_br);
  output.push_back(rect_bl);
  return output;
}

bool check_inside(vector<Point> &recto, vector<Point> &recti) {
  assert(recto.size() == 4);
  assert(recti.size() == 4);
  vector<Point> recto_o, recti_o;
  // first work with recto (rectangle outside)
  // get ordered rects first
  recto_o = order_vertices(recto);
  recti_o = order_vertices(recti);
  if (recto_o[0].x < recti_o[0].x &&
      recto_o[0].y < recti_o[0].y &&
      recto_o[1].x > recti_o[1].x &&
      recto_o[1].y < recti_o[1].y &&
      recto_o[2].x > recti_o[2].x &&
      recto_o[2].y > recti_o[2].y &&
      recto_o[3].x < recti_o[3].x &&
      recto_o[3].y > recti_o[3].y)
    // recti is inside of recto,
    // assuming that they aren't rotated too much
    return true;
  // else false
  return false;
}

/* end utility functions */

void find_targets(YAML::Node *config,
		  vector<vector<Point> > &rectangles,
		  vector<vector<Point> > &targets) {
  vector<set<size_t> > checked;
  set<size_t> test_case;
  size_t size = rectangles.size();
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      test_case = {i,j};
      // skip if we're checking a rectangle against itself
      if (i == j) continue;
      // skip if we've already checked this one
      if (count(checked.begin(), checked.end(), test_case) > 0) continue;
      // add this rectangle to the checked list
      checked.push_back(test_case);
      // check if one is inside of the other
      // take the one that is inside to be
      // the target rectangle
      if (check_inside(rectangles[i], rectangles[j]))
	targets.push_back(rectangles[j]);
      else if (check_inside(rectangles[j], rectangles[i]))
	targets.push_back(rectangles[i]);
    }
  }
}

void draw_targets(YAML::Node *config,
		  vector<vector<Point> > &rectangles,
		  vector<vector<Point> > &targets,
		  Mat &image) {
  const Point *points;
  int num_points;
  const Scalar RectangleColor =
    Scalar(config->FindValue("RectangleColor")->FindValue(0)->to<int>(),
	   config->FindValue("RectangleColor")->FindValue(1)->to<int>(),
	   config->FindValue("RectangleColor")->FindValue(2)->to<int>());
  const Scalar TargetColor = 
    Scalar(config->FindValue("TargetColor")->FindValue(0)->to<int>(),
	   config->FindValue("TargetColor")->FindValue(1)->to<int>(),
	   config->FindValue("TargetColor")->FindValue(2)->to<int>());
  const int RectangleThickness = config->FindValue("RectangleThickness")->to<int>();

  for (size_t i=0; i < rectangles.size(); i++) {
    if (count(targets.begin(), targets.end(), rectangles[i]) > 0) continue;
    points = &rectangles[i][0];
    num_points = (int)rectangles[i].size();
    polylines(image, &points, &num_points,
	      1, true, RectangleColor,
	      RectangleThickness, CV_AA);
  }

  for (size_t i = 0; i < targets.size(); i++) {
    points = &targets[i][0];
    num_points = (int)targets[i].size();;
    polylines(image, &points, &num_points,
	      1, true, TargetColor,
	      RectangleThickness, CV_AA);
  }
}
