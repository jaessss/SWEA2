//18.9.29 #No.1952 수영장 - DFS
//Coments : 3개월권 적용 주의, 탐색시작점을 초기 0으로 셋팅
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#define INF 0x7fffffff
using namespace std;
int ans;
typedef struct price_{
	int day, month, t_month, year;
};
price_ price;

int plan[12 + 1];

void DFS(int num, int value){
	if (num > 12){
		ans = min(ans, value);
		ans = min(ans, price.year);
		return;
	}
	if (value > ans) return;
	else {
		int temp_value = min(plan[num + 1] * price.day, price.month);
		DFS(num + 1, value + temp_value);
		DFS(num + 3, value + price.t_month);
	}		
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
		for (int i = 1; i <= 12; i++){ cin >> plan[i];}
		ans = INF;

		DFS(0,0);
		cout << "#" << testcase << " " << ans << endl;
	}
	return 0;
}
