#include "../include/utils.h"

const char* extractFromFile(const char* filepath);
void charArrToByteMat(const char* buffer, u_int8_t (*sudoku)[SIZE]);
void updateEntropyMat();
void initPossibleMat();
void updatePossibleMat(const u_int8_t val, const u_int8_t row, const u_int8_t col);
struct cell findBestCell();

size_t finish_count;
u_int8_t g_entropy_mat[SIZE][SIZE];
u_int16_t g_possible_mat[SIZE][SIZE];

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        printf("Missing an argument. Usage example: %s filepath/file.txt\n", argv[0]);
        exit(1);
    }

    printf("solving the sudoku\n");
    u_int8_t finished = 0;
    u_int8_t sudoku[SIZE][SIZE];
    size_t i = 1;
    while(!finished)
    {
        printf("Attempt number: %ld\n", i);
        finish_count = SIZE*SIZE;
        initSudoku(argv[1], sudoku);
        //printf("Sudoku matrix:\n");
        //printer(sudoku);

        initEntropyMat(sudoku);
        //printf("Entropy matrix initialize\n");
        //printer(g_entropy_mat);
        finished = solver(sudoku);
        i++;
    }

    printf("Sudoku resolved\n");
    printer(sudoku);
    return 0;
}
