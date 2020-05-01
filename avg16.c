#include <stdio.h>
#include <math.h>

/* 16進数の入力の平均と標準偏差を出力 */
int main()
{
    int x, i = 0, total = 0, total_2 = 0;
    double avg, avg_2;
    while (scanf("%1x", &x) == 1) {
        i++;
        total += x;
        total_2 += x * x;
    }
    avg = 1.0 * total / i;
    avg_2 = 1.0 * total_2 / i - avg * avg;
    printf("avg\t\tstddev\t\tn\n");
    printf("%lf\t%lf\t%d\n", avg, sqrt(avg_2), i);
    return 0;
}
