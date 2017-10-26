#!/usr/bin/env python
# coding=utf-8

from PIL import Image
import matplotlib.pyplot as plt
import numpy as np
import matplotlib.cm as cm

def GetMid(list):          #排序 并返回中值
    if(0 == len(list) % 2):
#        print len(list)
        return
    for i in range(len(list)):
        for j in range(i+1,len(list)):
            if(list[j] < list[i]):
                temp = list[i]
                list[i] = list[j]
                list[j] = temp

    return list[int(len(list)/2)]

img =Image.open('test2.bmp').convert("L") #打开图像文件 并转换为灰度图像
src_img_array = np.array(img) #获得图像的元素矩阵
dst_img_array = np.array(img)
list = []

#中值滤波算法部分
x,y = dst_img_array.shape
for i in range(1,x-1):      #边缘部分不处理
    for j in range(1,y-1):    
#        if((i-1 < 0) or (j-1<0) or (i+1) >= :
#            continue
        for u in range(i-1,i+2):      #将与模板重合的像素点放入排序容器中
            for v in range(j-1,j+2):
#                print u
                list.append(dst_img_array[u,v])
        dst_img_array[i,j] = GetMid(list)   #与模板中心点重合的像素点的值设为中值
        del list[:]


#图像显示和保存
plt.subplot(2,1,1)
plt.imshow(src_img_array,cmap=plt.cm.gray)
plt.axis("off")
plt.subplot(2,1,2)
plt.imshow(dst_img_array,cmap=plt.cm.gray)
plt.axis("off")
plt.show()

dst_img = Image.fromarray(dst_img_array)
dst_img.save("./test2_process.bmp")
