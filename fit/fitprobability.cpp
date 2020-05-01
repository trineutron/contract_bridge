#include <cstdio>
#include <random>
#include <algorithm>

int main()
{
    std::random_device seed;
    std::mt19937_64 rng(seed());
    const int iter = 1000000;
    int major8 = 0, minor8 = 0, major7 = 0, nofit = 0;
    for (int i = 0; i < iter; i++) {
        int hand[52], length[4] = { };
	for (int j = 0; j < 52; j++) hand[j] = j / 13;
	std::shuffle(hand, hand + 52, rng);
        for (int j = 0; j < 26; j++) {
            length[hand[j]]++;
        }
	if (length[0] >= 8 || length[1] >= 8) {
	    major8++;
	} else {
	    if (length[2] >= 8 || length[3] >= 8) minor8++;
	    if (length[0] >= 7 || length[1] >= 7) major7++;
	    if (length[0] < 7 && length[1] < 7 && length[2] < 8 && length[3] < 8) nofit++;
	}
    }
    printf("major8\t%f\nminor8\t%f\nmajor7\t%f\nnofit\t%f\n", 1.0 * major8 / iter, 1.0 * minor8 / iter, 1.0 * major7 / iter, 1.0 * nofit / iter);
    return 0;
}
