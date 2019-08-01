import math
import os
import sys

class Airfoil:
    def __init__(self,input_dir):
        
        # Initialize variables used in this class
        self.x =[]          # y coordinates
        self.y =[]          # x coordinates
        self.chord=0.0      # chord length
        
        # coefficients (dictionary)
        self.cp=dict()      # C_p : given pressure coefficients
        self.cxy=dict()     # C_x and C_y
        self.cl=dict()      # Lift coefficient
        self.stag=dict()    # Stagnation points
        
        # given path and 
        self.input_dir=input_dir
        self.file_dict=dict()
        try :
            self.list_files=os.listdir(self.input_dir)
        except:
            raise RuntimeError('Invalid directory')

        self.read_flist()   # read file list from path
        self.alpha=sorted(self.file_dict)

        self.read_xy()      # read coordinates from xy.dat
        self.cal_chord()    # calculate chord length

        self.read_cp()      # read cp from alpha*.*.dat
        self.cal_cxyl()     # calculate cx,cy,cl
        self.find_stag_pt() # find stagnation point
       

    def __repr__(self):
        # __repr__ for printing results in tabular form
        line=[]
        line.append('Test case:'+ self.input_dir)
        line.append('alpha \t cl \t    stagnation pt ')
        line.append('----- ------- --------------------------')
        for angle in self.alpha:
            line.append('{0:5.2f} {1:7.4f} ({2:7.4f}, {3:7.4f}) {4:7.4f}'\
                        .format(angle,self.cl[angle],self.stag[angle][0], \
                        self.stag[angle][1],self.stag[angle][2]))
        return '\n'.join(line)
        
    def read_flist(self):
        # read file list
        # this class can read only specific file names
        for file in self.list_files:
            if(file.find('alpha') == 0):
                # find corresponding angle of attack, alpha
                angle=file[file.find('alpha')+5:file.find('.dat')]
                # add file path to dictionary, file_dict
                self.file_dict[float(angle)]=file
        
        # print(len(self.file_dict))
        if(len(self.file_dict)==0):
            raise RuntimeError("Error reading file list")

    def read_xy(self):
        # read x and y coordinates from xy.dat file
        # only "xy.dat" is readable
        try:
            file_xy=open(self.input_dir+'/xy.dat','r')
            for line in file_xy:
                line_split = line.split()
                try:
                    float(line_split[0]), float(line_split[1])
                    self.x.append(float(line_split[0]))
                    self.y.append(float(line_split[1]))
                except:
                    continue
            file_xy.close()
        except:
            # if file can not open, raise error
            # raise runtime error
            raise RuntimeError("Reading xy.dat")

        if(len(self.x)==0 or len(self.y)==0):
            raise RuntimeError("Reading xy.dat")


    def cal_chord(self):
        # calculate chord length:
        # maximum distance from the point at the trailing edge
        for i in range(1,len(self.x)):
            temp_chord=((self.x[i]-self.x[0])**2.0 + \
                        (self.y[i]-self.y[0])**2.0)**0.5
            if(temp_chord > self.chord):
                self.chord=temp_chord

    def read_cp(self):
        # read pressure coefficient from alpha*.*.dat files
        for angle in self.alpha:
            cp=[]
            try:
                # print(self.input_dir+'/'+self.file_dict[angle])
                file_cp=open(self.input_dir+'/'+self.file_dict[angle],'r')
                for line in file_cp:
                    line_split=line.split()
                    try:
                        float(line_split[0])
                        cp.append(float(line_split[0]))
                    except:
                        continue
                file_cp.close()
            except:
            # raise error, 
                print('Reading pressure coefficient')

            self.cp[angle]=cp

            if(len(self.cp[angle])+1 != len(self.x)):
                raise RuntimeError("Size mismatching (xy and cp)")


    def cal_cxyl(self):
        for angle in self.alpha:
            #print(self.file_dict[angle])
            
            # intialize temporary data list
            # no need to be class-wide variables
            del_x=[]
            del_y=[]
            del_cx=[]
            del_cy=[]
            cx=0.0
            cy=0.0
            cxy=[]
        
            for i in range(0,len(self.cp[angle])):
                # delta x and y : coordinate difference between two points
                del_x.append(self.x[i+1]-self.x[i])
                del_y.append(self.y[i+1]-self.y[i])
                # delta cx and cy : piecewise pressure coefficient in x and y
                del_cx.append(-1*self.cp[angle][i]*del_y[i]/self.chord)
                del_cy.append( self.cp[angle][i]*del_x[i]/self.chord)
                # total pressure coefficient in x and y direction
                cx += del_cx[i]
                cy += del_cy[i]

            # print(cx,cy)
            cxy=[cx,cy]
            self.cxy[angle]=cxy
            # compute lift coefficient, using given equation
            self.cl[angle]=self.cxy[angle][1]*math.cos(math.radians(angle))\
             - self.cxy[angle][0]*math.sin(math.radians(angle))


    def find_stag_pt(self):
        # find stagnation point :
        # a point has maximum pressure coefficient
        idx=0
        stag_pt=[]
        for angle in self.alpha:
            # find an index of the maximum pressure
            idx=self.cp[angle].index(max(self.cp[angle]))
            stag_pt=[(self.x[idx+1]+self.x[idx])/2.0, \
            (self.y[idx+1]+self.y[idx])/2.0, max(self.cp[angle])]
            
            # add the corresponding stagnation point in the dictionary
            self.stag[angle]=stag_pt