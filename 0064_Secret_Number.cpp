
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
#include <set>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> P;

int main(){

	stack<int> stk;
	string str;
	int c=0;
	int sum=0;
	while(cin>>str){
		for(int i=0;i<str.size();i++){
			if(isdigit(str[i])){
				stk.push(str[i]-'0');
			}
			else{
				int tmp=0;
				int digit=1;
				while(!stk.empty()){
					tmp += stk.top() * digit;
					stk.pop();
					digit *= 10;
				}
				sum+=tmp;
			}
		}

		int tmp=0;
		int digit = 1;
		while(!stk.empty()){
			tmp += stk.top() * digit;
			stk.pop();
			digit *= 10;
		}
		sum+=tmp;
	}

	cout << sum << endl;
}

