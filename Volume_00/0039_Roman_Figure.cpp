
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

//char name[] = {'I','V','X','L','C','D','M'};
//int num[] = {1,5,10,50,100,500,1000};

int roma2num(char c){
	return c=='I'? 1:
		c=='V'? 5:
		c=='X'? 10:
		c=='L'? 50:
		c=='C'? 100:
		c=='D'? 500: 1000;
}

int main(){

	string str;
	while(cin >> str){
		int sum=0;
		int i=0;
		for(;i<str.size()-1;i++){
			int now = roma2num(str[i]);
			int next = roma2num(str[i+1]);

			if(now >= next){
				sum += now;
			}else{
				sum += next - now;
				i++;
			}
		}

		if(i < str.size()) sum += roma2num(str[i]);

		cout << sum << endl;
	}
}


