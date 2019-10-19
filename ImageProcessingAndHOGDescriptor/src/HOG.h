/*
 * HOG.h
 *
 *  Created on: Dec 28, 2018
 *      Author: hossam
 */

#ifndef SRC_HOG_H_
#define SRC_HOG_H_
#include <opencv2/opencv.hpp>
#include<string>
using namespace cv;
class HOG {
public:
	HOGDescriptor hog_detector;
	HOG(Mat Original);
	Mat src;
	virtual ~HOG();
	/*
	 * img - the image used for computing HOG descriptors. **Attention here the size of the image should be the same as the window size of your cv::HOGDescriptor instance **
	 * feats - the hog descriptors you get after calling cv::HOGDescriptor::compute
	 * hog_detector - the instance of cv::HOGDescriptor you used
	 * scale_factor - scale the image *scale_factor* times larger for better visualization
	 */
	void visualizeHOG(const Mat& img,std::vector<float> &feats,String s,int scale_factor = 3);
/*
 * src: image
 * Size _winSize: window size. A window contains multiple blocks, and the
	descriptor for a window is a concatenation of all the descriptors of those blocks
	within that window.
 * Size _blockSize: block size. A block contains multiple cells, and the descriptor
	for a block is a concatenation of all the histograms from cells within that block.
 * Size _blockStride: stride of sliding block
 * Size _cellSize: cell size, the minimal unit for computing histogram.
 * int _nbins: number of bins for histograms
 */
	void computeHOG(const Mat& img,std::vector<float>& feats,Size _wsize=Size(64, 128),Size _blockSize=Size(16, 16),Size _blockStride=Size(8, 8),Size _cellSize=Size(8, 8),int _nbins=9);
	void GrayScale(Mat &dst);
	void Resized(Mat &dst,float xfactor=0.75,float yfactor=70.5);
	void Rotated(Mat &dst,double angle=60,double scale=1);
	void Flip(Mat &dst,int x=0);

};

#endif /* SRC_HOG_H_ */
