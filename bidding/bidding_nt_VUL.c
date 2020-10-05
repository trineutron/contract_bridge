#include <stdio.h>
#include <stdlib.h>

int imp(int);
int loss_deal(int, int, int);
int bidding(int, int, int);
void gethand(int[], int[], int[]);
int atohcp(char a);

const int deals = 717102;
int hcp1[deals], hcp2[deals], tricks[deals];

int main()
{
    int loss_total = 0;
    gethand(hcp1, hcp2, tricks);
    for (int i = 0; i < deals; i++) {
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
    int optimal = 0, score = 0, level = bidding(hcp1, hcp2, 0);
    if (tricks >= 9) {
        optimal = 500 + 30 * (tricks - 6) + 10;
    } else if (tricks >= 7) {
        optimal = 50 + 30 * (tricks - 6) + 10;
    }
    if (level >= 1 && tricks < level + 6) {
        score = -100 * (level + 6 - tricks);
    } else if (level >= 3) {
        score = 500 + 30 * (tricks - 6) + 10;
    } else if (level >= 1) {
        score = 50 + 30 * (tricks - 6) + 10;
    }
    return imp(optimal - score);
}

// ビッド（返り値はレベル）
int bidding(int hcp1, int hcp2, int sequence)
{
    const int system[8] = { 0, 14, 19, 9, 22, 10, 5, 15 };
    if (hcp1 >= system[sequence + 4])
        return 3;
    if (sequence >= 2)
        return 2;
    if (hcp1 >= system[sequence + 2])
        return bidding(hcp2, hcp1, sequence + 2);
    if (sequence >= 1)
        return 1;
    if (hcp1 >= system[sequence + 1])
        return bidding(hcp2, hcp1, sequence + 1);
    return 0;
}

// Library.ascからHCPとトリックを取得
void gethand(int hcp1[], int hcp2[], int tricks[])
{
    FILE *data = fopen("../Library.asc", "r");
    for (int i = 0; i < deals; i++) {
        for (int j = 0; j < 17; j++)
            getc(data);
        for (int j = 0; j < 17; j++)
            hcp1[i] += atohcp(getc(data));
        for (int j = 0; j < 17; j++)
            getc(data);
        for (int j = 0; j < 17; j++)
            hcp2[i] += atohcp(getc(data));
        if (fscanf(data, "%*1c%1x%*19c", &tricks[i]) != 1)
            abort();
        if (hcp1[i] < hcp2[i]) {
            int w = hcp1[i];
            hcp1[i] = hcp2[i];
            hcp2[i] = w;
        }
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
