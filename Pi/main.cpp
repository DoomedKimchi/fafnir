#include <iostream>

#include <cv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

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
    image_blurred, dst, cdst;
  vector<Mat> image_t;

  cvtColor(image, image_hsv, CV_RGB2HSV);

  split(image_hsv, image_t);
  image_value = image_t.at(2);
  threshold(image_value, image_threshold, 200, 255, THRESH_BINARY);
  GaussianBlur(image_threshold, image_blurred, Size(5,5), 5);

  Canny(image_blurred, dst, 50, 200, 3);
  cvtColor(dst, cdst, CV_GRAY2BGR);

  vector<Vec4i> lines;
  Vec4i l;
  HoughLinesP(dst, lines, 1, CV_PI/180, 20, 20, 15);

  for (size_t i=0; i < lines.size(); i++) {
    l = lines[i];
    line(cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255,0,0), 3, CV_AA);
  }

  imshow("Source Image", image_blurred);
  imshow("Detected Lines", cdst);

  waitKey(0);

  return 0;
}
