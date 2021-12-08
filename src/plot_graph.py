#!/usr/bin/env python
import matplotlib.pyplot as plt

x = []
y = []

for line in open('./src/output_data.txt', 'r'):
    lines = [i for i in line.split()]
    x.append(lines[0])
    y.append(int(lines[1]))
      
plt.title("number of electric cars in CZR")
plt.xlabel('year')
plt.ylabel('electric cars')
plt.yticks(y)
plt.plot(x, y, marker = 'o', c = 'g')
  
plt.show()
