#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>

#include <math.h>

#include "COO2CSR.hpp"
#include "COO2CSR.cpp"

int CGSolver(std::vector<double> &val,
             std::vector<int>    &row_ptr,
             std::vector<int>    &col_idx,
             std::vector<double> &b,
             std::vector<double> &x,
             double              tol);

double Vector_norm(std::vector<double> &u);
double inner_product(std::vector<double> &a, std::vector<double> &b);

int CSR_mult(std::vector<double> &val,
                std::vector<int>    &row_ptr,
                std::vector<int>    &col_idx,
                std::vector<double> &u,
                std::vector<double> &b_temp);



int main(void)
{
/*  part 1.   */
    int nRow, nCol;     // the number of row and column
    int Row, Col;
    double val;

    double tol=0.001;


    std::vector<int> Row_idx;
    std::vector<int> Col_idx;
    std::vector<double> Val_mat;
    std::vector<double> u;
    std::vector<double> b;
    std::vector<double> x;



/*  part 2. open input file and read   */

//    std::string file_input = "matrix1.txt";
    std::ifstream f;
    f.open("matrix1.txt");
    
    // initialize maze array
    f >> nRow >> nCol;
    std::cout << nRow << ", " << nCol << std::endl;

    // read data from input file
    while(f >> Row >> Col >> val)
    {
        std::cout << Row << ", " << Col << ", " << val << std::endl;
        Row_idx.push_back(Row);
        Col_idx.push_back(Col);
        Val_mat.push_back(val);
    }
    f.close();

/*
    std::cout << Row_idx.size() << ", " << Col_idx.size() << ", " << Val_mat.size() << std::endl;
    for(unsigned int n=0; n< Val_mat.size(); n++)
    {
        std::cout << Row_idx[n] <<","<< Col_idx[n]<<"," << Val_mat[n] << std::endl;
    }
    */

    COO2CSR(Val_mat, Row_idx, Col_idx);
    std::cout << "Size after running COO2CSR" << std::endl;
    std::cout << Row_idx.size() << ", " << Col_idx.size() << ", " << Val_mat.size() << std::endl;
/*    
    std::cout << "Values" << std::endl;
    for(unsigned int n=0; n< Val_mat.size(); n++)
    {
        std::cout << Val_mat[n] << std::endl;
    }

    std::cout << "Row idx" << std::endl;
    for(unsigned int n=0; n< Row_idx.size(); n++)
    {
        std::cout << Row_idx[n]  << std::endl;
    }

    std::cout << "Column idx" << std::endl;
    for(unsigned int n=0; n< Col_idx.size(); n++)
    {
        std::cout <<  Col_idx[n] << std::endl;
    }
*/
    // CGSolver(Val_mat, Row_idx, Col_idx, b_temp, x, tol);
    


    b.push_back(1.0);
    b.push_back(1.0);
    // b.push_back(30.0);
    
    
    std::cout << "Test vector norm : " <<Vector_norm(u) << std::endl;
    std::cout << "Test inner product : " << inner_product(u,b) << std::endl;

    CGSolver(Val_mat, Row_idx, Col_idx, b, x, tol);
    // CSR_mult(Val_mat, Row_idx, Col_idx, u, b_temp);
    return 0;
}


int CGSolver(std::vector<double> &val,
             std::vector<int>    &row_ptr,
             std::vector<int>    &col_idx,
             std::vector<double> &b,
             std::vector<double> &x,
             double              tol)
{
    unsigned int nIter_max=10;
    unsigned int nIter=0;

    unsigned int num_val = val.size();
    unsigned int num_dim = row_ptr.size() -1;

    double norm_r0=0.0;
    double norm_r=0.0;
    double alpha, beta;

    std::vector<double> u(num_dim);
    std::vector<double> u_new(num_dim);

    std::vector<double> r(num_dim);
    std::vector<double> r_new(num_dim);

    std::vector<double> p(num_dim);
    std::vector<double> p_new(num_dim);

    std::vector<double> Ap(num_dim);
    std::vector<double> b_temp(num_dim);
    

    std::cout << u.size() << "," <<  r.size() << "," << p.size() << "," << b_temp.size() << std::endl;
    
    
    // initialize u0 
    // u_vec
    u[0]=0.0;
    u[1]=0.0;
    // u[2]=0.0;

    std::cout << "--------------------" << std::endl;
    std::cout << "iteration : 1" << std::endl;
    std::cout << "--------------------" << std::endl;

    CSR_mult(val,row_ptr,col_idx,u, b_temp);
    std::cout << "r = b - A*u" << std::endl;
    std::cout << "  where A*u : b_temp" << std::endl;

    // r = b - b_temp;
    for(unsigned int i=0;i<num_dim;i++)
    {
        r[i] = b[i]-b_temp[i];
    }

    norm_r0 = Vector_norm(r);
    p = r;
    std::cout << norm_r0 << std::endl;
    
    while(nIter < nIter_max)
    {
        // increase # of iterations
        nIter+=1;
        std::cout << "--------------------" << std::endl;
        std::cout << "iteration :" << nIter << std::endl;
        std::cout << "--------------------" << std::endl;

        CSR_mult(val,row_ptr,col_idx,p,Ap);
        alpha = inner_product(r,r)/inner_product(p,Ap);
        std::cout << "alpha : " << alpha << std::endl;

        for(unsigned int i=0;i<num_dim;i++)
        {
            u_new[i] = u[i] + alpha* p[i];
            r_new[i] = r[i] - alpha*Ap[i];    
        }
        std::cout << "u_new : "  << std::endl;
        for(unsigned int i=0;i<num_dim;i++)
        {
            std::cout << u_new[i] << std::endl;
        }

        std::cout << "r_new : "  << std::endl;
        for(unsigned int i=0;i<num_dim;i++)
        {
            std::cout << r_new[i] << std::endl;
        }


        std::cout << "vector norm : " << Vector_norm(r_new) << std::endl;
        std::cout << "residual : " << Vector_norm(r_new)/norm_r0 << std::endl;
        if( (Vector_norm(r_new)/norm_r0) < tol)
        {
            std::cout << "Converged, residual : " << Vector_norm(r_new)/norm_r0 << std::endl;
            u=u_new;
            break;
        }
            
        
        beta = inner_product(r_new,r_new) / inner_product(r,r);
        
        for(unsigned int i=0;i<num_dim;i++)
        {
            p_new[i] = r_new[i] + beta *p[i];
        }
       
        r=r_new;
        u=u_new;
        p=p_new;

    }
    std::cout << "Solution : " << std::endl;
    for(unsigned int i=0;i<num_dim;i++)
    {
        std::cout << u[i] << std::endl;
    }
    

    return 0;
}

double Vector_norm(std::vector<double> &u)
{
    unsigned int num_dim = u.size();
    double norm=0.0;
    for(unsigned int i=0;i<num_dim;i++)
    {
        norm+= u[i]*u[i];
    }
    return sqrt(norm);
}

double inner_product(std::vector<double> &a, std::vector<double> &b)
{
    unsigned int num_dim = a.size();
    double value=0.0;

    for(unsigned int i=0;i<num_dim;i++)
    {
        value += a[i]*b[i];
    }
    return value;
}


int CSR_mult(std::vector<double> &val,
                std::vector<int>    &row_ptr,
                std::vector<int>    &col_idx,
                std::vector<double> &u,
                std::vector<double> &b_temp)
{
    unsigned int num_val = val.size();
    unsigned int num_dim = row_ptr.size()-1;
    unsigned int k=0;   // index, number of values

    // std::cout << "\n Size in CSR multiplication \n " << std::endl;
    // std::cout << row_ptr.size() << ", " << col_idx.size() << ", " << val.size() << std::endl;
    // std::cout << u.size() << std::endl;


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
        // std::cout << b_temp[j-1] << std::endl;
    }

    // std::cout << "--------------------" << std::endl;
    // std::cout << "Result vector" << std::endl;
    // for(unsigned int i=0; i< num_dim ; i++)
    // {
        // std::cout << b_temp[i] << std::endl;
    // }
    // std::cout << "--------------------" << std::endl;

    return 0;
}
