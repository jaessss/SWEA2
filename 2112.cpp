//18.10.08 #No.2112 보호필름
//Coments : 다중재귀 뛰는 방향 고민 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#define MAXW 20 + 1
#define MAXD 13 + 1
#define INF 0x7fffffff
using namespace std;
int ans;
int input[MAXD][MAXW];
int D, W, K;
int depth = 1;
int ok = 1;

bool isPass(int map[][MAXW]){
	for (int j = 0; j < W; j++){
		depth = 1;
		ok = 0;
		for (int i = 1; i < D; i++){
			if (map[i - 1][j] == map[i][j]) depth++;
			else depth = 1;
			if (depth >= K){ ok = 1; break; }
			ok = 0;
			if (i + K - depth >= D) return false;
		}
		if (ok == 0) return false;
	}
	if (ok == 1) return true;
}

void DFS(int cnt, int map[][MAXW], int search){
	if (ans <= cnt || search >D) return;
	if (isPass(map)){ ans = min(cnt, ans); return; }

	int save[MAXW] = { -1 };
    DFS(cnt, map, search + 1);
    for (int j = 0; j < W; j++)	save[j] = map[search][j];
    for (int j = 0; j < W; j++) map[search][j] = 0;
    DFS(cnt + 1, map, search+1);
    for (int j = 0; j < W; j++) map[search][j] = 1;
    DFS(cnt + 1, map, search+1);
    for (int j = 0; j < W; j++) map[search][j] = save[j];
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int T;
	setbuf(stdout, NULL);
	cin >> T;

	for (int testcase = 1; testcase <= T; ++testcase)
	{
		cin >> D >> W >> K;
		for (int i = 0; i < D; i++) for (int j = 0; j < W; j++) cin >> input[i][j];

		ans = INF;
		DFS(0, input, 0 );

		cout << "#" << testcase << " " << ans << endl;
	}
	return 0;
}
