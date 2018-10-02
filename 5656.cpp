//18.10.02 #No.5656 벽돌깨기 1825
//Coments : DFS로 넘길 파라미터 설계 주의 ~ 전역변수를 원상복구할 것인지 그때그때 새로운 맵을 만들어 최신화된 맵을 전달할 것인지
// 2차원 배열을 함수 파라미터로 넘기는 것을 너무 주저하지 말기

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
int ans;
#define MAXW 12+1
#define MAXH 15 + 1
#define INF 0x7fffffff
int N, W, H;
int MAP[MAXH][MAXW];
int MAP_save[MAXH][MAXW];

void calc(int map[][MAXW]){
	int cnt = 0;
	for (int i = 0; i < H; i++){
		for (int j = 0; j < W; j++){
			if (map[i][j] >= 1) cnt++;
		}
		if (cnt > ans)return;
	}
	ans = min(ans, cnt);
}

void recul(int r, int c, int map[][MAXW]){
	if (r < 0 || r >= H || c < 0 || c >= W) return;

	int value = map[r][c];
	map[r][c] = 0;
	if (value >= 2){
		//가로
		int i = r;
		for (int j = c - value + 1; j < c; j++) recul(i, j, map);
		for (int j = c + value - 1; j > c; j--) recul(i, j, map);
		//세로
		int j = c;
		for (int i = r - value + 1; i < r; i++) recul(i, j, map);
		for (int i = r + value - 1; i > r; i--) recul(i, j, map);
	}
	else return;
}

void break_wall(int sel, int map[][MAXW]){
	int bkp=0;
	for (int i = 0; i < H; i++){
		if (map[i][sel] >= 1){
			bkp = i; break;
		}
	}
	recul(bkp, sel, map);
    int arr[MAXH] = { 0 };
	int ptr = 0;
	for (int j = 0; j < W; j++){
		ptr = 0;
		for (int i = H - 1; i >= 0; i--){
			if (map[i][j]){
				arr[ptr++] = map[i][j];
			}			
		}
		int wp = 0;
		for (int i = H - 1; i >= H - ptr; i--) map[i][j] = arr[wp++];
		for (int i = H - ptr - 1; i >= 0; i--) map[i][j] = 0;
	}
}

void DFS(int sel, int try_cnt, int saved_map[][MAXW]){
	int new_map[MAXH][MAXW];
	for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) new_map[i][j] = saved_map[i][j];

	if (try_cnt > N) {
		calc(new_map);
		return;
	}
	if (try_cnt > 0) break_wall(sel, new_map);
	for (int i = 0; i < W; i++)	DFS(i, try_cnt + 1, new_map);
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
		cin >> N >> W >> H;
		for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) cin >> MAP[i][j];
		ans = INF;
		
		DFS(-1, 0, MAP);
		cout << "#" << testcase << " " << ans << endl;
	}
	return 0;
}
