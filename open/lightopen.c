#include <stdio.h>
#include <math.h>

int main()
{
    const int hcp_card[4] = { 4, 3, 2, 1 }, sp[4] = { 2, 1, 0, -1 };
    int totaltrick = 0;
    long sxx = 0, sxy = 0, syy = 0;
    FILE *data = fopen("Library.bin", "rb");

    for (int row = 0; row < 717102; row++) {
        int hcp[2] = { }, ns = 0, ew = 13, shortest[2] = { 3, 3 };
        for (int suit = 0; suit < 4; suit++) {
            int length[2] = { };
            for (int i = 0; i < 4; i++) {
                int cache = getc(data);
                for (int j = 0; j < 4; j++) {
                    if (cache % 2 == 1) {
                        length[(cache / 2) % 2]++;
                        if (i == 3)
                            hcp[(cache / 2) % 2] += hcp_card[j];
                    }
                    cache >>= 2;
                }
            }
            if (length[0] < shortest[0])
                shortest[0] = length[0];
            if (length[1] < shortest[1])
                shortest[1] = length[1];
        }
        hcp[0] += sp[shortest[0]];
        hcp[1] += sp[shortest[1]];
        for (int suit = 0; suit < 5; suit++) {
            int cache = getc(data) % 16;
            if (cache > ns) {
                ns = cache;
            }
            cache = getc(data) / 16;
            if (cache < ew) {
                ew = cache;
            }
        }
        if (hcp[0] + hcp[1] >= 21) {
            totaltrick += ns + ew - 13;
        }
	sxx += (ns + ew - 13) * (ns + ew - 13);
        sxy += (ns + ew - 13) * (hcp[0] + hcp[1] - 20);
	syy += (hcp[0] + hcp[1] - 20) * (hcp[0] + hcp[1] - 20);
    }
    fclose(data);
    printf("totaltrick = %d\nR = %f\n", totaltrick, 1.0 * sxy / sqrt(sxx * syy));
    return 0;
}
