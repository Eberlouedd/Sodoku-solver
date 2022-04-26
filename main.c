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

int differ(int nb){
    if(nb > 9)
        return nb / 10;
    else
        return nb;
}

int compare_box(int case_con, int x, int y, int tab[9][9])
{
    int ligne = (find_case(x, y) % 3) * 3, colonne = find_case(x, y);
    int i = ligne + 2, j;
    while (colonne % 3 != 0)
        colonne--;
    j = colonne + 2;
    while (colonne <= j)
    {
        while(ligne <= i)
        {
            if(differ(tab[colonne][ligne]) == case_con && (x != colonne || y != ligne)){
                return 0;
            }
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
        if(differ(tab[y][x]) == case_con && y != mem_y){
            return 0;
        }
        y++;
    }
    x = 0;
    while (x < 9)
    {
        if(differ(tab[mem_y][x]) == case_con && x != mem_x){
            return 0;
        }
        x++;
    }
    return compare_box(case_con, mem_y, mem_x, tab);
}

void back_track(int tab[9][9], int i, int j, int av_rec)
{
    if(j == 8 && i == 8)
        return ;
    if(tab[i][j] <= 9){
        while (tab[i][j] < 9)
        {
            tab[i][j]++;
            //printf("i = %d, j = %d, val = %d\n", i, j, tab[i][j]);
            if(test_case(tab[i][j], j, i, tab))
            {
                if(j == 8)
                    return back_track(tab, i + 1, 0, 1);
                else
                    return back_track(tab, i, j + 1, 1);
            }
        }
        tab[i][j] = 0;
        if(j == 0)
            return back_track(tab, i - 1, 8, 0);
        else
            return back_track(tab, i, j - 1, 0);
    }else{
        if(av_rec && j == 8)
            return back_track(tab, i + 1, 0, 1);
        else if(av_rec && j < 8)
            return back_track(tab, i, j + 1, 1);
        else if(!av_rec && j == 0)
            return back_track(tab, i - 1, 8, 0);
        else if(!av_rec && j > 0)
            return back_track(tab, i, j - 1, 0);
    }
}

int main()
{

    int tab[9][9] = {{0, 90, 80, 0, 0, 0, 0, 0, 0},
                     {0, 0, 20, 0, 0, 60, 0, 0, 40},
                     {0, 50, 0, 0, 0, 10, 0, 20, 0},
                     {0, 20, 0, 60, 0, 0, 70, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 30, 0, 0, 0, 90, 0, 50, 0},
                     {30, 80, 0, 70, 0, 0, 0, 0, 50},
                     {0, 60, 0, 30, 0, 0, 0, 90, 0},
                     {0, 0, 0, 80, 0, 0, 0, 40, 0}};

    back_track(tab, 0, 0, 1);
    for (int i = 0; i < 9; i++)
    {
        for (int c = 0; c < 9; c++)
        {
            printf("%d ", differ(tab[i][c]));
            if(c == 2 || c == 5)
                printf(" ");
        }
        if(i == 2 || i == 5)
                printf("\n");
        printf("\n");
    }
    return 0;
}

