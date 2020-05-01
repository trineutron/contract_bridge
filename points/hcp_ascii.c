#include <stdio.h>
#include "atohcp.c"

#define MAXHCP 40

int itox(int);

int main()
{
    int count[MAXHCP + 1] = { }, game[MAXHCP + 1][7] = { };

    {
        FILE *data = fopen("Library.asc", "r");
        while (!feof(data)) {
            int hcp[4] = { }, hcptotal, tricks;
            for (int player = 0; player < 4; player++) {
                for (int i = 0; i < 17; i++)
                    hcp[player] += atohcp(getc(data));
            }
            hcptotal = hcp[1] + hcp[3];
            getc(data);
            tricks = itox(getc(data));
            for (int i = 70; i < 89; i++)
                getc(data);
            count[hcptotal]++;
            for (int i = 0; i < tricks - 6; i++) {
                game[hcptotal][i]++;
            }
        }
        fclose(data);
    }

    for (int hcp = 0; hcp <= MAXHCP; hcp++) {
        printf("%d", hcp);
        for (int i = 0; i < 7; i++) {
            printf("\t%lf", (double) game[hcp][i] / count[hcp]);
        }
        printf("\t%d\n", count[hcp]);
    }

    return 0;
}

int itox(int a)
{
    if (a >= 'A') {
        return a - 'A' + 10;
    } else {
        return a - '0';
    }
}
