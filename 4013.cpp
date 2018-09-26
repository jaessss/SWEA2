//18.9.26 #No.1043 특이한자석
//재귀 구현 시 와리가리 주의 
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
using namespace std;

typedef struct magnetic{
	int polar[8];
	int ptr;
};// MAG[5];
magnetic MAG[5];
int K;

int check(int num, int option){
	//option 1: 왼 2:오
	if (option == 1){
		if (MAG[num].polar[(MAG[num].ptr + 6) % 8] != MAG[num - 1].polar[(MAG[num - 1].ptr + 2) % 8])
			return 1;
		else return 0;
	}
	else if (option == 2){
		if (MAG[num].polar[(MAG[num].ptr + 2) % 8] != MAG[num + 1].polar[(MAG[num + 1].ptr + 6) % 8])
			return 1;
		else return 0;
	}
	else return 0;
}

void solve(int num, int dir, int option){
	//양쪽확인 - 탐색방향 와리가리 주의
	if (option == 0){
		if (num - 1 >= 1 && check(num, 1)) solve(num - 1, dir*(-1),1);
		if (num + 1 <= 4 && check(num, 2)) solve(num + 1, dir*(-1),2);
	}
	else{
		if (option == 1 && num - 1 >= 1 && check(num, 1)) solve(num - 1, dir*(-1),1);
		if (option == 2 && num + 1 <= 4 && check(num, 2)) solve(num + 1, dir*(-1),2);
	}
	
	if (dir == 1)//시계방향
		MAG[num].ptr = (MAG[num].ptr + 7) % 8;
	else if (dir == -1)//반시계
		MAG[num].ptr = (MAG[num].ptr + 1) % 8;
	else return;
}

int main(void)
{
	int T;
	int num, dir;
	//file inout
	//freopen("sample_input.txt", "r", stdin);
	setbuf(stdout, NULL);
	scanf("%d", &T);

	for (int testcase = 1; testcase <= T; ++testcase)
	{
		int ans = 0;
		//input
		cin >> K;
		for (int i = 1; i <= 4; i++){
			for (int j = 0; j < 8; j++)
				cin >> MAG[i].polar[j];
				//scanf("%d", &MAG[i].polar[j]); 
			MAG[i].ptr = 0;
		}
		//solve
		for (int i = 0; i < K; i++){
			cin >> num;
			cin >> dir;
			solve(num, dir, 0);
		}
		//output
		for (int i = 1; i <= 4; i++){
			if (MAG[i].polar[MAG[i].ptr] == 1) ans += 1 << (i-1);
		}
		printf("#%d %d\n", testcase,ans);
	}
	return 0;
}
