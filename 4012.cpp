//18.9.27 #No.4012 요리사
//Coments : MAX 범위 확실히!!, DFS시 뛰는 조건 걸어서 오류처리 및 가지치기
// DFS 복귀시 원상복구!!
// #define 함수에는 지정된 형식만, 연산식 반영 x
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
using namespace std;
#define MAXN 16+1
#define INF 0x7fffffff
#define abs(a) (a)>0?(a):(-a)
#define min(a,b) (a>b)?(b):(a)

int S[MAXN][MAXN];
int check[MAXN];
int N;
int min_value;

int cal_diff(int *check){
	int tempA = 0;
	int tempB = 0;
	int temp_diff = 0;
	for (int i = 0; i < N - 1; i++){
		for (int j = i + 1; j < N; j++){
			if (check[i] == 1 && check[j] == 1){
				tempA += S[i][j];
				tempA += S[j][i];
			}
			else if (check[i] == 0 && check[j] == 0){
				tempB += S[i][j];
				tempB += S[j][i];
			}
			else continue;
		}
	}
	temp_diff = tempA - tempB;
	temp_diff = abs(temp_diff);
	return temp_diff;
}

void select(int cnt, int ptr, int* check){
	if (cnt == (N / 2)){
		int temp_diff;
		temp_diff = cal_diff(check);
		min_value = min(min_value, temp_diff);
		return;
	}
	else if (cnt + N - ptr >= (N / 2)){
		check[ptr] = 1;
		select(cnt + 1, ptr + 1, check);
		check[ptr] = 0;
		select(cnt, ptr + 1, check);
	}
	else return;
}

int main(void)
{
	int T;
	int ans;
	int check[MAXN];

	//file inout
	//freopen("sample_input.txt", "r", stdin);
	setbuf(stdout, NULL);
	scanf("%d", &T);

	for (int testcase = 1; testcase <= T; ++testcase)
	{
		cin >> N;
		for (int i = 0; i < N; i++){
			for (int j = 0; j < N; j++){
				cin >> S[i][j];
				//scanf("%d", &S[i][j]);
			}
		}
		for (int i = 0; i < MAXN; i++) check[i] = 0;
		min_value = INF;
		ans = 0;

		select(0, 0, check);
		ans = min_value;

		printf("#%d %d\n", testcase, ans);
	}
	return 0;
}
