#include <bits/stdc++.h>
using namespace std;

bool isdelimiter(char);
int xtoi(char);

int main() {
    map<int, pair<int, int>> tricks;
    for (int deal = 0; deal < 717102; deal++) {
	string s;
	getline(cin, s);
	int length = 0;
	for (int i = 17; i < 34; i++) {
	    if (isdelimiter(s.at(i))) {
		length *= 10;
	    } else {
		length++;
	    }
	}
	for (int i = 51; i < 68; i++) {
	    if (isdelimiter(s.at(i))) {
		length *= 10;
	    } else {
		length++;
	    }
	}
	length /= 10;
	int length0 = length / 10000, length1 = length % 10000;
	length = max(length0, length1) * 10000 + min(length0, length1);
	int suit[3] = { length / 1000000 % 10 * 10000 + length / 100 % 10,
			length / 100000 % 10 * 10000 + length / 10 % 10,
			length / 10000 % 10 * 10000 + length % 10 };
	sort(suit, suit + 3);
	reverse(suit, suit + 3);
	length = (length / 10000000 % 10 * 10000 + length / 1000 % 10) * 1000 + suit[0] * 100 + suit[1] * 10 + suit[2];
	length0 = length / 10000, length1 = length % 10000;
	length = max(length0, length1) * 10000 + min(length0, length1);
	int trump = length / 10000000 % 10 + length / 1000 % 10;
	if (trump != 8) continue;
	tricks[length].first++;
	tricks[length].second += xtoi(s.at(74));
    }
    for (auto x : tricks) {
	if (x.second.first < 100) continue;
	cout << 1.0 * x.second.second / x.second.first << '\t' << x.first << '\t' << x.second.first << endl;
    }
}

bool isdelimiter(char c) {
    return c == '.' || c == ' ' || c == ':';
}

int xtoi(char c) {
    if (isdigit(c)) {
	return c - '0';
    } else {
	return c - 'A' + 10;
    }
}
