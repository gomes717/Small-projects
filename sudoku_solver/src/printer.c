#include "../include/utils.h"

void printer(const u_int8_t (*sudoku)[SIZE])
{
    for(size_t i = 0; i < 25; i++)
    {
        printf("-");
    }
    printf("\n");

    for(size_t i = 0; i < SIZE; i++)
    {
        printf("| ");
        for(size_t j = 0; j < SIZE; j++)
        {
            printf("%d ", sudoku[i][j]);
            if((j+1)%3 == 0)
                printf("| ");
        }
        printf("\n");

        if((i+1)%3 == 0)
        {
            for(size_t i = 0; i < 25; i++)
            {
                printf("-");
            }
            printf("\n");
        }
    }
}