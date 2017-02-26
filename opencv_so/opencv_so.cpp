#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

//���ش�������Ƶ������������֡��
int video_convert_edges(std::string in_filename, std::string out_filename)
{
	cv::VideoCapture vcap(in_filename);  //����һ����Ƶ���󣬿�����Դ����Ƶ��ͼ�����л����
	//    cv::VideoCapture vcap(0);  //��ʾ��Ĭ���������һ����Ƶ����vcap
	if (!vcap.isOpened()) { //ȷ���ļ�������
		std::cout << "Video or camera open failed!" << std::endl;
		return -1;
	}
	cv::VideoWriter outputVideo;
	int ex = static_cast<int>(vcap.get(CV_CAP_PROP_FOURCC));     // Get Codec Type- Int form
	cv::Size S = cv::Size((int)vcap.get(CV_CAP_PROP_FRAME_WIDTH),    // Acquire input size
		(int)vcap.get(CV_CAP_PROP_FRAME_HEIGHT));
	outputVideo.open(out_filename, ex, vcap.get(CV_CAP_PROP_FPS), S, false);
	cv::Mat edges;  //����һ��Mat����洢ͼ��
	cv::namedWindow("Edges", 1);  //����һ����ΪEdges�Ĵ���
	int cont = 0;
	for (;;) {
		++cont;
		cv::Mat frame;
		vcap >> frame;   //����Ƶ�е�һ֡���뵽frame��
		cv::cvtColor(frame, edges, CV_BGR2GRAY);  //���ûҶȻ���������ͼ�񣬲��洢��edges��
		cv::GaussianBlur(edges, edges, cv::Size(7, 7), 1.5, 1.5);  //���ø�˹ģ����������edges�е�ͼ����Ϣ
		cv::Canny(edges, edges, 0, 30, 3);  //���ñ�Ե��⺯��������edges��ͼ��
		cv::imshow("Edges", edges);  //��edges�е�ͼ����ʾ����ΪEdges�Ĵ�����
		outputVideo << edges;
		if (cv::waitKey(30) >= 0) break;  //�ӳ�30������һ��һ֡ͼ��Ĵ���
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