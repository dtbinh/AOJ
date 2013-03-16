
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
#include <bitset>

using namespace std;

typedef long long ll;
typedef pair<int,int> P;


void dfs(const string& A,const string& B,string C,int pos,int borrow,int K,string& res){

	if(K<0) return;

	if(pos == A.size()){
		reverse(C.begin(),C.end());
		res = max(res,C);
		//cout << res << endl;
		return;
	}
	if((A[pos]-'0') - borrow >= (B[pos]-'0')){
		C[pos] = ((A[pos]-'0') - borrow - (B[pos]-'0') + '0');
		if(C[pos] < '0' || C[pos] > '9') return;
		dfs(A,B,C,pos+1,0,K,res);
	}
	else if((A[pos]-'0') - borrow < (B[pos]-'0')){
		C[pos] = ((A[pos]-'0') - borrow + 10 - (B[pos]-'0') + '0');
		if(C[pos] < '0' || C[pos] > '9') return;
		dfs(A,B,C,pos+1,1,K,res);
		dfs(A,B,C,pos+1,0,K-1,res);
	}
}

int main(){
	char A[16],B[16];
	int K;
	while(~scanf("%s %s %d",A,B,&K)){
		string strA=A,strB=B;
		reverse(strA.begin(),strA.end());
		reverse(strB.begin(),strB.end());

		strA.size() > strB.size() 
			? strB.append(strA.size()-strB.size(),'0') : strA.append(strB.size()-strA.size(),'0');

		string strC;
		string res;
		strC.resize(max(strA.size(),strB.size()));
		dfs(strA,strB,strC,0,0,K,res);

		bool isok = false;
		for(int i=0;i<res.size();i++){
			if(res[i] != '0') isok = true;
			if(isok) cout << res[i];
		}
		cout << endl;
	}
}

