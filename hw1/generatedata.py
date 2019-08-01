# check submission criteria
# process
import random as rand
import sys

# handle command line arguments
# print useful message if no arguments given
if len(sys.argv) < 5:
    print("Usage:")
    print("  $ python3 generatedata.py <ref_length> <nreads> <read_len> <ref_file> <reads_file>")
    print("Example:")
    print("  $ python3 generatedata.py 1000 600 50 \"reference_test.txt\" \"reads_test.txt\" ")
    sys.exit()

# parameters
#   len_ref     : length of reference DNA sequence
#   num_read    : total number of read
#   len_read    : length of each read
#   fname_ref   : name of file that stores reference DNA sequence
#   fname_read  : name of file that stores reads

len_ref     = int(sys.argv[1])
num_read    = int(sys.argv[2])
len_read    = int(sys.argv[3])
fname_ref   = sys.argv[4]
fname_read  = sys.argv[5]

file_ref  = open(fname_ref,'w')
file_read = open(fname_read,'w')

# Define function that generates random DNA sequence of input length
#   generate random integer in range(0,3) and replace each number with G,C,T,A
def generate_seq(length):
    str_dictionary={0:'G',1:'C',2:'T',3:'A'}
    rand_str=''
    for i in range(0,length):
        rand_int=rand.randint(0,3)
        rand_str+=str_dictionary[rand_int]
    return rand_str

# generate DHA sequence length with 75% of reference length
# copy the last part of temporary sequence and append it
temp_seq = generate_seq(int(len_ref*0.75))
reference = temp_seq + temp_seq[int(0.5*len_ref):]

# write reference DNA sequence in file
# close the file after writing
file_ref.write(reference)

# set 
set_read=set()
# the number of alignment
num_align=[0,0,0]

for i in range(0,num_read):
    # random number generation for zero, one and two aligns
    # exit_flag : while loop for finding a read that satisfies requirements
    #   1. not exist in the set of reads
    #   2. the number of alignment (0, 1, 2)
    num_rand = rand.random()
    exit_flag=1

    # zero repeat : 10%
    if(num_rand<0.10): 
        while(exit_flag):
            temp_read = generate_seq(len_read)
            exit_flag = (reference.find(temp_read)>=0) or (temp_read in set_read)
        num_align[0]+=1

    # double repeat : 15%
    elif(num_rand>0.85):
        while(exit_flag):
            init_read = rand.randint(int(len_ref*0.75),len_ref-len_read)
            temp_read = reference[init_read:init_read+len_read]
            exit_flag=((reference.find(temp_read)+0.25*len_ref)!=init_read) or (temp_read in set_read)
        num_align[2]+=1
    
    # single repeat : 75%
    else:
        while(exit_flag):
            init_read = rand.randint(0,int(len_ref*0.5))
            temp_read = reference[init_read:init_read+len_read]
            exit_flag = (reference[int(len_ref*0.5):].find(temp_read)>=0) or (temp_read in set_read)
        num_align[1]+=1
    
    # After finding the read that meets all requirement,
    # write it in the file and add it in the set
    file_read.write(temp_read+'\n')
    set_read.add(temp_read)

# close files
file_ref.close()        
file_read.close()

print('reference length:', len_ref)
print('number reads:',num_read)
print('read length',len_read)
print('aligns 0:', num_align[0]/num_read)
print('aligns 1:', num_align[1]/num_read)
print('aligns 2:', num_align[2]/num_read)
