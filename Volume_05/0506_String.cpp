
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

static const double eps = 1e-8;

int main(){
	int n;
	while(~scanf("%d",&n)){
		if(n==0) break;
		string num;
		cin >> num;
		for(int i=0;i<n;i++){
			string next;
			for(int j=0;j<num.size();){
				int c = 0;
				char alph;
				for(int k=0;k<=9;k++){					
					for(int len=1;j+len-1<num.size();len++){
						string tmp = num.substr(j,len);
						if(count(tmp.begin(),tmp.end(),'0'+k) == len){
							c++;
							alph = '0' + k;
						}
						else break;
					}
				}

				j+=c;
				
				char buf[32];
				sprintf(buf,"%d",c);
				string tmp = buf;
				next.append(tmp);
				next.push_back(alph);
			}
			num = next;
		}

		cout << num << endl;
	}
}

