

#include <iostream>
#include <time.h>

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

/**
    Prints the usage message to std::cout.

    @return always -1
*/
int readme()
{
    std::cout << "Usage: ./cvtask1a <config-file>" << std::endl;
    return -1;
}


int main(int argc, char** argv)
{
    std::cout << "CV/task1a framework version 1.0" << std::endl;  // DO NOT REMOVE THIS LINE!!!

    if (argc != 2) 	return readme();
    try
    {
      std::cout << "Running TC: " << argv[1] << std::endl;

      rapidjson::Document cfg;
      FILE* fp = fopen(argv[1], "r");
      char readBuffer[65536];
      rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));

      cfg.ParseStream(is);
      assert(cfg.IsObject());
      

      const string input_path = cfg["input_path"].GetString();

      // Edge Parameters
      const int edge_threshold = cfg["edge_threshold"].GetInt();

      // Matching parameters
      const int match_window_size = cfg["matching_window_size"].GetInt();

      //Output parameters
      const string out_b_edge_filename = cfg["out_01_edges_B"].GetString();
      const string out_g_edge_filename = cfg["out_01_edges_G"].GetString();
      const string out_r_edge_filename = cfg["out_01_edges_R"].GetString();

      const string out_g_transformed_filename = cfg["out_02_warped_G"].GetString();
      const string out_b_transformed_filename = cfg["out_02_warped_B"].GetString();

      const string out_combined_image_filename = cfg["out_03_combined"].GetString();

      const string out_cropped_image_filename = cfg["out_04_cropped"].GetString(); 
  
      // Input Images
      // - We will expect to have files named 01.png (R), 02.png (G) and 03.png (B) in the specified folder.
      Mat img_r = imread(input_path + "/01.png", CV_LOAD_IMAGE_GRAYSCALE);
      Mat img_g = imread(input_path + "/02.png", CV_LOAD_IMAGE_GRAYSCALE);
      Mat img_b = imread(input_path + "/03.png", CV_LOAD_IMAGE_GRAYSCALE);

      // Edge Images
      Mat img_r_edge = Mat::zeros(img_r.size(), CV_8UC1);
      Mat img_g_edge = Mat::zeros(img_g.size(), CV_8UC1);
      Mat img_b_edge = Mat::zeros(img_b.size(), CV_8UC1);

      // Aligned images
      Mat img_g_aligned = Mat::zeros(img_g.size(), CV_8UC1);
      Mat img_b_aligned = Mat::zeros(img_b.size(), CV_8UC1);

      // Output image
      Mat out = Mat::zeros(img_r.size(), CV_8UC3);

      // Cropped output image
      Mat out_cropped = Mat::zeros(img_r.size(), CV_8UC3);

      std::cout << "Step 1 - calculating edge images... ";
      // TODO: 1) Calculate the 1st Sobel derivative once in x and once in y direction and combine these two
      //          (for every channel).
      //       2) Normalize every gradient image and convert the results to CV_8UC1.
      //       3) Threshold the retrieved (normalized) gradient images using the parameter "edgeThreshold".
      //       4) Save the results in the cv::Mats below.

      imwrite(out_r_edge_filename, img_r_edge);
      imwrite(out_g_edge_filename, img_g_edge);
      imwrite(out_b_edge_filename, img_b_edge);

      std::cout << "done." <<std::endl;

      std::cout << "Step 2 - determining best matching offset and transforming images... ";
        // TODO: 1) Determine the best matching offset for the channels G and B. To accomplish this the images are
        //          transformed (shifted in the x and y direction) and a score for every possible transformation is
        //          calculated by checking how many edge pixels in the reference channel (R) lie on edge pixels in the
        //          transformed channels (G, B).
        //       2) After calculating the best offset transform the channels according to this offset and save them to the
        //          cv::Mats imgG_aligned and imgB_aligned respectively.
        // Note: The expected output images are of the same size as their untransformed original images.
        //
        imwrite(out_g_transformed_filename, img_g_aligned);
        imwrite(out_b_transformed_filename, img_b_aligned);

        std::cout << "done." << std::endl;

        std::cout << "Step 3 - combining images... ";
        // TODO: Combine the three image channels into one single image. Mind the pixel format!
        // Note: The expected image has the same dimensions as the reference channel (R).
        //
        imwrite(out_combined_image_filename, out);
        std::cout << "done." << std::endl;

        std::cout << "Step 4 - cropping output image... ";
        // TODO: Crop the above generated image s.t. only pixels defined in every channel (R, G, B) remain in the resulting
        //       cropped output image.
        imwrite(out_cropped_image_filename, out_cropped);
        std::cout << "done." << std::endl;
    }
    catch (std::exception &ex)
    {
        std::cout << "An exception occured:" << std::endl;
        std::cout << ex.what() << std::endl;
        return -2;
    }
    return 0;
}

