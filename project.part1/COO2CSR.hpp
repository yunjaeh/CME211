#ifndef COO2CSR_HPP
#define COO2CSR_HPP

#include <vector>

/* In place conversion of square matrix from COO to CSR format */
void SortRow(std::vector<int> &row_idx, std::vector<int> &col_idx,
             std::vector<double> &a, unsigned int start, unsigned int end, unsigned int nz);

void COO2CSR(std::vector<double> &val,
             std::vector<int>    &i_idx,
             std::vector<int>    &j_idx);

#endif /* COO2CSR_HPP */
