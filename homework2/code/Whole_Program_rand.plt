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
16.506890 notitle lt 2, \
'-' title 'Burdened Parallelism' with lines lt 1
1 1.000000
2 1.812006
3 2.484477
4 3.050532
5 3.533580
6 3.950632
7 4.314347
8 4.634344
9 4.918057
10 5.171326
11 5.398802
12 5.604235
13 5.790680
14 5.960654
15 6.116247
16 6.259209
e
