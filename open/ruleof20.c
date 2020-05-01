#include <stdio.h>

int main()
{
    const int hcp_card[4] = { 4, 3, 2, 1 };
    int totaltrick14 = 0, totaltrick13 = 0;
    FILE *data = fopen("Library.bin", "rb");

    for (int row = 0; row < 717102; row++) {
        int hcp[2] = { }, ns = 0, ew = 13, longest[2] = { }, long_2nd[2] = { };
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
            if (length[0] >= longest[0]) {
		long_2nd[0] = longest[0];
                longest[0] = length[0];
	    } else if (length[0] > long_2nd[0]) {
		long_2nd[0] = length[0];
	    }
            if (length[1] >= longest[1]) {
		long_2nd[1] = longest[1];
                longest[1] = length[1];
	    } else if (length[1] > long_2nd[1]) {
		long_2nd[1] = length[1];
	    }
        }
        hcp[0] += longest[0] + long_2nd[0];
        hcp[1] += longest[1] + long_2nd[1];
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
        if (hcp[0] >= 18 || hcp[1] >= 200) {
            totaltrick14 += ns + ew - 13;
        }
        if (hcp[0] >= 19 || hcp[1] >= 200) {
            totaltrick13 += ns + ew - 13;
        }
    }
    fclose(data);
    printf("totaltrick14 = %d\ntotaltrick13 = %d\n", totaltrick14,
           totaltrick13);
    return 0;
}
