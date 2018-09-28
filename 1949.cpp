//18.9.28 #No. 등산로 조성
//출발지점 선정에 있어 조건 해석 논란의 여지.. 
//Coments 최대공사가능!K값만큼 무조건 깍는거x
//2차원 배열 함수 파라미터로 넘기는 방법, call by reference로 전달됨
//실행시간 줄일 수 있는 방법 생각해보기
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

typedef struct point{
	int x, y;
	int depth;
};

bool range_check(point p){
	if (p.x >= 0 && p.x < N && p.y >= 0 && p.y < N) return true;
	else return false;
}

int BFS(int MAP[][MAXN], int x, int y){
	vector<point> v;
	unsigned int ptr = 0;
	int visit[MAXN][MAXN] = { 0, };
	point start_point;
	point temp_point;
	point next_point;
	start_point.x = x;
	start_point.y = y;
	start_point.depth = 1;
	v.push_back(start_point);

	while (v.size() >= ptr + 1){//종료조건확인
		temp_point = v.at(ptr++);
		visit[temp_point.x][temp_point.y] = max(visit[temp_point.x][temp_point.y], temp_point.depth);

		for (int i = 0; i < 4; i++){
			next_point.x = temp_point.x + dx[i];
			next_point.y = temp_point.y + dy[i];
			next_point.depth = temp_point.depth + 1;
			if (range_check(next_point) && MAP[next_point.x][next_point.y] < MAP[temp_point.x][temp_point.y]){
					v.push_back(next_point);
			}
		}
	}
	int length = -INF;
	for (int i = 0; i < N; i++) for (int j = 0; j < N; j++)
		length = max(length, visit[i][j]);
	return length;
}

int solve(int x, int y, int z){
	int max_h = -INF;
	int temp = 0;
	for (int i = 0; i < N; i++) for (int j = 0; j < N; j++)
		max_h = max(max_h, MAP[i][j]);
	
	for (int i = 0; i < N; i++) for (int j = 0; j < N; j++){
		if (MAP[i][j] == max_h){//return  함부러 xxx
			MAP[x][y] -= z;
			temp = max(temp, BFS(MAP, i, j));
			MAP[x][y] += z;
		} 
		else continue;
	}	
	return temp;
}

int main(void)
{
	//ios::sync_with_stdio(false);
	//cin.tie(NULL);
	int T;
	//file inout
	freopen("sample_input.txt", "r", stdin);
	setbuf(stdout, NULL);
	scanf("%d", &T);

	for (int testcase = 1; testcase <= T; ++testcase)
	{
		cin >> N >> K;
		for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) cin >> MAP[i][j];

		ans = -INF;
		int temp_leng;//= solve(MAP, 0, 0, 0);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++){
				for (int k = 1; k <= K; k++){					
					temp_leng = solve(i,j,k);					
					ans = max(temp_leng, ans);
				}				
			}
		cout << "#" << testcase << " " << ans << endl;
	}
	return 0;
}
