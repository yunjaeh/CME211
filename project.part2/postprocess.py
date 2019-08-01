import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm
import sys

if len(sys.argv) < 3:
    print('Usage:')
    print('  python3 {} [input file] [solution file]'.format(sys.argv[0]))
    sys.exit(0)

input_file = sys.argv[1]
solution_file = sys.argv[2]

# open and read input file
file_input = open(input_file,"r")
inp_line_1 = file_input.readline().split()
inp_line_2 = file_input.readline().split()
file_input.close()

length = float(inp_line_1[0])
width = float(inp_line_1[1])
h = float(inp_line_1[2])
T_c = float(inp_line_2[0])
T_h = float(inp_line_2[1])

# number of nodes in x and y 
nx = int(length/h+1)
ny = int(width/h+1)

# x and y coordinates in linear space
x = np.linspace(0,length,nx)
y = np.linspace(0,width,ny)

# x and y coordinates in meshgrid
X, Y = np.meshgrid(x,y)

# read solution file
T = np.loadtxt(solution_file,dtype=float)
T_mean = T.mean()
x_iso_T = []
for i in range(0,nx):
    x_iso_T.append(np.interp(T_mean,T[:,i],y))

fig, ax = plt.subplots()
cs = ax.contourf(X,Y,T,40,cmap=cm.jet )

ax.plot(x,x_iso_T,'k')
ax.set_aspect('equal','box')
cbar = plt.colorbar(cs)


# print output in console and save figure
print("Input file processed: ", input_file)
print("mean Temperature: ", T_mean)

# plt.show()
plt.savefig(input_file+'.jpg')