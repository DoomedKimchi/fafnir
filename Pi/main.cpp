#include "vision_includes.hpp"
#include "image_processing.hpp"
#include "target_processing.hpp"
#include "client.hpp"

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

int main(int argc, char **argv) {
  // Use webcam as source by default
  VideoCapture capture;
  double rate;

	int i;
  int gui = 0; // Value for "-g" optional argument to show gui
  int write = 0;
	int host = 0;
	int cam = 0;
	int file = 0;
	int camera = 0;
	char* hostname;
	char* filename;
	int bearingState;

  for (i = 1/*skip argv[0]*/; i < argc; i++) {
	  /*
	   * Use the 'strcmp function to compare the argv values
	   * to a string of your choice (here, it's the optional
	   * argument "-q"). When strcmp returns 0, it means that the 
	   * two strings are identical.
	   */
	  // Process optional arguments
	  if ( (strcmp(argv[i], "-g") == 0) || 
						(strcmp(argv[i], "--gui") == 0) ) 
		  gui = 1; // This is used as a bool
		else if ( (strcmp(argv[i], "-w") == 0) ||
					 	(strcmp(argv[i], "--write") == 0) )
			write = 1;
		else if ( (strcmp(argv[i], "-h") == 0) || 
						(strcmp(argv[i], "--host") == 0) ) {
			host = 1;
			if (i + 1 <= argc -1) {
				i++;
				hostname = argv[i];
			}
			else {
				printf("Usage: -h <host IP>\n");
				return -1;
			}
		}
		else if ( (strcmp(argv[i], "-c") == 0) || 
						(strcmp(argv[i], "--cam") == 0) ) {
				cout << "Using camera: ";
				cam = 1; // used as bool
				if (i + 1 <= argc-1) {
						i++;
						camera = atoi(argv[i]); // convert string to int
						cout << camera << endl;
				}
				else
						printf("Usage: -c <camera number>\n");
		}
		else if ( (strcmp(argv[i], "-f") == 0) ||
						(strcmp(argv[i], "--cam") == 0) ) {
				// video or image file
				cout << "Using video/image file: ";
				file = 1; // used as bool
				if (i + 1 <= argc-1) {
						i++;
						filename = argv[i];
						cout << filename << endl;
				}
		}
	  else {
		  // Process non-optional arguments here
	  }
  }

	if (argc < 2) {
		//usage instructions
	  printf ("Usage: %s <options>\n", argv[0] );
		// need more usage instructions
		return(-1);
	}

	// print what we got from the arguments
	cout << "GUI: " << gui << endl;
	cout << "Write to file: " << write << endl;
	if (host) cout << "Hostname: " << hostname << endl;
	if (cam) cout << "Camera: " << cam << endl;
	if (file) cout << "Filename: " << filename << endl;
	
	// connect to the server (robot) 
	if (host == 0) {
		printf("Not connecting to a server\n");
	}
	else {
 		if(server_connect(hostname)) {
	  	cerr << "Couldn't connect to server" << endl;
			server_disconnect();
  	}
	}

  if (cam) {
    capture.open(camera);
    // On Linux: /dev/video0
    //capture.open(1); // Use /dev/video1
    // Get the frame rate
    rate = 30; /* I hardcoded the frame rate for now
		  because my webcam isn't reporting the
		  frame rate correctly. */
  }
	else if (file) {
    capture.open(filename); // Use video file if specified
    rate = capture.get(CV_CAP_PROP_FPS); // Use frame rate from video file
  }

  // check if video successfully opened
  if (!capture.isOpened())
    cerr << "No input stream" << endl;
  bool stop(false);
  int delay = 1000 / rate;

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
  //load_conf("conf.yaml", config);

  //int counter = 0; //counter for the while loop for debugging purposes

  while (!stop) {
    //cout << "\n\ncounter: " << counter << endl;
    // read next frame if any
    if (!capture.read(image))
      break;

    // process image for edge finding
    process_image(image, image_processed);
    // find edges
    findContours(image_processed, contours, CV_RETR_LIST,
		 CV_CHAIN_APPROX_SIMPLE);
    // find rectangles from edges
    find_rectangles(contours, rectangles);
    // find targets
    find_targets(rectangles, targets);
    // draw rectangles
    draw_targets(rectangles, targets, image);

    //cout << "Image width:" << image.cols << endl;
    //cout << "Image height:" << image.rows << endl;
    //cout << "Image center x:" << (image.cols/2) << endl;

    cout << "Found " << contours.size() << " contours" << endl;
    cout << "Found " << rectangles.size() << " rectangles" << endl;
    cout << "Found " << targets.size() << " targets" << endl;

		if (targets.size() == 0) {
			printf("Target not found\n");
			bearingState = 0;
			printf("bearing state is: %d\n", bearingState);
	  	if (host) server_send(bearingState);
		}

    for (size_t i = 0; i < targets.size(); i++) {
		int img_center;
		int bearing;
      // process targets
      process_target(image.size(), targets[i], center, hangle,
		     vangle, distance);
	  /*
      cout << "Target " << i << ":" << endl;
      cout << "Center: (" << center.x << ", " << center.y << ")" << endl;
      cout << "Distance: " << distance << " cm" << endl;
      cout << "Horizontal angle: " << hangle << " degrees" << endl;
      cout << "Vertical angle: " << vangle << " degrees" << endl;
	  */

	  img_center = (image.cols/2); // not oriented towards saving memory
	  bearing = center.x - img_center; // number of pixels off center of image
	  cout << "Bearing: " << bearing << endl;

      if (center.x >= ((image.cols)/2 + 5))
    	  cout << "Target is on the right" << endl;
      else if (center.x <= ((image.cols)/2 -5))
    	  cout << "Target is on the left" << endl;
      else // +-5 pixel threshold for being aligned
    	  cout << "Target is aligned" << endl;
		if (bearing >= 5) // target is on right
				bearingState = 2;
		if (bearing <= -5) // target on left
				bearingState = 1;
		else if ( (bearing < 5) && (bearing > -5) )
				bearingState = 3; // target aligned
		printf("bearing state: %d\n", bearingState);
	  if (host) server_send(bearingState);
    }

    // show the result
	if (gui)
    	imshow("Detected Lines", image);

    // save result to file
	if (write)
    	imwrite("result.jpg", image);

    contours.clear(); // clear these after each iteration of the while loop or else they will increase exponentially
    rectangles.clear();
    targets.clear();

    //waitKey(0);
    if (waitKey(delay) >= 0)
      stop = true;

    //counter++;
  }

  // Close the video file
  capture.release();
  return 0;
}
