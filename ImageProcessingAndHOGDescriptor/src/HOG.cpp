/*
 * HOG.cpp
 *
 *  Created on: Dec 28, 2018
 *      Author: hossam
 */

#include "HOG.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include<string>
using namespace cv;
using namespace std;

HOG::HOG(Mat Original) {
	// TODO Auto-generated constructor stub
	src=Original;
}

void HOG::computeHOG(const Mat& img,std::vector<float>& feats,Size _wsize,Size _blockSize,Size _blockStride,Size _cellSize,int _nbins){
	hog_detector.winSize = _wsize;
	hog_detector.blockSize=_blockSize;
	hog_detector.blockStride=_blockStride;
	hog_detector.cellSize=_cellSize;
	hog_detector.nbins=_nbins;
	hog_detector.compute( img, feats,Size(8,8),Size(0,0));
}

void HOG::GrayScale(Mat &dst){
cvtColor( src, dst, COLOR_BGR2GRAY );

}
void HOG::Resized(Mat &dst,float xfactor,float yfactor){
	resize(src, dst,Size(src.cols * xfactor,src.rows * yfactor),0,0);
}
void HOG::Rotated(Mat &dst,double angle,double scale){
	 Mat rot_mat( 2, 3, CV_32FC1 );
	 Point center = Point( src.cols/2, src.rows/2 );
	 rot_mat = getRotationMatrix2D( center, angle, scale );
	  warpAffine( src, dst, rot_mat, src.size() );

}
void HOG::Flip(Mat &dst,int x){
	flip(src, dst, x);
}
void HOG::visualizeHOG(const Mat& img,std::vector<float> &feats,String s,int scale_factor) {

    Mat visual_image;
    resize(img, visual_image, Size(img.cols * scale_factor, img.rows * scale_factor));

    int n_bins = hog_detector.nbins;
    float rad_per_bin = 3.14 / (float) n_bins;
    Size win_size = hog_detector.winSize;
    Size cell_size = hog_detector.cellSize;
    Size block_size = hog_detector.blockSize;
    Size block_stride = hog_detector.blockStride;

    // prepare data structure: 9 orientation / gradient strenghts for each cell
    int cells_in_x_dir = win_size.width / cell_size.width;
    int cells_in_y_dir = win_size.height / cell_size.height;
    int n_cells = cells_in_x_dir * cells_in_y_dir;
    int cells_per_block = (block_size.width / cell_size.width) * (block_size.height / cell_size.height);

    int blocks_in_x_dir = (win_size.width - block_size.width) / block_stride.width + 1;
    int blocks_in_y_dir = (win_size.height - block_size.height) / block_stride.height + 1;
    int n_blocks = blocks_in_x_dir * blocks_in_y_dir;

    float ***gradientStrengths = new float **[cells_in_y_dir];
    int **cellUpdateCounter = new int *[cells_in_y_dir];
    for (int y = 0; y < cells_in_y_dir; y++) {
        gradientStrengths[y] = new float *[cells_in_x_dir];
        cellUpdateCounter[y] = new int[cells_in_x_dir];
        for (int x = 0; x < cells_in_x_dir; x++) {
            gradientStrengths[y][x] = new float[n_bins];
            cellUpdateCounter[y][x] = 0;

            for (int bin = 0; bin < n_bins; bin++)
                gradientStrengths[y][x][bin] = 0.0;
        }
    }


    // compute gradient strengths per cell
    int descriptorDataIdx = 0;


    for (int block_x = 0; block_x < blocks_in_x_dir; block_x++) {
        for (int block_y = 0; block_y < blocks_in_y_dir; block_y++) {
            int cell_start_x = block_x * block_stride.width / cell_size.width;
            int cell_start_y = block_y * block_stride.height / cell_size.height;

            for (int cell_id_x = cell_start_x;
                 cell_id_x < cell_start_x + block_size.width / cell_size.width; cell_id_x++)
                for (int cell_id_y = cell_start_y;
                     cell_id_y < cell_start_y + block_size.height / cell_size.height; cell_id_y++) {

                    for (int bin = 0; bin < n_bins; bin++) {
                        float val = feats.at(descriptorDataIdx++);
                        gradientStrengths[cell_id_y][cell_id_x][bin] += val;
                    }
                    cellUpdateCounter[cell_id_y][cell_id_x]++;
                }
        }
    }


    // compute average gradient strengths
    for (int celly = 0; celly < cells_in_y_dir; celly++) {
        for (int cellx = 0; cellx < cells_in_x_dir; cellx++) {

            float NrUpdatesForThisCell = (float) cellUpdateCounter[celly][cellx];

            // compute average gradient strenghts for each gradient bin direction
            for (int bin = 0; bin < n_bins; bin++) {
                gradientStrengths[celly][cellx][bin] /= NrUpdatesForThisCell;
            }
        }
    }


    for (int celly = 0; celly < cells_in_y_dir; celly++) {
        for (int cellx = 0; cellx < cells_in_x_dir; cellx++) {
            int drawX = cellx * cell_size.width;
            int drawY = celly * cell_size.height;

            int mx = drawX + cell_size.width / 2;
            int my = drawY + cell_size.height / 2;

            rectangle(visual_image,
                      Point(drawX * scale_factor, drawY * scale_factor),
                      Point((drawX + cell_size.width) * scale_factor,
                                (drawY + cell_size.height) * scale_factor),
                      CV_RGB(100, 100, 100),
                      1);

            for (int bin = 0; bin < n_bins; bin++) {
                float currentGradStrength = gradientStrengths[celly][cellx][bin];

                if (currentGradStrength == 0)
                    continue;

                float currRad = bin * rad_per_bin + rad_per_bin / 2;

                float dirVecX = cos(currRad);
                float dirVecY = sin(currRad);
                float maxVecLen = cell_size.width / 2;
                float scale = scale_factor / 5.0; // just a visual_imagealization scale,

                // compute line coordinates
                float x1 = mx - dirVecX * currentGradStrength * maxVecLen * scale;
                float y1 = my - dirVecY * currentGradStrength * maxVecLen * scale;
                float x2 = mx + dirVecX * currentGradStrength * maxVecLen * scale;
                float y2 = my + dirVecY * currentGradStrength * maxVecLen * scale;

                // draw gradient visual_imagealization
                line(visual_image,
                     Point(x1 * scale_factor, y1 * scale_factor),
                     Point(x2 * scale_factor, y2 * scale_factor),
                     CV_RGB(0, 0, 255),
                     1);

            }

        }
    }


    for (int y = 0; y < cells_in_y_dir; y++) {
        for (int x = 0; x < cells_in_x_dir; x++) {
            delete[] gradientStrengths[y][x];
        }
        delete[] gradientStrengths[y];
        delete[] cellUpdateCounter[y];
    }
    delete[] gradientStrengths;
    delete[] cellUpdateCounter;
    imwrite( s, visual_image);
    imshow(s, visual_image);
    waitKey(-1);
}
HOG::~HOG() {
	// TODO Auto-generated destructor stub
}



