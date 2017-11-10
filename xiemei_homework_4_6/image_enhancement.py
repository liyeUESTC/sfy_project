#!/usr/bin/env python
# coding=utf-8

#使用拉普拉斯算子锐化图像

from PIL import Image
from PIL import ImageFilter
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import numpy as np

src_img = Image.open("test1.bmp").convert("L")  #打开图像文件 并转换为灰度图像
#dst_img1 = src_img.filter(ImageFilter.SHARPEN)    #锐化滤波器  增强图像边缘
src_img_array = np.array(src_img,dtype=int)
x,y = src_img_array.shape
dst_img_array = np.zeros((x,y),dtype=np.int)
#dst_img_array1 = np.array(dst_img1)


for i in range(0,x):
    for j in range(0,y):
        if((0 == i) or (x-1 == i) or (0 == j) or (y-1 == j)):
            dst_img_array[i,j] = src_img_array[i,j]
        else:
            second_diff = int(4*src_img_array[i,j] - src_img_array[i-1,j]-src_img_array[i+1,j]-src_img_array[i,j-1]-src_img_array[i,j+1]) 
       # print(second_diff)
       # temp = dst_img_array[i,j] + second_diff
            dst_img_array[i,j] = src_img_array[i,j] + second_diff


min = 0
max = 255
for i in range(0,x):
    for j in range(0,y):
        if(dst_img_array[i,j] < 0):
            min = dst_img_array[i,j]
        elif(dst_img_array[i,j] > 255):
            max = dst_img_array[i,j]

print min
print max
for i in range(0,x):
    for j in range(0,y):
        dst_img_array[i,j] = 255*(dst_img_array[i,j] - min)/(max-min)
        print dst_img_array[i,j]

plt.subplot(2,1,1)
plt.imshow(src_img_array,cmap=plt.cm.gray)
plt.axis("off")
plt.subplot(2,1,2)
plt.imshow(dst_img_array,cmap=plt.cm.gray)
plt.axis("off")
plt.show()
