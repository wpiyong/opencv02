#include "opencv2/opencv.hpp"

using namespace cv;

int main(int argc, char **argv)
{
	// Read image
	Mat im_in = imread("../../images/eagle02.jpg", IMREAD_GRAYSCALE);
	imshow("origin image", im_in);

	int thresh = 30;
	Mat gausB;
	GaussianBlur(im_in, gausB, Size(5, 5), 0);
	Canny(gausB, im_in, thresh, thresh * 2, 3);
	im_in = 255 - im_in;
	int a = 150;
	for (int i = 0; i < 1; i++) {
		//im_in = 255 - im_in;
		imshow("origin image", im_in);
		// Threshold.
		// Set values equal to or above 220 to 0.
		// Set values below 220 to 255.
		Mat im_th;
		threshold(im_in, im_th, a, 255, THRESH_BINARY_INV);

		// Floodfill from point (0, 0)
		Mat im_floodfill = im_th.clone();
		floodFill(im_floodfill, cv::Point(0, 0), Scalar(255));

		// Invert floodfilled image
		Mat im_floodfill_inv;
		bitwise_not(im_floodfill, im_floodfill_inv);

		// Combine the two images to get the foreground.
		Mat im_out = (im_th | im_floodfill_inv);

		// Display images
		imshow("Thresholded Image", im_th);
		imshow("Floodfilled Image", im_floodfill);
		imshow("Inverted Floodfilled Image", im_floodfill_inv);
		imshow("Foreground", im_out);
		im_in = im_out;
		a -= 20;
	}
	waitKey(0);

}