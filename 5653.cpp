//18.10.15 #No.5653 <줄기세포배양> 2053-2310
//Coments : 최대 범위 갱신 주의, if문 안에 여러 조건을 때려넣을때 가능한지 확실히 판단, 초기화주의
//단순히 사이즈 제한 없다고 생각하지말고 최대치를 고려해서 배열로 진행할 생각하도록
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string.h>
#define MAXSIZE 350+2
#define offset 151
using namespace std;
int ans;
int N, M, K;
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };
struct POINT{
	short life, now;
};
POINT map[MAXSIZE][MAXSIZE];
int rs, re, cs, ce;

void expand(){
	int rss = rs; int ree = re; int css = cs; int cee = ce;/////////////////////
	short newmap[MAXSIZE][MAXSIZE] = { 0, };
	for (int i = rss; i < ree; i++){
		for (int j = css; j < cee; j++){
			if (map[i][j].life && map[i][j].now >= 0 && map[i][j].now < map[i][j].life){
				for (int k = 0; k < 4; k++){
					int rr = i + dr[k];
					int cc = j + dc[k];
					if (map[rr][cc].life == 0){
						if (newmap[rr][cc]){//////////////주의!
							if (newmap[rr][cc] < map[i][j].life) newmap[rr][cc] = map[i][j].life;
						}
						else{
							newmap[rr][cc] = map[i][j].life;
							rs = min(rs, rr);
							re = max(re, rr + 1);////////////
							cs = min(cs, cc);
							ce = max(ce, cc + 1);////////////
						}
					}
					else continue;
				}
			}
		}
	}
	//map change
	for (int i = rs; i < re; i++){
		for (int j = cs; j < ce; j++){
			if (newmap[i][j]) map[i][j] = { newmap[i][j], newmap[i][j] * 2 };
		}
	}

}

void calc(){
	for (int i = rs; i < re; i++){
		for (int j = cs; j < ce; j++){
			if (map[i][j].life && map[i][j].now > 0) ans++;//////////////0보다크게
		}
	}
}

void solve(){
	int time = 0;
	while (time++ < K){
		//change state
		for (int i = rs; i <= re; i++){
			for (int j = cs; j <= ce; j++){
				if (map[i][j].life && map[i][j].now > -1) map[i][j].now--;
			}
		}
		expand();
	}
	calc();
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(NULL);
	int T;
	freopen("sample_input.txt", "r", stdin);
	setbuf(stdout, NULL);

	cin >> T;
	for (int testcase = 1; testcase <= T; ++testcase)
	{
		memset(map, 0, sizeof(map));////////////초기화주의
		rs = re = cs = ce = offset;
		int temp;
		cin >> N >> M >> K;
		re += N;   ce += M;
		for (int i = offset; i < offset + N; i++){
			for (int j = offset; j < offset + M; j++){
				cin >> temp;
				if (temp) map[i][j] = { temp, temp * 2 };
			}
		}
		ans = 0;
		solve();
		cout << "#" << testcase << " " << ans << endl;
	}
	return 0;
}
