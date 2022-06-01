#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
  Mat img(450, 300, CV_8UC1);
  Mat img1,img2, img3(450, 300, CV_32FC1);;
  Mat_<float> filter1(3, 3);
  Mat_<float> filter2(3, 3);
  filter1 << 1, 0, -1, 2, 0, -2, 1, 0, -1;
  filter2 << 1, 2, 1, 0, 0, 0, -1, -2, -1;

  for (int i = 0; i < 150; i++)
    for (int j = 0; j < 150; j++)
    {
      img.at<uchar>(i, j) = 0;
      img.at<uchar>(i+150, j) = 127;
      img.at<uchar>(i+300, j) = 255;
      img.at<uchar>(i, j+150) = 255;
      img.at<uchar>(i+150, j+150) = 0;
      img.at<uchar>(i+300, j+150) = 127;
    }
  circle(img, Point(75, 75), 49, 255, FILLED);
  circle(img, Point(75, 75+149), 49, 0, FILLED);
  circle(img, Point(75, 75+298), 49, 127, FILLED);
  circle(img, Point(75+149, 75), 49, 0, FILLED);
  circle(img, Point(75+149, 75+149), 49, 127, FILLED);
  circle(img, Point(75+149, 75+298), 49, 255, FILLED);
  imshow("img", img);

  img.convertTo(img, CV_32FC1);

  filter2D(img, img1, -1, filter1, Point(-1, -1), 0.0);
  normalize(img1, img1, 255, 0, NORM_MINMAX);

  filter2D(img, img2, -1, filter2, Point(-1, -1), 0.0);
  normalize(img2, img2, 225, 0, NORM_MINMAX);

  for (int i = 0; i < img.rows; i++)
    for (int j = 0; j < img.cols; j++)
      img3.at<float>(i, j) = sqrt(img1.at<float>(i, j) * img2.at<float>(i, j));

  img1.convertTo(img1, CV_8UC1);
  img2.convertTo(img2, CV_8UC1);
  img3.convertTo(img3, CV_8UC1);

  imshow("img1", img1);
  imshow("img2", img2);
  imshow("img3", img3);

  waitKey();
  
  return 0;
}