#include <stdio.h>

int main()
{
    int m1[2][4] = {{1, 2, 3, 4}, {4, 6, 8, 2}};
    int m2[4][2] = {
        {6, 8},
        {9, 0},
        {2, 1},
        {4, 4},
    };
    int r[2][2] = {0};
    int m1Rows = 2, m1Cols = 4, m2Rows = 4, m2Cols = 2;

    for (int i = 0; i < m1Rows; i++)
    {
        for (int j = 0; j < m2Cols; j++)
        {
            for (int k = 0; k < m1Cols; k++)
            {
                r[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }

    // print
    for (int i = 0; i < m1Rows; i++)
    {
        printf("\n[ ");
        for (int j = 0; j < m2Cols; j++)
        {
            printf(" %d", r[i][j]);
        }
        printf(" ]");
    }

    printf("\n");
    return 0;
}
