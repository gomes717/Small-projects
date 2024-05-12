#include "../include/utils.h"

void updatePossibleMat(const u_int8_t val, const u_int8_t row, const u_int8_t col)
{
    //update cell
    g_possible_mat[row][col] = 0; 
    //update column
    for(size_t i = 0; i < SIZE; i++)
    {
        if(i != row)
        {
            g_possible_mat[i][col] &= ~(1<<(val - 1)); 
        }
    }
    //update row
    for(size_t i = 0; i < SIZE; i++)
    {
        if(i != col)
        {
            g_possible_mat[row][i] &= ~(1<<(val-1)); 
        }
    }
    //update block
    //find block
    const u_int8_t block = (col/3) + (row/3)*3;
    const u_int8_t row_block = (block/3)*3;
    const u_int8_t col_block = (block%3)*3;
    for(size_t i = row_block ; i < row_block + 3; i++)
    {
        if(i == row)
            continue;
        for(size_t j = col_block; j < col_block + 3; j++)
        {
            if(j == col)
                continue;
            g_possible_mat[i][j] &= ~(1<<(val-1));
        }
    }
}

static void initPossibleMat(const u_int8_t (*sudoku)[SIZE])
{
    memset(g_possible_mat, 0x01ff, (sizeof g_possible_mat));
    for(size_t i = 0; i < SIZE; i++)
    {
        for(size_t j = 0; j < SIZE; j++)
        {
            if(sudoku[i][j] != 0)
            {
                updatePossibleMat(sudoku[i][j], i, j);
            }
        }
    }
}

void initEntropyMat(const u_int8_t (*sudoku)[SIZE])
{
    memset(g_entropy_mat, 9, (sizeof g_entropy_mat));
    initPossibleMat(sudoku);
    updateEntropyMat();
}

void updateEntropyMat()
{
    for(size_t i = 0; i < SIZE; i++)
    {
        for(size_t j = 0; j < SIZE; j++)
        {
            u_int8_t entropy = 0;
            for(size_t k = 0; k < SIZE; k++)
            {
                entropy += (g_possible_mat[i][j] >> k) & 1;
            }
            g_entropy_mat[i][j] = entropy;
        }
    }
}