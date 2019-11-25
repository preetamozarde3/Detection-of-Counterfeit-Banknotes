
import cv2
from matplotlib import pyplot as plt
import numpy as np
import time as t

target_image = 'realf1.jpg'
img = cv2.imread(target_image)
channel = cv2.cvtColor(img, cv2.COLOR_RGB2YCrCb)
plt.imshow(channel)
plt.show()

channel0, channel1, channel2 = channel[:,:,0], channel[:,:,1], channel[:,:,2]

plt.figure(figsize=(10,8))
plt.subplot(311)                             #plot in the first cell
plt.subplots_adjust(hspace=.5)
plt.title("channel0")
plt.hist(np.ndarray.flatten(channel0), bins=256)
plt.subplot(312)                             #plot in the second cell
plt.title("channel1")
plt.hist(np.ndarray.flatten(channel1), bins=256)
plt.subplot(313)                             #plot in the third cell
plt.title("channel2")
plt.hist(np.ndarray.flatten(channel2), bins=256)
plt.show()
