
#define _USE_MATH_DEFINES
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

int main()
{
	string str;
	while(getline(cin,str)){
		for(int rot = 0;rot< 'z' - 'a' + 1;rot++){
			string tmp = str;
			for(int i=0; i<str.size(); i++){
				if(tmp[i] == ' ') continue;
				if(tmp[i] == '.') continue;
				tmp[i] = (rot + tmp[i]-'a') % ('z' - 'a' + 1) + 'a';
			}
			//cout << tmp << endl;
			if(tmp.find("the") != string::npos
				|| tmp.find("this") != string::npos
				|| tmp.find("that") != string::npos)
			{
				cout << tmp << endl;
			}
		}
	}
	return 0;
}

