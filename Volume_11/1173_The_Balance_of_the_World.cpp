
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
typedef pair <int,P> PP;
 
static const double EPS = 1e-8;
 
int main(){
    string str;
    while(getline(cin,str)){
        if(str==".") break;
        stack<char> stk;
        string res = "yes";
        for(int i=0;i<str.size();i++){
            if(str[i]=='(') stk.push('(');
            if(str[i]=='[') stk.push('[');
 
            if(str[i]==')'){
                if(!stk.empty() && stk.top() != '(') res = "no";
                else if(stk.empty()) res = "no";
                else stk.pop();
            }
 
            if(str[i]==']'){
                if(!stk.empty() && stk.top() != '[') res = "no";
                else if(stk.empty()) res = "no";
                else stk.pop();
            }
 
        }
 
        if(!stk.empty()) res = "no";
        cout << res << endl;
    }
}

