#include "face_detect.h"
using namespace std;
using namespace cvb;
using namespace cv;
double scale = 1;

double faceDetect(CamCapture &capture)
{
    CascadeClassifier cascade, nestedCascade;
    string cascadeName = "Source/imgProc/haarcascade_frontalface_alt.xml";
    string nestedCascadeName = "Source/imgProc/haarcascade_eye_tree_eyeglasses.xml";
	if( !nestedCascade.load( nestedCascadeName ) )
    {
        cerr << " ERROR: Could not load classifier nestedcascade" << endl;
        return -1;
    }

    if( !cascade.load( cascadeName ) )
    {
        cerr << " ERROR: Could not load classifier cascade" << endl;
        return -1;
    }
    // cascade.load( cascadeName );
        Mat frame(capture.rgbimg_full);
        return detectAndDraw(frame,cascade,nestedCascade);    
}

double detectAndDraw( Mat& img, CascadeClassifier& cascade,
                    CascadeClassifier& nestedCascade)
{
    int i = 0;
    double t = 0;
    vector<Rect> faces, faces2;
    const static Scalar colors[] =  { CV_RGB(0,0,255),
        CV_RGB(0,128,255),
        CV_RGB(0,255,255),
        CV_RGB(0,255,0),
        CV_RGB(255,128,0),
        CV_RGB(255,255,0),
        CV_RGB(255,0,0),
        CV_RGB(255,0,255)} ;
    Mat gray, smallImg( cvRound (img.rows/scale), cvRound(img.cols/scale), CV_8UC1 );

    cvtColor( img, gray, CV_BGR2GRAY );
    resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );
    equalizeHist( smallImg, smallImg );

    t = (double)cvGetTickCount();
    cascade.detectMultiScale( smallImg, faces,
        1.1, 2, 0
        //|CV_HAAR_FIND_BIGGEST_OBJECT
        //|CV_HAAR_DO_ROUGH_SEARCH
        |CV_HAAR_SCALE_IMAGE
        ,
        Size(30, 30) );
  
    t = (double)cvGetTickCount() - t;
    printf( "detection time = %g ms\n", t/((double)cvGetTickFrequency()*1000.) );
    for( vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++, i++ )
    {
        Mat smallImgROI;
        // vector<Rect> nestedObjects;
        cv::Point center;
        Scalar color = colors[i%8];
        int radius;

        double aspect_ratio = (double)r->width/r->height;
        if( 0.75 < aspect_ratio && aspect_ratio < 1.3 )
        {
            center.x = cvRound((r->x + r->width*0.5)*scale);
            center.y = cvRound((r->y + r->height*0.5)*scale);
            radius = cvRound((r->width + r->height)*0.25*scale);
            circle( img, center, radius, color, 2, 8, 0 );
            // imshow("result",img);
            return 1.0;
        }
        else
            return 0;
        // else
        //     rectangle( img, cvPoint(cvRound(r->x*scale), cvRound(r->y*scale)),
        //                cvPoint(cvRound((r->x + r->width-1)*scale), cvRound((r->y + r->height-1)*scale)),
        //                color, 3, 8, 0);
        // if( nestedCascade.empty() )
        //     continue;
        // smallImgROI = smallImg(*r);
        // nestedCascade.detectMultiScale( smallImgROI, nestedObjects,
        //     1.1, 2, 0
        //     //|CV_HAAR_FIND_BIGGEST_OBJECT
        //     //|CV_HAAR_DO_ROUGH_SEARCH
        //     //|CV_HAAR_DO_CANNY_PRUNING
        //     |CV_HAAR_SCALE_IMAGE
        //     ,
        //     Size(30, 30) );
        // for( vector<Rect>::const_iterator nr = nestedObjects.begin(); nr != nestedObjects.end(); nr++ )
        // {
        //     center.x = cvRound((r->x + nr->x + nr->width*0.5)*scale);
        //     center.y = cvRound((r->y + nr->y + nr->height*0.5)*scale);
        //     radius = cvRound((nr->width + nr->height)*0.25*scale);
        //     circle( img, center, radius, color, 3, 8, 0 );
        // }
    }
}