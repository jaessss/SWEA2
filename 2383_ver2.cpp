//18.10.08 #No.2383 <점심식사시간>.ver2
//Coments : 한 순간에 이루어져야 할 일들의 세부적인 순서, 사람의 경우 입구에 도착하고 다음턴에 계단진입
// 계단 내려가는 경우, 다내려간 순간에 계단에서 아웃!
// 크게 사람과 계단위에 대한 판단은 순서~time 초기값 잡아주기나름
// 자료구조 어떻게 사용할지 고민, STL의 queue는 제약이 많음...
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <queue>
#define INF 0x7fffffff
#define MAXN 10+1
using namespace std;
int ans;
int N;

typedef struct PERSON{
	int r, c;
	int dist;
	int run;
};

typedef struct QUEUE{
	int rp, wp;
	PERSON q[MAXN];
};
QUEUE rdA, rdB, runA, runB;

vector<PERSON> ready;

typedef struct STEP{
	int r, c;
	int length;
};
STEP step[2];

void init(){
	rdA.rp = rdA.wp = rdB.rp = rdB.wp = 0;
	runA.rp = runA.wp = runB.rp = runB.wp = 0;
}

void move(){
	int cnt = (int)ready.size();
	
	int time = 1;
	while (runA.rp + runB.rp <cnt){
		time++;
		if (time >= ans) break;

		for (int i = 0; i < rdA.wp; i++){
			if (rdA.q[i].dist == 0){
				if (runA.wp - runA.rp < 3) { 
					runA.q[runA.wp++] = rdA.q[i];
					rdA.q[i].dist = -1;
				}
			}
			else if (rdA.q[i].dist > 0) rdA.q[i].dist--;
		}
		for (int i = 0; i < rdB.wp; i++){
			if (rdB.q[i].dist == 0){
				if (runB.wp - runB.rp < 3) {
					runB.q[runB.wp++] = rdB.q[i];
					rdB.q[i].dist = -1;
				}
			}
			else if (rdB.q[i].dist > 0) rdB.q[i].dist--;
		}

		for (int i = runA.rp; i < runA.wp; i++){
			if (runA.q[i].run > 0){
				runA.q[i].run--;
			}
			if (runA.q[i].run == 0){
				runA.rp++;
				runA.q[i].run = -1;
			}
			
		}
		for (int i = runB.rp; i < runB.wp; i++){
			if (runB.q[i].run > 0){
				runB.q[i].run--;
			}
			if (runB.q[i].run == 0){
				runB.rp++;
				runB.q[i].run = -1;
			}
			
		}
	}
	ans = min(ans, time);
}

void solve(){
	//combination
	for (int i = 0; i < (1 << ready.size()); i++){
		init();
		for (unsigned int j = 0; j < ready.size(); j++){
			if (i & (1 << j)){
				ready.at(j).dist = abs(ready.at(j).r - step[0].r) + abs(ready.at(j).c - step[0].c);
				ready.at(j).run = step[0].length;
				rdA.q[rdA.wp++] = ready.at(j);
			}
			else{
				ready.at(j).dist = abs(ready.at(j).r - step[1].r) + abs(ready.at(j).c - step[1].c);
				ready.at(j).run = step[1].length;
				rdB.q[rdB.wp++] = ready.at(j);
			}
		}		
		move();
	}
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
		cin >> N;
		int input;
		int temp = 0;
		ready.clear();
		for (int i = 0; i < N; i++){
			for (int j = 0; j < N; j++){
				cin >> input;
				if (input == 1){
					PERSON per = { i, j, -1, -1 };
					ready.push_back(per);
				}
				else if (input > 1){
					step[temp].r = i;
					step[temp].c = j;
					step[temp++].length = input;
				}
			}
		}
		ans = INF;
		solve();

		cout << "#" << testcase << " " << ans << endl;
	}
	return 0;
}
