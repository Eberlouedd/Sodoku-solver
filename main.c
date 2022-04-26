#include <stdio.h>
#include <unistd.h>

int find_case(int x, int y)
{
    int j = 2;
    int c = 2;
    int i = 0;
    int b = 0;
    while(j <= 8)
    {
        while (c <= 8)
        {
            if(x <= c && y <= j){
                return i;
            }
            c += 3;
            i += 3;
        }
        b++;
        i = b;
        c = 2;
        j += 3;
    }
}

int compare_box(int case_con, int x, int y, int tab[9][9])
{
    int ligne = (find_case(x, y) % 3) * 3, colonne = find_case(x, y);
    int i = ligne + 2, j = colonne + 2;
    while (colonne % 3 != 0)
        colonne--;
    while (colonne <= j)
    {
        while(ligne <= i)
        {
            
            if(tab[colonne][ligne] == case_con && (x != colonne || y != ligne))
                return 0;
            ligne++;
        }
        ligne = i - 2;
        colonne++;
    }
    return 1;
}

int test_case(int case_con, int x, int y, int tab[9][9])
{
    int mem_x = x, mem_y = y, i = 0, a = 1;
    y = 0;
    while(y < 9)
    {
        if(tab[y][x] == case_con && y != mem_y)
            return 0;
        y++;
    }
    x = 0;
    while (x < 9)
    {
        if(tab[mem_y][x] == case_con && x != mem_x)
            return 0;
        x++;
    }
    return compare_box(case_con, mem_y, mem_x, tab);
}

void back_track(int tab[9][9], int i, int j)
{
        while (tab[i][j] < 9)
        {
            tab[i][j]++;
            if(test_case(tab[i][j], j, i, tab))
            {
                if(j == 8 && i == 8)
                    return ;
                if(j == 8)
                    return back_track(tab, i + 1, 0);
                else
                    return back_track(tab, i, j + 1);
            }
        }
        tab[i][j] = 0;
        if(j == 0)
            return back_track(tab, i - 1, 8);
        else
            return back_track(tab, i, j - 1);
}

int main()
{
    int tab[9][9] = {{0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0, 0}};

    back_track(tab, 0, 0);
    for (int i = 0; i < 9; i++)
    {
        for (int c = 0; c < 9; c++)
        {
            printf("%d ", tab[i][c]);
            if(c == 2 || c == 5)
                printf(" ");
        }
        if(i == 2 || i == 5)
                printf("\n");
        printf("\n");
    }
    return 0;
}

