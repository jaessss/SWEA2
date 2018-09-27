//18.9.27 #No.4014 활주로 건설
//Coments : 문제에서 주어진 주의해야할만한 상황 필히 체크
// 반복문 사용시 갱신되어야하는 값 주의
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
#define MAXN 20+1
int MAP[MAXN][MAXN];
int N, X;
int ans = 0;

bool check(vector<int> &v, int now_ptr){
	int next_h = v.at(now_ptr + 1);
	int now_h = v.at(now_ptr);
	if (now_h - next_h > 1) return false;//if문안에서 v.at호출해도 정상동작?
	else{
		for (int i = 1; i < X; i++){
			if (now_ptr + 1 + i < N){
				if (next_h == v.at(now_ptr + 1 + i)) continue;
				else return false;
			}
			else return false;
		}
		return true;
	}
}

void solve(vector<int> &v){
	int ptr = 0;
	int now_h = v.at(0);
	int next_h;
	int action;
	int cnt = 1;

	while (ptr < N - 1){//조건확인
		ptr++;
		next_h = v.at(ptr);
		action = now_h - next_h;
		switch (action)
		{
		case 0:
			cnt++;
			break; 
		case 1:
			if (check(v, ptr - 1)){
				cnt = 0;//이미 설치한 칸 기준으로 다시 탐색을 시작하기때문에 cnt는0
				ptr += X-1;
				next_h = v.at(ptr);
				break; 
			}
			return;
		case -1:
			if (cnt >= X){cnt = 1; break;}
			else return;
		default:
			return;
		}
		now_h = next_h;
	}
	ans++;
	return;
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
		ans = 0;
		cin >> N;
		cin >> X;
		for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) cin >> MAP[i][j];

		//가로 라인
		for (int i = 0; i < N; i++){
			vector<int> v;
			for (int j = 0; j < N; j++)	v.push_back(MAP[i][j]);
			solve(v);
		}
		for (int i = 0; i < N; i++){
			vector<int> v;
			for (int j = 0; j < N; j++)	v.push_back(MAP[j][i]);			
			solve(v);
		}

		printf("#%d %d\n", testcase, ans);

	}


	return 0;
}
