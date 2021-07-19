#include <iostream>
#include <omp.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

// 取散斑点
bool comparisonBrightness(int box, int x, int y, Mat image) {
    int width = box / 2, counter = 0;
    // 获取中心点的像素值（灰度）
    double point = image.at<Vec3b>(y, x)[0];
    for (int i = -width; i < width + 1; i++) {
        for (int j = -width; j < width + 1; j++) {
            // 对图像边缘进行处理（对称）
            int num1 = i, num2 = j;
            if (y + num1 < 0)
                num1 = -num1;
            if (x + num2 < 0)
                num2 = -num2;
            double color = image.at<Vec3b>(y + num1, x + num2)[0];
            // 对灰度小于中心的点进行计数
            // 同时背景存在噪点，需要进行控制（-3）
            if (color <= point - 3) {
                counter++;
            }
        }
    }
    // 当中心点灰度大于范围内所有点，返回true
    // 否则返回false
    if (counter == box * box - 1)
        return true;
    else
        return false;
}

int main() {
    double start = omp_get_wtime();
    // 确定方框的大小
    int box = 7;
    // 设置阈值，认为低于该值的点为背景
    double threshold_value = 34;
    int num1 = 0, num2 = 0;
    Mat whole = imread("../images/whole.bmp");
    Mat img = whole.clone();
    // 遍历散斑图
#pragma omp parallel for
    for (int y = 0; y < whole.rows; y++) {
        for (int x = 0; x < whole.cols; x++) {
            // 通过灰度值进行判断，该点是否为灰度较高的点
            if (comparisonBrightness(box, x, y, whole)) {
                num1++;
                img.at<Vec3b>(y, x)[0] = 0;
                img.at<Vec3b>(y, x)[1] = 255;
                img.at<Vec3b>(y, x)[2] = 0;
            }
            // 对大于该灰度阈值的点进行计数
            if (whole.at<Vec3b>(y, x)[0] >= threshold_value)
                num2++;
        }
    }
    cout << num2 / num1 << endl;
    double end = omp_get_wtime();
    cout << "time:" << end - start << "s" << endl;
    imwrite("../images/image1.bmp", img);
    return 0;
}
