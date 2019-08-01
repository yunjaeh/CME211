#include "COO2CSR.hpp"
#include "CGSolver.hpp"
#include "matvecops.hpp"

int matvecops(std::vector<double> &val,
                std::vector<int>    &row_ptr,
                std::vector<int>    &col_idx,
                std::vector<double> &u,
                std::vector<double> &b_temp)
{
    // unsigned int num_val = val.size();
    long unsigned int num_dim = row_ptr.size()-1;
    unsigned int k=0;   // index, number of values

    // iterate over row
    for(unsigned int j=1;j<=num_dim;j++)
    {
        // number of element in the row
        unsigned int num_elem = row_ptr[j] - row_ptr[j-1];
        // temporary value for storing each row
        double elem_temp = 0.0;
        // std::cout << "j=" << j << ", num elem : "<< num_elem << std::endl;
        
        // iterate over number of element in row
        for(unsigned int i=0;i<num_elem;i++)
        {   
            // std::cout << "k=" << k << ", val=" << val[k] << ", u="<< u[j] << std::endl;
            elem_temp += val[k] * u[col_idx[k]];
            k++;
        }
        b_temp[j-1]=elem_temp;
     }
 
    return 0;
}           

// function to compute vector norm 
double Vector_norm(std::vector<double> &u)
{
    long unsigned int num_dim = u.size();
    double norm=0.0;
    for(unsigned int i=0;i<num_dim;i++)
    {
        norm+= u[i]*u[i];
    }
    return sqrt(norm);
}

// function to compute inner product of two vectors
double inner_product(std::vector<double> &a, std::vector<double> &b)
{
    long unsigned int num_dim = a.size();
    double value=0.0;

    for(unsigned int i=0;i<num_dim;i++)
    {
        value += a[i]*b[i];
    }
    return value;
}