//18.10.17 #No.1767 <프로세서 연결하기>
//Coments : 이정도사이즈에서는 맵복사가 오버헤드가 아냐... 설계에서 문제점 찾기
//전선 까는 과정에서 깔수있다는 보장이 있을때 깔도록
//깔면서 확인할 경우 안된다고 판단되면 깔았던거 지워야
//DFS 값 갱신 조건 세분화 및 minMAX 초기화 주의
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string.h>
#define MAXN 12+1
#define INF 0x7fffffff
using namespace std;
int N;
int ans;
pair<int, int> core[MAXN];
int map[MAXN][MAXN];
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };
int num;
int cnt, length;

int move_check(int nowptr, int dir, int nowmap[MAXN][MAXN]){
	
	int temp_leng = 0;
	int rr, cc;
	rr = core[nowptr].first; cc = core[nowptr].second;
	bool ok = true;
	while (true){
		rr += dr[dir];
		cc += dc[dir];
		if (nowmap[rr][cc] != 0 ){
			ok = false; break;
		}
		if (rr == 0 || rr == N - 1 || cc == 0 || cc == N - 1) break;
	}
	if (ok){
		rr = core[nowptr].first; cc = core[nowptr].second;
		while (true){
			rr += dr[dir];
			cc += dc[dir];
			if (nowmap[rr][cc] == 0){
				temp_leng++;
				nowmap[rr][cc] = 2;
				if (rr == 0 || rr == N - 1 || cc == 0 || cc == N - 1) break;
			}
		}
	}
	return temp_leng;
}

void DFS(int nowptr, int nowcnt, int nowlength, int nowmap[MAXN][MAXN]){
	if (nowptr == num){
		if (cnt < nowcnt) {
			length = nowlength;
			cnt = nowcnt;
		}
		else if (cnt == nowcnt){
			length = min(length, nowlength);
		}
		return;
	}
	if (nowcnt + num - nowptr < cnt) return;

	int newmap[MAXN][MAXN];
	memcpy(newmap, nowmap, sizeof(newmap));
	DFS(nowptr + 1, nowcnt, nowlength, newmap);
	//memcpy(newmap, nowmap, sizeof(newmap));
	for (int k = 0; k < 4; k++){
		int temp = move_check(nowptr, k, newmap);
		if (temp){
			DFS(nowptr + 1, nowcnt + 1, nowlength + temp, newmap);
			memcpy(newmap, nowmap, sizeof(newmap));
		}
	}
}

void init(){
	num = 0;
	cnt = -INF;
	length = INF;
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(NULL);
	int T;
	setbuf(stdout, NULL);
	//freopen("sample_input.txt", "r", stdin);
	cin >> T;
	for (int testcase = 1; testcase <= T; ++testcase)
	{
		init();
		cin >> N;
		for (int i = 0; i < N; i++){
			for (int j = 0; j < N; j++){
				cin >> map[i][j];
				if (map[i][j] && i != 0 && i != N - 1 && j != 0 && j != N - 1){
					core[num].first = i; core[num++].second = j;
				}
			}
		}
		if (num>0) DFS(0, 0, 0, map);
		ans = length;
		if (ans == INF) ans = 0;
		cout << "#" << testcase << " " << ans << endl;
	}
	return 0;
}
