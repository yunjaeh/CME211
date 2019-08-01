# cme211-hw4-files
import numpy as np 
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from scipy.sparse.linalg import spsolve
from scipy.sparse import csr_matrix
import warnings

class Truss:
    def __init__(self,input_joints,input_beams):
        # read data from given input files
        self.dat_joints = np.loadtxt(input_joints)
        self.dat_beams = np.loadtxt(input_beams,dtype=int)

        # change first column in joints data file to integer
        self.dat_joints[:,0].astype(int)
        
        # initialize delta x, y and norm 
        self.del_xy=[]
        self.norm_xy=[]

        # the number of beams, joints and forces
        # nforces = num of element + reaction forces(two components, x and y)
        self.nbeams = int(max(self.dat_beams[:,0]))
        self.njoints = int(max(self.dat_joints[:,0]))
        self.nforces = int(sum(self.dat_joints[:,-1])*2+self.nbeams)
        
        # initialize matrix and vectors for given truss
        self.A = csr_matrix((self.njoints*2,self.nforces))
        self.b = csr_matrix((self.njoints*2,1))
        self.x = csr_matrix((self.nforces,1))
       
        self.force=[]

        # if the matrix is not square, raise an error
        if( self.nforces != self.njoints*2):
            raise RuntimeError('Truss geometry not suitable \
for static equilibrium analysis')

        # Call method for computing static equilibrium
        self.ComputeStaticEquilibrium()

    def __repr__(self):
        # for printing the summary of forces in beams
        line=[]
        line.append(' Beam \t Force')
        line.append('-----------------')
        for i in range(0,self.nbeams):
            line.append('   {0:d} {1:10.3f} '.format(i+1,self.force[i]))
        return '\n'.join(line)


    def PlotGeometry(self,input_figure):
        # for plotting geometry of matrix
        # saves a .png file, file name : input_figure
        fig, ax = plt.subplots()
        for idx in self.dat_beams[:,0]:
            j1 = self.dat_beams[idx-1,1]-1
            j2 = self.dat_beams[idx-1,2]-1
            ax.plot([self.dat_joints[j1,1],self.dat_joints[j2,1]],\
            [self.dat_joints[j1,2],self.dat_joints[j2,2]],'b')
        plt.savefig(input_figure)


    def ComputeStaticEquilibrium(self):
        # for computing static equilibrium of truss
        # element in A matrix
        for i in range(0,self.nbeams):
            # computes delta x and delta y
            self.del_xy.append(self.dat_joints[self.dat_beams[i][2]-1][1:3]-\
                                 self.dat_joints[self.dat_beams[i][1]-1][1:3])
            self.norm_xy.append(np.linalg.norm(self.del_xy[i]))
            joint1 = self.dat_beams[i][1]
            joint2 = self.dat_beams[i][2]

            self.A[2*joint1-2,i] = self.del_xy[i][0]/self.norm_xy[i]
            self.A[2*joint1-1,i] = self.del_xy[i][1]/self.norm_xy[i]

            self.A[2*joint2-2,i] = -self.del_xy[i][0]/self.norm_xy[i]
            self.A[2*joint2-1,i] = -self.del_xy[i][1]/self.norm_xy[i]
    
        # to assign force bcs, zero displacement
        num_zero_disp=0
        for i in range(0,self.njoints):
            if(self.dat_joints[i][3]):
                self.b[2*i]=self.dat_joints[i][3]
            if(self.dat_joints[i][4]):
                self.b[2*i+1]=self.dat_joints[i][4]
            if(self.dat_joints[i][-1]):
                id_joint = int(self.dat_joints[i][0])
                self.A[2*id_joint-2,self.nbeams+2*num_zero_disp]=1
                self.A[2*id_joint-1,self.nbeams+2*num_zero_disp+1]=1
                num_zero_disp+=1
                
        # solve matrix equation
        try :
            # Catch warnings as exceptions
            warnings.filterwarnings('error')
            self.x = spsolve(self.A,self.b)
            self.force = self.x[:self.nbeams]
        except:
            raise RuntimeError("Can not solve the linear system,\
unstable truss?")
# end of code, truss.py