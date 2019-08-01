import sys
import numpy as np

if len(sys.argv) < 3:
    print('Usage:')
    print('     pythone3 {} [maze file] [solution file]'.format(sys.argv[0]))
    sys.exit(0)

input_maze = sys.argv[1]
input_solution = sys.argv[2]

dat_maze = np.loadtxt(input_maze,dtype=int)
dat_sol = np.loadtxt(input_solution,dtype=int)

# store length of data
len_maze = dat_maze.shape[0]
len_sol = dat_sol.shape[0]
# print(len_maze,len_sol)


# the number of Row and Column of the maze
nRow = dat_maze[0][0]
nCol = dat_maze[0][1]
print('Maze size : ',nRow,'x',nCol)

# construct maze
#   0 for open 
#   1 for walls
maze = np.zeros((nRow,nCol))
for i in range(1,len_maze):
#     print(dat_maze[i][0],dat_maze[i][1])
    maze[dat_maze[i][0],dat_maze[i][1]]=1

# test section
# store the result of three tests
test =[0, 0, 0]
#-------------------------------------------------------------------------#
print('--------------------')
print('Check starting and end points are valid :')
print('(Starts from the first row and ends at the last row)')
if(dat_sol[0][0]!=0 or dat_sol[len_sol-1][0] != nRow-1):
    print('\tERROR, INVALID!')
    test[0]=1
else:
    print('\tPASS, VALID!')

#-------------------------------------------------------------------------#
print('--------------------')    
is_block = 0;
print('Check whether the path includes blocked position(wall)')
for i in range(0,len_sol):
    is_block+=maze[dat_sol[i][0],dat_sol[i][1]]
if(is_block):
    print('\tERROR, INVALID!')
    test[1]=1
else:
    print('\tPASS, VALID!')

#-------------------------------------------------------------------------#
print('--------------------')
print('Check each step has one increment')
print('(all of step size == 1 ?)')
step_size=0
for i in range(0,len_sol-1):
    step_size+=abs(dat_sol[i+1][0]-dat_sol[i][0])\
            +abs(dat_sol[i+1][1]-dat_sol[i][1])

if(step_size != (len_sol-1)):
    print('\tERROR, INVALID!')
    test[2]=1
else:
    print('\tPASS, VALID!')

#-------------------------------------------------------------------------#
print('--------------------')
print('Final result : ')
if(sum(test)):
    print('\tSolution INVALID!')
else :
    print('\tSolution VALID!')