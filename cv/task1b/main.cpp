#include <iostream>
#include <iomanip>
#include <algorithm>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctime>
#include <math.h>
#include <iostream>
#include <sstream>
#include <fstream>

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/core/core.hpp"

using namespace std;
using namespace cv;

#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

#define FULL_VERSION 1
#define PNG ".png"
#define JPG ".jpg"

#define DIAMETER 15
#define SIGMACOLOR 30
#define SIGMASPACE 50

//================================================================================
// void hist_equal(Mat src, Mat &out)
//--------------------------------------------------------------------------------
// TODO:
//	- implement adaptive histogram equalization
//	- Transform into LAB colorspace and apply the CLAHE algorithm to the L channel
//  - do not forget to set clip limit to default parameter 'clip_lim'
//
// Parameters:
//	- src: the tone mapped image
//	- out: image with adaptive histogram equalization in RGB colorspace
//================================================================================
void hist_equal(Mat src, Mat &out) {

	//--- default clip limit - DO NOT CHANGE THIS
	const int clip_lim = 2;
}

//================================================================================
// void merge_pics(Mat &out, vector<Mat> hdr_images)
//--------------------------------------------------------------------------------
// TODO:
//	- Merge 32 bit float images to a single 8 bit image
//
// Parameters:
//	- hdr_images: the single images that should be merged
//	- out: matrix which contains the merged image
//================================================================================
void merge_pics(Mat &out, vector<Mat> hdr_images) {


}

//================================================================================
// void reinhard05(vector<Mat> &hdr_images_out, vector<Mat> images)
//--------------------------------------------------------------------------------
// TODO: BONUS
//	- perform the tone mapping algorithm reinhard05 on every image in the vector 'images'
//  - 1) transform the images to 32bit float values and normalize them properly, then convert into
//	     right colorspace and split channels
//	- 2) calculate the average and maximal luminance, overall-luminance and average value of
//		 all RGB values per image
//	- 3) calculate specific tone mapping parameters (as described in documentation)
//  - 4) calculate new RGB values for each pixel
//  - 5) normalize RGB values
//  - 6) merge  RGB-channels
//  - 7) after tone mapping, save the output images in the vector 'hdr_images_out'
//		 REMEMBER: the images have to be transformed into right colorspace as we perform the tonemapping operations
//		 on the RGB channels
//
// Parameters:
//	- images: the input images
//	- hdr_images_out: vector which contains the tone-mapped images ( 32bit float values; XYZ-colorspace)
//================================================================================
void reinhard05(vector<Mat> &hdr_images_out, vector<Mat> images) {

	//--- default tone mapping parameters - DO NOT CHANGE THIS
	const float br = 0.0f; 	// brightness
	const float ca = 0.5f; 	// chromatic-adaptation
	const float la = 0.5f;	// light-adaptation

}

//================================================================================
// void drago(vector<Mat> &hdr_images_out, vector<Mat> images)
//--------------------------------------------------------------------------------
// TODO:
//	- perform the tone mapping algorithm on every image in the vector 'images'
//  - 1) transform the images to 32bit float values and normalize, then convert into
//	     right colorspace and split channels
//	- 2) calculate the average and maximal luminance;
//		 don't forget to handle the zero-values properly
//	- 3) perform tone mapping on every pixel
//	- 4) merge channels
//  - 5) after tone mapping, save the output images in the vector 'hdr_images_out'
//
// Parameters:
//	- images: the input images
//	- hdr_images_out: vector which contains the tone-mapped images (32bit float values; XYZ-colorspace)
//================================================================================
void drago(vector<Mat> &hdr_images_out, vector<Mat> images) {

	//--- default tone mapping parameters - DO NOT CHANGE THIS
	const float LOG05 = -0.693147f;
	const float bias = 0.99f;


}

//================================================================================
// main()
//
//================================================================================
int main(int argc, char *argv[]) {
	printf("CV/task1b framework version 1.0\n"); // DO NOT REMOVE THIS LINE!

	if (argc != 2) {
		cout << "Usage: ./cvtask1b <config-file>\n" << endl;
		return -1;
	}

	try {
		cout << "===================================" << endl;
		cout << "               CV Task 1b 2016     " << endl;
		cout << "===================================" << endl;

		// Config and input parameters
		rapidjson::Document cfg;
		FILE* fp = fopen(argv[1], "r");
		char readBuffer[65536];
		rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));

		cfg.ParseStream(is);
		assert(cfg.IsObject());

		const unsigned int num_images = cfg["num_images"].GetInt();
		const string image_path = cfg["image_path"].GetString();
		const string name_image = cfg["name_image"].GetString();

		// Output parameters
		const string out_drago_name_raw = cfg["out_01_drago_raw"].GetString();
		const string out_drago_name = cfg["out_02_drago_tonemap"].GetString();
		const string out_drago_name_equal =
				cfg["out_03_drago_hist_equal"].GetString();
		const string out_drago_name_filtered =
				cfg["out_04_drago_filtered"].GetString();
		const string out_reinhard_name_raw =
				cfg["out_01_reinhard_raw"].GetString();
		const string out_reinhard_name =
				cfg["out_02_reinhard_tonemap"].GetString();
		const string out_reinhard_name_equal =
				cfg["out_03_reinhard_hist_equal"].GetString();

		cout << "reading config file :                DONE" << endl;

		// Input images loaded and stored in vector hdr_images
		vector<Mat> hdr_images;
		for (int i = 1; i <= num_images; i++) {
			string path = image_path + name_image + std::to_string(i) + ".jpg";
			Mat image = imread(path);
			hdr_images.push_back(image);
		}

		cout << "getting input data:                  DONE" << endl;

		// Output images
		Mat drago_raw = Mat::zeros(hdr_images[0].size(), CV_8UC3);
		Mat drago_tonemapped = Mat::zeros(hdr_images[0].size(), CV_8UC3);
		Mat drago_Hist_equal = Mat::zeros(hdr_images[0].size(), CV_8UC3);
		Mat drago_filtered = Mat::zeros(hdr_images[0].size(), CV_8UC3);

		Mat reinhard_raw = Mat::zeros(hdr_images[0].size(), CV_8UC3);
		Mat reinhard_tonemapped = Mat::zeros(hdr_images[0].size(), CV_8UC3);
		Mat reinhard_Hist_equal = Mat::zeros(hdr_images[0].size(), CV_8UC3);

		vector<Mat> hdr_images_out_drago;
		vector<Mat> hdr_images_out_rein;

		//_______________________________________________________
		// TODO:
		//	- implement the method drago(hdr_images_out_drago, hdr_images) to perform
		//    the tonemap algorithm on the different images
		//_______________________________________________________
		drago(hdr_images_out_drago, hdr_images);

		//_______________________________________________________
		// TODO:
		//  - take the first tone mapped image and write it to 'drago_raw'
		//  - remember that the image has to be transformed in RGB colorspace and converted back
		//	  into 8 bit 3 channel RGB image
		//_______________________________________________________
		imwrite(out_drago_name_raw, drago_raw);

		//_______________________________________________________
		// TODO:
		//	- implement the method merge_pics(drago_tonemapped, hdr_images_out_drago)
		//    to merge all tonemapped images
		//_______________________________________________________
		merge_pics(drago_tonemapped, hdr_images_out_drago);
		imwrite(out_drago_name, drago_tonemapped);

		//_______________________________________________________
		// TODO:
		//	- implement the method hist_equal(drago_tonemapped, drago_Hist_equal) to
		//    apply histogram equalization
		//_______________________________________________________
		hist_equal(drago_tonemapped, drago_Hist_equal);
		imwrite(out_drago_name_equal, drago_Hist_equal);

		//_______________________________________________________
		// TODO:
		//	- use the 'drago_Hist_equal' image and perform a bilateral Filter on it
		//	- use the defined parameters DIAMETER, SIGMACOLOR, SIGMASPACE for configuration
		//_______________________________________________________
		imwrite(out_drago_name_filtered, drago_filtered);

		cout << "calculating output with drago:       DONE" << endl;

		//_______________________________________________________
		// TODO: BONUS
		//  - implement the tone mapping algorithm reinhard05
		//  - merging and histogram equalization is the same
		//	  as for the basic task
		//_______________________________________________________
		reinhard05(hdr_images_out_rein, hdr_images);

		//_______________________________________________________
		// TODO: BONUS
		//  - take the first tone mapped image and write in 'reinhard_raw'
		//  - can be solved the same way as for the basic task
		//_______________________________________________________
		imwrite(out_reinhard_name_raw, reinhard_raw);

		// merging pictures - use the method only if you have implemented the bonus task
//		merge_pics(reinhard_tonemapped, hdr_images_out_rein);
		imwrite(out_reinhard_name, reinhard_tonemapped);

		//	histogram equalization - use the method only if you have implemented the bonus task
//		hist_equal(reinhard_tonemapped, reinhard_Hist_equal);
		imwrite(out_reinhard_name_equal, reinhard_Hist_equal);

		cout << "calculating output with reinhard:    DONE" << endl;
	}

	catch (exception &ex) {
		cout << ex.what() << endl;
		cout << "Program exited with errors!" << endl;
		return -1;
	}
	cout << "Program exited normally!" << endl;
	return 0;
}
