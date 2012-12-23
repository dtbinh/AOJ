
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

vector<int> split(string delim,string str){
	vector<int> res;
	str += delim;
	for(int i=0;i<str.size();i++){
		for(int j=1;i+j<=str.size();j++){
			if(str.substr(i,j).find(delim) != string::npos){
				int num = atoi(str.substr(i,j-1).c_str());
				if(str.substr(i,j-1).size() >0 ) res.push_back(num);
				i+=j-1;
				break;
			}
		}
	}

	return res;
}

int main(){
	string str;
	while(getline(cin,str)){
		vector<int> data = split(" ",str);
		if(data.size()==1 && data[0]==0) break;
		set<int>* dp = new set<int>[data.size()+1]; 

		dp[0].insert(0);
		for(int i=0;i<data.size();i++){
			if(data[i] == 1){
				for(set<int>::iterator it = dp[i].begin(); it != dp[i].end(); it++){
					if(*it+1 <= 21) dp[i+1].insert(*it+1);
					if(*it+11 <= 21) dp[i+1].insert(*it+11);
				}
			}
			else if(2 <= data[i] && data[i] <= 9){
				for(set<int>::iterator it = dp[i].begin(); it != dp[i].end(); it++){
					if(*it+data[i] <= 21) dp[i+1].insert(*it+data[i]);
				}
			}
			else{
				for(set<int>::iterator it = dp[i].begin(); it != dp[i].end(); it++){
					if(*it+10<= 21) dp[i+1].insert(*it+10);
				}
			}
		}

		int res=MAX_N;
		for(set<int>::iterator it = dp[data.size()].begin(); it != dp[data.size()].end(); it++){
			if(*it <= 21 && abs(*it-21) < abs(res-21)){
				res = * it;
			}
		}

		printf("%d\n",res == MAX_N ? 0 : res);

		delete[] dp;
	}
}

