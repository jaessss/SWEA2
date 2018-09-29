//18.9.29 #No.1953 탈주범 검거 - DFS
//Coments : DFS visit 체크기준, 첫방문보다 나은 경로로 방문하는 경우가 있을 수 있음 -> BFS라면 문제되지 않았을 부분
//+가지치기
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
#define MAXNUM 50+1
#define MAXL 20+1
int MAP[MAXNUM][MAXNUM];
int N, M, R, C, L;
int ans;
int up[4] = { 1, 2, 5, 6 };
int down[4] = { 1, 2, 4, 7 };
int left_[4] = { 1, 3, 4, 5 };
int right_[4] = { 1, 3, 6, 7 };
int visit[MAXNUM][MAXNUM];
int dr[4] = { -1, 1, 0, 0 };
int dc[4] = { 0, 0, -1, 1 };

typedef struct point_{
	int r, c, depth;
};

bool check(point_ p){
	if (visit[p.r][p.c] > p.depth && MAP[p.r][p.c] != 0 && p.r >= 0 && p.r < N && p.c >= 0 && p.c < M) return true;
	else return false;
}

void DFS(point_ now){
	visit[now.r][now.c] = now.depth;
	if (now.depth >= L) return;
	
	for (int i = 0; i < 4; i++){
		point_ next = { now.r + dr[i], now.c + dc[i], now.depth + 1 };
		if (check(next)){
			if (i == 0){
				for (int j = 0; j < 4; j++){
					if (MAP[now.r][now.c] == down[j]){
						for (int k = 0; k < 4; k++) if(MAP[next.r][next.c] == up[k]) DFS(next);	}}}
			if (i == 1){
				for (int j = 0; j < 4; j++){
					if (MAP[now.r][now.c] == up[j]){
						for (int k = 0; k < 4; k++) if (MAP[next.r][next.c] == down[k]) DFS(next);	}}}
			if (i == 2){
				for (int j = 0; j < 4; j++){
					if (MAP[now.r][now.c] == right_[j]){
						for (int k = 0; k < 4; k++) if (MAP[next.r][next.c] == left_[k]) DFS(next);	}}}
			if (i == 3){
				for (int j = 0; j < 4; j++){
					if (MAP[now.r][now.c] == left_[j]){
						for (int k = 0; k < 4; k++) if (MAP[next.r][next.c] == right_[k]) DFS(next);}}}
		}
		else continue;
		
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
		cin >> N >> M >> R >> C >> L;
		ans = 0;
		for (int i = 0; i < N; i++) for (int j = 0; j < M; j++){ cin >> MAP[i][j]; visit[i][j] = MAXL; }
		point_ start_point = { R, C, 1 };
		DFS(start_point);

		for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) if (visit[i][j] < MAXL) ans++;
		cout << "#" << testcase << " " << ans << endl;
	}
	return 0;
}
