#include <stdlib.h>
#include <stdio.h>

#include "sortStr.h"



int main(int argc, char* argv[]) 
{
    int ch = 0;
    SORT();
    while (1)
    {
        printf("\nRun it again?\n(yes - enter, no - another key):");
        ch = getch(stdin);
        if (ch != 13)
            break;
        SORT();
    }
    printf("\n\n");
    system("pause");
    return 0;
}