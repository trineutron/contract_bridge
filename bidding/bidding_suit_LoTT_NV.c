#include <stdio.h>
#include <stdlib.h>

#define DEALS 717102

int imp(int);
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

// IMPを計算
int imp(int diff) {
    const int table[] = { 0, 20, 50, 90, 130, 170, 220, 270, 320, 370, 430, 500, 600, 750, 900, 1100,
                          1300, 1500, 1750, 2000, 2250, 2500, 3000, 3500, 4000 };
    int res = 0;
    while (diff >= table[res + 1]) res++;
    return res;
}

// そのディールでのロス
int loss_deal(int hcp1, int hcp2, int tricks)
{
    if (hcp1 < 0)
        return 0;
    int optimal = 0, score = 0, level = bidding(hcp1, hcp2, -1);
    if (tricks >= 10) {
        optimal = 300 + 30 * (tricks - 6);
    } else if (tricks >= 8) {
        optimal = 50 + 30 * (tricks - 6);
    }
    if (level >= 1 && tricks < level + 6) {
        score = -50 * (level + 6 - tricks);
    } else if (level >= 4) {
        score = 300 + 30 * (tricks - 6);
    } else if (level >= 2) {
        score = 50 + 30 * (tricks - 6);
    }
    return imp(optimal - score);
}

// ビッド（返り値はレベル）
int bidding(int hcp1, int hcp2, int sequence)
{
    int system[8];
    system[0] = 11;
    system[1] = 5;
    system[2] = 21 - system[0];
    system[3] = 21 - system[1];
    system[4] = 22 - system[0];
    system[5] = 23 - system[1];
    system[6] = 23 - system[2];
    system[7] = 22 - system[3];
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
    FILE *data = fopen("../Library.asc", "r");
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
