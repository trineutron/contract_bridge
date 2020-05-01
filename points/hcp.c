#include <stdio.h>
#include <math.h>

#define MAXHCP 40

int main()
{
    const int hcp_card[4] = { 4, 3, 2, 1 };
    int count[MAXHCP + 1] = { }, make[MAXHCP + 1][7] = { }, totaltrick[MAXHCP + 1] = { }, totaltrick2[MAXHCP + 1] = { }, product = 0;

    /* HCPとトリック数を取得 */
    {
        FILE *data = fopen("Library.bin", "rb");
        for (;;) {
            int hcp = 0, shortest_suit[2] = { 13, 13 };
            for (int suit = 0; suit < 4; suit++) {
                int length[2] = { };
                for (int i = 0; i < 4; i++) {
                    unsigned char cache = getc(data);
                    for (int j = 0; j < 4; j++) {
                        if (cache % 2 == 1) {
                            length[(cache / 2) % 2]++;
                            if (i == 3)
                                hcp += hcp_card[j];
                        }
                        cache /= 4;
                    }
                }
                if (length[0] < shortest_suit[0])
                    shortest_suit[0] = length[0];
                if (length[1] < shortest_suit[1])
                    shortest_suit[1] = length[1];
            }
            unsigned char trick = getc(data) % 16;
            for (int i = 0; i < 9; i++)
                getc(data);
            if (shortest_suit[0] >= 2 && shortest_suit[1] >= 2) {
                count[hcp]++;
                totaltrick[hcp] += trick;
		totaltrick2[hcp] += trick * trick;
		product += hcp * trick;
                for (int i = 0; i < trick - 6; i++)
                    make[hcp][i]++;
            }
            if (feof(data))
                break;
        }
        fclose(data);
    }

    /* HCPとトリック数を表示 */
    int deal = 0, totalhcp = 0, totalhcp2 = 0, totaltricks = 0, totaltricks2 = 0;
    for (int i = 0; i <= MAXHCP; i++) {
        if (count[i] == 0)
            continue;
        printf("%2d", i);
        for (int j = 0; j < 7; j++) {
            printf(" %f", 1.0 * make[i][j] / count[i]);
        }
	double avg = 1.0 * totaltrick[i] / count[i];
        printf(" %9.6f %f %5d\n", avg, 1.0 * totaltrick2[i] / count[i] - avg * avg, count[i]);
	deal += count[i];
	totalhcp += count[i] * i;
	totalhcp2 += count[i] * i * i;
	totaltricks += totaltrick[i];
	totaltricks2 += totaltrick2[i];
    }
    double avghcp = (double) totalhcp / deal, avgtricks = (double) totaltricks / deal, avghcp2 = (double) totalhcp2 / deal, avgtricks2 = (double) totaltricks2 / deal;
    printf("%f\n", ((double) product / deal - avghcp * avgtricks) / sqrt((avghcp2 - avghcp * avghcp) * (avgtricks2 - avgtricks * avgtricks)));

    return 0;
}
