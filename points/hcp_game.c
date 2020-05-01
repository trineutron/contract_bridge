#include <stdio.h>
#include <ctype.h>
#include "atohcp.c"

#define MAXHCP 44

int itox(int);

int main()
{
    int count[MAXHCP + 1] = { }, game[MAXHCP + 1][3] = { };

    FILE *data = fopen("Library.asc", "r");
    while (!feof(data)) {
	const int lp_suit[14] = { 2, 1, 0 };
	int hcp[4] = { }, hcptotal, lp[4] = { }, tricks[5], level = 0, fit[4] = { };
	for (int player = 0; player < 4; player++) {
	    int length = 0, suit = 0;
	    for (int i = 0; i < 17; i++) {
		char card = getc(data);
		hcp[player] += atohcp(card);
		if (isalnum(card)) {
		    length++;
		} else {
		    lp[player] += lp_suit[length];
		    if (player % 2) fit[suit] += length;
		    suit++;
		    length = 0;
		}
	    }
	}
	hcptotal = hcp[1] + hcp[3] + lp[1] + lp[3];
	for (int suit = 0; suit < 5; suit++) {
	    getc(data); // 読み捨て
	    tricks[suit] = itox(getc(data));
	    getc(data); // 読み捨て
	    getc(data); // 読み捨て

	    if (tricks[suit] == 13) {
		level = 3;
	    } else if (tricks[suit] == 12 && level < 2) {
		level = 2;
	    }
	}
	getc(data); // 改行を読み捨て
	if (level == 0) {
	    if (tricks[0] >= 9 || tricks[1] >= 10 || tricks[2] >= 10
		|| tricks[3] >= 11 || tricks[4] >= 11) {
		level = 1;
	    }
	}
	int fitpoint = 0, fitpoint_minor = 0;
	if (fit[0] - 7 > fitpoint) fitpoint = fit[0] - 7;
	if (fit[1] - 7 > fitpoint) fitpoint = fit[1] - 7;
	if (fit[2] - 7 > fitpoint_minor) fitpoint_minor = fit[2] - 7;
	if (fit[3] - 7 > fitpoint_minor) fitpoint_minor = fit[3] - 7;
	//if (fitpoint < fitpoint_minor) fitpoint = fitpoint_minor;
	hcptotal += fitpoint;
	count[hcptotal]++;
	for (int i = 0; i < level; i++) {
	    game[hcptotal][i]++;
	}
    }
    fclose(data);

    int wrong[3] = { };
    for (int hcp = 0; hcp <= MAXHCP; hcp++) {
        printf("%d", hcp);
        for (int i = 0; i < 3; i++) {
	    double r = (double) game[hcp][i] / count[hcp];
            printf("\t%lf", r);
	    if (r >= 0.5) {
		wrong[i] += count[hcp] - game[hcp][i];
	    } else {
		wrong[i] += game[hcp][i];
	    }
        }
        printf("\t%d\n", count[hcp]);
    }
    for (int i = 0; i < 3; i++) {
	printf("\t%d", wrong[i]);
    }
    puts("");

    return 0;
}

int itox(int a)
{
    if (a >= 'A') {
        return a - 'A' + 10;
    } else {
        return a - '0';
    }
}
