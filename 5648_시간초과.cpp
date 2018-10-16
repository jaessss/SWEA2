//18.10.16 #No.5648 <원자 소멸 시뮬레이션>
//Coments : 40~43개 시간초과
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
vector<POINT> vec;
int dx[] = { 0, 0, -1, 1 };
int dy[] = { 1, -1, 0, 0 };
short check[SIZE][SIZE];

void init(){
	vec.clear();
	ans = 0;
}

void solve(){
	int num = N;
	int flag;
	POINT temp;
	vector<POINT> tmp;

	while (num){
		//memset(check, 0, sizeof(check));
		flag = 0;
		//move
		for (int i = 0; i < num; i++){
			vec.at(i).x += dx[vec.at(i).dir];
			vec.at(i).y += dy[vec.at(i).dir];
			temp = vec.at(i);
			if (temp.x < 0 || temp.x >4000 || temp.y < 0 || temp.y >4000){
				vec.at(i).energy = 0; flag = 1;
			}
			else check[vec.at(i).y][vec.at(i).x]++;
		}
		//boom
		for (int i = 0; i < num; i++){
			temp = vec.at(i);
			if (temp.x < 0 || temp.x >4000 || temp.y < 0 || temp.y >4000) continue;
			else{
				//int x = vec.at(i).x; int y = vec.at(i).y;
				if (check[temp.y][temp.x] == 1) check[temp.y][temp.x] = 0;
				else if (check[temp.y][temp.x] >= 2){
					for (int j = i + 1; j < num; j++){
						if (vec.at(j).x == temp.x && vec.at(j).y == temp.y){
							ans += vec.at(j).energy;
							vec.at(j).energy = 0;
						}
					}
					ans += vec.at(i).energy;
					vec.at(i).energy = 0;
					check[temp.y][temp.x] = 0; flag = 1;
				}
			}
		}
		//erase
		/*if (flag){
			tmp.clear();
			int bound = num;
			for (int i = 0; i < bound; i++){
				if (vec.at(i).energy == 0)	num--;
				else tmp.push_back(vec.at(i));
			}
			vec = tmp;
		}*/
		if (flag){
			int bound = num;
			while (bound--){
				if (vec.at(0).energy == 0) num--;
				else vec.push_back(vec.at(0));
				vec.erase(vec.begin());
			}
		}
	}
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
		init();
		cin >> N;
		POINT temp;
		for (int i = 0; i < N; i++){
			cin >> temp.x >> temp.y >> temp.dir >> temp.energy;
			temp.x += offset; temp.y += offset;
			temp.x *= 2; temp.y *= 2;
			vec.push_back(temp);
		}
		solve();
		cout << "#" << testcase << " " << ans << endl;
	}
	return 0;
}
