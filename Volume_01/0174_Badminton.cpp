
#define _USE_MATH_DEFINES
#define MAX_N 1000000
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
#include <deque>
#include <bitset>

using namespace std;

typedef long long ll;
typedef pair<int,int> P;

static const double eps = 1e-8;

int main(){
	string str;
	bool isA = true;
	while(cin >> str){
		if(str.size() == 1 && str[0] == '0') break;
		int A = count(str.begin()+1,str.end(),'A');
		int B = count(str.begin()+1,str.end(),'B');

		if(A > B){
			if(B < 10) A = 11;
			else A = B + 2;			
		}
		else if(B > A){
			if(A < 10) B = 11;
			else B = A + 2;
		}
		printf("%d %d\n",A,B);
	}
}

