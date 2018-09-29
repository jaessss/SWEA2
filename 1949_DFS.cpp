//18.9.29 #No.1949 등산로 조성 - DFS ver.
//각각의 한번의 탐색에 있어 visit check 후 원상복구
//이 문제의 경우 BFS보다 DFS가 더 빠른 이유
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
#define MAXN 8+1
#define INF 0x7fffffff

int dx[] = { 0, 0, -1, 1 };
int dy[] = { -1, 1, 0, 0 };

int MAP[MAXN][MAXN];
int ans;
int N, K;
int max_h = -INF;
int visit[MAXN][MAXN];

typedef struct point{
	int x, y;
	int depth;
	bool used;
};

bool range_check(point p){
	if (p.x >= 0 && p.x < N && p.y >= 0 && p.y < N) return true;
	else return false;
}

void DFS(point cur){
	visit[cur.x][cur.y] = 1;
	ans = max(ans, cur.depth);
	point next;

	for (int i = 0; i < 4; i++){
		next.x = cur.x + dx[i];
		next.y = cur.y + dy[i];
		next.depth = cur.depth + 1;
		next.used = cur.used;
		if (range_check(next) && visit[next.x][next.y] == 0){
			//그냥진행가능
			if (MAP[cur.x][cur.y] > MAP[next.x][next.y]) DFS(next);
			//깍고진행가능
			else if (!cur.used && MAP[cur.x][cur.y] > MAP[next.x][next.y] - K){
				int temp = MAP[next.x][next.y];
				MAP[next.x][next.y] = MAP[cur.x][cur.y] - 1;
				next.used = true;
				DFS(next);
				MAP[next.x][next.y] = temp;
			}
			//진행 불가
			else continue;
		}
		else continue;
	}
	visit[cur.x][cur.y] = 0;
}

void solve(){
	for (int i = 0; i < N; i++) for (int j = 0; j < N; j++){
		if (max_h == MAP[i][j]){
			point temp = { i, j, 1, false };
			DFS(temp);
		}
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
		cin >> N >> K;
		ans = max_h = -INF;
		for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
			visit[i][j] = 0;
			cin >> MAP[i][j];
			max_h = max(max_h, MAP[i][j]);
		}
		solve();
		cout << "#" << testcase << " " << ans << endl;
	}
	return 0;
}
