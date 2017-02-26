#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

//返回处理后的视频中所包含的总帧数
int video_convert_edges(std::string in_filename, std::string out_filename)
{
	cv::VideoCapture vcap(in_filename);  //创建一个视频对象，可以来源于视频、图像序列或像机
	//    cv::VideoCapture vcap(0);  //表示从默认相机创建一个视频对象vcap
	if (!vcap.isOpened()) { //确定文件正常打开
		std::cout << "Video or camera open failed!" << std::endl;
		return -1;
	}
	cv::VideoWriter outputVideo;
	int ex = static_cast<int>(vcap.get(CV_CAP_PROP_FOURCC));     // Get Codec Type- Int form
	cv::Size S = cv::Size((int)vcap.get(CV_CAP_PROP_FRAME_WIDTH),    // Acquire input size
		(int)vcap.get(CV_CAP_PROP_FRAME_HEIGHT));
	outputVideo.open(out_filename, ex, vcap.get(CV_CAP_PROP_FPS), S, false);
	cv::Mat edges;  //创建一个Mat对象存储图像
	cv::namedWindow("Edges", 1);  //创建一个名为Edges的窗口
	int cont = 0;
	for (;;) {
		++cont;
		cv::Mat frame;
		vcap >> frame;   //将视频中的一帧读入到frame中
		cv::cvtColor(frame, edges, CV_BGR2GRAY);  //调用灰度化函数处理图像，并存储到edges中
		cv::GaussianBlur(edges, edges, cv::Size(7, 7), 1.5, 1.5);  //调用高斯模糊函数处理edges中的图像信息
		cv::Canny(edges, edges, 0, 30, 3);  //调用边缘检测函数来处理edges中图像
		cv::imshow("Edges", edges);  //将edges中的图像显示到名为Edges的窗口中
		outputVideo << edges;
		if (cv::waitKey(30) >= 0) break;  //延迟30秒后进行一下一帧图像的处理
	}
	return cont;
}

int main(void)
{
	std::string in_name = "F:\\bunny.avi";
	std::string out_name = "F:\\bunny_edge.avi";
	video_convert_edges(in_name, out_name);
	return 0;
}