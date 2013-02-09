#include <math.h>

#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

double angle(Point pt1, Point pt2, Point pt0) {
  double dx1 = pt1.x - pt0.x;
  double dy1 = pt1.y - pt0.y;
  double dx2 = pt2.x - pt0.x;
  double dy2 = pt2.y - pt0.y;
  return (dx1*dx2 + dy1*dy2)/
    sqrt((dx1*dx2 + dy1*dy2)*
	 (dx2*dx2 + dy2*dy2) + 1e-10);
}

int main (int argc, char **argv) {
  if (argc < 2) {
    cerr << "No argument provided" << endl;
    return -1;
  }
  Mat image;

  image = imread(argv[1], 1);

  if (!image.data) {
    cerr << "No image data" << endl;
    return -1;
  }

  Mat image_hsv, image_value, image_threshold,
    image_dilated, image_downscaled, dst, element, image_final;
  vector<Mat> image_t;

  element = getStructuringElement(MORPH_RECT, Size(11,11), Point(5,5));

  cvtColor(image, image_hsv, CV_RGB2HSV);

  split(image_hsv, image_t);
  image_value = image_t.at(2);
  threshold(image_value, image_threshold, 200, 255, THRESH_BINARY);
  dilate(image_threshold, image_dilated, element);
  pyrDown(image_dilated, image_downscaled,
	  Size(image_dilated.cols/2, image_dilated.rows/2));
  pyrUp(image_downscaled, image_final, image_dilated.size());
  Canny(image_final, dst, 50, 200, 3);

  vector<vector<Point> > contours, squares;
  vector<Point> approx;
  double maxCosine, cosine;
  const Point *p;
  int n;
  findContours(dst, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

  for (size_t i=0; i < contours.size(); i++) {
    approxPolyDP(Mat(contours[i]), approx,
		 arcLength(Mat(contours[i]), true)*.02, true);
    if (approx.size() == 4 &&
	fabs(contourArea(Mat(approx))) > 100 &&
	isContourConvex(Mat(approx))) {
      maxCosine = 0;
      for (int j=2; j<5; j++) {
	cosine = fabs(angle(approx[j%4], approx[j-2], approx[j-1]));
	maxCosine = MAX(maxCosine, cosine);
      }
      if (maxCosine < 0.3)
	squares.push_back(approx);
    }
  }

  cout << "Detected " << squares.size() << " squares" << endl;

  for (size_t i=0; i < squares.size(); i++) {
    p = &squares[i][0];
    n = (int)squares[i].size();
    polylines(image, &p, &n, 1, true, Scalar(0,0,255), 3, CV_AA);
  }

  imshow("Detected Lines", image);

  waitKey(0);

  return 0;
}
