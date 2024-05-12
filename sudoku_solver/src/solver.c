#include "../include/utils.h"

static struct cell findBestCell()
{   
    //bruteforce, find a better way to search for a best cell
    struct cell best_cell = { .col = -1, .row = -1};
    u_int8_t best_val = 10;
    for(size_t i = 0 ; i < SIZE; i++)
    {
        for(size_t j = 0; j < SIZE; j++)
        {
            if(best_val > g_entropy_mat[i][j] && g_entropy_mat[i][j] > 0)
            {
                best_cell.col = j;
                best_cell.row = i;
                best_val = g_entropy_mat[i][j];
            }
        }
    }
    return best_cell;
}

static u_int8_t findBestVal(struct cell best_cell)
{
    //roll a dice to se what value to use
    srand(time(NULL));
    u_int32_t val = rand()%9;
    //if the value is not possible at that cell find another
    while((g_possible_mat[best_cell.row][best_cell.col] & (1 << val)) == 0)
    {
        val = rand()%9;
    }
    return val + 1;
}

u_int8_t solver(u_int8_t (*sudoku)[SIZE])
{
    while(finish_count > 0)
    {
        //find the cell with less entropy
        struct cell best_cell = findBestCell();
        if(best_cell.row == -1 && best_cell.col == -1)
            return 0;

        const u_int8_t val = findBestVal(best_cell);
        //printf("row: %d, col: %d\n", best_cell.row, best_cell.col);
        sudoku[best_cell.row][best_cell.col] = val;
        finish_count--;
        //printf("finish count: %ld\n", finish_count);
        updatePossibleMat(val, best_cell.row, best_cell.col);
        updateEntropyMat();

    }
    return 1;
}