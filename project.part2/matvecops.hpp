#ifndef MATVECOPS_HPP
#define MATVECOPS_HPP

#include <vector>
#include <iostream>
#include <math.h>

int matvecops(std::vector<double> &val,
                std::vector<int>    &row_ptr,
                std::vector<int>    &col_idx,
                std::vector<double> &u,
                std::vector<double> &b_temp);

double Vector_norm(std::vector<double> &u);

double inner_product(std::vector<double> &a,
                    std::vector<double> &b);


#endif