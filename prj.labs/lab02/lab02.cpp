#include <opencv2/opencv.hpp>

using namespace std;

vector<cv::Mat> red(cv::Mat rgbChannel, cv::Mat g){
  vector<cv::Mat> channels;
  channels.push_back(g);
  channels.push_back(g);
  channels.push_back(rgbChannel);

  return channels;
}

vector<cv::Mat> green(cv::Mat rgbChannel, cv::Mat g) {
  vector<cv::Mat> channels;
  channels.push_back(g);
  channels.push_back(rgbChannel);
  channels.push_back(g);

  return channels;
}

vector<cv::Mat> blue(cv::Mat rgbChannel, cv::Mat g) {
  vector<cv::Mat> channels;
  channels.push_back(rgbChannel);
  channels.push_back(g);
  channels.push_back(g);

  return channels;
}


cv::Mat visualisation(cv::Mat img) {
  cv::Mat rgbChannels[3];
  cv::split(img, rgbChannels);
  cv::Mat full_img;
  cv::Mat g = cv::Mat::zeros(cv::Size(img.cols, img.rows), CV_8UC1);
  cv::Rect2d rc = { 0, 0, 256, 256 };
  img.copyTo(full_img);
  rc.y += rc.height;
  cv::merge(red(rgbChannels[2],g), full_img);
  cv::merge(green(rgbChannels[1], g), full_img);
  cv::merge(blue(rgbChannels[0], g), full_img);
  return full_img;
}

int main() {
  string img_path = "../../../data/cross_0256x0256.png";
  cv::Mat img = cv::imread(img_path);

  vector<int> compression_params;
  compression_params.push_back(cv::IMWRITE_JPEG_QUALITY);
  compression_params.push_back(25);

  cv::imwrite("cross_0256x0256_025.jpg", img, compression_params);
  cv::Mat img2 = cv::imread("../../../data/cross_0256x0256.jpeg");

  cv::imshow("lab02", visualisation(img));

  cv::waitKey(0);
}