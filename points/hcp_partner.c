#include <stdio.h>
#include <shuffle.cpp>

#define HANDS 1000000

int main()
{
    int count_hcp[41] = { }, total = 0, count_total = 0, hcp0;
    puts("Enter HCP.");
    if (scanf("%d", &hcp0) != 1)
        return 1;
    for (int i = 0; i < HANDS; i++) {
        int hcp[52], hcp1 = 0, hcp2 = 0;
	for (int j = 0; j < 52; j++) {
	    hcp[j] = 4 - j / 4;
	    if (hcp[j] < 0) hcp[j] = 0;
	}
        shuffle(hcp, hcp + 52);
        for (int j = 0; j < 13; j++) {
            hcp1 += hcp[j];
        }
        if (hcp1 != hcp0)
            continue;
        for (int j = 13; j < 26; j++) {
            hcp2 += hcp[j];
        }
        count_hcp[hcp2]++;
    }
    for (int i = 0; i <= 40; i++) {
        if (count_hcp[i] == 0)
            continue;
        total += i * count_hcp[i];
        count_total += count_hcp[i];
        printf("%d\t%d\t%d\t%d\n", i, count_hcp[i], total, count_total);
    }
    return 0;
}
