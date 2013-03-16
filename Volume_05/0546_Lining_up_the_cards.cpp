
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


int tx[] = {-1,0,1,0};
int ty[] = {0,1,0,-1};

int path[501][501];


int main(){
	int n,k;
	while(~scanf("%d %d",&n,&k)){
		if(n==k && k==0) break;

		vector<string> nums;
		for(int i=0;i<n;i++){
			string num;
			cin >> num;
			nums.push_back(num);
		}

		sort(nums.begin(),nums.end());
		map<string,int> visited;


		vector<int> choice;
		for(int j=0;j<n-k;j++) choice.push_back(0);
		while(choice.size()!=n) choice.push_back(1);

		int res=0;
		do{
			vector<string> str;

			for(int j=0;j<choice.size();j++){
				if(choice[j]==1) str.push_back(nums[j]);
			}

			sort(str.begin(),str.end());

			do{
				string num;
				for(int j=0;j<str.size();j++) num.append(str[j]);
				if(visited.find(num) == visited.end()){
					visited[num]=1;
					res++;
				}
			}while(next_permutation(str.begin(),str.end()));
		}while(next_permutation(choice.begin(),choice.end()));

		printf("%d\n",res);
	}
}

