#include "HomographyHelper.h"

namespace ns_HomographyHelper
{
	bool getting_input;
	int clicknum;
	cv::Point2d* points = (cv::Point2d*)malloc(8 * sizeof(cv::Point2d));
}

using namespace ns_HomographyHelper;

void MouseCallback(int action, int x, int y, int flag, void* userInput)
{
	if (getting_input)
	{
		if (action == CV_EVENT_LBUTTONUP)
		{
			points[clicknum].x = x;
			points[clicknum].y = y;
			clicknum++;
		}
	}

	//DEBUG
	if (action == CV_EVENT_LBUTTONUP)
	{
		std::cout << x << ", " << y << std::endl;
	}
}

void HomographyHelper::Homography22d(cv::Mat& imgsrc, cv::Mat& imgdst, cv::Mat& output, bool save = false, char* filepath = "../../data")
{
	if (imgsrc.empty())
	{
		std::cout << "Could not find color image.  Aborting..." << std::endl;
		return;
	}
	if (imgdst.empty())
	{
		std::cout << "Could not find depth image.  Aborting..." << std::endl;
		return;
	}

	const char* winname = "Homography Chooser";
	getting_input = false;
	clicknum = 0;
	char keyInput = 'r';


	cv::imshow(winname, imgsrc);
	cv::setMouseCallback(winname, MouseCallback);


	while (keyInput == 'r')
	{
		cv::Mat tempImg;
		imgsrc.copyTo(tempImg);
		cv::imshow(winname, imgsrc);

		clicknum = 0;

		getting_input = true;
		while (clicknum < 4)
		{
			for (int i = 0; i < clicknum; i++)
				cv::circle(tempImg, points[i], 4, cv::Scalar(50 * i, 50 * i, 255));

			cv::imshow(winname, tempImg);

			cv::waitKey(25);
		}
		getting_input = false;

		for (int i = 0; i < clicknum; i++)
			cv::circle(tempImg, points[i], 4, cv::Scalar(50 * i, 50 * i, 255));

		cv::imshow(winname, tempImg);

		std::cout << "Press r to redo capture, and any other key to continue" << std::endl;
		keyInput = cv::waitKey(0);
	}

	keyInput = 'r';
	while (keyInput == 'r')
	{
		cv::Mat tempImg;
		imgdst.copyTo(tempImg);
		cv::imshow(winname, imgdst);

		clicknum = 4;

		getting_input = true;
		while (clicknum < 8)
		{
			for (int i = 4; i < clicknum; i++)
				cv::circle(tempImg, points[i], 4, cv::Scalar(30, 40 * i, 255));

			cv::imshow(winname, tempImg);

			cv::waitKey(25);
		}
		getting_input = false;

		for (int i = 0; i < clicknum; i++)
			cv::circle(tempImg, points[i], 4, cv::Scalar(30, 40 * i, 255));

		cv::imshow(winname, tempImg);

		std::cout << "Press r to redo capture, and any other key to continue" << std::endl;
		keyInput = cv::waitKey(0);
	}

	cv::Point2f srcpts[4] = { points[0], points[1], points[2], points[3] };
	cv::Point2f dstpts[4] = { points[4], points[5], points[6], points[7] };

	cv::Mat p_trans = cv::getPerspectiveTransform(srcpts, dstpts);

	cv::warpPerspective(imgsrc, output, p_trans, cv::Size(std::fmax(imgsrc.cols, imgdst.cols), std::fmax(imgsrc.rows, imgdst.rows)));

	cv::destroyWindow(winname);
}

void HomographyHelper::Homography22d(cv::Mat& input, cv::Mat& output, bool save = false, char* filepath = "../../data")
{

}