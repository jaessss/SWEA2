//18.10.17 #No.5648 <원자 소멸 시뮬레이션> 887ms
//Coments : 시간초과 해결 요인은 vector->array
//memset도 사이즈 큰거 할때는 오버헤드 매우 큼
//시간초과가 뜬다면 고려해야할 사항들 고민
//맵에 제한이 없다고 하는 경우 제한을 만들어서 2차원 배열로 접근할 수 있도록
//사이즈가 매우 큰 맵을 대상으로 각 좌료를 모두 탐색하는 짓은 미친짓! 최대한 적은 범위를 대상으로 각 케이스 확인할 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string.h>
#define SIZE 4000 + 5
#define offset 1000
#define INF 0x7fffffff
using namespace std;
int ans, N;
struct POINT{
	short x, y, dir, energy;
};
int dx[] = { 0, 0, -1, 1 };
int dy[] = { 1, -1, 0, 0 };
short check[SIZE][SIZE];

POINT atom[1000 + 2];
POINT copy_[1000 + 2];

void init(){
	ans = 0;
}

void solve(){
	int num = N;
	int flag;
	POINT temp;

	while (num){
		//memset(check, 0, sizeof(check));
		flag = 0;
		//move
		for (int i = 0; i < num; i++){
			atom[i].x += dx[atom[i].dir];
			atom[i].y += dy[atom[i].dir];
			temp = atom[i];
			if (temp.x < 0 || temp.x >4000 || temp.y < 0 || temp.y >4000){
				atom[i].energy = 0;
				flag = 1;
			}
			else check[atom[i].y][atom[i].x]++;
		}
		//boom
		for (int i = 0; i < num; i++){
			temp = atom[i];
			if (temp.x < 0 || temp.x >4000 || temp.y < 0 || temp.y >4000) continue;
			else{
				if (check[temp.y][temp.x] == 1) check[temp.y][temp.x] = 0;
				else if (check[temp.y][temp.x] >= 2){
					for (int j = i + 1; j < num; j++){
						if (atom[j].x == temp.x && atom[j].y == temp.y){
							ans += atom[j].energy;
							atom[j].energy = 0;
						}
					}
					ans += atom[i].energy;
					atom[i].energy = 0;
					check[temp.y][temp.x] = 0; flag = 1;
				}
			}
		}
		//erase
		if (flag){
			int bound = num;
			int ptr = 0;
			for (int i = 0; i < bound; i++){
				if (atom[i].energy == 0)	num--;
				else copy_[ptr++] = atom[i];
			}
			for (int i = 0; i < num; i++){
				atom[i] = copy_[i];
			}
		}
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
		init();
		cin >> N;
		POINT temp;
		for (int i = 0; i < N; i++){
			cin >> temp.x >> temp.y >> temp.dir >> temp.energy;
			temp.x += offset; temp.y += offset;
			temp.x *= 2; temp.y *= 2;
			atom[i] = temp;
		}
		solve();
		cout << "#" << testcase << " " << ans << endl;
	}
	return 0;
}
