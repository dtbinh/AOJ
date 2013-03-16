
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

int tx[] = {1,0};
int ty[] = {0,1};

int main(){
	int sum=0;
	string str;
	while(cin >> str){
		int n;
		scanf("%d",&n);
		int res=0;
		for(int i=0;i<n;i++){
			string tmp;
			cin >> tmp;
			for(int i=0;i<tmp.size();i++){
				string tmp2 = tmp;
				rotate(tmp2.begin(),tmp2.begin()+i,tmp2.end());
				if(tmp2.find(str) != string::npos){
					res++;
					break;
				}
			}
		}
		printf("%d\n",res);
	}
}

