//18.10.01 #No.2117 홈방범서비스
//Coments : 범위최대값주변 주의
//문구주의 : 손해보지 않는 범위 -> 이익이 0원이어도 ok
//#define 된 매크로 상수를 연산해서 변수선언 하지마 int x[MAXN*MAXN];
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define MAXNN 401
#define MAXN 20+5
#define INF 0x7fffffff

typedef struct HOME{
	int r, c;
};
HOME home[MAXNN];
int num_home;
int cost[MAXN];
int MAP[MAXN][MAXN];
int N, M;
int ans;

void solve(){
	int profit = 0;
	int cnt = 0;
	for (int k = 1; k < N+3; k++){
		for (int i = 0; i < N; i++){
			for (int j = 0; j < N; j++){
				cnt = 0;
				for (int n = 0; n < num_home; n++){
					int temp_dis = abs(i - home[n].r) + abs(j - home[n].c);
					if (temp_dis < k) cnt++;
				}
				profit = cnt*M - cost[k];
				if (profit >= 0) ans = max(ans, cnt);
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

	for (int k = 1; k < MAXN; k++) cost[k] = k*k + (k - 1)*(k - 1);

	for (int testcase = 1; testcase <= T; ++testcase)
	{
		num_home = 0;
		cin >> N >> M;
		for (int i = 0; i < N; i++){
			for (int j = 0; j < N; j++){
				cin >> MAP[i][j];
				if (MAP[i][j]){
					home[num_home].r = i;
					home[num_home++].c = j;
				}
			}
		}
		ans = -INF;
		solve();
		cout << "#" << testcase << " " << ans << endl;
	}
	return 0;
}
