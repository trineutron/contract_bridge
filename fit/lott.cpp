#include <bits/stdc++.h>
using namespace std;

#define MAXLEN 12

void gettricks(int[], int[], int[]);

int main()
{
    int count[MAXLEN + 1] = { }, totaltrick[MAXLEN + 1] = { }, totaltrick2[MAXLEN + 1] = { };

    /* 切り札枚数とトリック数を取得 */
    gettricks(count, totaltrick, totaltrick2);

    /* 切り札枚数とトリック数を表示 */
    for (int i = 0; i <= MAXLEN; i++) {
        if (count[i] == 0) continue;
	double avg = 1.0 * totaltrick[i] / count[i], var = 1.0 * totaltrick2[i] / count[i] - avg * avg;
        printf("%d", i + 14);
        printf("\t%f\t%f\t%d\n", avg, sqrt(var), count[i]);
    }

    return 0;
}

/* 切り札枚数とトリック数を取得 */
void gettricks(int count[], int totaltrick[], int totaltrick2[])
{
    FILE *data = fopen("Library.bin", "rb");
    for (int hand = 0; hand < 717102; hand++) {
	pair<int, int> longest = make_pair(0, 0), shortest = make_pair(0, 13);
        for (int suit = 0; suit < 4; suit++) {
            int length = 0;
            for (int i = 0; i < 4; i++) {
                unsigned char cache = getc(data);
                for (int j = 0; j < 4; j++) {
                    if (cache % 2 == 1) {
                        length++;
                    }
                    cache /= 4;
                }
            }
	    if (length > longest.second) {
		longest.first = suit;
		longest.second = length;
	    }
	    if (length < shortest.second) {
		shortest.first = suit;
		shortest.second = length;
	    }
        }
	int trumps = 13 + longest.second - shortest.second, tricks = 13;
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
	count[trumps - 14]++;
	totaltrick[trumps - 14] += tricks;
	totaltrick2[trumps - 14] += tricks * tricks;
    }
    fclose(data);
}
