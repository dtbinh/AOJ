
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
#include <deque>

using namespace std;

typedef long long ll;
typedef pair<double,double> P;

int main(){
	
	int num;
	
	while(~scanf("%d",&num)){
		if(num==0) break;
		bool isok=false;
		map<int,ll> val;
		vector<int> order;
		for(int i=0;i<num;i++){
			int n;
			ll p,q;
			scanf("%d %lld %lld",&n,&p,&q);
			val[n] += p*q;
			if(find(order.begin(),order.end(),n) == order.end()){
				order.push_back(n);
			}
		}

		for(vector<int>::iterator it = order.begin(); it != order.end(); it++){
			if(val[*it] >= 1000000){
				cout << *it << endl;
				isok=true;
			}
		}
		if(!isok) cout <<  "NA" << endl;
	}
}

