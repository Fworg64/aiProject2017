#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <commands.h>
#include <ourposition.h>
#include <theplayer.h>
#include "realbot.h"

extern "C" {
#include "apriltag.h"
#include "tag36h11.h"
}

void sendCmd(uint32_t myrobotid, int8_t leftwheel, int8_t rightwheel)
{
   printf("id: %d, cmdL:%d, cmdR:%d", myrobotid, leftwheel, rightwheel);
   command_bot(myrobotid, leftwheel, rightwheel);
}

using namespace cv;

int main(int argc, char** argv)
{

    init_bots("/dev/ttyACM0");
    VideoCapture cap(0);
    if(!cap.isOpened()) return -1; //check for success
    //char* imageName = argv[1];
    //Mat img =imread(imageName, 1);
	Mat img(480, 640, CV_8UC3, Scalar(69,42,200));
    Mat img2(480, 640, CV_8UC3, Scalar(69,42,200));
    Mat img3(480, 640, CV_8UC3, Scalar(69,42,200));
    Mat img4(480, 640, CV_8UC3, Scalar(69,42,200));
    Mat img5(480, 640, CV_8UC3, Scalar(69,42,200));
    Mat img6(480, 640, CV_8UC3, Scalar(69,42,200));
    Mat img7(480, 640, CV_8UC3, Scalar(69,42,200));
    Mat channels[3];
    
    SimpleBlobDetector::Params params;
    params.filterByInertia = true;
    params.minInertiaRatio = 0.01;
    params.filterByConvexity = true;
    params.minConvexity = 0.07;
    params.filterByArea = true;
    params.minArea = 150;

    SimpleBlobDetector detector(params);
    std::vector<KeyPoint> keypoints;

    


    apriltag_detector_t *td = apriltag_detector_create();
    apriltag_family_t *tf = tag36h11_create();

    tf->black_border = 1; //from example

    apriltag_detector_add_family(td, tf);

    td->quad_decimate = 1.0;
    td->quad_sigma = 0.0;
    td->refine_edges = 1;
    td->refine_decode = 0;
    td->refine_pose = 0;

    zarray_t *detections;

    std::cout << "Warming up camera(2sec)"<< std::endl;

    //waitKey(2000); //let camera warm up

    std::cout << "CAMERA HOT" <<std::endl;

    ourposition player1pos = {0,0,0};
    theplayer player1(&player1pos);
    commands p1cmd;
	double p1obstacles[10]; //5 obstacles, x,y,x,y,x,y,x,y...
	//change this later with other player positions, weight enemy players higher
	p1obstacles[0] = 2.2;
	p1obstacles[1] = 5.5;
	std::cout <<"initialized player objects"<<std::endl;

    Size_<int> mysize(5, 5); //kernal for gaussian blur

	namedWindow("COMPUTER VISION");
	namedWindow("Blurred");
	namedWindow("converted");
	namedWindow("BALL");

    while(1)
    {
	cap >> img; //c++ is the future
	cvtColor(img, img2, COLOR_BGR2GRAY);
	img3 = img;
	imshow("COMPUTER VISION", img3);
	std::cout <<"FRAME"<<std::endl;

	image_u8_t img_header = { .width = img2.cols, //convert opencv to apriltag img
        	.height = img2.rows,
        	.stride = img2.cols,
        	.buf = img2.data
    		};

	detections = apriltag_detector_detect(td, &img_header); //detect april tags

	for (int i = 0; i < zarray_size(detections); i++) { //iterate through detections
        apriltag_detection_t *det;
        zarray_get(detections, i, &det); //store dection at adress pointed by det
		std::cout << det->id <<std::endl;
		std::cout <<det->hamming<<std::endl;
		std::cout << det->c[0]<<std::endl;
		std::cout << det->c[1]<<std::endl;

		if (det->id == 0) //populate position of player from tag id
		{
			player1pos.x = det->c[0];
			player1pos.y = det->c[1];
			player1pos.w = atan2(det->p[0][0] - det->c[0], -(det->p[0][1] - det->c[1]));
		}
}

       //find ball here
       // GaussianBlur(img3, img4, Size(5,5), 5,5,BORDER_ISOLATED);
        GaussianBlur(img3, img4, mysize, 5);//, 5, BORDER_ISOLATED);
        imshow("Blurred", img4);
        split(img4, channels);
        channels[0]=Mat::zeros(img4.rows, img4.cols, CV_8UC1);//Set blue channel to 0
        channels[1]=Mat::zeros(img4.rows, img4.cols, CV_8UC1);//Set blue channel to 0
        
        cvtColor(img4, img5, COLOR_BGR2HSV);
	//merge(channels, 3, img5);
	//cvtColor(img5, img6, COLOR_BGR2GRAY);
        imshow("converted", img5);
        inRange(img5, Scalar(15, 175, 175), Scalar(50, 255, 255), img6);
        bitwise_not(img6, img7);
        imshow("BALL", img7);

        detector.detect(img7, keypoints);
        if (keypoints.size() >0)
		{
        	std::cout <<keypoints.at(0).pt.x<<"    "<<keypoints.at(0).pt.y<<std::endl;
			p1cmd = player1.eval(&player1pos, p1obstacles, (double)keypoints.at(0).pt.x,(double) keypoints.at(0).pt.y);
        	sendCmd(100, (p1cmd == GOFWD || p1cmd == GOLEFT) ? 1: (p1cmd==GOBKWD) ? -1: 0, (p1cmd == GOFWD || p1cmd == GORGHT) ? 1: (p1cmd==GOBKWD) ? -1: 0);
		}
        else
        std::cout << "no balls found, no command issued"<<std::endl;

        apriltag_detections_destroy(detections); //not sure if neccesary
        //if(waitKey(3000) >= 0) break;
        waitKey(30); //neccesary
    }
    
    //prevent memory leaks!
    apriltag_detector_destroy(td);
    tag36h11_destroy(tf);
    return 0;
}
