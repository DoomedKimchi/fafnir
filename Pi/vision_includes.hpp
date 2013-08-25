#ifndef __vision_includes_hpp__
#define __vision_includes_hpp__
#include <math.h>
#include <assert.h>
#include <sysexits.h>
#include <ctime>

#include <iostream>
#include <fstream>
#include <algorithm>

/* OpenCV */
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <yaml-cpp/yaml.h>

using namespace cv;
using namespace std;

/* Bash color codes, non-portable */
#define RESET  "\033[0m"
#define RED	   "\033[31m" /* Red */

#endif
