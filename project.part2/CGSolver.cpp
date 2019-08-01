#include "COO2CSR.hpp"
#include "CGSolver.hpp"
#include "matvecops.hpp"
#include "heat.hpp"
#include "sparse.hpp"

int CGSolver(SparseMatrix &A,
             std::vector<double> &b,
             std::vector<double> &x,
             double              tol,
             struct DataInput &inp,
             std::string soln_prefix)
{

    // initialize variables
    int num_dim = A.nRows;

    int nIter_max=num_dim;
    int nIter=0;

    double norm_r0=0.0;
    double alpha, beta;

    std::string soln_fname;

    // initialize vectors
    std::vector<double> u(num_dim);
    std::vector<double> u_new(num_dim);

    std::vector<double> r(num_dim);
    std::vector<double> r_new(num_dim);

    std::vector<double> p(num_dim);
    std::vector<double> p_new(num_dim);

    std::vector<double> Ap(num_dim);
    std::vector<double> b_temp(num_dim);
    
        
    // initialize u0 (initial guess of the solution)
    for(int i=0;i<num_dim;i++){
        // u[i]=100.0;
        u[i] = (inp.T_c + inp.T_h)/2.0;
    }
    
    // iteration 0
    std::cout << "---------- iteration : 0 ----------" << std::endl;
    b_temp = A.MulVec(u);

    // r = b - b_temp;
    for(int i=0;i<num_dim;i++){
        r[i] = b[i]-b_temp[i];
    }

    // reference norm
    norm_r0 = Vector_norm(r);
    p = r;

    // write initial guess
    soln_fname = soln_prefix + "_0.txt";
    WriteSolution(inp,u,soln_fname);


    // iteration starts
    while(nIter < nIter_max)
    {
        // increase # of iterations
        nIter+=1;

        // compute alpha 
        // update u_new and r_new
        Ap = A.MulVec(p);
        alpha = inner_product(r,r)/inner_product(p,Ap);
        for(int i=0;i<num_dim;i++){
            u_new[i] = u[i] + alpha* p[i];
            r_new[i] = r[i] - alpha*Ap[i];    
        }

        // check convergence
        std::cout << "Iteration: "<< nIter <<", Residual: " << (Vector_norm(r_new)/norm_r0) << std::endl;
        if( (Vector_norm(r_new)/norm_r0) < tol){
            std::cout << "SUCCESS: CG solver converged in " << nIter << " iterations." << std::endl;
            break;
        }

        // conpute beta
        beta = inner_product(r_new,r_new) / inner_product(r,r);
        for(int i=0;i<num_dim;i++){
            p_new[i] = r_new[i] + beta *p[i];
            
        }

        // save updated values
        r=r_new;
        u=u_new;
        p=p_new;

        // write files every 10 iterations
        if((nIter % 10) == 0){
            soln_fname = soln_prefix+"_"+std::to_string(nIter)+".txt";
            WriteSolution(inp,u,soln_fname);
        }
    }

    // save final result
    x=u_new;
    soln_fname = soln_prefix+"_"+std::to_string(nIter)+".txt";
    WriteSolution(inp,x,soln_fname);

    return 0;
}

// function to compute vector norm
double Vector_norm(std::vector<double> &u)
{
    long unsigned int num_dim = u.size();
    double norm=0.0;
    for(unsigned int i=0;i<num_dim;i++) {
        norm+= u[i]*u[i];
    }
    return sqrt(norm);
}

// function to compute inner product of two vectors
double inner_product(std::vector<double> &a, std::vector<double> &b){

    long unsigned int num_dim = a.size();
    double value=0.0;
    for(unsigned int i=0;i<num_dim;i++){
        value += a[i]*b[i];
    }
    return value;
}

int WriteSolution(struct DataInput &inp,std::vector<double> &sol,std::string &file_name){

    int nx = int(inp.length / inp.h) +1;
    int ny = int(inp.width / inp.h) -1;
    // std::cout << "-------------------" << std::endl;
    // std::cout << "FUNCTION:Write solutions" << std::endl;
    // std::cout << "-------------------" << std::endl;
    // std::cout << "length: " << inp.length << ", width: "<< inp.width << ", h: " << inp.h<< std::endl;
    // std::cout << "T_h: " << inp.T_h << ", T_c: " << inp.T_c << std::endl;
    // std::cout << "nx: " << nx << ", ny: " << ny << std::endl;

    std::ofstream f_x;
    f_x.open(file_name);

    // iso-thermal boundary    
    for(int i=0;i<nx;i++){
        double temp = -inp.T_c * (exp(-10.0*pow(inp.h*i-inp.length/2.0,2))-2.0);
        f_x << temp << "\t";
    }
    f_x << "\n";

    // internal nodes
    for(int j=0;j<ny;j++){
        for(int i=0;i<nx;i++){
            f_x << sol[nx*j+i] << "\t";
        }
        f_x << "\n";
    }

    // iso-thermal boundary
    for(int i=0;i<nx;i++){
        f_x << inp.T_h << "\t";
    }
    f_x.close();

    return 0;
}