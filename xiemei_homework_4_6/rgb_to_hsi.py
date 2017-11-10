#!/usr/bin/env python
# coding=utf-8

from PIL import Image
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import numpy as np
import math
import cv2

PI = 3.141592653

def RGB2HSI(r,g,b):
    #rgb归一化
    r = r /255.0
    g = g /255.0
    b = b /255.0

    temp1 = 0.5*((r-g)+(r-b))
    temp2 = np.sqrt((r-g)*(r-g)+(r-b)*(g-b))
    theta = float(np.arccos(temp1/temp2))

    if(0 == temp2):
        h = 0
    elif(b <= g):
        h = theta
    else:
        h = 2*PI-theta

    min_rgb = min(r,g,b)
    temp3 = r+g+b
    if(0 == temp3):
        s = 0
    else:
        s = 1 - 3*min_rgb/temp3

    i = temp3/3

    #归一化到0-255
    h = 255*h/2*PI
    s = 255*s
    i = 255*i
#    print "next"
#    print h
#    print s
#    print i
    return [h,s,i]

src_img = cv2.imread('三原色.bmp')
src_img_array = np.array(src_img)
x,y,z = src_img.shape
print x
print y
print z
dst_img = src_img.copy()

for i in range(0,x):
    for j in range(0,y):
        b,g,r = src_img[i,j]
        k = RGB2HSI(r,g,b)
        dst_img[i,j,0] = k[0]
        dst_img[i,j,1] = k[1]
        dst_img[i,j,2] = k[2]

        #dst_img[i,j] = RGB2HSI(r,g,b)

#plt.subplot(2,1,1)
#plt.imshow(src_img_array)
#plt.axis("off")
#plt.subplot(2,1,2)
#plt.imshow(dst_img_array,cmap=cm.hsv)
#plt.axis("off")
#plt.show()

#cv2.cvtcolor(src_img,dst_img,
cv2.imshow("rgb",src_img)
cv2.imshow("hsi",dst_img)
key = cv2.waitKey(0)
if('q' == key):
    cv2.destoryAllWindows()
