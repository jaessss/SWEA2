//9.26
//숫자로 받아서 %연산 진행하는 것보다 string으로 받아서 1의 자리수만 가지고 
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
using namespace std;

int main(void)
{
	//vector<string> input_arr;
	string input_arr;
	int T;
	int ans;

	cin >> T;

	for (int testcase = 1; testcase <= T; ++testcase)
	{
		cin >> input_arr;
		int temp = input_arr.at(input_arr.length()-1) - '0';

		if (temp % 2 == 0) ans = 1;//even
		else ans = 0;

		if (ans == 1) printf("#%d Even\n", testcase);
		else if (ans == 0) printf("#%d Odd\n", testcase);

	}


	return 0;
}
