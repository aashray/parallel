# Uncomment 2 lines below to create a .png file instead of displaying using X
#set terminal png size 600, 600
#set output "det-cc-cilkviewapi-v2.png"
# Set aspect ration, zoom factor
set size square 1.0, 1.0
# Set plot title
set title "Trial results for det-cc-cilkviewapi-v2"
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
2967.147049 notitle lt 2, \
'-' title 'Burdened Parallelism' with lines lt 1
1 1.000000
2 1.900000
3 2.795863
4 3.605159
5 4.362895
6 5.073846
7 5.742214
8 6.371715
9 6.965642
10 7.526929
11 8.058195
12 8.561784
13 9.039805
14 9.494158
15 9.926556
16 10.338555
e
