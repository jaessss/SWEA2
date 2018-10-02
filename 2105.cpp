//18.10.02 #No.2105 디저트 카페
//Coments : visit을 쓰면 안되는 경우, visit check를 대신한말한 존재?
// DFS 호출 후 복귀시 원상복구 ~ 파라미터 상에 변화주는 것 이외에 전역으로 선언된 모든 관련 변수
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#define INF 0x7fffffff
#define MAXN 20+2
#define MAXcase 100 + 2
using namespace std;

int N;
int MAP[MAXN][MAXN];
int visit[MAXN][MAXN];
int check[MAXcase];
int start_r, start_c;
int ans;
int temp_cnt;
int dr[5] = {0, 1, 1, -1, -1 };
int dc[5] = {0, 1, -1, -1, 1 };

void init(){
	for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) visit[i][j] = 0;
	for (int i = 0; i < MAXcase; i++) check[i] = 0;
}

bool move_check(int r, int c, int dir){
	int rr = r + dr[dir];
	int cc = c + dc[dir];
	if (rr < 0 || rr >= N || cc < 0 || cc >= N) return false;
	else{
		if (!check[MAP[rr][cc]] ){ return true; }
		else return false;
	}
	/*if ((rr >= 0) && (rr < N) && (cc >= 0) && (cc < N)){
		if (!check[MAP[rr][cc]]){ return true; }
		else return false;
	}
	else false;*/
	//&& !visit[rr][cc]
}

void DFS(int r, int c, int dir, int cnt){
	//끝조건 주의
	if (r == start_r+1 && c == start_c-1){
		temp_cnt = max(temp_cnt, cnt);
		return;
	}
	//visit[r][c] = 1;
	check[MAP[r][c]] = 1;

	if (dir == 1){
		if (move_check(r, c, 1) || move_check(r, c, 2)){
			if (move_check(r, c, 1)) {
				DFS(r + dr[1], c + dc[1], 1, cnt + 1);
				check[MAP[r + dr[1]][c + dc[1]]] = 0;
			}
			if (move_check(r, c, 2)){
				DFS(r + dr[2], c + dc[2], 2, cnt + 1);
				check[MAP[r + dr[2]][c + dc[2]]] = 0;
			}
		}
		else{
			check[MAP[r][c]] = 0; return;
		}
	}
	else if (dir == 2){
		if (move_check(r, c, 2) || move_check(r, c, 3)){
			if (move_check(r, c, 2)){
				DFS(r + dr[2], c + dc[2], 2, cnt + 1);
				check[MAP[r + dr[2]][c + dc[2]]] = 0;
			}
			if (move_check(r, c, 3)){
				DFS(r + dr[3], c + dc[3], 3, cnt + 1);
				check[MAP[r + dr[3]][c + dc[3]]] = 0;
			}
		}
		else{
			check[MAP[r][c]] = 0; return;
		}
	}
	else if (dir == 3){
		if (move_check(r, c, 3) || move_check(r, c, 4)){
				
			if (move_check(r, c, 3)){
				DFS(r + dr[3], c + dc[3], 3, cnt + 1);
				check[MAP[r + dr[3]][c + dc[3]]] = 0;
			}
			if (move_check(r, c, 4)){
				DFS(r + dr[4], c + dc[4], 4, cnt + 1);
				check[MAP[r + dr[4]][c + dc[4]]] = 0;
			}
			
		}
		else{
			check[MAP[r][c]] = 0; return;
		}
	}
	else{
		if (move_check(r, c, 4)){
			DFS(r + dr[4], c + dc[4], 4, cnt + 1);
			check[MAP[r + dr[4]][c + dc[4]]] = 0;
		}
		else{
			check[MAP[r][c]] = 0; return;
		}
	}
}

void solve(){
	for (int i = 0; i < N-2; i++){
		for (int j = 1; j < N; j++){
			//init();
			memset(check, 0, sizeof(check));
			start_r = i; start_c = j;
			check[MAP[i][j]] = 1;
			if (move_check(i, j, 1)){
				temp_cnt = 0;
				DFS(start_r + dr[1], start_c + dc[1], 1, 2);
				ans = max(temp_cnt, ans);
			}
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
		cin >> N;
		for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) cin >> MAP[i][j];

		ans = -INF;
		solve();
		if (ans <= 0) ans = -1;
		cout << "#" << testcase << " " << ans << endl;
	}
	return 0;
}
