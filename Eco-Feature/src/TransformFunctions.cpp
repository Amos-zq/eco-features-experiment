/******************************************************************************
 * Filename      : TransformFunctions.cpp
 * Header File(s): Transform.hpp
 * Description   :
 * Authors(s)    : 
 * Date Created  : 
 * Date Modified :
 * Modifier(s)   :
*******************************************************************************/
/************************************
 * Included Headers 
 ************************************/
#include "Transform.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cstdlib>

/************************************
 * Namespaces 
 ************************************/
using namespace std;
using namespace cv;
using namespace Transforms;

/************************************
 * Local Variables 
 ************************************/

/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::gabor_filter ( Mat src )
{
    Mat tmp;    
    cvtColor(src, transformed_image, CV_BGR2GRAY);
    transformed_image.convertTo(tmp, CV_32F, 1.0/255.0, 0);

    if ( paramaters.size() != GABOR_FILTER_PARAMETER_NUMBER )
        return;
    
    if ( paramaters[0] < 0 ) /* kernel size */
        paramaters[0] = 0;
    if ( !(int(paramaters[0])%2) )
        paramaters[0]++;
    
    if ( paramaters[1] < 0 ) /* sigma */
        paramaters[1] = 0;
    if ( paramaters[1] > paramaters[0] )
        paramaters[1] = paramaters[0];
    
    if ( paramaters[2] < 0 ) /* theta */
        paramaters[2] = 0;
    if ( paramaters[2] > 180 ) 
        paramaters[2] = 180;
        
    if ( paramaters[3] < 0 ) /* lambda */
        paramaters[3] = 0;
    if ( paramaters[3] > 100 )
        paramaters[3] = 100;
    
    if ( paramaters[4] < 0.2 ) /* gamma */
        paramaters[4] = 0.2;
    if ( paramaters[4] > 1 )
        paramaters[4] = rand() / double(RAND_MAX);
    
    if ( paramaters[5] < 0 ) /* psi */
        paramaters[5] = 0;
     if ( paramaters[5] > 360 )
        paramaters[5] = 360;
        
        
    
    Size size(paramaters[0],paramaters[0]);
    double sigma  = paramaters[1]/((paramaters[0]==0)?1:paramaters[0]);
    double theta  = paramaters[2]*CV_PI/180;
    double lambda = paramaters[3];
    double gamma  = paramaters[4];
    double psi    = paramaters[5]*CV_PI/180;
    
#if DEFINE_COMPUTE_GF_KERNEL
    int ks=21;
        
    double sig = 5;             // 0 - kernel_size
    double lm = 0.5+50.0/100.0; // 0 - 100
    double th = 0;              // 0 - 180
    double ps = 90;             // 0 - 360
    
    
    if (!ks%2)
    {
        ks+=1;
    }      
    int hks = (ks-1)/2;
    double theta = th*CV_PI/180;
    double psi = ps*CV_PI/180;
    double del = 2.0/(ks-1);
    double lmbd = lm;
    double sigma = sig/ks;
    double x_theta;
    double y_theta;
    
    Mat kernel(ks,ks, CV_32F);
    for (int y=-hks; y<=hks; y++)
    {
        for (int x=-hks; x<=hks; x++)
        {
            x_theta = x*del*cos(theta)+y*del*sin(theta);
            y_theta = -x*del*sin(theta)+y*del*cos(theta);
            kernel.at<float>(hks+y,hks+x) = (float)exp(-0.5*(pow(x_theta,2)+pow(y_theta,2))/pow(sigma,2))* cos(2*CV_PI*x_theta/lmbd + psi);
        }
    }
    filter2D(tmp, transformed_image, CV_32F, kernel);    
#else
    filter2D(tmp, transformed_image, CV_32F, getGaborKernel(size,sigma,theta,lambda,gamma,psi,CV_32F));
#endif    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::morphological_erode ( cv::Mat src )
{
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::haussian_blur ( cv::Mat src )
{
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::histogram ( cv::Mat src )
{
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::hough_circles ( cv::Mat src )
{
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::normalize ( cv::Mat src )
{
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::discrete_fourier_transform ( cv::Mat src )
{
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::square_root ( cv::Mat src )
{
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::canny_edge ( cv::Mat src )
{
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::integral_image ( cv::Mat src )
{
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::difference_gaussians ( cv::Mat src )
{
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::census_transform ( cv::Mat src )
{
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::sobel_operator ( cv::Mat src )
{
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::morphological_dilate ( cv::Mat src )
{
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::adaptive_thresholding ( cv::Mat src )
{
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::hough_lines ( cv::Mat src )
{
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::harris_corner_strength ( cv::Mat src )
{
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::histogram_equalization ( cv::Mat src )
{
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::log ( cv::Mat src )
{
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::median_blur ( cv::Mat src )
{
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::distance_transform ( cv::Mat src )
{
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::laplacian_edged_etection ( cv::Mat src )
{
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::rank_transform ( cv::Mat src )
{
    
}
/*******************************************************************************
* Function     : 
* Description  : 
* Arguments    : 
* Returns      : 
* Remarks      : 
********************************************************************************/
void Transform::convert ( cv::Mat src )
{
    
}
