//18.10.03 #No.5658 보물상자 비밀번호  1130-1232
//Coments : vector, iterator, sort 내림차순 쓰는 법 연습
//모듈로 연산으로 인덱스 회전 접근하는 것 혹은 필요한 부분만 복사해서 배열자체를 키운채로 접근
//vector내 중복 원소 제거 vec.erase(unique(vec.begin(),vec.end()),vec.end())
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <functional>//greater, less 포함하는 헤더
#define MAXN 28+8
int N, K;
using namespace std;
int ans;
char input[MAXN];
int term;

int solve(){
	vector<int> v;
	vector<int> ::iterator itr;
	for (int i = 0; i < term; i++){//회전 N/4-1번
		for (int j = 0; j < N; j += term){
			int check = 0;
			int temp;
			int num=0;
			for (int k = 0; k < term; k++){
				temp = input[i + j + k];
				if (temp >= 65) temp -= 55;
				else if (temp >= 48 && temp < 65) temp -= 48;
				num += temp * (int)pow(16, term - 1 - k);
			}
			for (itr = v.begin(); itr != v.end(); itr++){
				if (*itr == num){ check = 1; break; }
			}
			if (check != 1){ v.push_back(num); check = 0; }
		}
	}
	sort(v.begin(), v.end(), greater<int>());
	return v.at(K - 1);
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
		cin >> N >> K;
		for (int i = 0; i < N; i++) cin >> input[i];
		term = N / 4;
		for (int i = N; i < N + term; i++) input[i] = input[i - N];

		ans = solve();

		cout << "#" << testcase << " " << ans << endl;
	}
	return 0;
}
