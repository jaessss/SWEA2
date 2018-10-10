//18.10.10 #No.4172 <삼성이의 쇼핑 - easy>
//Coments : 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string.h>
#define MAXM 25+1
#define INF 0x7fffffff
using namespace std;
int ans;
int N, M;
typedef struct{
	int price, satis;
}PRODUCT;
PRODUCT product[MAXM];

void DFS( int ind, int now_price, int now_satis){
	if (ind >= M) { 
		if (now_satis > ans) ans = now_satis;
		return; 
	}
	DFS(ind + 1, now_price, now_satis);
	if (now_price + product[ind].price < N) DFS( ind + 1, now_price + product[ind].price, now_satis + product[ind].satis);
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(NULL);
	int T;
	setbuf(stdout, NULL);

	cin >> T;
	for (int testcase = 1; testcase <= T; ++testcase)
	{
		cin >> N >> M;
		for (int i = 0; i < M; i++) cin >> product[i].price >> product[i].satis;
		ans = -INF;
		DFS(0, 0, 0);

		cout << "#" << testcase << " " << ans << endl;
	}
	return 0;
}
