
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;

int main()
{	
	int t;
	scanf("%d",&t);
	for(int i=0;i<t;i++){
		string a;
		string b;

		cin >> a;
		cin >> b;	
		string res;
		reverse(a.begin(),a.end());
		reverse(b.begin(),b.end());
		int carry = 0;
		int idx;
		for(int j=0;j<min(a.size(),b.size());j++){
			int lhs = a[j] - '0';
			int rhs = b[j] - '0';
			res.push_back((carry + lhs + rhs) % 10 + '0');
			carry = (carry + lhs + rhs) / 10 ? 1 : 0;
			idx =j;
		}

		for(int j=idx+1;j<max(a.size(),b.size());j++){
			if(a.size() > b.size()){
				int lhs = a[j] - '0';
				res.push_back((carry + lhs) % 10 + '0');
				carry = (carry + lhs) / 10 ? 1 : 0;
			}
			else{
				int rhs = b[j] - '0';
				res.push_back((carry + rhs) % 10 + '0');
				carry = (carry + rhs) / 10 ? 1 : 0;
			}
		}
		if(carry) res.push_back(carry+'0');
		reverse(res.begin(),res.end());
		res = (res.size() > 80) ? "overflow" : res;
		cout << res << endl;
	}	
}

