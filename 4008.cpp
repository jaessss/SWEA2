//18.9.26 #No. 4008 숫자 만들기
//Coments : min,MAX 초기화 주의, DFS 복귀시 원상복구 해야하는 대상 확인
//다중재귀 for문 이용시 조건 주의(순서가 생기지 않게)
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
using namespace std;
#define MAX(a,b) (a)>(b)?a:b
#define min(a,b) (a)<(b)?a:b
#define INF 0x7fffffff

int number[12 + 1];
int oper[4];
int MAX_val;
int min_val;

int end_check(int* oper){
	for (int i = 0; i < 4; i++)
		if (oper[i] >0) return 0;

	return 1;
}

void DFS(int ptr, int value, int* oper){

	for (int i = 0; i < 4; i++){
		if (i == 0 && oper[i] >= 1){
			oper[i]--;
			DFS(ptr + 1, value + number[ptr], oper);
			oper[i]++;
		}
		if (i == 1 && oper[i] >= 1){
			oper[i]--;
			DFS(ptr + 1, value - number[ptr], oper);
			oper[i]++;
		}
		if (i == 2 && oper[i] >= 1){
			oper[i]--;
			DFS(ptr + 1, value * number[ptr], oper);
			oper[i]++;
		}
		if (i == 3 && oper[i] >= 1){
			oper[i]--;
			DFS(ptr + 1, value / number[ptr], oper);
			oper[i]++;
		}
	}
	if (end_check(oper)) {
		MAX_val = MAX(value, MAX_val);
		min_val = min(value, min_val);
	}

}

int main(void)
{
	int T,N;
	int ans, ptr;
	//file inout
	//freopen("sample_input.txt", "r", stdin);
	setbuf(stdout, NULL);
	scanf("%d", &T);

	for (int testcase = 1; testcase <= T; ++testcase)
	{
		ans = ptr = 0;
		MAX_val = -INF;
		min_val = INF;
		//input
		cin >> N;
		for (int i = 0; i < 4; i++)
			cin >> oper[i];
		for (int i = 0; i < N; i++)
			cin >> number[i];

		DFS(ptr+1, number[0], oper);

		ans = MAX_val - min_val;
		printf("#%d %d\n", testcase, ans);
	}

	return 0;
}
