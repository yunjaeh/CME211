# homework submission
0. 
two vector compared by calling private data in class
instance._Vector__data

1. matrix class
All methods implemented


2. dense matrix class


3. compexity of dense matrix methods
a multiplication between a vector and a matrix depends on their size.
If we assume they are square and we are using dense matrices, 
in each column we need n times of multiplication and n-1 times summation
and we have n elements.
Generally, the computational time for multiplication overrides that of summation,
A matrix and a vector multiplication is complexity of n^2,
where n is the size of a vector.


4. 
I printed the matrix and compared the result of multiplication to what I did by hand in simple case.
ex) given 5x5 matrix * [11111]

5.
sparse matrix implementation is done

6.
verification of sparse matrix implementation is done by comparing its result with the dense matrix case.
It performed well.

7. 
Compexity of sparse matrix methods.
Actually it will depend on how sparse the matrix is.
e.g. it can be reduced and the order will depend on the number of elements.
but in general, its complexity will be order n considering the case with vector size of n.

8. verification at scale

9. performance testing

