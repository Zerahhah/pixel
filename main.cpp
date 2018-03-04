#include<iostream>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<windows.h>
#include<string>

class Pixel {
public:
	Pixel(int _block,std::string _image) {
		cv::Mat colorImage = cv::imread(_image);
		col = colorImage.cols;
		row = colorImage.rows;
		std::cout << "col is : " << col << std::endl;
		std::cout << "row is : " << row << std::endl;
		block = _block;//块大小
		resCol = col / block;
		resRow = row / block;
		std::cout << resCol << std::endl;
		std::cout << resRow << std::endl;
		resImage = cv::Mat(resRow*block, resCol*block, CV_8UC3, cv::Scalar::all(0));

		for (int i = 0; i < resRow; ++i) {
			for (int j = 0; j < resCol; ++j) {
				int blue = 0, green = 0, red = 0;
				for (int n = i*block; n <= (i + 1)*block - 1; ++n) {
					for (int m = j*block; m <= (j + 1)*block - 1; ++m) {
						blue += colorImage.at<cv::Vec3b>(n, m)[0];
						green += colorImage.at<cv::Vec3b>(n, m)[1];
						red += colorImage.at<cv::Vec3b>(n, m)[2];
					}
				}

				blue = blue / (block*block);
				green = green / (block*block);
				red = red / (block*block);
				for (int n = i*block; n <= (i + 1)*block - 1; ++n) {
					for (int m = j*block; m <= (j + 1)*block - 1; ++m) {
						resImage.at<cv::Vec3b>(n, m)[0] = blue;
						resImage.at<cv::Vec3b>(n, m)[1] = green;
						resImage.at<cv::Vec3b>(n, m)[2] = red;
					}
				}

			}
		}

		cv::imshow("res", resImage);
		cv::imwrite("res.jpg", resImage);
	}
private:
	cv::Mat colorImage,resImage;
	int block;
	int col, row;//输入图片的长宽
	int resCol, resRow;//输出图片被分成多少块

};


int main() {
	Pixel p(8, "1.jpg");

	std::cout << "success!"<<std::endl;
	cv::waitKey(0);
	system("pause");
	return 0;
}
