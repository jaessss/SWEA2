//18.10.1 #No.2115 벌꿀채취
//Coments : 설계단계에서 구현 시 놓칠 수 있는 부분 캐치할 수 있도록
//인덱스 주의 쉬운 예로 판단하기
//더 나은 조합 및 탐색 방법? 일꾼들이 연달아서 최적의 값을 선택하면 결과가 최적일까?(그리디)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
#define MAXN 10+1
#define INF 0x7fffffff
int ans;
int N, M_num, C_max;
int MAP[MAXN][MAXN];

int calc(int r, int c){//선택된 좌표에서 최대 채취가능한 양 계산
	int temp_ans = -INF;
	for (int i = 0; i < (1 << M_num ); i++){//범위 주의
		int temp_sum = 0, temp_sq = 0;
		for (int j = 0; j <= M_num - 1; j++){
			if (i & (1 << j)){//인덱스 주의
				temp_sum += MAP[r][c + M_num - j-1];
				temp_sq += MAP[r][c + M_num - j-1] * MAP[r][c + M_num - j-1];
			}
		}
		if (temp_sum > C_max) continue;
		else temp_ans = max(temp_ans, temp_sq);
	}
	return temp_ans;
}

void second(int r, int c, int first_ans){
	int second_ans = -INF;
	if (c + M_num <= N - M_num){//같은 행에 탐색할 경우가 남았을 때
		int i = r;
		for (int j = c + M_num; j <= N - M_num; j++){
			second_ans = calc(i, j);
			ans = max(ans, first_ans + second_ans);
		}
	}
	//다음행 부터 탐색
	for (int i = r + 1; i <= N - 1; i++){
		for (int j = 0; j <= N - M_num; j++){
			second_ans = calc(i, j);
			ans = max(ans, first_ans + second_ans);
		}
	}			
}

void solve(){//첫번째 선택
	for (int i = 0; i <= N - 1; i++)
		for (int j = 0; j <= N - M_num; j++){
			int first_ans = calc(i, j);
			second(i, j, first_ans);
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
		cin >> N >> M_num >> C_max;
		for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) cin >> MAP[i][j];
		ans = -INF;
		solve();

		cout << "#" << testcase << " " << ans << endl;
	}
	return 0;
}
