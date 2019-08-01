import time
import sys

# not enough input -> print usage
if len(sys.argv) < 3:
    print("Usage:")
    print("     python3 similarity.py <data_file> <output_file> [user_thresh (default=5)]")
    sys.exit()


# inputs
data_file = sys.argv[1]
output_file = sys.argv[2]
if len(sys.argv) == 4:
    user_thresh = int(sys.argv[3])
else:
    user_thresh = 5


# open files
file_input = open(data_file,'r')
file_output = open(output_file,'w')


# start function definitions

# 1. find users in both sets
def common_users(user1, user2):
    return list(set(user1).intersection(user2))

# 2. calculate cosine similarity value between list a and b
def calc_p(key1,key2,common_user,user_dict1,user_dict2,rate_dict1,rate_dict2):
    
    # get list of rates for each movie
    rate1=[]
    rate2=[]
    for user in common_user:
        rate1.append(rate_dict1[user_dict1.index(user)])
        rate2.append(rate_dict2[user_dict2.index(user)])
    
    # mean rates
    r1_mean = sum(rate_dict1)/len(rate_dict1)
    r2_mean = sum(rate_dict2)/len(rate_dict2)
    
    # compute numerator and denominator
    numer = calc_term(rate1,r1_mean,rate2,r2_mean)
    denom1 = calc_term(rate1,r1_mean,rate1,r1_mean)
    denom2 = calc_term(rate2,r2_mean,rate2,r2_mean)

    # try, except
    # ZeroDivisionError handling
    try:
        p_ab = numer/(denom1*denom2)**0.5
    except ZeroDivisionError:
        p_ab = -10.0

    return p_ab

# 3. calculate term in cosine similarity
def calc_term(rate1,rate1_mean,rate2,rate2_mean):
    result=0
    for i in range(0,len(rate1)):
        result=result+(rate1[i]-rate1_mean)*(rate2[i]-rate2_mean)
    return result
   



##### start main
time_start = time.time()

# initialize two dictionary files
# store users and rates for each movie in two dictionary
user_dict={}
rate_dict={}
num_line=0
user_set=set()
for line in file_input:
    num_line+=1
    line_split = line.split()
    user_set.add(int(line_split[0]))
    if(int(line_split[1]) in user_dict):
        user_dict[int(line_split[1])].append(int(line_split[0]))
        rate_dict[int(line_split[1])].append(int(line_split[2]))
    else:
        user_dict[int(line_split[1])]=list()
        rate_dict[int(line_split[1])]=list()
        
        user_dict[int(line_split[1])].append(int(line_split[0]))
        rate_dict[int(line_split[1])].append(int(line_split[2]))

# sort movie list in increasing order
movie_list = sorted(user_dict)

# print out time spent for reading and sorting data
# print(time.time()-time_start)

# initialize dictionaries to save cosine similarities and relevant values
#   p_max : maximum p 
#   p_id  : the corresponding index having maximum p
#   p_u_common : the number of users rated in common

p_max={}
p_id={}
p_u_common={}

# initialize calculation

# initialize values of -10 for max p
for key1 in movie_list:
    p_max[key1]=-10.0

# iterate over all movies in the list : key1
for key1 in movie_list:
    # iterate over the movies that have not compared yet to key1 : key2
    for key2_idx in range(movie_list.index(key1)+1,len(movie_list)):
        key2 = movie_list[key2_idx]
        
        # find users rated the movie in common
        user_common = common_users(user_dict[key1],user_dict[key2])

        # if two movies have common users less than the specified number
        if(len(user_common) < user_thresh):
            continue
        else :
            # calculate p
            new_p = calc_p(key1,key2,user_common,\
            user_dict[key1],user_dict[key2],rate_dict[key1],rate_dict[key2])
            
            # compare and store p and corresponding movie
            if(p_max[key1] < new_p):
                p_max[key1] = new_p
                p_id[key1] = key2
                p_u_common[key1] = len(user_common)

            if(p_max[key2] < new_p):
                p_max[key2] = new_p
                p_id[key2] = key1
                p_u_common[key2] = len(user_common)
        

# write output file
for key in movie_list:
    try:
        file_output.write('{} ({},{:.2f},{})\n'\
        .format(key,p_id[key],p_max[key],p_u_common[key]))
    except:
        file_output.write('{}\n'.format(key))


# print output lines
print('Input MovieLens file:', data_file)
print('Output file for similarity data:',output_file)
print('Minimum number of common users:',user_thresh)
print('Read',num_line,'lines with total of ', end='')
print(len(movie_list),'movies and',len(user_set),'users')
print('Computed similarities in {0:.2f} seconds'\
    .format(time.time()-time_start))
