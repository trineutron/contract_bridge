#include <stdio.h>
#include <math.h>

#define MAXHCP 100

void getHCP(int[], int[][7], int[], int[]);

int main()
{
    int count[MAXHCP + 1] = { }, make[MAXHCP + 1][7] = { }, totaltrick[MAXHCP + 1] = { }, totaltrick2[MAXHCP + 1] = { };
    int deal = 0, totalhcp = 0, totalhcp2 = 0, totaltricks = 0, totaltricks2 = 0, product = 0;

    /* HCPとトリック数を取得 */
    getHCP(count, make, totaltrick, totaltrick2);

    /* HCPとトリック数を表示 */
    for (int i = 0; i <= MAXHCP; i++) {
        if (count[i] == 0) continue;
        printf("%2d", i);
        for (int j = 0; j < 7; j++) {
            printf(" %f", 1.0 * make[i][j] / count[i]);
        }
	double avg = (double) totaltrick[i] / count[i];
        printf(" %9.6f %f %5d\n", avg, (double) totaltrick2[i] / count[i] - avg * avg, count[i]);
	deal += count[i];
	totalhcp += count[i] * i;
	totalhcp2 += count[i] * i * i;
	totaltricks += totaltrick[i];
	totaltricks2 += totaltrick2[i];
	product += totaltrick[i] * i;
    }
    double avghcp = (double) totalhcp / deal, avgtricks = (double) totaltricks / deal, avghcp2 = (double) totalhcp2 / deal, avgtricks2 = (double) totaltricks2 / deal;
    printf("%f\n", ((double) product / deal - avghcp * avgtricks) / sqrt((avghcp2 - avghcp * avghcp) * (avgtricks2 - avgtricks * avgtricks)));

    return 0;
}

/* HCPとトリック数を取得 */
void getHCP(int count[], int make[][7], int totaltrick[], int totaltrick2[])
{
    const int hcp_card[4] = { 4, 3, 2, 1 };
    FILE *data = fopen("Library.bin", "rb");
    for (;;) {
        int hcp = 0, shortest[2] = { 3, 3 }, spade[2] = { 0, 0 };
        unsigned char trick;
        for (int suit = 0; suit < 4; suit++) {
            int length[2] = { 0, 0 }, hcp_suit[2] = { 0, 0 };

            for (int i = 0; i < 4; i++) {
                unsigned char cache = getc(data);
                for (int j = 0; j < 4; j++) {
                    if (cache % 2 == 1) {
                        int side = (cache / 2) % 2;
                        if (suit == 0) spade[side]++;
                        length[side]++;
                        if (i == 3) {
			    hcp_suit[side] += hcp_card[j];
			}
                    }
                    cache /= 4;
                }
            }
            for (int side = 0; side < 2; side++) {
                hcp += hcp_suit[side];
		if (length[side] < shortest[side]) shortest[side] = length[side];
		if (length[side] < 2) hcp += 2 - length[side];
            }
        }

        if (fscanf(data, "%*2c%1c%*7c", &trick) != 1) break;
	/* トリック数の取得 */
        trick %= 16;
        if (spade[0] + spade[1] == 8) {
            count[hcp]++;
            totaltrick[hcp] += trick;
	    totaltrick2[hcp] += trick * trick;
            for (int i = 0; i < trick - 6; i++)
                make[hcp][i]++;
        }
    }
    fclose(data);
}
