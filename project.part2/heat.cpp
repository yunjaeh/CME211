#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include <math.h>

#include "sparse.hpp"
#include "heat.hpp"

int HeatEquation2D::Setup(std::string inputfile)
{
    // read input file
    std::ifstream f;
    f.open(inputfile);
    f >> inp.length >> inp.width >> inp.h;
    f >> inp.T_c >> inp.T_h;
    f.close();
    
    double h_sq = 1.0/(inp.h*inp.h);
    int nx = int(inp.length / inp.h)+1;
    int ny = int(inp.width / inp.h)-1;

    A.Resize(nx*ny,nx*ny);
    b.resize(nx*ny);
    x.resize(nx*ny);

    std::cout << "length: " << inp.length << ", width: "<< inp.width << ", h: " << inp.h<< std::endl;
    std::cout << "T_h: " << inp.T_h << ", T_c: " << inp.T_c << std::endl;
    std::cout << "nx: " << nx << ", ny: " << ny << std::endl;

    std::cout << "size of b : " <<b.size() << std::endl;

    // setup A and b matrix
    // fill A matrix with constants
    std::cout << "h_square: " << h_sq << std::endl;
    for(int j=0; j<ny; j++) {
        for(int i=0;i<nx;i++) {
            int k =nx*j+i;
            A.AddEntry(k   , k, -4.0*h_sq);

            if(j == 0){
                A.AddEntry(k+nx, k, 1.0*h_sq);
            } else if (j == ny-1){
                A.AddEntry(k-nx, k, 1.0*h_sq);
            } else {
                A.AddEntry(k-nx, k, 1.0*h_sq);
                A.AddEntry(k+nx, k, 1.0*h_sq);
            }
                
            if(i==0){
                A.AddEntry(k+nx-1, k,1.0*h_sq);
                A.AddEntry(k+1   , k,1.0*h_sq);
            } else if ( i == (nx-1)){
                A.AddEntry(k-1   , k, 1.0*h_sq);
                A.AddEntry(k-nx+1, k, 1.0*h_sq);
            } else {
                A.AddEntry(k-1 ,   k, 1.0*h_sq);
                A.AddEntry(k+1 ,   k, 1.0*h_sq);
            }
        }
    }
    
    // construct b vector
    for(int i=0;i<nx;i++){
        // b[i] = T_c;
        b[i] = inp.T_c * (exp(-10.0*pow(inp.h*i-inp.length/2.0,2))-2.0)*h_sq;
        // std::cout << b[i] << std::endl;
        b[nx*(ny-1)+i] = -1.0*inp.T_h*h_sq;
    }


    // reverse the sign of elements in A matrix and b vector
    // system definition
    for(int i=0; i<(int)A.a.size() ; i++){
        A.a[i] = -1.0*A.a[i];
    }
    for(int j=0;j<ny;j++){
        for(int i=0;i<nx;i++){
            b[nx*j+i] = -1.0 *b[nx*j+i] ;
        }
    }

    // change sparse matrix to CSR format from COO
    A.ConvertToCSR();

    return 0;
}

int HeatEquation2D::Solve(std::string soln_prefix)
{
    CGSolver(A,b,x,tol,inp,soln_prefix);

    return 0;
}