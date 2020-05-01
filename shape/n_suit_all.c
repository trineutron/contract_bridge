#include <stdio.h>
#include <stdlib.h>
#include <shuffle.cpp>

int bid(int[]);
int desc(const void *, const void *);

int main()
{
    const int iter = 10000000;
    int totaltrump[4] = { }, fit[4] = { }, totaltrump_best = 0, fit_best =
        0;

    for (int i = 0; i < iter; i++) {
        int trumps[4], best = bid(trumps);
        for (int suit = 0; suit < 4; suit++) {
            totaltrump[suit] += trumps[suit];
            if (trumps[suit] >= 8) {
                fit[suit]++;
            }
        }
        totaltrump_best += best;
        if (best >= 8)
            fit_best++;
    }

    for (int i = 0; i < 4; i++) {
        printf("%dsuiter\t%.7f\t0.%d\n", i + 1, 1.0 * totaltrump[i] / iter,
               fit[i]);
    }
    printf("best\t%.7f\t0.%d\n", 1.0 * totaltrump_best / iter, fit_best);

    return 0;
}

int bid(int trumps[])
{
    int cards[52], hand_total[4] = { }, hand_partner[4];
    for (int i = 0; i < 52; i++) cards[i] = i;
    shuffle(cards, cards + 52);
    for (int i = 0; i < 26; i++) {
        int cache = cards[i] % 4;
        hand_total[cache]++;
        if (i < 13) {
            hand_total[cache] += 256;
        }
    }
    qsort(hand_total, 4, sizeof(int), desc);
    if (xrand() % 6 == 0) {
        int w = hand_total[1];
        hand_total[1] = hand_total[2];
        hand_total[2] = w;
    }
    for (int suit = 0; suit < 4; suit++) {
        int cache = hand_total[suit] % 256;
        hand_partner[suit] = cache - hand_total[suit] / 256;
        hand_total[suit] = cache;
    }

    for (int nsuit = 0; nsuit < 4; nsuit++) {
        int longest = hand_partner[0], longest_total =
            hand_total[0], maxsuit = 0;
        for (int suit = 1; suit < 4; suit++) {
            if (hand_partner[suit] > longest) {
                longest = hand_partner[suit];
                longest_total = hand_total[suit];
                if (suit <= nsuit)
                    maxsuit = suit;
            }
        }
        if (longest > hand_partner[maxsuit] + 2) {
            trumps[nsuit] = longest_total;
        } else {
            trumps[nsuit] = hand_total[maxsuit];
        }
    }

    int best = hand_total[0];
    for (int suit = 1; suit < 4; suit++) {
        if (best < hand_total[suit])
            best = hand_total[suit];
    }

    return best;
}

int desc(const void *a, const void *b)
{
    return (*(int *) b - *(int *) a) / 64;
}
