#include <vector>
#include <iostream>
#include "sparse.hpp"
// #include "CGSolver.hpp"
#include "COO2CSR.hpp"

void SparseMatrix::Resize(int nrows, int ncols)
{
    nRows = nrows;
    nCols = ncols;
}

void SparseMatrix::AddEntry(int i, int j, double val)
{
    a.push_back(val);
    i_idx.push_back(i);
    j_idx.push_back(j);
}

/* Method to convert COO matrix to CSR format using provided function */
void SparseMatrix::ConvertToCSR()
{
    COO2CSR(a,i_idx,j_idx);
}

/* Method to perform sparse matrix vector multiplication using CSR formatted matrix */
std::vector<double> SparseMatrix::MulVec(std::vector<double> &vec)
{
    std::vector<double> vec_result(nRows);

    int k=0;
    double elem_temp =0.0;      // temporary value for storing each row
    
    // iterate over row
    for(int j=1;j<=nRows;j++){

        // number of element in the row
        int num_elem = i_idx[j] - i_idx[j-1];
        elem_temp =0.0;
        // iterate over number of element in row
        for(int i=0;i<num_elem;i++)
        {
            elem_temp += a[k] * vec[j_idx[k]];
            k++;
        }
        vec_result[j-1] = elem_temp;
    }

    return vec_result;    
}