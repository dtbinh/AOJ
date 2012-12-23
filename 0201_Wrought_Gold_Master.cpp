
#define _USE_MATH_DEFINES
#define INF 10000000
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
#include <list>

using namespace std;

typedef long long ll;
typedef pair<int,string> P;

static const double eps = 1e-8;

int main(){
	int n,m;
	while(~scanf("%d",&n)){
		if(n==0) break;
		map<string,int> items;
		for(int i=0;i<n;i++){
			string name;
			int cost;
			cin >> name >> cost;
			items[name] = cost;
		}
		scanf("%d",&m);
		for(int i=0;i<m;i++){
			string name;
			cin >> name;
			int k;
			scanf("%d",&k);

			int sum = 0;
			string elem;
			for(int j=0;j<k;j++){
				string elem;
				cin >> elem;
				sum += items[elem];
			}

			items[name] = min(items[name],sum);
		}

		string target;
		cin >> target;

		cout << items[target] << endl;
	}
}

