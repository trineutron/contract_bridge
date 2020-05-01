#include <stdio.h>
#include <stdlib.h>

#define DEALS 717102

int loss_deal(int, int, int);
int bidding(int, int, int);
void gethand(int[], int[], int[]);
int atohcp(char a);

int hcp1[DEALS], hcp2[DEALS], tricks[DEALS];

int main()
{
    int loss_total = 0;
    gethand(hcp1, hcp2, tricks);
    for (int i = 0; i < DEALS; i++) {
        loss_total += loss_deal(hcp1[i], hcp2[i], tricks[i]);
    }
    printf("%d\n", loss_total);
    return 0;
}

// そのディールでのロス
int loss_deal(int hcp1, int hcp2, int tricks)
{
    if (hcp1 < 0)
        return 0;
    int loss = 0, level = bidding(hcp1, hcp2, -1);
    if (tricks < level + 6) loss += level + 6 - tricks;
    if ((tricks >= 10 && level < 4) || (tricks >= 9 && level == 0))
        loss++;
    return loss;
}

// ビッド（返り値はレベル）
int bidding(int hcp1, int hcp2, int sequence)
{
    int system[8];
    system[0] = 12;
    system[1] = 8;
    system[2] = 23 - system[0];
    system[3] = 23 - system[1];
    system[4] = 24 - system[0];
    system[5] = 24 - system[1];
    system[6] = 24 - system[2];
    system[7] = 24 - system[3];
    if (sequence == -1) {
        if (hcp1 >= system[0])
            return bidding(hcp2, hcp1, 0);
        if (hcp2 >= system[0])
            return bidding(hcp1, hcp2, 0);
        return 0;
    }
    if (hcp1 >= system[sequence + 4])
        return 4;
    if (sequence >= 2)
        return 3;
    if (hcp1 >= system[sequence + 2])
        return bidding(hcp2, hcp1, sequence + 2);
    if (sequence >= 1)
        return 2;
    if (hcp1 >= system[sequence + 1])
        return bidding(hcp2, hcp1, sequence + 1);
    return 1;
}

// Library.ascからHCPとトリックを取得
void gethand(int hcp1[], int hcp2[], int tricks[])
{
    FILE *data = fopen("Library.asc", "r");
    for (int i = 0; i < DEALS; i++) {
        int spade = 0, flag_spade = 1;
        for (int j = 0; j < 17; j++)
            getc(data);
        for (int j = 0; j < 17; j++) {
            char card = getc(data);
            if (card == '.')
                flag_spade = 0;
            spade += flag_spade;
            hcp1[i] += atohcp(card);
        }
        for (int j = 0; j < 17; j++)
            getc(data);
        flag_spade = 1;
        for (int j = 0; j < 17; j++) {
            char card = getc(data);
            if (card == '.')
                flag_spade = 0;
            spade += flag_spade;
            hcp2[i] += atohcp(card);
        }
        if (fscanf(data, "%*5c%1x%*15c", &tricks[i]) != 1)
            abort();
        if (spade != 8)
            hcp1[i] = -1;
    }
    fclose(data);
}

// 文字をHCPに変換
int atohcp(char a)
{
    switch (a) {
    case 'A':
        return 4;
    case 'K':
        return 3;
    case 'Q':
        return 2;
    case 'J':
        return 1;
    default:
        return 0;
    }
}
