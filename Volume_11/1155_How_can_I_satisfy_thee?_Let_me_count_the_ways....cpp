
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
#include <cctype>
#include <utility>
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
 
 
static const double EPS = 1e-8;
 
int tx[] = {-1,0,1,0};
int ty[] = {0,1,0,-1};
 
P formula(const string &str, int pos=0);
 
P formula(const string &str, int pos){
    if(str[pos] == '('){
        P res1_ = formula(str,pos+1);
        pos = res1_.second;
        char ch = str[pos];
        P res2_ = formula(str,pos+1);
 
        if(ch=='*') return P(min(res1_.first,res2_.first),res2_.second+1);
        if(ch=='+') return P(max(res1_.first,res2_.first),res2_.second+1);
    }
    else if(isdigit(str[pos])){
        return P(str[pos]-'0',pos+1);
    }
 
    else if(str[pos] == '-'){
        P res_ = formula(str,pos+1);
        if(res_.first==0) res_.first=2;
        else if(res_.first==2) res_.first=0;
 
        return res_;
    }
}
 
 
int main()
{
    string str;
    while(getline(cin,str)){
        if(str == ".") break;
        int res = 0;
        for(int p=0;p<=2;p++){
            for(int q=0;q<=2;q++){
                for(int r=0;r<=2;r++){
                    string tmp = str;
                    for(int i=0;i<tmp.size();i++){
                        if(tmp[i]=='P') tmp[i] = '0' + p;
                        else if(tmp[i]=='Q') tmp[i] = '0' + q;
                        else if(tmp[i]=='R') tmp[i] = '0' + r;
                    }
                    //P result;
                    //result = formula(tmp,0);
                    //printf("%s = %d\n",tmp.c_str(),result.first);
                    if(formula(tmp,0).first == 2) res++;
                }
            }
        }
 
        printf("%d\n",res);
    }
}

