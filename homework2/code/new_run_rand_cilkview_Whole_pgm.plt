# Uncomment 2 lines below to create a .png file instead of displaying using X
#set terminal png size 600, 600
#set output "Whole_Program.png"
# Set aspect ration, zoom factor
set size square 1.0, 1.0
# Set plot title
set title "Trial results for Whole Program"
# Set X, Y axis titles
set xlabel "Worker Count"
set ylabel "Speedup"
# Specify where key is to be displayed
set key left top box
# Make points a bit bigger than the defaultset pointsize 1.8
set xrange [0:16]
set yrange [0:16]
# Plot the data
plot x title 'Parallelism' lt 2, \
16.515512 notitle lt 2, \
'-' title 'Burdened Parallelism' with lines lt 1
1 1.000000
2 1.812095
3 2.484698
4 3.050907
5 3.534117
6 3.951331
7 4.315205
8 4.635354
9 4.919212
10 5.172620
11 5.400227
12 5.605783
13 5.792344
14 5.962427
15 6.118123
16 6.261184
e
