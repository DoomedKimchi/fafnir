#ifndef __vision_includes_hpp__
#define __vision_includes_hpp__
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

#define dilateElementSize 5
#define HSVThresholdMin: 200
#define HSVThresholdMax 255
#define CannyThreshold1 50
#define CannyThreshold2 200
#define CannyAperatureSize 3
#define MinRectangleArea 1000
#define MaxRectangleCosine 0.3
#define PolyEpsilonFactor 0.02
#define RectangleColorR 0
#define RectangleColorG 0
#define RectangleColorB 255
#define TargetColorR 0
#define TargetColorG 255
#define TargetColorB 255
#define RectangleThickness 3
#define TargetWidth 137.16

// these values need to be calibrated for each camera
#define PixelToCM 1.791451063459854
#define DistanceAtFull 30

#endif
