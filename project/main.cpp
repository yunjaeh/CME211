#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>


#include "CGSolver.hpp"
// #include "CGSolver.cpp"
#include "COO2CSR.hpp"
// #include "COO2CSR.cpp"
#include "matvecops.hpp"

int main(int argc, char *argv[])
{
    /* part 1, Input anf output file names */
    if(argc < 3)
    {
        std::cout << "Usage:" << std::endl;
        std::cout << " " << argv[0] << \
        "<input matrix file name> <output solution file name>" << std::endl;
        return 0;
    }
    std::string file_input  = argv[1];
    std::string file_output = argv[2];

    
    /* part 2, initialize variables */
    unsigned int nRow, nCol;     // the number of row and column
    unsigned int Row, Col;       // temporary variable for reading input files
    double val;

    // convergence tolerance
    double tol=1.e-5;

    // Linear system : A_mat * x = b;
    std::vector<double> A_mat;
    std::vector<double> b;
    std::vector<double> x;

    std::vector<int> Row_idx;
    std::vector<int> Col_idx;


    /*  part 3, open input file and read   */
    std::ifstream f;
    f.open(file_input);    
    f >> nRow >> nCol;
    
    // print the number of row and column
    // std::cout << "# of row and column :" << std::endl;
    // std::cout << nRow << ", " << nCol << std::endl;
    
    // read data from input file
    while(f >> Row >> Col >> val)
    {
        // std::cout << Row << ", " << Col << ", " << val << std::endl;
        Row_idx.push_back(Row);
        Col_idx.push_back(Col);
        A_mat.push_back(val);
    }
    f.close();

    /*  part 4, calculation   */
    // transform COO matrix to CSR matrix
    COO2CSR(A_mat, Row_idx, Col_idx);

    // construct temporary b matrix
    for(unsigned int i=0;i<nCol;i++)
    {
        b.push_back(0.0);
    }
    
    // run solver
    CGSolver(A_mat, Row_idx, Col_idx, b, x, tol);

    // print x
    std::ofstream output(file_output);
    output.setf(std::ios::scientific);
    output.precision(4);
    for(unsigned int i=0;i<nCol;i++)
    {
        output << x[i] << std::endl;
    }
    f.close();

    return 0;
}