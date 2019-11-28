#include "ORBextractor.h"
#include <fstream>
#include <iostream>
#include <opencv2/features2d.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;
using namespace ORB_SLAM2;
void GrabImage(cv::Mat &mImGray, int mbRGB)
{
    if(mImGray.channels()==3)
    {
        if(mbRGB)
        {
            cvtColor(mImGray,mImGray,CV_RGB2GRAY);
        }
        else
        {
            cvtColor(mImGray,mImGray,CV_BGR2GRAY);
        }
    }
    else if(mImGray.channels()==4)
    {
        if(mbRGB)
        {
            cvtColor(mImGray,mImGray,CV_RGBA2GRAY);
        }
        else
        {
            cvtColor(mImGray,mImGray,CV_BGRA2GRAY);
        }
    }

}
int main(int argc, char **argv)
{
    if(argc != 3)
    {
        cerr << endl << "Usage: ./ORBextractor path_to_a_picture named liu.png path to orb.yaml" << endl;
        return 1;
    }
    cout << "liu";
    string strSettingPath = argv[2];

    // 载入参数文件
    cv::FileStorage fSettings(strSettingPath, cv::FileStorage::READ);

    // 1:RGB 0:BGR
    int nRGB = fSettings["Camera.RGB"];

    if(nRGB)
        cout << "- color order: RGB (ignored if grayscale)" << endl;
    else
        cout << "- color order: BGR (ignored if grayscale)" << endl;

    // 每一帧提取的特征点数 1000
    int nFeatures = fSettings["ORBextractor.nFeatures"];
    // 图像建立金字塔时的变化尺度 1.2
    float fScaleFactor = fSettings["ORBextractor.scaleFactor"];
    // 尺度金字塔的层数 8
    int nLevels = fSettings["ORBextractor.nLevels"];
    // 提取fast特征点的默认阈值 20
    int fIniThFAST = fSettings["ORBextractor.iniThFAST"];
    // 如果默认阈值提取不出足够fast特征点，则使用最小阈值 8
    int fMinThFAST = fSettings["ORBextractor.minThFAST"];
    cout << endl  << "ORB Extractor Parameters: " << endl;
    cout << "- Number of Features: " << nFeatures << endl;
    cout << "- Scale Levels: " << nLevels << endl;
    cout << "- Scale Factor: " << fScaleFactor << endl;
    cout << "- Initial Fast Threshold: " << fIniThFAST << endl;
    cout << "- Minimum Fast Threshold: " << fMinThFAST << endl;
    
//******************************************************************************************************************************************
    // 初始化mpORBextractorLeft作为特征点提取器  
    ORBextractor* mpORBextractorLeft = new ORBextractor(nFeatures,fScaleFactor,nLevels,fIniThFAST,fMinThFAST);
   
    // 载入原图
    cv::Mat imLeft;   
    imLeft = cv::imread(argv[1],CV_LOAD_IMAGE_UNCHANGED);
    if( imLeft.empty() )                      
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
    // 转为灰度图
    cv::Mat &mImGray = imLeft;
    GrabImage(mImGray,nRGB);
 
    // 当前帧图像中提取的特征点集合
    std::vector<cv::KeyPoint> mvKeys;
    // 特征点对应的描述子
    cv::Mat mDescriptors;
    (*mpORBextractorLeft)(mImGray,cv::Mat(),mvKeys,mDescriptors);
    
    // diaplay
    Mat out1;
    //drawKeypoints(imLeft, mvKeys, out1, Scalar::all(-1), DrawMatchesFlags::DEFAULT); 
    drawKeypoints(imLeft, mvKeys, out1, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS); 
    namedWindow("orb_features", WINDOW_NORMAL);
    imshow("orb_features", out1);
    waitKey(0);
    imwrite("orb_features.jpg", out1);
    return 0;

}    