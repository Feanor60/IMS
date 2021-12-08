#!/usr/bin/env python
import matplotlib.pyplot as plt

file = open('./input_data.txt', 'r')
lines = file.readlines()

x = []
y = [2013, 2014, 2015, 2016, 2017, 2018, 2019, 2020, 2021]

for line in lines:
    line = line.split() # split by space by default
    tmp = 0
    for letter in line:
        tmp += int(letter)
    x.append(tmp)
print(x)

plt.title("number of electric cars in CZR")
plt.xlabel('year')
plt.ylabel('electric cars')
plt.yticks(x)
plt.plot(y, x, marker = 'o', c = 'g')

plt.show()
