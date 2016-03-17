

#include <iostream>
#include <time.h>

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <omp.h>

using namespace cv;
using namespace std;

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
#pragma omp parallel for
      for (int n = 0; n < 10; ++n) {
        cout << " " << n << " ";
      }

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

      Mat images[3] = {img_r, img_g, img_b};
      Mat edges[3] = {img_r_edge, img_g_edge, img_b_edge};
      for (int i = 0; i < 3; ++i){
        // Generate grad_x and grad_y
        Mat grad_x, grad_y;

        //gradient x
        Sobel(images[i], grad_x, CV_32F, 1, 0);
        //gradient y
        Sobel(images[i], grad_y, CV_32F, 0, 1);

        pow(grad_x, 2, grad_x);
        pow(grad_y, 2, grad_y);
        Mat combined = grad_x + grad_y;
        sqrt(combined, combined);

        normalize(combined, combined, 0.0, 255.0, NORM_MINMAX);
        combined.convertTo(combined, CV_8UC1);
        threshold(combined, edges[i], edge_threshold, 255.0, CV_8UC1);
      }

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

      int best_i_b, best_j_b, best_i_g, best_j_g;
      double score_b = -100.0, score_g = -100.0;
      for (int i = -match_window_size/2; i <= match_window_size/2; ++i) {
        for (int j = -match_window_size/2; j <= match_window_size/2; ++j) {
          double score_b_tmp = -100.0;
          double score_g_tmp = -100.0;
#pragma omp parallel for
          for (int k = 0; k < img_r_edge.rows; ++k) {
            for (int l = 0; l < img_r_edge.cols; ++l) {
              score_g_tmp += img_r_edge.at<uchar>(k,l) / 255 * img_g_edge.at<uchar>(k+i,l+j)/255;
              score_b_tmp += img_r_edge.at<uchar>(k,l) / 255 * img_b_edge.at<uchar>(k+i,l+j)/255;
            }
          }
          if (score_b_tmp > score_b){
            score_b = score_b_tmp;
            best_i_b = i;
            best_j_b = j;
          }
          if (score_g_tmp > score_g){
            score_g = score_g_tmp;
            best_i_g = i;
            best_j_g = j;
          }
        }
      }

      for (int x = 0; x < img_b.rows; ++x) {
        for (int y = 0; y < img_b.cols; ++y) {
          img_b_aligned.at<uchar>(x,y) = img_b.at<uchar>(x+best_i_b, y+best_j_b);
        }
      }
      for (int x = 0; x < img_g.rows; ++x) {
        for (int y = 0; y < img_g.cols; ++y) {
          img_g_aligned.at<uchar>(x,y) = img_g.at<uchar>(x+best_i_g, y+best_j_g);
        }
      }
      
      imwrite(out_g_transformed_filename, img_g_aligned);
      imwrite(out_b_transformed_filename, img_b_aligned);

      std::cout << "done." << std::endl;

      std::cout << "Step 3 - combining images... ";
      // TODO: Combine the three image channels into one single image. Mind the pixel format!
      // Note: The expected image has the same dimensions as the reference channel (R).
      //

      for (int x = 0; x < img_r.rows; ++x) {
        for (int y = 0; y < img_r.cols; ++y) {
          out.at<Vec3b>(x, y)[2] = img_r.at<uchar>(x, y);

          if (img_b_aligned.rows > x && img_b_aligned.cols > y){
            out.at<Vec3b>(x, y)[0] = img_b_aligned.at<uchar>(x, y);
          } else {
            out.at<Vec3b>(x, y)[0] = 0;
          }

          if (img_g_aligned.rows > x && img_g_aligned.cols > y){
            out.at<Vec3b>(x, y)[1] = img_g_aligned.at<uchar>(x, y);
          } else {
            out.at<Vec3b>(x, y)[1] = 0;
          }
        }
      }


      imwrite(out_combined_image_filename, out);
      std::cout << "done." << std::endl;

      std::cout << "Step 4 - cropping output image... ";
      // TODO: Crop the above generated image s.t. only pixels defined in every channel (R, G, B) remain in the resulting
      //       cropped output image.

      /*
      int y = (best_j_b < best_j_g) ? (abs(best_j_b)) : (abs(best_j_g));
      int x = (best_i_b < best_i_g) ? (abs(best_i_b)) : (abs(best_i_g));
      int h = (img_g_aligned.rows - x < img_b_aligned.rows - x) ? (img_g_aligned.rows - x) : (img_b_aligned.rows - x);
      int w = (img_g_aligned.cols - y < img_b_aligned.cols - y) ? (img_g_aligned.cols - y) : (img_b_aligned.cols - y);
      Rect final1 = Rect(y,x,w,h);
       */


      Rect gBound1 = Rect(abs(best_j_g), abs(best_i_g), abs(img_g_aligned.cols-abs(best_j_g)), abs(img_g_aligned.rows-abs(best_i_g)));
      Rect bBound1 = Rect(abs(best_j_b), abs(best_i_b), abs(img_b_aligned.cols-abs(best_j_b)), abs(img_b_aligned.rows-abs(best_i_b)));

      Rect imgSize = Rect(0,0,out.cols,out.rows);

      Rect final =  imgSize & gBound1 & bBound1;


      out(final).copyTo(out_cropped);

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

