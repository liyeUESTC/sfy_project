#!/usr/bin/env python
# coding=utf-8

from PIL import Image
import matplotlib.pyplot as plt
import numpy as np
import matplotlib.cm as cm

img =Image.open('test1.bmp').convert("L") #打开图像文件 并转换为灰度图像
src_img_array = np.array(img)                 #获得图像的元素矩阵
size = src_img_array.size
dst_img_array = np.array(img)


list1 = [0]*256  #建立256位的空数组   
list2 = [0]*256     #

#直方图计算和均衡算法
for element in src_img_array.flat:     #计算像素出现的次数
    list1[element] = list1[element] + 1;

pre_sum = 0;
for i in range(len(list1)): #计算概率密度 和 概率分布
    if(0 != list1[i]):
        list1[i] = list1[i] / float(size)
        list2[i] = pre_sum + list1[i]
        pre_sum = list2[i]


for i in range(len(list2)):
    if(list2[i] != 0):
        list2[i] = int(255 * list2[i]+0.5)  #四舍五入取整

x,y = dst_img_array.shape
for i in range(x):
    for j in range(y):
        dst_img_array[i,j] = list2[dst_img_array[i,j]]  #改变原图像值


#图像显示和保存
plt.subplot(2,2,1)
plt.imshow(src_img_array,cmap=plt.cm.gray)
plt.axis("off")
plt.subplot(2,2,2)
plt.hist(src_img_array.flatten(),256)
#plt.show()
plt.subplot(2,2,3)
plt.imshow(dst_img_array,cmap=plt.cm.gray)
plt.axis("off")
plt.subplot(2,2,4)
plt.hist(dst_img_array.flatten(),256)
plt.show()

#dst_img = Image.fromarray(dst_img_array)
#dst_img.save("./test1_process.bmp")
