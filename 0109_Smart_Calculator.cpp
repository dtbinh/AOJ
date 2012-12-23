
#define _USE_MATH_DEFINES
#define INF 100000000
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <stack>
#include <limits>
#include <map>
#include <string>
#include <cstring>
#include <set>
#include <deque>
#include <bitset>
#include <list>

using namespace std;

typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P> PP;

static const double EPS = 1e-8;

const int tx[] = {0,1,0,-1};
const int ty[] = {-1,0,1,0};

P equation(const string &str, int pos=0);
P factor(const string &str, int pos = 0);
P term(const string &str, int pos = 0);

P equation(const string &str, int pos){
	P res = factor(str,pos);
	while(str[res.second] == '+' || str[res.second] == '-'){
		P res_ = factor(str,res.second+1);
		if(str[res.second] == '+') res.first += res_.first;
		else res.first -= res_.first;
		res.second = res_.second;
	}
	return res;
}

P factor(const string &str, int pos) {
	P res = term(str, pos);
	while (str[res.second] == '*' || str[res.second] == '/') {
		P res_ = term(str, res.second+1);
		if(str[res.second] == '*') res.first *= res_.first;
		else res.first /= res_.first;
		res.second = res_.second;
	}
	return res;
}

P term(const string &str, int pos) {
	if(str[pos] == '('){
		P res = equation(str,pos+1);
		res.second += 1;
		return res;
	} else {
		int val = 0;
		while(isdigit(str[pos])){
			val = val * 10 + (str[pos++]-'0');
		}
		return P(val,pos);
	}
}


int main(){
	string str;
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		cin>>str;
		P res = equation(str);
		cout << res.first << endl;
	}
}

