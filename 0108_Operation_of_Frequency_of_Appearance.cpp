
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
typedef pair<int,int> P;

int main(){
	int n;
	while(~scanf("%d",&n)){
		if(n==0) break;
		vector<int> S;
		vector<int> S_old;
		for(int i=0;i<n;i++){
			int s;
			scanf("%d",&s);
			S.push_back(s);
		}

		int c=0;
		while(1){
			map<int,int> freq;
			S_old = S;
			for(int i=0;i<S.size();i++){
				freq[S[i]]++;
			}

			for(int i=0;i<S.size();i++){
				S[i] = freq[S[i]];
			}

			if(S == S_old) break;
			c++;
		}

		cout << c << endl;
		for(int i=0;i<S.size();i++){
			printf("%d%s",S[i],i==S.size()-1 ? "\n" : " ");
		}

	}
}

