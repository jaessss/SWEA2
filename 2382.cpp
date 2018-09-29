//18.9.29 #No.2382 미생물 격리
//Coments : 3개 이상 겹치는거 주의
// 방향 변경시 독립적으로... else if , if만 열거하는거 주의
// 체크 카운트 시 없어진 군집 제외하고 카운트
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
int ans;
int N, M, K;
#define MAXN 100+1
#define MAXK 1000+1
#define INF 0x7fffffff;
int dr[4] = { -1, 1, 0, 0 };
int dc[4] = { 0, 0, -1, 1 };
typedef struct info{
	int r, c, num, dir;
};//dir 상하좌우 1 2 3 4
info mi[MAXK];
int check[MAXN][MAXN];

void merge(int r, int c){
	int temp_max = -INF;
	int max_ind = -1;
	for (int i = 0; i < K; i++)	{
		if (mi[i].r == r && mi[i].c == c){
			if (temp_max < mi[i].num){
				temp_max = mi[i].num;
				max_ind = i;
			}
		}
	}
		
	for (int i = 0; i < K; i++){
		if (mi[i].r == r && mi[i].c == c && i != max_ind){		
				mi[max_ind].num += mi[i].num;
				mi[i].num = 0;			
				mi[i].r = mi[i].c = -1;
		}
	}
}

bool boundary(info mi){
	if ((mi.r == 0 || mi.r == N - 1) || (mi.c == 0 || mi.c == N - 1)) return true;
	else return false;
}

void change(){
	//boundary change dir,num
	for (int i = 0; i < K; i++){
		if (boundary(mi[i])){
			mi[i].num /= 2;
			if (mi[i].dir == 1)mi[i].dir = 2;
			else if (mi[i].dir == 2)mi[i].dir = 1;
			else if (mi[i].dir == 3)mi[i].dir = 4;
			else if (mi[i].dir == 4)mi[i].dir = 3;
		}
	}
	//merge
	for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) check[i][j] = 0;
	for (int i = 0; i < K; i++){ if (mi[i].num > 0){ check[mi[i].r][mi[i].c]++; } }
	
	for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) if (check[i][j] >= 2) merge(i,j);
}

void move(){
	for (int i = 0; i < K; i++){
		if (mi[i].num > 0){
			mi[i].r += dr[mi[i].dir - 1];
			mi[i].c += dc[mi[i].dir - 1];
		}		
	}
}

void solve(){
	int time = 0;
	while (time < M){
		move();
		change();
		time++;
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
		cin >> N >> M >> K;
		for (int i = 0; i < K; i++)	cin >> mi[i].r >> mi[i].c >> mi[i].num >> mi[i].dir;
		solve();
		ans = 0;
		for (int i = 0; i < K; i++) ans += mi[i].num;
		cout << "#" << testcase << " " << ans << endl;
	}
	return 0;
}
