#!/usr/bin/env python
# coding=utf-8

from PIL import Image
from PIL import ImageFilter
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import numpy as np

src_img = Image.open("test1.bmp").convert("L")
src_img_array = np.array(src_img)
x,y = src_img_array.shape
dst_img_array = np.zeros((x,y),dtype=np.int)

threshold_value = 127

for i in range(0,x):
    for j in range(0,y):
        if(src_img_array[i,j] > threshold_value):
            dst_img_array[i,j] = 255
        else:
            dst_img_array[i,j] = 0

plt.subplot(2,1,1)
plt.imshow(src_img_array,cmap=plt.cm.gray)
plt.axis("off")
plt.subplot(2,1,2)
plt.imshow(dst_img_array,cmap=plt.cm.gray)
plt.axis("off")
plt.show()
