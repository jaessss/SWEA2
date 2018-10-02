//18.10.02 #No.5656 벽돌깨기 1825
//Coments : DFS 전달 파라미터 어떻게 설계할지 신중하게, 2차원 배열 넘기는걸 너무 꺼려하진 말기
//Undo 기능 구현 or 파라미터로 최신화된 정보만 계속 반영해서 원상복구x
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

void recul(int r, int c, int saved_map[][MAXW]){
	if (r < 0 || r >= H || c < 0 || c >= W) return;
	int value = saved_map[r][c];
	saved_map[r][c] = 0;
	if (value >= 2){
		//가로
		int i = r;
		for (int j = c - value + 1; j < c; j++) recul(i, j, saved_map);
		for (int j = c + value - 1; j > c; j--) recul(i, j, saved_map);
		//세로
		int j = c;
		for (int i = r - value + 1; i < r; i++) recul(i, j, saved_map);
		for (int i = r + value - 1; i > r; i--) recul(i, j, saved_map);
	}
	else return;
}

void break_wall(int sel, int saved_map[][MAXW]){
	int bkp=0;
	for (int i = 0; i < H; i++){
		if (saved_map[i][sel] >= 1){
			bkp = i; break;
		}
	}
	recul(bkp, sel, saved_map);
}

void erase_wall(int saved_map[][MAXW]){
	int arr[MAXH] = { 0 };
	int ptr = 0;
	for (int j = 0; j < W; j++){
		ptr = 0;
		for (int i = H - 1; i >= 0; i--){
			if (saved_map[i][j]){
				arr[ptr++] = saved_map[i][j];
			}			
		}
		int wp = 0;
		for (int i = H - 1; i >= H - ptr; i--) saved_map[i][j] = arr[wp++];
		for (int i = H - ptr - 1; i >= 0; i--)saved_map[i][j] = 0;
	}
}

void calc(int saved_map[][MAXW]){
	int cnt = 0;
	for (int i = 0; i < H; i++){
		for (int j = 0; j < W; j++){
			if (saved_map[i][j] >= 1) cnt++;
		}
		if (cnt > ans)return;
	}
	ans = min(ans, cnt);
}

void DFS(int sel, int try_cnt, int saved_map[][MAXW]){
	int old_map[MAXH][MAXW];
	for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) old_map[i][j] = saved_map[i][j];

	if (try_cnt > N) {
		calc(saved_map);
		return;
	}
	if (try_cnt > 0){
		break_wall(sel, old_map);
		erase_wall(old_map);
	}
	
	for (int i = 0; i < W; i++){
		DFS(i, try_cnt + 1, old_map);
		//for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) MAP[i][j] = old_map[i][j];
	}
	
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
