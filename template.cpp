//18.##.## #No. <Title>
//Coments : 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
int ans;

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(NULL);
	int T;
	freopen("sample_input.txt", "r", stdin);
	setbuf(stdout, NULL);
	
	cin >> T;
	for (int testcase = 1; testcase <= T; ++testcase)
	{


		
		cout << "#" << testcase << " " << ans << endl;
	}
	return 0;
}
