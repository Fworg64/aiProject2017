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
   printf("id: %d, cmdL:%d, cmdR:%d \n", myrobotid, leftwheel, rightwheel);
   command_bot(myrobotid, leftwheel, rightwheel);
}

using namespace cv;

int main(int argc, char** argv)
{

    init_bots("/dev/ttyUSB0");
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
    params.minArea = 50;

    //SimpleBlobDetector detector(params);
    Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);
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

    ourposition player0pos = {0,0,0};
    theplayer player0(&player0pos);
    commands p0cmd;
	double p0obstacles[10]; //5 obstacles, x,y,x,y,x,y,x,y...
	//change this later with other player positions, weight enemy players higher
	p0obstacles[0] = 2.2;
	p0obstacles[1] = 5.5;
		RotatedRect p0Rect = RotatedRect(Point2f(0,0), Size2f(20,20), 0);
    
	ourposition player1pos = {0,0,0};
    theplayer player1(&player1pos);
    commands p1cmd;
	double p1obstacles[10]; //5 obstacles, x,y,x,y,x,y,x,y...
	//change this later with other player positions, weight enemy players higher
	p1obstacles[0] = 2.2;
	p1obstacles[1] = 5.5;
		RotatedRect p1Rect= RotatedRect(Point2f(0,0), Size2f(20,20), 0);

	ourposition player2pos = {0,0,0};
    theplayer player2(&player2pos);
    commands p2cmd;
	double p2obstacles[10]; //5 obstacles, x,y,x,y,x,y,x,y...
	//change this later with other player positions, weight enemy players higher
	p2obstacles[0] = 2.2;
	p2obstacles[1] = 5.5;
		RotatedRect p2Rect = RotatedRect(Point2f(0,0), Size2f(20,20), 0);;

	std::cout <<"initialized player objects"<<std::endl;

    Size_<int> mysize(5, 5); //kernal for gaussian blur

	namedWindow("COMPUTER VISION");
	//namedWindow("Blurred");
	//namedWindow("converted");
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

			if (det->id == 0) //populate position of player from tag id
			{
				std::cout << "found tag "<<det->id<<" with error: " << det->hamming <<std::endl;
				player0pos.x = det->c[0];
				player0pos.y = det->c[1];
				player0pos.w = (180.0/3.1415)*atan2(det->p[0][0] - det->c[0], -(det->p[0][1] - det->c[1]));
				p0Rect = RotatedRect(Point2f(player0pos.x, player0pos.y), Size2f(20,20), player0pos.w +45);

				std::cout << "reading p0 pos as x: "<< player0pos.x <<" y: "<<player0pos.y<< " w: " <<player0pos.w<<std::endl;
			}
			if (det->id == 1) //populate position of player from tag id
			{
				std::cout << "found tag "<<det->id<<" with error: " << det->hamming <<std::endl;
				player1pos.x = det->c[0];
				player1pos.y = det->c[1];
				player1pos.w = (180.0/3.1415)*atan2(det->p[0][0] - det->c[0], -(det->p[0][1] - det->c[1]));
				p1Rect = RotatedRect(Point2f(player1pos.x, player1pos.y), Size2f(20,20), player1pos.w + 45);
				std::cout << "reading p1 pos as x: "<< player1pos.x <<" y: "<<player1pos.y<< " w: " <<player1pos.w<<std::endl;
			}
			if (det->id == 2) //populate position of player from tag id
			{
				std::cout << "found tag "<<det->id<<" with error: " << det->hamming <<std::endl;
				player2pos.x = det->c[0];
				player2pos.y = det->c[1];
				player2pos.w = (180.0/3.1415)*atan2(det->p[0][0] - det->c[0], -(det->p[0][1] - det->c[1]));
				p2Rect = RotatedRect(Point2f(player2pos.x, player2pos.y), Size2f(20,20), player2pos.w + 45);
				std::cout << "reading p2 pos as x: "<< player2pos.x <<" y: "<<player2pos.y<< " w: " <<player2pos.w<<std::endl;
			}
		}

       //find ball here
       // GaussianBlur(img3, img4, Size(5,5), 5,5,BORDER_ISOLATED);
        GaussianBlur(img3, img4, mysize, 5);//, 5, BORDER_ISOLATED);
        imshow("Blurred", img4);
        split(img4, channels);
        channels[0]=Mat::zeros(img4.rows, img4.cols, CV_8UC1);//Set blue channel to 0
        channels[1]=Mat::zeros(img4.rows, img4.cols, CV_8UC1);//Set green channel to 0
        
        cvtColor(img4, img5, COLOR_BGR2HSV);
	//merge(channels, 3, img5);
	//cvtColor(img5, img6, COLOR_BGR2GRAY);
	namedWindow("hsv", WINDOW_AUTOSIZE);
        imshow("hsv", img5);
        inRange(img5, Scalar(15, 175, 175), Scalar(50, 255, 255), img6);
        bitwise_not(img6, img7);
		//draw player pos's here
		Point2f vertices[4];
		p0Rect.points(vertices);
		for (int i = 0; i < 4; i++)
    		line(img7, vertices[i], vertices[(i+1)%4], Scalar(0,255,0));
		p1Rect.points(vertices);
		for (int i = 0; i < 4; i++)
    		line(img7, vertices[i], vertices[(i+1)%4], Scalar(0,255,0));
		p2Rect.points(vertices);
		for (int i = 0; i < 4; i++)
    		line(img7, vertices[i], vertices[(i+1)%4], Scalar(0,255,0));
		
		
        imshow("BALL", img7);

        detector->detect(img7, keypoints);
        if (keypoints.size() >0)
		{
        	std::cout <<"ball found at: " << keypoints.at(0).pt.x<<", "<<keypoints.at(0).pt.y<<std::endl;
			//populate obstacles here
			p0cmd = player0.eval(&player0pos, p0obstacles, (double)keypoints.at(0).pt.x,(double) keypoints.at(0).pt.y);
			p1cmd = player1.eval(&player1pos, p1obstacles, (double)keypoints.at(0).pt.x,(double) keypoints.at(0).pt.y);
			p2cmd = player2.eval(&player2pos, p2obstacles, (double)keypoints.at(0).pt.x,(double) keypoints.at(0).pt.y);
        	sendCmd(1554593, (p0cmd == GOFWD || p0cmd == GOLEFT) ? 127: (p0cmd==GOBKWD) ? -127: 0, (p0cmd == GOFWD || p0cmd == GORGHT) ? 127: (p0cmd==GOBKWD) ? -127: 0); // nobody can understand this
        	sendCmd(1481416, (p1cmd == GOFWD || p1cmd == GOLEFT) ? 127: (p1cmd==GOBKWD) ? -127: 0, (p1cmd == GOFWD || p1cmd == GORGHT) ? 127: (p1cmd==GOBKWD) ? -127: 0);
        	sendCmd(1557094, (p2cmd == GOFWD || p2cmd == GOLEFT) ? 127: (p2cmd==GOBKWD) ? -127: 0, (p2cmd == GOFWD || p2cmd == GORGHT) ? 127: (p2cmd==GOBKWD) ? -127: 0);
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
