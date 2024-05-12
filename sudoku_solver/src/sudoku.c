#include "../include/utils.h"

static void charArrToByteMat(const char* buffer, u_int8_t (*sudoku)[SIZE])
{
    size_t col = 0;
    size_t row = 0;
    size_t i = 0;
    while(row < SIZE)
    {
        if(buffer[i] == '\n')
        {
            row++;
            col = 0;
            i++;
            continue;
        }

        if(buffer[i] != ' ')
        {
            sudoku[row][col] = (char)buffer[i] - '0';
            if(sudoku[row][col] > 0)
                finish_count--;
            col++;
        }
        i++;
    }
}

static const char* extractFromFile(const char* filepath)
{
    printf("Openning: %s\n", filepath);
    int32_t fd = open(filepath, O_RDONLY);

    if(fd < 0)
    {
        printf("File \"%s\" could not open\n", filepath);
        exit(2);
    }

    struct stat statbuf;
    int32_t status = fstat(fd, &statbuf);

    if(status < 0)
    {
        printf("file \"%s\" could not open\n", filepath);
        exit(2);
    }

    char *buff = mmap(NULL, statbuf.st_size, PROT_READ,MAP_PRIVATE, fd, 0);
    if(buff == MAP_FAILED){
        printf("Mapping Failed\n");
        exit(3);
    }
    close(fd);
    return buff;
}

void initSudoku(const char* filepath, u_int8_t (*sudoku)[SIZE])
{
    const char *buff = extractFromFile(filepath);
    charArrToByteMat(buff, sudoku);
}
