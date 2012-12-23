
#define _USE_MATH_DEFINES
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <queue>
#include <stack>

typedef long long ll;
using namespace std;

int main()
{
	string str;
	getline(cin,str);
	for(int i=0;i<str.size();i++){
		if(str[i] == ' ' || str[i] == '.') continue;
		str[i] = toupper(str[i]);
	}

	cout << str << endl;	
}

