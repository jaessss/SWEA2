//18.10.1 #No.5644 무선충전
//Coments : 초기 사람 위치 주의, 순서를 정해서 조합 구할 경우 소외되는 경우의 수 생각
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
#define INF 0x7fffffff
#define MAXN 11
#define MAXM 100+1

int ans;
int M_time, A_num;
int track[2][MAXM];

int dx[5] = { 0, 0, 1, 0, -1 };//정상우하좌
int dy[5] = { 0, -1, 0, 1, 0 };

typedef struct PERSON_{
	int x, y;
	int sel[9];
};
PERSON_ person[2];

typedef struct BC_{
	int x, y, c, p;
};
BC_ BC[9];

void search(int who){
	for (int i = 0; i < A_num; i++){
		int temp_dis = abs(person[who].x - BC[i].x) + abs(person[who].y - BC[i].y);
		if (temp_dis <= BC[i].c){
			person[who].sel[i] = 1;
		}
		else person[who].sel[i] = 0;
	}
}

void solve(){
	//charge -> move
	int t = 0;
	int charge = 0;
	int temp_max = -INF;
	int temp_sum = 0;
	person[0].x = person[0].y = 1;
	person[1].x = person[1].y = 10;

	while (t <= M_time){
		search(0);
		search(1);
		temp_max = -INF;
		for (int i = 0; i < A_num; i++){
			temp_sum = 0;
			
			if (person[0].sel[i] == 1){
				temp_sum += BC[i].p;
			}
			for (int j = 0; j < A_num; j++){
				if (person[1].sel[j] == 1){
					if (i == j && temp_sum>0){
						temp_max = max(temp_max, temp_sum);
					}
					else{
						temp_sum += BC[j].p;
						temp_max = max(temp_max, temp_sum);
						temp_sum -= BC[j].p;
					}
				}
				else temp_max = max(temp_max, temp_sum);	
			}
		}
		charge += temp_max;
		//move
		for (int i = 0; i < 2; i++){
			person[i].x += dx[track[i][t]];
			person[i].y += dy[track[i][t]];
		}
		t++;
	}
	ans = charge;
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
		cin >> M_time >> A_num;
		for (int i = 0; i < M_time; i++) cin >> track[0][i];
		for (int i = 0; i < M_time; i++) cin >> track[1][i];
		for (int i = 0; i < A_num; i++) cin >> BC[i].x >> BC[i].y >> BC[i].c >> BC[i].p;

		ans = -INF;
		solve();

		cout << "#" << testcase << " " << ans << endl;
	}
	return 0;
}
