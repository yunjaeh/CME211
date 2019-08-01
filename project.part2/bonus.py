import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import cm
import numpy as np
import sys

if len(sys.argv) < 3:
    print('Usage:')
    print('  python3 {} [input file] [solution prefix]'.format(sys.argv[0]))
    sys.exit(0)

# open and read input file
input_file = sys.argv[1]
solution_file = sys.argv[2]

file_input = open(input_file,"r")
inp_line_1 = file_input.readline().split()
inp_line_2 = file_input.readline().split()
file_input.close()

length = float(inp_line_1[0])
width = float(inp_line_1[1])
h = float(inp_line_1[2])
T_c = float(inp_line_2[0])
T_h = float(inp_line_2[1])

nx = int(length/h+1)
ny = int(width/h+1)

# x and y coordinates in linear space
x = np.linspace(0,length,nx)
y = np.linspace(0,width,ny)

# x and y coordinates in meshgrid
X, Y = np.meshgrid(x,y)

# initialize sets of contour plots
fig,ax = plt.subplots()
plt_set =[]

# append contour plot of every 10 iterations
for i in range(0,int(nx*ny/10)):
    num_output = i*10
    title = solution_file +'_'+ str(num_output)+'.txt'
    try:
        T = np.loadtxt(title,dtype=float)
    except:
        break
    cs = ax.contourf(X,Y,T, 50,cmap=cm.jet)
    plt_set.append(cs.collections)

# append contour plot of the last iteration
for j in range(1,10):
    title = solution_file +'_'+ str((i-1)*10+j)+'.txt'
    try:
        T = np.loadtxt(title,dtype=float)
        cs = plt.contourf(X,Y,T, 50,cmap=cm.jet)
        plt_set.append(cs.collections)
    except:
        continue
    
cbar = fig.colorbar(cs)
ax.set_aspect('equal','box')
    
im_ani =animation.ArtistAnimation(fig,plt_set,500,blit=False)    
# im_ani.save('im.mp4')
plt.show()