#!/usr/bin/env python
# coding=utf-8


import cv2
import numpy as np

img = np.zeros((500,500,3),np.uint8)
x,y,z=img.shape
for i in range(0,x):
    for j in range(0,y):
        img[i,j] = 127,255,127

cv2.imshow("img",img)
cv2.imwrite("img.bmp",img)
key =cv2.waitKey(0)
if('q' == key):
    cv2.destoryAllWindows()
