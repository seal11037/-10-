# -10-
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    Mat image = imread("");//這邊你要打你存的檔名

    if (image.empty()) 
    {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    namedWindow("Display window", WINDOW_AUTOSIZE);
    imshow("Display window", image);

    waitKey(0);
    return 0;
}
