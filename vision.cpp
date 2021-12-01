#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::vision(image_t *img)
{

    //----------------------
    // SUDOKU
    //----------------------

    // Show the original image
    showImg(img, "source image");

    // Make sure we are using a basic image for further processing
    image_t *src = toBasicImage(img);
    showImg(src, "basic image");

    // Create a destination image
    image_t *dst = newBasicImage(src->cols, src->rows);

    int32_t i, j;

    //adaptive threshold
    nonlinearFilter(src,dst,AVERAGE,7);
    subtract(src, dst);
    threshold(dst, dst, 0, 1);
    invert(dst,dst);
    showImg(dst, "thresh");

    //label blobs
    int32_t blobCount = (int32_t)labelBlobs(dst,dst,EIGHT);
    showImg(dst, "label blobs");

    //find biggest blob
    uint32_t biggestBlob;
    uint64_t maxSize = 0;
    for(i = 1; i <= blobCount; i++)
    {
        blobinfo_t info = {0,0,0,0};
        blobAnalyse(dst,i,&info);
        if((uint32_t)info.nof_pixels > maxSize){
            biggestBlob = i;
            maxSize = (uint32_t)info.nof_pixels;
        }
    }
    //remove all non biggest blobs
    for(i = dst->rows -1; i > -1; i--)
    {
        // Loop all pixels in the image (cols)
        for(j = dst->cols -1; j > -1; j--)
        {
            if(getBasicPixel(dst,j,i) != biggestBlob)
            {
                setBasicPixel(dst,j,i,0);
            }
        }
    }
    //set biggest blob to 1
    for(i = dst->rows -1; i > -1; i--)
    {
        // Loop all pixels in the image (cols)
        for(j = dst->cols -1; j > -1; j--)
        {
            if(getBasicPixel(dst,j,i) != 0)
            {
                setBasicPixel(dst,j,i,1);
            }
        }
    }
    showImg(dst, "biggest blob");

    //label blobs again in case of more than 256 blobs
    blobCount = (int32_t)labelBlobs(dst,dst,EIGHT);
    showImg(dst, "label blobs2");


    //find biggest blob
    maxSize = 0;
    for(i = 1; i <= blobCount; i++)
    {
        blobinfo_t info = {0,0,0,0};
        blobAnalyse(dst,i,&info);
        if((uint32_t)info.nof_pixels > maxSize){
            biggestBlob = i;
            maxSize = (uint32_t)info.nof_pixels;
        }
    }
    //remove all non biggest blobs
    for(i = dst->rows -1; i > -1; i--)
    {
        // Loop all pixels in the image (cols)
        for(j = dst->cols -1; j > -1; j--)
        {
            if(getBasicPixel(dst,j,i) != biggestBlob)
            {
                setBasicPixel(dst,j,i,0);
            }
        }
    }
    showImg(dst, "biggest blob2");
    uint32_t topLeftX,topLeftY;
    uint32_t bottomLeftX, bottomLeftY;
    uint32_t topRightX, topRightY;
    uint32_t bottomRightX, bottomRightY;

    //decide in which corner the point belongs
    int32_t sum = 0; //minimum sum = top left, maximum sum = bottom right
    int32_t diff; //maximum diff (x - y) = top right, minimum diff = bottom left

    int32_t maxDiff = 0;
    int32_t minDiff = dst->rows + dst->cols;
    int32_t maxSum = 0;
    int32_t minSum = dst->rows + dst->cols;


    // RB -> LT
    // Loop all pixels in the image (rows)
    for(i = dst->rows - 1; i > -1; i--)
    {
        // Loop all pixels in the image (cols)
        for(j = dst->cols - 1; j > -1; j--)
        {
            if(getBasicPixel(dst,j,i) == biggestBlob)
            {
                sum = j + i;
                diff = j - i;

                //top right
                if (diff >= maxDiff)
                {
                    maxDiff = diff;
                    topRightX = j;
                    topRightY = i;
                }
                //bottom left
                if (diff <= minDiff)
                {
                    minDiff = diff;
                    bottomLeftX = j;
                    bottomLeftY = i;
                }
                //bottom right
                if (sum >= maxSum)
                {
                    maxSum = sum;
                    bottomRightX = j;
                    bottomRightY = i;
                }
                //top left
                if (sum <= minSum)
                {
                    minSum = sum;
                    topLeftX = j;
                    topLeftY = i;
                }
            }
        }
    }

    image_t *warp = newBasicImage(1000, 1000);
    image_t *cutout = newBasicImage(450, 450);
    erase(warp);
    setSelectedToValue(warp,warp,0,255);

    // Warp image
    uint32_t pointsSrc[4][2] = {{topLeftX,topLeftY},{topRightX,topRightY},{bottomLeftX,bottomLeftY},{bottomRightX,bottomRightY}};
    uint32_t pointsDst[4][2] = {{0,0},{450,0},{0,450},{450,450}};

    //copy = copyRectMinMax(src,minX,minY,);
    //showImg(copy,"cut");
    contrastStretch(src,src,0,254);
    showImg(src, "stretched");
    warpBasic(src,warp,pointsSrc,pointsDst);
    showImg(warp, "warped");

    copyRect(warp,cutout,0,0,450,450);
    showImg(cutout, "cutout");
    interpolate(cutout);
    showImg(cutout, "interpolated");

    //adaptive threshold
    image_t *temp = newBasicImage(450, 450);
    nonlinearFilter(cutout,temp,AVERAGE,7);
    subtract(cutout, temp);
    threshold(temp, cutout, 0, 1);
    deleteImage(temp);
    invert(cutout,cutout);
    showImg(cutout, "warpthresh");

    image_t *smallcutout = newBasicImage(50,50);
    uint32_t m,n;
    //rows
    for (m = 0; m < 450; m += 50)
    {
        //columns
        for (n = 0; n < 450; n += 50)
        {
            copyRect(cutout,smallcutout,m,n,50,50);
            showImg(smallcutout, "smallcutout");
            //------------------------------------AI stuff hier met smallcutout-----------------------------------
        }
    }

    // Clean up
    deleteImage(warp);
    deleteImage(cutout);

    //----------------------
    // EINDE SUDOKU
    //----------------------
    deleteImage(src);
    deleteImage(dst);

}
