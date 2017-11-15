#!/usr/bin/env python
# coding=utf-8


import cv2
import numpy as np

L = 256
def Gray2RGB(gray):
    #red处理
    if(gray < L/2):
        r = 0
    elif(gray > L*0.75):
        r = 255
    else:
        r = 255.0/64.0*gray-510

    #green处理
    if(gray < L/4):
        g = gray *255*4/256
    elif(gray > L*0.75):
        g = 4*255-255/64*gray
    else:
        g = 255

    #blue处理
    if(gray < L/4):
        b = 255
    elif(gray > L/2):
        b = 0
    else:
        b = 2*255-255/64*gray

    return [b,g,r]
src_img = cv2.imread("lz.bmp",0)
x,y = src_img.shape
print x
print y
dst_img = np.zeros((x,y,3),np.uint8)

for i in range(0,x):
    for j in range(0,y):
        gray = src_img[i,j]
        dst_img[i,j] = Gray2RGB(gray)


cv2.imshow("gray",src_img)
cv2.imshow("rgb",dst_img)
cv2.imwrite("rgb.bmp",dst_img)
k = cv2.waitKey(0)
if('q' == k):
   cv2.destoryAllWindow() 
