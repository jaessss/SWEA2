//18.9.30 #No.2383 점심식사시간 ver.1
//Coments : 비트마스킹으로 조합 경우의수 구현할 때, 범위 매우 주의!!! 4개에 대한 조합의 경우 1<<3 = 1000
// 따라서 i < (1<<4) 가 되어야 0~1111까지 탐색 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
#define MAXN 10+1
#define INF 0x7fffffff
int N;
int MAP[MAXN][MAXN];
int ans;
int ptr_p, ptr_s;

typedef struct person_{
	int r, c, ustep, dist, instep;
};
typedef struct step_{
	int length, r, c, ucnt;
};
person_ person[MAXN];
step_ step[2];

bool end_check(){
	for (int i = 0; i < ptr_p; i++)
		if (person[i].instep > 0) return false;
	return true;
}

void move(){
	int temp_ans = 1;
	step[0].ucnt = step[1].ucnt = 0;

	while (!end_check()){
		for (int i = 0; i < ptr_p; i++){
			if (person[i].dist == 0 && step[person[i].ustep].ucnt < 3){//입구 대기중인 사람 시작
				step[person[i].ustep].ucnt++;
				person[i].instep = step[person[i].ustep].length;
				person[i].dist = -1;
			}

		}
		for (int i = 0; i < ptr_p; i++)//계단까지 이동중
			if (person[i].dist > 0) person[i].dist--;

		for (int i = 0; i < ptr_p; i++){
			if (person[i].dist == -1 && person[i].instep > 0){//다 내려감
				if (--(person[i].instep) == 0){
					person[i].instep = -1;
					step[person[i].ustep].ucnt--;
				}

			}
		}
		temp_ans++;
	}
	ans = min(ans, temp_ans);
	return;
}

void solve(){
	for (int i = 0; i < (1 << (ptr_p)); i++){
		for (int j = 0; j < ptr_p; j++){
			if (i & (1 << j)){//첫번째계단 이용
				int temp = abs(person[j].r - step[0].r) + abs(person[j].c - step[0].c);
				person[j].dist = temp;
				person[j].ustep = 0;
				person[j].instep = 10;// step[0].length;
			}
			else{
				int temp = abs(person[j].r - step[1].r) + abs(person[j].c - step[1].c);
				person[j].dist = temp;
				person[j].ustep = 1;
				person[j].instep = 10;// step[1].length;
			}
		}
		move();
	}
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int T;
	//file inout
	setbuf(stdout, NULL);
	cin >> T;

	for (int testcase = 1; testcase <= T; ++testcase)
	{
		//input
		cin >> N;
		ptr_p = 0, ptr_s = 0;
		for (int i = 0; i < N; i++) for (int j = 0; j < N; j++){
			cin >> MAP[i][j];
			if (MAP[i][j] == 1){
				person[ptr_p].instep = 0;
				person[ptr_p].r = i;
				person[ptr_p++].c = j;
			}
			else if (MAP[i][j] >= 2){
				step[ptr_s].r = i;
				step[ptr_s].c = j;
				step[ptr_s++].length = MAP[i][j];
			}
			else continue;
		}
		ans = INF;//최소 시간 탐색
		solve();

		cout << "#" << testcase << " " << ans << endl;
	}
	return 0;
}
