#include <bits/stdc++.h>
using namespace std;

#define MAXDP 10000

void gettricks(int[], int[], int[]);
int lp(int);

int main()
{
    int count[MAXDP + 1] = { }, totaltrick[MAXDP + 1] = { }, totaltrick2[MAXDP + 1] = { };

    /* DPとトリック数を取得 */
    gettricks(count, totaltrick, totaltrick2);

    /* DPとトリック数を表示 */
    for (int i = 0; i <= MAXDP; i++) {
        if (count[i] < 1) continue;
	double avg = 1.0 * totaltrick[i] / count[i], var = 1.0 * totaltrick2[i] / count[i] - avg * avg;
        printf("%f\t%f\t%d", avg, sqrt(var), count[i]);
        printf("\t%d\n", i);
    }

    return 0;
}

/* DPとトリック数を取得 */
void gettricks(int count[], int totaltrick[], int totaltrick2[])
{
    const int sp[14] = { 3, 2, 1 };
    FILE *data = fopen("Library.bin", "rb");
    for (int hand = 0; hand < 717102; hand++) {
	int dp = 0;
	pair<int, int> longest = make_pair(0, 0), shortest = make_pair(0, 13);
        for (int suit = 0; suit < 4; suit++) {
            int length[4] = { 0, 0, 0, 0 };
            for (int i = 0; i < 4; i++) {
                unsigned char cache = getc(data);
                for (int j = 0; j < 4; j++) {
		    length[cache % 4]++;
                    cache /= 4;
                }
            }
	    length[0] -= 3;
	    for (int i = 0; i < 4; i++) {
		dp += sp[length[i]];
	    }
	    if (length[1] + length[3] > longest.second) {
		longest.first = suit;
		longest.second = length[1] + length[3];
	    }
	    if (length[1] + length[3] < shortest.second) {
		shortest.first = suit;
		shortest.second = length[1] + length[3];
	    }
	    if (abs(length[0] - length[2]) >= 4) dp--;
	    if (abs(length[1] - length[3]) >= 4) dp--;
        }
	dp += lp(longest.second) + lp(13 - shortest.second);

	int tricks = 13;
	getc(data); // NTを読み捨て
	getc(data);
	for (int suit = 0; suit < 4; suit++) {
	    unsigned char trick;
	    if (fscanf(data, "%1c%*1c", &trick) != 1) break;
	    /* トリック数の取得 */
	    trick %= 16;
	    if (suit == longest.first) tricks += trick;
	    if (suit == shortest.first) tricks -= trick;
	}
	count[dp]++;
	totaltrick[dp] += tricks;
	totaltrick2[dp] += tricks * tricks;
    }
    fclose(data);
}

int lp(int length)
{
    if (length == 7) return 0;
    if (length == 8) return 20;
    return length + 13;
}
