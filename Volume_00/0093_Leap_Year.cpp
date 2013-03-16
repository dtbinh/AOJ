
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
	int n,m;
	vector<vector<int> > ans;
	while(~scanf("%d %d",&n,&m)){
		if(n==m && n==0) break;
		
		vector<int> tmp;
		for(int i=n;i<=m;i++){
			bool isok = i % 400 == 0 
				? true : i % 100 == 0
				? false : i % 4 == 0
				? true : false;

			if(isok){
				tmp.push_back(i);
			}
		}

		ans.push_back(tmp);
	}

	for(int i=0;i<ans.size();i++){
		for(int j=0;j<ans[i].size();j++){
			cout << ans[i][j] << endl;
		}

		if(ans[i].size() == 0)
		{
			cout << "NA" << endl;
		}

		printf("%s",i==ans.size()-1 ? "" : "\n");
	}
}

