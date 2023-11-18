#include "sudoku.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

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

void growStack(struct solveStack* stack)
{
    if (stack->size == 0)
    {
        stack->data = malloc(sizeof(struct grid));
        assert(stack->data);
    }
    else
    {
        size_t newSize = stack->size*2;
        stack->data = realloc(stack->data, newSize);
        assert(stack->data);
        stack->size = newSize;
    }
}

void pushStack(struct solveStack* stack, struct grid in)
{
    if (stack->top == stack->size)
    {
        growStack(stack);
    }
    stack->top++;
    stack->data[stack->top] = in;
}

struct grid peekStack(struct solveStack* stack)
{
    return stack->data[stack->top];
}

void popStack(struct solveStack* stack)
{
    if (stack->top > 0)
    {
        stack->top--;
    }
}

bool check(struct grid in)
{
    bool squareChecks[3][3][9]={false};
    for (unsigned i=0; i<9; i++)
    {
        bool rowChecks[9]={false};
        bool colChecks[9]={false};
        
        for (unsigned j=0; j<9; j++)
        {
            // check rows and columns
            if (in.data[i][j])
            {
                if(rowChecks[in.data[i][j]-1])
                {
                    return false;
                }
                else
                {
                    rowChecks[in.data[i][j]-1] = true;
                }

                //check squares
                unsigned squareRow = i/3;
                unsigned squareCol = j/3;
                if(squareChecks[squareRow][squareCol][in.data[i][j]-1])
                {
                    return false;
                }
                else
                {
                    squareChecks[squareRow][squareCol][in.data[i][j]-1] = true;
                }
            }
            if (in.data[j][i])
            {
                if(colChecks[in.data[j][i]-1])
                {
                    return false;
                }
                else
                {
                    colChecks[in.data[j][i]-1] = true;
                }
            }
        }
    }
    return true;
}

struct grid solve(struct grid input)
{
    struct solveStack stack;
    stack.top = 0;
    stack.size = 0;

    pushStack(&stack, input);


    // start solving

    while (stack.top > 0)
    {
    //find first empty square
        for (unsigned i=0; i<9; i++)//row
        {
            for (unsigned j=0; j<9; j++)//column
            {
                bool found = false; //if any paths are found

                //test all values and add to stack if fits
                for (unsigned k=0; k<9; k++)//test value
                {

                }
            }
        }
    }
}

int main(int argc, char* argv)
{
    FILE *inFile = fopen("puzzle.txt", "r");
    struct grid puzzle = streamInGrid(inFile);
    fclose(inFile);
    printGrid(puzzle, stdout);
    if (check(puzzle))
    {
        printf("valid\n");
    }
    else
    {
        printf("invalid\n");
    }
}