//
//// Created by shanyi on 2021/7/19.
////
//
//#include <iostream>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//
//using namespace std;
//using namespace cv;
//
//int main() {
//    Mat whole = imread("../images/whole.bmp",IMREAD_UNCHANGED);
//    Mat temp = imread("../images/Tiger_181.bmp");
//    Mat result = Mat(whole.cols - temp.cols + 1, whole.rows - temp.rows + 1, CV_32F, Scalar(0));
//    matchTemplate(whole, temp, result, TM_CCOEFF_NORMED);
//    double minVal, maxVal;
//    Point minLoc, maxLoc, matchLoc;
//    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
//    matchLoc = maxLoc;
//    Mat mask = whole.clone();
//    rectangle(mask, matchLoc, Point(matchLoc.x + temp.cols, matchLoc.y + temp.rows), Scalar(0, 255, 0));
//    imwrite("../images/result.bmp", mask);
//    return 0;
//}