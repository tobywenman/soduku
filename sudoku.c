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
                        int tmp = scanf("%*[^\n]%*c");
                    }
                }
                else
                {
                    printf("invalid input\n");
                    int tmp = scanf("%*[^\n]%*c");
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
    out.nextTest = 1;
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

    for (unsigned i=0; i<9; i++)
    {
        for (unsigned j=0; j<9; j++)
        {
            if (out.data[i][j]==0)
            {
                out.x = i;
                out.y = j;
                return out;
            }
        }
    }
    return out;
}

void growStack(struct solveStack* stack)
{
    size_t newSize = stack->size*2;
    stack->data = realloc(stack->data, sizeof(struct grid)*newSize);
    assert(stack->data);
    stack->size = newSize;
}

void initStack(struct solveStack* stack)
{
    stack->data = malloc(sizeof(struct grid));
    stack->top = 0;
    stack->size = 1;
}

void pushStack(struct solveStack* stack, struct grid in)
{
    if (stack->top == stack->size)
    {
        growStack(stack);
    }
    stack->data[stack->top] = in;
    stack->top++;
}

struct grid peekStack(struct solveStack* stack)
{
    return stack->data[stack->top-1];
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

bool checkComplete(struct grid in)
{
    for (unsigned i=0; i<9; i++)
    {
        for (unsigned j=0; j<9; j++)
        {
            if (in.data[i][j]==0)
            {
                return false;
            }
        }
    }
    return true;
}

struct grid solve(struct grid input)
{
    struct solveStack stack;
    initStack(&stack);

    pushStack(&stack, input);

    // start solving

    while (true)
    {
        next:
        struct grid curTest = peekStack(&stack);

        popStack(&stack);

        curTest.data[curTest.x][curTest.y] = curTest.nextTest;

        if (curTest.nextTest < 9)
        {
            curTest.nextTest++;
            pushStack(&stack, curTest);
        }

        if (check(curTest))
        {
            if (checkComplete(curTest))
            {
                return curTest;
            }
            //find first empty square
            for (unsigned i=0; i<9; i++)//row
            {
                for (unsigned j=0; j<9; j++)//column
                {
                    if(curTest.data[i][j] == 0)
                    {
                        struct grid newTest;
                        newTest = curTest;
                        newTest.x = i;
                        newTest.y = j;
                        newTest.nextTest = 1;
                        pushStack(&stack, newTest);
                        goto next;
                    }
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

    printGrid(solve(puzzle), stdout);
}