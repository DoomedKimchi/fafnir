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

int main(int argc, char **argv) {
	bool gui = false; // Value for "-g" optional argument to show gui
	bool write = false;
	bool host = false;
	bool port = false;
	bool cam = false;
	bool file = false;

	int camera;
	int portno;
	char* hostname;
	char* filename;

	for (int i = 1/*skip argv[0]*/; i < argc; i++) {
		/* Process optional arguments */
		if ( (strcmp(argv[i], "-g") == 0) ||
				(strcmp(argv[i], "--gui") == 0) ) {
			/* Show graphical output */
			gui = true;
			cout << "Using GUI" << endl;
		}
		else if ( (strcmp(argv[i], "-w") == 0) ||
				(strcmp(argv[i], "--write") == 0) )
			write = true;
		else if ( (strcmp(argv[i], "-h") == 0) ||
				(strcmp(argv[i], "--host") == 0) ) {
			host = true;
			if (i + 1 <= argc - 1) {
				hostname = argv[i++];
			}
			else {
				cout << RED << "USAGE: -h <host IP>" << RESET << endl;
				return EX_USAGE;
			}
		}
		else if ( (strcmp(argv[i], "-p") == 0) ||
				(strcmp(argv[i], "--port") == 0) ) {
			port = true;
			if (i + 1 <= argc -1)
				sscanf(argv[++i], "%d", &portno);
			else {
				cout << RED << "USAGE: -p <port number>" << RESET << endl;
				return EX_USAGE;
			}
		}
		/* Process required arguments */
		else if ( (strcmp(argv[i], "-c") == 0) ||
				(strcmp(argv[i], "--cam") == 0) ) {
			/* Live webcam */
			cam = 1; // used as bool
			if (i + 1 <= argc-1) {
				sscanf(argv[++i], "%d", &camera);
				cout << "Using camera: /dev/video" << camera << endl;
			}
			else {
				cout << RED << "USAGE: -c <camera number>" << endl;
				return EX_USAGE;
			}
		}
		else if ( (strcmp(argv[i], "-f") == 0) ||
				(strcmp(argv[i], "--cam") == 0) ) {
			/* Video or image file */
			file = 1; // used as bool
			if (i + 1 <= argc-1) {
				filename = argv[++i];
				cout << "Using video/image file: " << filename << endl;
			}
			else {
				cout << RED << "USAGE: -f <media filename" << RESET << endl;
				return EX_USAGE;
			}
		}
	}

	if (argc < 2) {
		/* Usage instructions */
		cout << RED << "USAGE: " << argv[0] << " <options>" << RESET << endl;
		// need more usage instructions
		return EX_USAGE;
	}
	if (port && !host) {
		cout << RED << "Please specify a hostname" << RESET << endl;
		return EX_USAGE;
	}
	else if (!port && host) {
		cout << RED << "Please specify a port number" << RESET << endl;
		return EX_USAGE;
	}
	else if (!file && !cam) {
		cout << RED << "Please specify either a camera or media file" << RESET << endl;
		return EX_USAGE;
	}

	/* Print what we got from the arguments */
	cout << "GUI: " << gui << endl;
	cout << "Write to file: " << write << endl;
	if (host) cout << "Hostname: " << hostname << endl;
	if (port) cout << "Port Number: " << portno << endl;
	if (cam) cout << "Camera: " << camera << endl;
	if (file) cout << "Filename: " << filename << endl;


	VideoCapture capture;
	double rate; /* Framerate */

	if (cam) {
		capture.open(camera);
		/* Get the frame rate */
		rate = 30; /* I hardcoded the frame rate for now
					  because my webcam isn't reporting the
					  frame rate correctly. */
	}
	else if (file) {
		capture.open(filename); // Use video/image file if specified
		rate = capture.get(CV_CAP_PROP_FPS); // Use frame rate from video file
	}

	// check if video successfully opened
	if (!capture.isOpened()) {
		cout << RED << "No input stream" << RESET << endl;
		return EX_NOINPUT;
	}
	bool stop(false);
	int delay = 1000 / rate;

	Mat image;
	Mat image_processed;

	vector<vector<Point> > contours, rectangles, targets;
	Point center;
	double hangle, vangle, distance;

	YAML::Node config;
	/* Load config file */
	load_conf("conf.yaml", config);

	for (int frame_count = 0; !stop; frame_count++) {
		//cout << "\n\nFrame: " << frame_count << endl; /* Uncomment to display frame count */
		/* Read next frame, if any */
		if (!capture.read(image))
			break;

		/* Process image for edge finding */
		process_image(&config, image, image_processed);
		/* Find edges */
		findContours(image_processed, contours, CV_RETR_LIST,
				CV_CHAIN_APPROX_SIMPLE);
		/* Find rectangles from edges */
		find_rectangles(&config, contours, rectangles);
		/* Find targets */
		find_targets(&config, rectangles, targets);
		/* Draw rectangles */
		draw_targets(&config, rectangles, targets, image);

		//cout << "Image width:" << image.cols << endl;
		//cout << "Image height:" << image.rows << endl;
		//cout << "Image center x:" << (image.cols/2) << endl;

		cout << "Found " << contours.size() << " contours" << endl;
		cout << "Found " << rectangles.size() << " rectangles" << endl;
		cout << "Found " << targets.size() << " targets" << endl;

		if (targets.size() == 0) {
			printf("Target not found\n");
		}

		vector<Point> center_target;

		if (targets.size() > 0) {
			/* Select target nearest to the center */
			select_target(&config, targets, center_target, image);
			/* Process center target */
			process_target(&config, image.size(), center_target, center, hangle, vangle, distance);

			int bearing;

			bearing = center.x - image.cols/2; // number of pixels off center of image
			cout << "Bearing: " << bearing << endl;

			if (center.x >= ((image.cols)/2 + 5))
				cout << "Target is on the right" << endl;
			else if (center.x <= ((image.cols)/2 -5))
				cout << "Target is on the left" << endl;
			else // +-5 pixel threshold for being aligned
				cout << "Target is aligned" << endl;
		}

		/* Show the result */
		if (gui)
			imshow("Detected Lines", image);

		/* Save result to file */
		if (write)
			imwrite(filename, image);

		contours.clear(); // clear these after each iteration of the while loop or else they will increase exponentially
		rectangles.clear();
		targets.clear();

		//waitKey(0);
		if (waitKey(delay) >= 0)
			stop = true;

		//counter++;
	}
	if (gui) {
		cout << endl << "Press any key to exit" << endl;
		waitKey();
	}

	/* Close the video file */
	capture.release();
	return 0;
}
