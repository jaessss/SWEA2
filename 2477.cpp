//18.10.09 #No.2477 <차량정비소> 1344-1508
//Coments : 시뮬레이션의 전형, 자료구조 선정 중요, 대기사람수~빈창구수 케이스 나눠서 생각
//while문 구성시 마지막 단계부터 역순으로 구현시작
//STL queue를 사용할 수 있는 구조 확인
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <queue>
#define MAXNM 10+1
#define MAXK 1000+10
using namespace std;

int ans;
int N, M, K, A, B;

typedef struct CUSTOMER{
	int num, recep_N, refair_N;
};

typedef struct RECEP{
	int a, remain_t, use;
	CUSTOMER customer;
};

typedef struct REFAIR{
	int b, remain_t, use;
	CUSTOMER customer;
};

RECEP recep[MAXNM]; 
REFAIR refair[MAXNM];
queue<CUSTOMER> ready_q;
queue<CUSTOMER> wait_refair_q;
queue<int> tk;

void check(CUSTOMER end){
	if (end.recep_N == A && end.refair_N == B) ans += end.num;
	else return;
}

void solve(){
	int num = 1;
	int time = 0;
	int total_cus = K;

	while (K){
		//refair
		for (int i = 1; i <= M; i++){
			if (refair[i].use == 1 && --(refair[i].remain_t) == 0){
				refair[i].use = 0;
				check(refair[i].customer);
				K--;
			}
		}
		//recep -> refair
		for (int i = 1; i <= N; i++){
			if (recep[i].use == 1 && --(recep[i].remain_t) == 0){
				recep[i].use = 0;
				wait_refair_q.push(recep[i].customer);
			}
		}
		if (!wait_refair_q.empty()){
			for (int i = 1; i <= M; i++){
				if (refair[i].use == 0){
					refair[i].customer = wait_refair_q.front();
					refair[i].customer.refair_N = i;
					wait_refair_q.pop();
					refair[i].use = 1;
					refair[i].remain_t = refair[i].b;
				}
				if (wait_refair_q.empty()) break;
			}
		}
		//ready -> recep
		while (!tk.empty() && tk.front() == time){
			CUSTOMER temp = { num++, 0, 0 };
			ready_q.push(temp);
			tk.pop();
		}
		if (!ready_q.empty()){
			for (int i = 1; i <= N; i++){
				if (recep[i].use == 0){
					recep[i].customer = ready_q.front();
					recep[i].customer.recep_N = i;
					ready_q.pop();
					recep[i].use = 1;
					recep[i].remain_t = recep[i].a;
				}
				if (ready_q.empty()) break;
			}
		}		
		time++;
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
		int temp;
		cin >> N >> M >> K >> A >> B;
		for (int i = 1; i <= N; i++) cin >> recep[i].a;
		for (int i = 1; i <= M; i++) cin >> refair[i].b;
		for (int i = 1; i <= K; i++){ cin >> temp; tk.push(temp); }

		ans = 0;
		solve();
		if (ans <= 0) ans = -1;

		cout << "#" << testcase << " " << ans << endl;
	}
	return 0;
}
