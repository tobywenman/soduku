#include "sudoku.h"
#include <stdio.h>
#include <stdbool.h>

struct grid inputGrid()
{
    struct grid output;

    for (unsigned i=0; i<9; i++)
    {
        printf("Line %u:\n", i);
        for (unsigned j=0; j<9; j++)
        {
            printf("row %u: ", j);
            while (true)
            {
                int ret = scanf("%hhu", &output.data[i][j]) ;
                if(ret > 0)
                {
                    if (output.data[i][j] <= 9)
                    {
                        break;
                    }
                    else
                    {
                        printf("invalid input\n");
                        scanf("%*[^\n]%*c");
                    }
                }
                else
                {
                    printf("invalid input\n");
                    scanf("%*[^\n]%*c");
                }
            }
        }
    }
    return output;
}

void printGrid(struct grid in, FILE *stream)
{
    for (unsigned i=0; i<9; i++)
    {
        fprintf(stream, "| ");
        for (unsigned j=0; j<9; j++)
        {
            if (in.data[i][j] == 0)
            {
                fprintf(stream, "  | ");
            }
            else
            {
                fprintf(stream, "%u | ", in.data[i][j]);
            }
        }
        fprintf(stream, "\n");
    }
}

struct grid streamInGrid(FILE *stream)
{
    struct grid out;
    for (unsigned i=0; i<9; i++)
    {
        while(getc(stream) != '|');
        
        for (unsigned j=0; j<9; j++)
        {
            char nextChar;
            while (true)
            {
                nextChar = getc(stream);  

                if (nextChar >= '0' && nextChar <= '9')
                {
                    out.data[i][j] = (uint8_t)(nextChar-'0');
                }
                else if(nextChar == '|')
                {
                    break;
                }

            }
        }
    }
    return out;
}

int main(int argc, char* argv)
{
    FILE *inFile = fopen("puzzle.txt", "r");
    struct grid puzzle = streamInGrid(inFile);
    fclose(inFile);
    printGrid(puzzle, stdout);
}