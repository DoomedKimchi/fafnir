#include "vision_includes.hpp"
#include "image_processing.hpp"
#include "target_processing.hpp"

/* This function loads the yaml conf file */
void load_conf(string filename, YAML::Node &config) {
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


int main (int argc, char **argv) {
  /*if (argc < 2) {
    cerr << "No argument provided" << endl;
    return -1;
  }*/

  VideoCapture capture(0);
  // check if video successfully opened
  if (!capture.isOpened())
	  return 1;
  // Get the frame rate
  // double rate = capture.get(CV_CAP_PROP_FPS);
  double rate = 30; /* I hardcoded the frame rate for now
  	  	  	  	  	  because my webcam isn't reporting the
  	  	  	  	  	  frame rate correctly. */
  bool stop(false);
  int delay = 1000/rate;

  Mat image;
/*
  // read image from cli arguments
  image = imread(argv[1], 1);

  if (!image.data) {
    cerr << "No image data" << endl;
    return -1;
  }
*/

  Mat image_processed;
  vector<vector<Point> > contours, rectangles, targets;
  YAML::Node config;
  Point center;
  double hangle, vangle, distance;

  // load config file
  load_conf("conf.yaml", config);


  while (!stop) {
	  // read next frame if any
	  if (!capture.read(image))
		  break;

		// process image for edge finding
		process_image(&config, image, image_processed);
		// find edges
		findContours(image_processed, contours, CV_RETR_LIST,
				CV_CHAIN_APPROX_SIMPLE);
		// find rectangles from edges
		find_rectangles(&config, contours, rectangles);
		// find targets
		find_targets(&config, rectangles, targets);
		// draw rectangles
		draw_targets(&config, rectangles, targets, image);

		cout << "Found " << contours.size() << " contours" << endl;
		cout << "Found " << rectangles.size() << " rectangles" << endl;
		cout << "Found " << targets.size() << " targets" << endl;

		for (size_t i = 0; i < targets.size(); i++) {
			// process targets
			process_target(&config, image.size(), targets[i], center, hangle,
					vangle, distance);
			cout << "Target " << i << ":" << endl;
			cout << "Center: (" << center.x << ", " << center.y << ")" << endl;
			cout << "Distance: " << distance << " cm" << endl;
			cout << "Horizontal angle: " << hangle << " degrees" << endl;
			cout << "Vertical angle: " << vangle << " degrees" << endl;
		}

		// show the result
		imshow("Detected Lines", image);

		//waitKey(0);
		if(waitKey(delay) >= 0)
			stop = true;
	}

  // Close the video file
  capture.release();
  return 0;
}
