#!/usr/bin/env python
# coding=utf-8

#使用拉普拉斯算子锐化图像

import numpy as np
import cv2 

src_img = cv2.imread("test1.bmp",0)
x,y = src_img.shape
print x
print y
gaussian_img = cv2.GaussianBlur(src_img,(5,5),1.5) #高斯低通滤波 增强图像
retval,threshold_img = cv2.threshold(gaussian_img,127,255,cv2.THRESH_BINARY) #二值化图像

cv2.imshow("src_img",src_img)
cv2.imshow("gaussian_img",gaussian_img)
cv2.imshow("threshold_img",threshold_img)
cv2.imwrite("gaussian_result.png",gaussian_img)
cv2.imwrite("threshold_result.png",threshold_img)
#show()

k = cv2.waitKey(0)
if('q' == k):
    cv2.destoryAllWindow()
