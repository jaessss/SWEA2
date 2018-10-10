//18.10.10 #No.4168 <삼성이의 쇼핑>
//Coments : DFS 기본구조 확인
//DFS보다 비트마스킹이 더 느린듯
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string.h>
#define MAXM 25+1
#define INF 0x7fffffff
using namespace std;
int ans;
int N, M;
typedef struct{
	int price, satis;
}PRODUCT;
PRODUCT product[MAXM];
int check[MAXM];
int last_check[MAXM];
//
//void solve(){
//	
//	for (int i = 0; i < (1 << M); i++){
//		memset(check, 0, sizeof(int)*MAXM);
//		int total_price = 0;
//		int total_satis = 0;
//		int flag = 1;
//		for (int j = 0; j < M; j++){
//			if (i & (1 << j)){
//				total_price += product[j].price;
//				if (total_price >= N){ flag = 0; break; }
//				total_satis += product[j].satis;
//				check[j] = 1;
//				flag = 1;
//			}
//		}
//		if (flag){
//			if (total_satis > ans){
//				memcpy(last_check, check, sizeof(int)*MAXM);
//				ans = total_satis;
//			}
//		}
//	}
//}

void DFS(unsigned int select, int ind, int now_price, int now_satis){
	
	if (ind >= M) { 
		if (now_satis > ans){
			ans = now_satis;
			for (int i = 0; i < M; i++){
				if (select & (1 << i))last_check[i] = 1;
				else last_check[i] = 0;
			}
		}
		return; 
	}
	DFS(select, ind + 1, now_price, now_satis);
	if (now_price + product[ind].price < N) DFS(select |= (1 << ind), ind + 1, now_price + product[ind].price, now_satis + product[ind].satis);
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(NULL);
	int T;
	//freopen("sample_input.txt", "r", stdin);
	setbuf(stdout, NULL);

	cin >> T;
	for (int testcase = 1; testcase <= T; ++testcase)
	{
		cin >> N >> M;
		for (int i = 0; i < M; i++) cin >> product[i].price >> product[i].satis;
		ans = -INF;
		DFS(0, 0, 0, 0);
		//solve();

		cout << "#" << testcase;
		for (int i = 0; i < M; i++){
			if (last_check[i] == 1) cout << " " << i;
		}
		cout << " " << ans << endl;
	}
	return 0;
}
