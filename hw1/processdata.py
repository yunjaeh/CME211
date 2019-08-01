# check submission criteria
# process
import sys
import time

# handle command line arguments
# print useful message if no arguments given
if len(sys.argv) < 3:
    print("Usage:")
    print("  $ python3 processdata.py <ref_file> <reads_file> <align_file>")
    print("Example:")
    print("  $ python3 processdata.py \"reference0.txt\" \"reads0.txt\" \"align0.txt\"")
    sys.exit()

# input parameters
#   fname_ref   : input file storing reference DNA sequence
#   fname_read  : input file storing reads
#   fname_align : output file storing alignment result

fname_ref   = sys.argv[1]
fname_read  = sys.argv[2]
fname_align = sys.argv[3]

# open files
file_ref = open(fname_ref,'r')
file_read = open(fname_read,'r')
file_align = open(fname_align,'w')

# start timing
time_start= time.time()

# the number of each align
num_align=[0,0,0]

# reading referece DNA sequence
reference=file_ref.read()

# interate over the number of reads in the file
for line in file_read:
    # remove "\n" string
    line=line.replace("\n","")

    # find the read from reference DNA sequence
    #   string.find : search string from front
    #   string.rfind : search string from back
    idx_1=reference.find(line)
    idx_2=reference.rfind(line)
    
    # idx_1 = -1 if not matching
    if(idx_1 < 0):
        file_align.write(line+' '+str(idx_1)+'\n')
        num_align[0]+=1
    
    # idx_1 == idx_2 : a read aligns once in the reference
    elif(idx_1 == idx_2):
        file_align.write(line+' '+str(idx_1)+'\n')
        num_align[1]+=1

    # a read aligns twice
    else:
        file_align.write(line+' '+str(idx_1)+' '+str(idx_2)+'\n')
        num_align[2]+=1
        
# num_read : total number of read
num_read=num_align[0]+num_align[1]+num_align[2]

# time end
time_end= time.time()

# print outputs
print('reference length',len(reference))
print('number reads:',num_read)
print('aligns 0:', num_align[0]/num_read)
print('aligns 1:', num_align[1]/num_read)
print('aligns 2:', num_align[2]/num_read)
print('elapsed time:', time_end-time_start)

# close files
file_ref.close()
file_read.close()
file_align.close()    

