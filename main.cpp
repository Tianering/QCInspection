#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

// 取散斑点
bool comparisonBrightness(int x, int y, Mat image) {
    int counter = 0;
    double point = image.at<Vec3b>(y, x)[0];
    for (int i = -3; i < 4; i++) {
        for (int j = -3; j < 4; j++) {
            // 对图像边缘进行处理_对称
            int num1 = i, num2 = j;
            if (y + num1 < 0)
                num1 = -num1;
            if (x + num2 < 0)
                num2 = -num2;
            double color = image.at<Vec3b>(y + num1, x + num2)[0];
            if (color < point - 3) {
                counter++;
            }
        }
    }
    if (counter == 48)
        return true;
    else
        return false;
}

int main() {
    Mat whole = imread("../images/whole.bmp");
    Mat img = whole.clone();
    int num1 = 0, num2 = 0;

    for (int y = 0; y < whole.rows; y++) {
        for (int x = 0; x < whole.cols; x++) {
            bool torf = comparisonBrightness(x, y, whole);
            if (torf) {
                num1++;
                img.at<Vec3b>(y, x)[0] = 0;
                img.at<Vec3b>(y, x)[1] = 255;
                img.at<Vec3b>(y, x)[2] = 0;
            }
            if (whole.at<Vec3b>(y, x)[0] >= 40)
                num2++;
        }
    }

    cout << num2 / num1 << endl;
    imwrite("../images/image1.bmp", img);
    return 0;
}
