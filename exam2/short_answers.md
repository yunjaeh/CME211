1.1 Vocabulary

A.
1: initialize integer n in a memory
2: store integer 0 in the memory assgined in the previous line
3: pre-define (or initialize) function f gets no inputs and returns integer.
4: actual function description of function f, detailed subroutines in the { }.

B.
statically typed: checking types of variables when we compile a program
strongly typed: the type of each variable is pre-defined when we compile, can not be changed.
C++ is more strongly typed language since, after running the code snippet we will have the variable names pi with stored value 3(integer) instead of 3.14(double or float), but the program may print warning due to type conversion.

C.
static int a[3];
The sub-phrase "statically allocated" means the variable declared will last until a program ends running.

D. 
The function will return the sum over integer 0 to n-1 (n is the input of the function).

The code can be improved by changing the second line as it did not initialize the integer sum as 0.

Modification :
int sum=0;
  
E.
The code snippet is to declare the struct names "S" that contains intger "s".
Third line stores intger 42 in intger s which is the attribute of the struct S.
It will return nothing by itself but we can access integer "s" in the struct "S".
We can use this for storing certain set of data under one and group them.


1.2 Data types
A.
what data type for this course? string, because each student will have their own SUID, this could be a unique identifier and will be easier to distinguish each other. 
US population? Integer, probably integer will be enough.
world population today? Double or string. As the order of magnutude increases, I will need more complex identifier for each individual.

B.
Warning regarding the comparison between integer i and unsigned integer v.size().
The data types of the two are different.

C.
Well defined, it initializes a variable names s, and has the type of string.

D.
I would pass the pointer of the two vectors so that we can use the data efficiently.

The modification will be :
double Dot(std::vector<double> &x, std::vector<double> &y);


1.3 C-style strings
"const" refers to the character is constant.
The while loop runs as many as the number of characters in the string str.

1.4 Compilers
The error happans because the main.cpp needs reference of "foo.hpp".
We can easily solve this problem by changing the compile command to :
g++ -std=c++11 main.cpp -o main foo.hpp foo.cpp
(by adding the files referenced in the cpp file we want to compile)

1.5
random number or stack error
We only can access arr[2] as we defined arr[3], which means array of length 3, and the number starts from 0 and ends at 2.
output is not guarnteed and not reliable.
we can compile but may have warning flags.
we expect segmentation fault. 








