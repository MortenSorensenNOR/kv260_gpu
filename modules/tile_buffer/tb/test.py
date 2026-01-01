import numpy as np
import matplotlib.pyplot as plt

# Correct order: (height, width, 3)
img = np.zeros((100, 200, 3), dtype=int)
img[:, :100] = [255, 0, 0]  # Left half red
img[:, 100:] = [0, 0, 255]  # Right half blue
plt.imshow(img)
plt.show()  # Shows wide image (200 wide, 100 tall)
