//18.9.29 #No.1952 수영장 - DP
//Coments
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
int ans;
typedef struct price_{
	int day, month, t_month, year;
};
price_ price;

int plan[12 + 1];
int cost[12 + 1];

void DP(){
	cost[0] = 0;
	cost[1] = min(plan[1] * price.day, price.month);
	for (int i = 2; i <= 12; i++){
		cost[i] = min(cost[i - 1] + plan[i] * price.day, cost[i - 1] + price.month);
		if (i >= 3){
			cost[i] = min(cost[i], cost[i - 3] + price.t_month);
		}
	}
	cost[12] = min(cost[12], price.year);
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int T;
	//file inout
	freopen("sample_input.txt", "r", stdin);
	setbuf(stdout, NULL);
	cin >> T;

	for (int testcase = 1; testcase <= T; ++testcase)
	{
		cin >> price.day >> price.month >> price.t_month >> price.year;
		for (int i = 1; i <= 12; i++){ cin >> plan[i]; cost[i] = price.year; }

		DP();
		ans = cost[12];
		cout << "#" << testcase << " " << ans << endl;
	}
	return 0;
}
