#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <iostream>
#include <string>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <dirent.h>

using namespace cv;
using namespace std;
String win_src = "src";
String win_dst = "dst";

int main(){

  std::string photofilenamev1 = "linegetv1.png";
  std::string photofilenamev2 = "linegetv2.png";
  std::string outputfile1v1 = "smoothingv1.png";
  std::string outputfile1v2 = "smoothingv2.png";
  std::string outputfile2v1 = "sizechangev1.png";
  std::string outputfile2v2 = "sizechangev2.png";
  std::string outputfile3v1 = "grayv1.png";
  std::string outputfile3v2 = "grayv2.png";
  std::string outputfile4v1 = "lineedgev1.png";
  std::string outputfile4v2 = "lineedgev2.png";
  std::string outputfile1v3 = "smoothingv3.png";
  std::string outputfile2v3 = "sizechangev3.png";
  std::string outputfile3v3 = "grayv3.png";
  std::string outputfile4v3 = "lineedgev3.png";
  std::string outputfile1v4 = "smoothingv4.png";
  std::string outputfile2v4 = "sizechangev4.png";
  std::string outputfile3v4 = "grayv4.png";
  std::string outputfile4v4 = "lineedgev4.png";

  Mat src_image1 = imread(photofilenamev1.c_str());
  Mat src_image2 = imread(photofilenamev2.c_str());
  int width = src_image1.cols;//get image size
  int height = src_image1.rows;
  std::cout << height << ":" << width << std::endl;

  int cutwidth = 800;
  int cutheight =0;
  /*
  Rect roi1(3300,0,cutwidth,height);
  Mat img_src1=src_image(roi1);

  imwrite(outputfile2v1,img_src1);
  */
  Rect roi2(2800,0,cutwidth,height);
  Mat img_src2= src_image2(roi2);
  imwrite(outputfile2v2,img_src2);

  //cut noise
  int ksize = 15;
  Mat img_src11,img_src22;
  //bilateralFilter(img_src11,img_src1,15,75,75);
  bilateralFilter(img_src2,img_src22,15,75,75);
  cout << "ok" <<endl;
  //imwrite(outputfile3v1,img_src1);
  imwrite(outputfile3v2,img_src22);
  //change gray image
  Mat gray_image1,gray_image2,gray_image3,gray_image4;
  /*
  cvtColor(img_src1,gray_image1,COLOR_BGR2GRAY);
  Canny(gray_image1,gray_image1,80,100);
  imwrite(outputfile4v1,gray_image1);
  */
  cvtColor(img_src2,gray_image2,COLOR_BGR2GRAY);
  Canny(gray_image2,gray_image2,80,100);
  imwrite(outputfile4v2,gray_image2);

  //get the line edge
  vector<Vec4i> lines1,lines2,lines3,lines4;
  float rho1;//ρの分解能
  float theta1;//thetaの分解能
  int threshold1,threshold2,threshold3,threshold4;//直線を構成する点の数の閾値
  int minLineLength1,minLineLength2,minLineLength3,minLineLength4;//最小の線長
  int maxLineGap1,maxLineGap2,maxLineGap3,maxLineGap4;//同一直線内に許容される最大のギャップ
  rho1 =1;
  theta1 = M_PI/360;
  threshold1 =2000;
  minLineLength1 = 12000;
  maxLineGap1 = 500;
  threshold2 = 1000;
  minLineLength2=2000;
  maxLineGap2 = 100;

  //HoughLinesP(gray_image1,lines1,rho1,theta1,threshold1,minLineLength1,maxLineGap1);
  HoughLinesP(gray_image2,lines2,rho1,theta1,threshold2,minLineLength2,maxLineGap2);
  //Mat src_image_write1 = img_src1.clone();
  Mat src_image_write2 = img_src2.clone();
  /*
  for(size_t i = 0;i<lines1.size();i++){
    line(src_image_write1,Point(lines1[i][0],lines1[i][1]),Point(lines1[i][2],lines1[i][3]),Scalar(0,0,255),20,8);
  }
  */
  cout << lines2.size() << endl;
  for(size_t i2 = 0;i2<lines2.size();i2++){
    line(src_image_write2,Point(lines2[i2][0],lines2[i2][1]),Point(lines2[i2][2],lines2[i2][3]),Scalar(0,0,255),20,8);
  }
  /*
  imshow(win_src,gray_image1);
  imshow(win_dst,src_image_write1);
  imwrite(outputfile3v1,src_image_write1);
  */
  imshow(win_src,gray_image2);
  imshow(win_dst,src_image_write2);
  imwrite(outputfile4v2,src_image_write2);
  return 0;

}
