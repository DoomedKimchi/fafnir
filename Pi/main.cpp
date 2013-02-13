#include <math.h>

#include <iostream>
#include <fstream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <yaml-cpp/yaml.h>

using namespace cv;
using namespace std;

YAML::Node config;
const string config_file = "conf.yaml";

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

/* This function draws rectangles to an image */
void draw_rectangles(vector<vector<Point> > &rectangles,
		     Mat &image) {
  const Point *points;
  int num_points;
  const Scalar RectangleColor =
    Scalar(config["RectangleColor"][0].to<int>(),
	   config["RectangleColor"][1].to<int>(),
	   config["RectangleColor"][2].to<int>());
  const int RectangleThickness = config["RectangleThickness"].to<int>();

  for (size_t i=0; i < rectangles.size(); i++) {
    points = &rectangles[i][0];
    num_points = (int)rectangles[i].size();
    polylines(image, &points, &num_points,
	      1, true, RectangleColor,
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
  vector<vector<Point> > contours, rectangles;

  // load config file
  load_conf(config_file);

  // process image for edge finding
  process_image(image, image_processed);
  // find edges
  findContours(image_processed, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
  cout << "Found " << contours.size() << " contours" << endl;
  // find rectangles from edges
  find_rectangles(contours, rectangles);
  // draw rectangles
  draw_rectangles(rectangles, image);

  cout << "Detected " << rectangles.size() << " rectangles" << endl;

  // show the result
  imshow("Detected Lines", image);

  waitKey(0);

  return 0;
}
