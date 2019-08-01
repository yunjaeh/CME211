#!/usr/bin/env python3
#
# CME 211, Fall 2018
# Python Midterm Exam
#

# You can use some or all of these modules
import copy
import math
import sys
import time


class Vector:
    def __init__(self, size, val):
        self.__data=[val]*size
    def __len__(self):
        return len(self.__data)
    def get(self, i):
        return self.__data[i]
    def put(self, i, val):
        self.__data[i] = val

## Your code here ##

# function comparing the private variables in the Vector class
def areEqual(u,v):
    return u._Vector__data==v._Vector__data

# class prototyping
class Matrix:
    def __init__(self):
        self.__ncol=0
        self.__nrow=0
        self.__ndat=0
    def importMatrix(self,filename):

    def get(self,i,j):

    def matvec(self,v):

    def numCols(self):

    

class DenseMatrix(Matrix):
    def __init__(self):
        self.__ncol=0
        self.__nrow=0
        self.__ndat=0
        self.__dat=[]
#         self.__dat=dict()
#       dictionary is for sparse case
                
    def importMatrix(self,filename):
        file_input = open(filename,'r')
        mat=[]
        line_init=1
        for line in file_input:
            iscomment = (line.find('%') < 0)
            # if the line is not a comment line
            
            if(iscomment):
                line_split=line.split()
                if(line_init):
                    self.__nrow, self.__ncol, self.__ndat =\
                    int(line_split[0]), int(line_split[1]), int(line_split[2])
                    self.__dat = [[0.0]*self.__ncol]*self.__nrow
#                     print(self.__nrow)
                    # initialize 2d array
                    for i in range(0,self.__nrow):
                        print([0.0*self.__ncol])
                        mat.append([0.0]*self.__ncol)
                    
#                     print(self.__dat)
                    line_init=0
                else:
                    print(line_split)
                    mat[int(line_split[0])-1][int(line_split[1])-1] = float(line_split[2])

        self.__dat=mat
#         print(self.__nrow, self.__ncol, self.__ndat)
#         print(self.__dat)

        file_input.close()
        
    def get(self,i,j):
        dat = 0.0
        if(max(i,j) <= self.__ncol):
            dat = self.__dat[int(i)-1][int(j)-1]
        else:
            raise RuntimeError("Error : No element in the position")
        return dat
    
    def set(self,i,j,x):
        self.__dat[int(i)-1][int(j)-1] = x
                
        
    def matvec(self,v):
        if(len(v._Vector__data) != self.__ncol):
            raise RuntimeError("Size doesn't match")
        
        vector_out = Vector(self.__ncol,1.0)
        
        for i in range(1,self.__nrow+1):
            
            dat_temp = 0.0
            idx=1
            for element in v._Vector__data:
                dat_temp += element*self.get(i,idx)
                idx+=1
            
            vector_out.put(i-1,dat_temp)
        
#         print(vector_out._Vector__data)
        return vector_out

        
    def numCols(self):
        return self.__ncol




class SparseMatrix(Matrix):
    def __init__(self):
        self.__ncol=0
        self.__nrow=0
        self.__ndat=0
        self.__dat=dict()
                
       
    def importMatrix(self,filename):
        print(filename)
        file_input = open(filename,'r')
            
        for line in file_input:
            iscomment = (line.find('%') < 0)
            
            if(iscomment):
                line_split=line.split()
                try:
                    self.__nrow, self.__ncol, self.__ndat =\
                    int(line_split[0]), int(line_split[1]), int(line_split[2])
                except:
                    print(line_split)
                    self.__dat[(int(line_split[0]),int(line_split[1]))]=float(line_split[2])
        
#         print(self.__nrow, self.__ncol, self.__ndat)
#         print(self.__dat)
       
        file_input.close()
        
    def get(self,i,j):
#       initialize the value for return
        dat=0.0
        try:
            dat = self.__dat[(int(i),int(j))]
        except:
            if(max(i,j) <= self.__ncol):
                dat=0.0
            else:
                raise RuntimeError("Error : No element in the position")
        return dat
    
    def set(self,i,j,x):
        self.__dat[(int(i),int(j))] = x
        
        # increase the size of matrices
        if(max(i,j) > self.__ncol):
            self.__nrow=max(i,j)
            self.__ncol=max(i,j)
            
        
    def matvec(self,v):
        if(len(v._Vector__data) != self.__ncol):
            raise RuntimeError("Size doesn't match")
        
        vector_out = Vector(self.__ncol,1.0)
        
        for i in range(1,self.__nrow+1):
            
            dat_temp = 0.0
            idx=1
            for element in v._Vector__data:
                dat_temp += element*self.get(i,idx)
                idx+=1
            
            vector_out.put(i-1,dat_temp)
        
        print(vector_out._Vector__data)
        return vector_out

        
    def numCols(self):
        return self.__ncol


## Your code here ##

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print('Usage:')
        print('  python {} <matrix market file>'.format(sys.argv[0]))
        sys.exit(0)

    matrixdata = sys.argv[1]

    #
    # The code below this will not work until you implement
    # all `*Matrix` classes and `areEqual` function. You may comment
    # out portions of the code while you are developing and testing
    # your classes and the function. 
    #

    # Declare dense and sparse matrix
    M = DenseMatrix()
    S = SparseMatrix()

    # Load dense matrix
    M.importMatrix(matrixdata)

    # Load sparse matrix
    S.importMatrix(matrixdata)

    # Create vector for testing matvec method
    v = Vector(M.numCols(), 0.1)

    # Dense matrix-vector multiplication
    r = M.matvec(v)

    # Sparse matrix-vector multiplication
    q = S.matvec(v)

    # Verify sparse matrix vector multiplication against the dense one
    if areEqual(r,q):
        print("Sparse matvec verified!")
    else:
        print("Sparse matvec verification failed!")
