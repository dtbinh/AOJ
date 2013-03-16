
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
typedef pair<char,int> P;

class mycmp{
public:
	bool operator() (const P p1,const P p2){
		return p1.second < p2.second;
	}
};

int main(){

	int n;
	while(~scanf("%d",&n)){
		if(n==0) break;
		for(int i=0;i<n;i++){
			string str;
			cin >> str;

			vector<P> order;
			map<char,int> data;		
			set<char> alpha;

			for(int j=0;j<str.size();j++){
				if(isalpha(str[j])){
					alpha.insert(str[j]);
				}
			}

			int j=0;
			for(set<char>::iterator it = alpha.begin(); it != alpha.end(); it++){
				data[*it]=j++;
			}

			for(int k=0;k<alpha.size();k++){
				for(int j=0;j+3<str.size();j+=3){
					string tmp = str.substr(j,4);
					if(tmp.substr(1,2)=="<-"){
						if(data[tmp[0]] < data[tmp[3]]){
							swap(data[tmp[0]],data[tmp[3]]);
						}
					}
					else if(tmp.substr(1,2)=="->"){
						if(data[tmp[0]] > data[tmp[3]]){
							swap(data[tmp[0]],data[tmp[3]]);
						}
					}
				}
			}

			for(map<char,int>::iterator it = data.begin(); it != data.end();it++){
				order.push_back(P(it->first,it->second));
			}

			sort(order.begin(),order.end(),mycmp());

			for(vector<P>::iterator it = order.begin(); it != order.end();it++){
				cout << it->first;
			}

			cout << endl;
		}
	}
}


