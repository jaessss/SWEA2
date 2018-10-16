//18.10.16 #No.5650 <핀볼게임>
//Coments : 문제에 주어진 특성에 따라 적절하게 자료구조 선정해서 입력처리
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string.h>
#define INF 0x7fffffff
#define MAXN 100+5
using namespace std;
int ans,N;
int map[MAXN][MAXN];
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };
struct PINBALL{
	int start_r, start_c;
	int now_r, now_c, dir;
	int score;
};
vector<pair<int, int>> start;
pair<int, int> warm[2][5];
int warm_cnt[5];

void init(){
	memset(warm, 0, sizeof(warm));
	memset(warm_cnt, 0, sizeof(warm_cnt));
	start.clear();
	ans = -INF;
}

void solve(PINBALL ball){
	while (true){
		int rr = ball.now_r + dr[ball.dir];
		int cc = ball.now_c + dc[ball.dir];
		if (rr < 0 || rr >= N || cc < 0 || cc >= N){//wall
			ball.dir = (ball.dir + 2) % 4;
			ball.score++;
			ball.now_r = rr;
			ball.now_c = cc;
			continue;
		}
		int next = map[rr][cc];
		if (next == -1) break;//black hole
		else if (rr == ball.start_r && cc == ball.start_c) break;//start point

		else if (next == 0){//empty
			ball.now_r = rr;
			ball.now_c = cc;
			continue;
		}
		else if (next >= 6 && next <= 10){//warmhole
			if (rr == warm[0][next - 6].first && cc == warm[0][next - 6].second){
				ball.now_r = warm[1][next - 6].first;
				ball.now_c = warm[1][next - 6].second;
			}
			else{
				ball.now_r = warm[0][next - 6].first;
				ball.now_c = warm[0][next - 6].second;
			}
		}
		else{//block 
			ball.score++;
			ball.now_r = rr;
			ball.now_c = cc;
			switch (ball.dir)
			{
			case 0:
				switch (next)
				{
				case 1: case 4: case 5:
					ball.dir = (ball.dir + 2) % 4;
					break;
				case 2:
					ball.dir = 1;
					break;
				case 3:
					ball.dir = 3;
					break;
				}					
				break;
			case 1:
				switch (next)
				{
				case 1: case 2: case 5:
					ball.dir = (ball.dir + 2) % 4;
					break;
				case 3:
					ball.dir = 2;
					break;
				case 4:
					ball.dir = 0;
					break;
				}
				break;
			case 2:
				switch (next)
				{
				case 2: case 3: case 5:
					ball.dir = (ball.dir + 2) % 4;
					break;
				case 1:
					ball.dir = 1;
					break;
				case 4:
					ball.dir = 3;
					break;
				}
				break;
			case 3:
				switch (next)
				{
				case 3: case 4: case 5:
					ball.dir = (ball.dir + 2) % 4;
					break;
				case 1:
					ball.dir = 0;
					break;
				case 2:
					ball.dir = 2;
					break;
				}
				break;
			}
		}
	}
	ans = max(ans, ball.score);
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
		init();
		cin >> N;
		for (int i = 0; i < N; i++){
			for (int j = 0; j < N; j++){
				cin >> map[i][j];
				if (map[i][j] == 0){
					start.push_back(make_pair(i, j));
				}
				else if (map[i][j] >= 6 && map[i][j] <= 10){
					if (warm_cnt[map[i][j] - 6] == 0){ 
						warm[0][map[i][j] - 6] = make_pair(i, j); 
						warm_cnt[map[i][j] - 6]++;
					}
					else if (warm_cnt[map[i][j] - 6] == 1) warm[1][map[i][j] - 6] = make_pair(i, j);
				}
			}
		}

		for (vector<pair<int, int>> ::iterator itr = start.begin(); itr != start.end(); itr++){
			pair<int, int> temp = *itr;
			for (int dir = 0; dir < 4; dir++){
				PINBALL ball = { temp.first, temp.second, temp.first, temp.second, dir, 0 };
				solve(ball);
			}
		}

		cout << "#" << testcase << " " << ans << endl;
	}
	return 0;
}
