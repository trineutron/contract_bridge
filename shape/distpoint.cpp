#include <stdio.h>
#include <shuffle.cpp>

int main()
{
    const int iter = 10000, points_length[14] = { 3, 1, 0 };
    int fitness = 0;
    for (int i = 0; i < iter;) {
        int hand[52], length[2][4] = { }, longest = 0, points =
            0, is4333[2] = { 1, 1 };
	for (int j = 0; j < 52; j++) hand[j] = j / 13;
        shuffle(hand, hand + 52);
        for (int j = 0; j < 26; j++) {
            length[j / 13][hand[j]]++;
        }

        for (int suit = 0; suit < 4; suit++) {
            points +=
                points_length[length[0][suit]] +
                points_length[length[1][suit]];
            if (length[0][suit] + length[1][suit] > longest)
                longest = length[0][suit] + length[1][suit];
            for (int side = 0; side < 2; side++)
                if (length[side][suit] <= 2)
                    is4333[side] = 0;
        }
	// 4333型は1点減点
        points -= is4333[0] + is4333[1];
        fitness += longest - 8 + points;
        if (longest == 7) fitness -= 2;
        i++;
    }
    printf("%lf\n", 1.0 * fitness / iter);
    return 0;
}
