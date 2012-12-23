
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
	ll p,q;
	while(~scanf("%lld %lld",&p,&q)){
		string ans="";
		map<ll,int> remain;
		int idx=-1;

		remain[p%q] = 0;
		p*=10;
		for(int i=1;i<100;i++){
			if(p%q==0){
				ans+=(char)(p/q+'0');
				break;
			}
			else{
				ans+=(char)(p/q+'0');
				if(remain.find(p%q) != remain.end()){		
					idx = remain[p%q];
					break;
				}
				
				remain[p%q]=i;			

				p=(p%q)*10;
			}
		}

		cout << ans << endl;
		if(idx==-1) continue;
		for(int i=0;i<ans.size();i++){
			printf("%s%s", i>=idx ? "^" : " ", i==ans.size()-1 ? "\n" : "");
		}
	}
}


