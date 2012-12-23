
#define _USE_MATH_DEFINES
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <queue>
#include <stack>
#include <limits>
#include <map>
#include <string>
#include <cstring>

typedef long long ll;
using namespace std;

int F(int a, int b, int c){
	return (a*c+b) % 26;
}

int main(){
	int n;
	string str1;
	getline(cin,str1);

	n = atoi(str1.c_str());
	for(int i=0;i<n;i++){
		string str2;
		getline(cin,str2);

		for(int a=0;a<100;a++){
			for(int b=0;b<100;b++){
				string tmp = str2;
				for(int i=0;i<str2.size();i++){
					if(tmp[i]=='.') continue;
					if(tmp[i]==' ') continue;
					if(isdigit(tmp[i])) continue;
					tmp[i] = F(a,b,str2[i]-'a') + 'a';
				}

				if(tmp.find("that") != string::npos
					|| tmp.find("this") != string::npos){
						cout << tmp << endl;
						goto found;
				}
			}
		}
found:;
	}
}


