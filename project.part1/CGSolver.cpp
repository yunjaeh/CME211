#include "COO2CSR.hpp"
// #include "COO2CSR.cpp"
#include "CGSolver.hpp"
#include "matvecops.hpp"

int CGSolver(std::vector<double> &val,
             std::vector<int>    &row_ptr,
             std::vector<int>    &col_idx,
             std::vector<double> &b,
             std::vector<double> &x,
             double              tol)
{

    // initialize variables
    // unsigned int num_val = val.size();
    long unsigned int num_dim = row_ptr.size() -1;

    long unsigned int nIter_max=num_dim;
    unsigned int nIter=0;

    double norm_r0=0.0;
    double alpha, beta;

    // initialize vetors
    std::vector<double> u(num_dim);
    std::vector<double> u_new(num_dim);

    std::vector<double> r(num_dim);
    std::vector<double> r_new(num_dim);

    std::vector<double> p(num_dim);
    std::vector<double> p_new(num_dim);

    std::vector<double> Ap(num_dim);
    std::vector<double> b_temp(num_dim);
    
        
    // initialize u0 (initial guess of the solution)
    for(unsigned int i=0;i<num_dim;i++)
    {
        u[i]=1.0;
    }
    
    // std::cout << "---------- iteration : 0 ----------" << std::endl;
    matvecops(val,row_ptr,col_idx,u, b_temp);
    // r = b - b_temp;
    for(unsigned int i=0;i<num_dim;i++)
    {
        r[i] = b[i]-b_temp[i];
    }
    norm_r0 = Vector_norm(r);
    p = r;
    
    // iteration starts
    while(nIter < nIter_max)
    {
        // increase # of iterations
        nIter+=1;
        // std::cout << "---------- iteration : "<< nIter<< " ----------" << std::endl;
        
        matvecops(val,row_ptr,col_idx,p,Ap);
        alpha = inner_product(r,r)/inner_product(p,Ap);

        for(unsigned int i=0;i<num_dim;i++)
        {
            u_new[i] = u[i] + alpha* p[i];
            r_new[i] = r[i] - alpha*Ap[i];    
        }

        if( (Vector_norm(r_new)/norm_r0) < tol)
        {
            std::cout << "SUCCESS: CG solver converged in " << nIter << " iterations." << std::endl;
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
    
    x=u_new;

    return 0;
}