#ifndef HEAT_HPP
#define HEAT_HPP

#include <string>
#include <vector>

#include "sparse.hpp"
#include "CGSolver.hpp"

struct DataInput
{
  double length, width, h;
  double T_c, T_h;
};

class HeatEquation2D
{
  private:
    SparseMatrix A;
    double tol=1e-5;
    std::vector<double> b, x;
    /* TODO: Add any additional private data attributes and/or methods you need */

  public:
    DataInput inp;

    /* Method to setup Ax=b system */
    int Setup(std::string inputfile);

    /* Method to solve system using CGsolver */
    int Solve(std::string soln_prefix);

    /* TODO: Add any additional public methods you need */

};


#endif /* HEAT_HPP */
