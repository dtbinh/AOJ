
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

static const double EPS = 1e-8;


int main(){
	string str;
	while(cin >> str){
		int joi=0,ioi=0;
		for(int i=0;i+2<str.size();i++){
			string tmp = str.substr(i,3);
			if(tmp == "JOI") joi++;
			else if(tmp == "IOI") ioi++;
		}
		printf("%d\n%d\n",joi,ioi);
	}	
}

