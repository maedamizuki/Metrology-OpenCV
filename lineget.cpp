#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <iostream>
#include <string>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <dirent.h>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
using namespace cv;
string win_src = "src";
string win_dst = "dst";


int main()
{
  vector<string> filev;
  string filelist1;
  ifstream filelist("file.txt",ifstream::in);
  string filelist2;
  int a=0;
  //ファイルのパス生成＋読み込み
  if(!filelist){
    cout << "Error" << endl;
  }
  if(filelist){
    cout << "OK" << endl;
    while(true){
      a=a+1;
      if(filelist.eof())
	break;
      filelist >> filelist1;

      if(a==1){
	filelist1.erase(0,2);
	filelist1.erase(filelist1.length()-2,2);
      }else if(a==35){
	filelist1.erase(0,1);
	filelist1.erase(filelist1.length()-2,2);
      }else{
	filelist1.erase(0,1);
	filelist1.erase(filelist1.length()-2,2);
      }
      filev.push_back(filelist1);
      
    }
  }
  
  string file_dst1 = "linegetv1.png";//出力画像のファイル名
  string file_dst2 = "linegetv2.png";
  vector<Mat> img_src;
  int itn;
  for(itn=0;itn < filev.size();itn++){
    string path = filev[itn];
    Mat img1= imread(path,1);

    if(img1.empty()){
      cout << "error" <<endl;
      continue;
    }
    cout << filev[itn] << " importing image is done!" <<endl;
    img_src.push_back(img1);
  }

  int width;
  int height;

  Rect roi1(0,0,5110,3060);
  Rect roi2(0,0,6000,3060);
  Rect roi3(0,0,5110,4000);
  int count =0;
  vector<Mat> img_src2;
  int i;
  //写真のオーバーラップの部分をカット
  for(i=0;i<img_src.size();i++){
    count = count +1;
    if(count < 7){
      Mat img2 = img_src[i](roi2);
      img_src2.push_back(img2);
    }else if (count ==7){
      Mat img3 = img_src[i];
      img_src2.push_back(img3);
    }else if (count ==8 || count ==21 || count ==22 || count ==35){
      Mat img4 = img_src[i](roi3);
      img_src2.push_back(img4);
    }else if((count >8 && count <21) || (count>22 && count <35)){
      Mat img5 = img_src[i](roi1);
      img_src2.push_back(img5);
    }else{
      break;
    }
    
  }
  //ウインドウ生成
  namedWindow(win_src, WINDOW_AUTOSIZE);
  namedWindow(win_src, WINDOW_AUTOSIZE);

  Mat img_srch1,img_srch2,img_srch3,img_srch4,img_srch5;
  Mat img_srcconnect1;
  //縦に繋げる処理（列）

  for (i=0;i<img_src.size();i++){
    if(i==0){
      vconcat(img_src2[i],img_src2[i+1],img_srch1);
    }else if (i>1&&i<7){
      vconcat(img_srch1,img_src2[i],img_srch1);
    }else if (i==7){
      vconcat(img_src2[i+1],img_src2[i],img_srch2);
    }else if (i>8 && i<14){
      vconcat(img_src2[i],img_srch2,img_srch2);
    }else if (i==14){
      vconcat(img_src2[i],img_src2[i+1],img_srch3);
    }else if(i>15&&i<21){
      vconcat(img_srch3,img_src2[i],img_srch3);
    }else if(i==21){
      vconcat(img_src2[i+1],img_src2[i],img_srch4);
    }else if(i>22&&i<28){
      vconcat(img_src2[i],img_srch4,img_srch4);
    }else if (i==28){
      vconcat(img_src2[i],img_src2[i+1],img_srch5);
    }else if(i>29&&i<35){
      vconcat(img_srch5,img_src2[i],img_srch5);
    } else{
      continue;
    }
  }

  cout<<img_srch1.rows <<":"<< img_srch1.cols <<":"<< img_srch2.rows <<":"<< img_srch2.cols<<":"<<img_srch3.rows <<":"<<img_srch3.cols << endl;
  //横に繋げる
  hconcat(img_srch2,img_srch1,img_srcconnect1);
  hconcat(img_srch3,img_srcconnect1,img_srcconnect1);
  hconcat(img_srch4,img_srcconnect1,img_srcconnect1);
  hconcat(img_srch5,img_srcconnect1,img_srcconnect1);

  imshow(win_src,img_srcconnect1);
  imwrite(file_dst1,img_srch1);
  imwrite(file_dst2,img_srch5);
  return 0;
  
}
