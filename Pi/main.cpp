#include <math.h>
#include <assert.h>

#include <iostream>
#include <fstream>
#include <algorithm>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <yaml-cpp/yaml.h>

using namespace cv;
using namespace std;

YAML::Node config;
const string config_file = "conf.yaml";

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

/* This function finds the angle between three points */
double angle(Point pt1, Point pt2, Point pt0) {
  double dx1 = pt1.x - pt0.x;
  double dy1 = pt1.y - pt0.y;
  double dx2 = pt2.x - pt0.x;
  double dy2 = pt2.y - pt0.y;
  return (dx1*dx2 + dy1*dy2)/
    sqrt((dx1*dx2 + dy1*dy2)*
	 (dx2*dx2 + dy2*dy2) + 1e-10);
}

/* This function loads the yaml conf file */
void load_conf(string filename) {
  ifstream file(filename.c_str());
  if (file.is_open()) {
    YAML::Parser parser(file);
    if (!parser.GetNextDocument(config)) {
      cerr << "Could not load config" << endl;
      exit(-1);
    }
    file.close();
  } else {
    cerr << "Could not open config file" << endl;
    exit(-1);
  }
}

/* This function processes the input image to ready it
   for edge finding */
void process_image(Mat &image_in, Mat &image_out) {
  // image_1 and image_2 are used as
  // intermediaries for the image
  // processing
  Mat image_1, image_2, element;
  vector<Mat> image_split;
  const int dilateElementSize = config["dilateElementSize"].to<int>();
  const int HSVThresholdMin = config["HSVThresholdMin"].to<int>();
  const int HSVThresholdMax = config["HSVThresholdMax"].to<int>();
  const int CannyThreshold1 = config["CannyThreshold1"].to<int>();
  const int CannyThreshold2 = config["CannyThreshold2"].to<int>();
  const int CannyAperatureSize = config["CannyAperatureSize"].to<int>();
  element = getStructuringElement(MORPH_RECT,
				  Size(dilateElementSize*2 + 1,
				       dilateElementSize*2 + 1),
				  Point(dilateElementSize, dilateElementSize));
  cvtColor(image_in, image_1, CV_RGB2HSV);
  split(image_1, image_split);
  image_2 = image_split.at(2);
  threshold(image_2, image_1, HSVThresholdMin,
	    HSVThresholdMax,THRESH_BINARY);
  dilate(image_1, image_2, element);
  pyrDown(image_2, image_1,
	  Size(image_2.cols/2, image_2.rows/2));
  pyrUp(image_1, image_2, image_in.size());
  Canny(image_2, image_out, CannyThreshold1,
	CannyThreshold2, CannyAperatureSize);
  image_split.clear();
  image_1.release();
  image_2.release();
  element.release();
}

/* This function takes the object contours and
   figures out which ones are probably rectangles */
void find_rectangles (vector<vector<Point> > &contours,
		      vector<vector<Point> > &rectangles) {
  vector<Point> approx;
  double maxCosine, cosine;

  const int MinRectangleArea = config["MinRectangleArea"].to<int>();
  const double PolyEpsilonFactor = config["PolyEpsilonFactor"].to<double>();
  const double MaxRectangleCosine = config["MaxRectangleCosine"].to<double>();

  for (size_t i=0; i < contours.size(); i++) {
    approxPolyDP(Mat(contours[i]), approx,
		 arcLength(Mat(contours[i]),
			   true)*PolyEpsilonFactor, true);
    if (approx.size() == 4 &&
	fabs(contourArea(Mat(approx))) > MinRectangleArea &&
	isContourConvex(Mat(approx))) {
      maxCosine = 0;
      for (int j=2; j<5; j++) {
	cosine = fabs(angle(approx[j%4], approx[j-2], approx[j-1]));
	maxCosine = MAX(maxCosine, cosine);
      }
      if (maxCosine < MaxRectangleCosine)
	rectangles.push_back(approx);
    }
  }
}

/* This function finds targets by looking for rectangles
   inside other rectangles */
void find_targets(vector<vector<Point> > &rectangles, vector<vector<Point> > &targets) {
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

/* This function draws rectangles to an image */
void draw_targets(vector<vector<Point> > &rectangles,
		  vector<vector<Point> > &targets,
		  Mat &image) {
  const Point *points;
  int num_points;
  const Scalar RectangleColor =
    Scalar(config["RectangleColor"][0].to<int>(),
	   config["RectangleColor"][1].to<int>(),
	   config["RectangleColor"][2].to<int>());
  const Scalar TargetColor = 
    Scalar(config["TargetColor"][0].to<int>(),
	   config["TargetColor"][1].to<int>(),
	   config["TargetColor"][2].to<int>());
  const int RectangleThickness = config["RectangleThickness"].to<int>();

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

int main (int argc, char **argv) {
  if (argc < 2) {
    cerr << "No argument provided" << endl;
    return -1;
  }
  Mat image;

  // read image from cli arguments
  image = imread(argv[1], 1);

  if (!image.data) {
    cerr << "No image data" << endl;
    return -1;
  }

  Mat image_processed;
  vector<vector<Point> > contours, rectangles, targets;

  // load config file
  load_conf(config_file);

  // process image for edge finding
  process_image(image, image_processed);
  // find edges
  findContours(image_processed, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
  // find rectangles from edges
  find_rectangles(contours, rectangles);
  // find targets
  find_targets(rectangles, targets);
  // draw rectangles
  draw_targets(rectangles, targets, image);

  cout << "Found " << contours.size() << " contours" << endl;
  cout << "Found " << rectangles.size() << " rectangles" << endl;
  cout << "Found " << targets.size() << " targets" << endl;

  // show the result
  imshow("Detected Lines", image);

  waitKey(0);

  return 0;
}
