#include <opencv2/opencv.hpp>
#include <Eigen/Eigen>
#include <opencv2/core/eigen.hpp>
#include <time.h>
#include "imageProcessing/canny.h"
#include "imageProcessing/sobel.h"
#include "imageProcessing/distanceField.h"
// /home/mpl/data/EVIT/robot/robot_normal_result/1642661139.236530.jpg
using namespace CannyEVIT;


void build_canny(const cv::Mat& img, std::vector<std::pair<int, int>>&edge_pos, cv::Mat& canny_img)
{
  Eigen::MatrixXd img_eigen;
  cv::cv2eigen(img, img_eigen);
  Eigen::ArrayXXd grad_x, grad_y, grad_mag;
  image_processing::sobel_mag(img_eigen, grad_x, grad_y, grad_mag);
  image_processing::canny(grad_mag, grad_x, grad_y, edge_pos, 10);
  canny_img = cv::Mat(img.rows, img.cols, CV_8U, cv::Scalar(0));
  for (auto& pos: edge_pos)
    canny_img.at<uint8_t>(pos.first, pos.second) = 255;
}

int main() {
//  cv::Mat img = cv::imread("/home/mpl/data/EVIT/robot/robot_normal_result/1642661139.406530.jpg", cv::IMREAD_GRAYSCALE);
//  size_t row = img.rows;
//  size_t col = img.cols;
//  cv::imshow("img", img);
//  cv::Mat edge;
//  clock_t start = clock();
//  cv::Canny(img, edge, 10, 40, 3);
//  std::vector<std::pair<int, int>> hl_first;
//  for (int i = 0; i < edge.rows; i++)
//    for(int j = 0; j < edge.cols; j++)
//      if (edge.at<uint8_t>(i, j) == 255)
//        hl_first.emplace_back(i, j);
//  std::cout << "size:" << hl_first.size() << std::endl;
//  clock_t end = clock();
//  double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
//  std::cout << "first time:" << elapsed_time << std::endl;
//
//  cv::imshow("cv_edge", edge);

//  cv::Mat grad_x_cv, grad_y_cv;
//  cv::Sobel(img, grad_x_cv, CV_64F, 1, 0);
//  cv::Sobel(img, grad_y_cv, CV_64F, 0, 1);
//  Eigen::MatrixXf grad_x, grad_y, grad_mag;
//  cv::cv2eigen(grad_x_cv, grad_x);
//  cv::cv2eigen(grad_y_cv, grad_y);
//  grad_mag = grad_x.array()*grad_x.array() + grad_y.array()*grad_y.array();
//  std::cout << grad_mag << std::endl;
//  grad_mag = Eigen::sqrt(grad_mag.array());
//  std::cout << grad_mag << std::endl;


  cv::Mat img_neutral = cv::imread("/home/mpl/data/EVIT/robot/robot_fast_result/neutral/1642661814.296115.jpg", cv::IMREAD_GRAYSCALE);
  cv::Mat img_positive = cv::imread("/home/mpl/data/EVIT/robot/robot_fast_result/positive/1642661814.296115.jpg", cv::IMREAD_GRAYSCALE);
  cv::Mat img_negative = cv::imread("/home/mpl/data/EVIT/robot/robot_fast_result/negative/1642661814.296115.jpg", cv::IMREAD_GRAYSCALE);
  cv::threshold(img_neutral, img_neutral, 50, 255, cv::THRESH_TOZERO);
  cv::threshold(img_positive, img_positive, 50, 255, cv::THRESH_TOZERO);
  cv::threshold(img_negative, img_negative, 50, 255, cv::THRESH_TOZERO);

  std::vector<std::pair<int, int>> edge_pos_neutral;
  std::vector<std::pair<int, int>> edge_pos_positive;
  std::vector<std::pair<int, int>> edge_pos_negative;
  cv::Mat edge_neutral, edge_positive, edge_negative;

  build_canny(img_neutral, edge_pos_neutral, edge_neutral);
  build_canny(img_positive, edge_pos_positive, edge_positive);
  build_canny(img_negative, edge_pos_negative, edge_negative);

  cv::imshow("img_neutral", img_neutral);
  cv::imshow("img_positive", img_positive);
  cv::imshow("img_negative", img_negative);


  cv::imshow("edge_neutral", edge_neutral);
  cv::imshow("edge_positive", edge_positive);
  cv::imshow("edge_negative", edge_negative);
  cv::waitKey(0);
//  Eigen::ArrayXXd distance_field;
//  image_processing::chebychevDistanceField(row, col, hl, distance_field);
//  cv::Mat distance_field_cv;
//  Eigen::MatrixXd distance_field_matrix = distance_field;
//  cv::eigen2cv(distance_field_matrix, distance_field_cv);
//  std::cout << distance_field_matrix << std::endl;
//  cv::imshow("edge_polyview", edge_polyview);
//  cv::imshow("distance_field_matrix", distance_field_cv);
//  cv::waitKey(0);




//  Eigen::MatrixXf img_eigen;
//  cv::cv2eigen(img, img_eigen);
//  Eigen::MatrixXf grad_x_eigen, grad_y_eigen;
//  image_processing::canny(img_eigen, grad_x_eigen, grad_y_eigen, 1);
//  cv::Mat grad_x, grad_y;
//  cv::eigen2cv(grad_x_eigen, grad_x);
//  cv::eigen2cv(grad_y_eigen, grad_y);
//
//  cv::imshow("grad_x", grad_x);
//  cv::imshow("grad_y", grad_y);
//  cv::waitKey(0);
}