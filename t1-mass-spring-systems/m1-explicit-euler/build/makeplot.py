import matplotlib.pyplot as plt
import sys

if len(sys.argv) != 8 :
  print "Invalid arguments to " + sys.argv[0]
  print "Usage: python " + sys.argv[0] + " file_to_plot output_file.png x_column y_column x_label y_label title"
  sys.exit()

datafilename = sys.argv[1]
outputfilename = sys.argv[2]
xcol = int(sys.argv[3])
ycol = int(sys.argv[4])
xlabel = sys.argv[5]
ylabel = sys.argv[6]
title = sys.argv[7]

# Load numeric data from the datafile
datafile = open(datafilename, 'r')

firstline = datafile.readline().split()

if( xcol < 0 or xcol >= len(firstline) ):
  print "Invalid data column selected for x axis"
  datafile.close()
  sys.exit()

if( ycol < 0 or ycol >= len(firstline) ):
  print "Invalid data column selected for y axis"
  datafile.close()
  sys.exit()

data = []
i = 0
for col in firstline:
  data.append([float(col)])
  i += 1

for line in datafile:
  contents = line.split()
  i = 0
  for col in contents:
    data[i].append(float(col))
    i += 1

datafile.close()

plt.plot(data[xcol],data[ycol])
plt.xlabel(xlabel)
plt.ylabel(ylabel)
plt.title(title)
#plt.show()
plt.savefig(outputfilename)

