#include <bits/stdc++.h>
using namespace std;

int main() {
    const int deal = 717102;
    FILE *data = fopen("Library.asc", "r");
    vector<vector<int>> c(14, vector<int>(14)), d(14, vector<int>(14));
    for (int i = 0; i < deal; i++) {
	vector<int> length(4), trick(4), trick_defense(4);
	for (int j = 0; j < 17; j++) getc(data); // 読み捨て
	for (int j = 0; j < 4; j++) {
	    char c;
	    while ((c = getc(data)) != '.' && c != ' ') length.at(j)++;
	}
	for (int j = 0; j < 17; j++) getc(data); // 読み捨て
	for (int j = 0; j < 4; j++) {
	    char c;
	    while ((c = getc(data)) != '.' && c != ':') length.at(j)++;
	}
	for (int j = 0; j < 4; j++) getc(data); // 読み捨て
	for (int j = 0; j < 4; j++) {
	    if (fscanf(data, "%1x%1x%*2c", &trick_defense.at(j), &trick.at(j)) != 2) abort();
	}
	getc(data);
	for (int j = 1; j < 4; j++) {
	    for (int k = 0; k < j; k++) {
		int l = max(length.at(j), length.at(k)), s = min(length.at(j), length.at(k));
		int m = length.at(j) >= length.at(k) ? 1 : -1;
		c.at(l).at(s)++;
		d.at(l).at(s) += m * (trick.at(j) - trick.at(k));
		c.at(13 - s).at(13 - l)++;
		d.at(13 - s).at(13 - l) += m * (trick_defense.at(j) - trick_defense.at(k));
	    }
	}
    }
    fclose(data);
    cout << fixed << setprecision(2);
    cout << "Tricks";
    for (int i = 0; i <= 13; i++) {
	cout << '\t' << i;
    }
    cout << endl;
    for (int i = 0; i <= 13; i++) {
	cout << i << '\t';
	for (int j = 0; j <= 13; j++) {
	    cout << (c.at(i).at(j) >= 500 ? (double) d.at(i).at(j) / c.at(i).at(j) : (0.0 / 0.0));
	    if (j == 13) {
		cout << endl;
	    } else {
		cout << '\t';
	    }
	}
    }
}
