
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
typedef pair <string,string> P;
typedef pair <int,P> PP;
 
static const double EPS = 1e-8;
 
int tx[] = {0,1,1,1,0,-1,-1,-1};
int ty[] = {-1,-1,0,1,1,1,0,-1};
 
bool isMatch(const P& p1,const P& p2){
    //p1:deny or permit
    for(int i=0;i<8;i++){
         
        if(p1.first[i] != '?' && p2.first[i] != '?'){
            if(p1.first[i] != p2.first[i]) return false;
        }
 
        if(p1.second[i] != '?' && p2.second[i] != '?'){
            if(p1.second[i] != p2.second[i]) return false;
        }
    }
 
    return true;
}
 
class Output{
public:
    string from;
    string to;
    string msg;
    Output(string _from, string _to , string _msg){
        from = _from;
        to = _to;
        msg = _msg;
    }
};
 
class Rule{
public:
    string from;
    string to;
    int filter;
    int priority;
    Rule(string _from, string _to ,int _f, int _p){
        from = _from;
        to = _to;
        filter = _f;
        priority = _p;
    }
};
 
int main(){
    int n,m;
    while(~scanf("%d %d",&n,&m)){
        if(n==m && m==0) break;
        vector<Rule> r;
        for(int i=0;i<n;i++){
            string str;
            cin >> str;
            if(str == "permit"){
                string from,to;
                cin >> from >> to;
                r.push_back(Rule(from,to,1,i));
            }
            else{
                string from,to;
                cin >> from >> to;
                r.push_back(Rule(from,to,0,i));
            }
        }
 
        vector<Output> out;
        for(int i=0;i<m;i++){
            string from,to,msg;
            cin >> from >> to >> msg;
 
            for(int j=r.size()-1;j>=0;j--){
                if(isMatch(P(r[j].from,r[j].to),P(from,to))){
                    if(r[j].filter == 1){
                        out.push_back(Output(from,to,msg));
                        break;
                    }
                    else{
                        break;
                    }
                }
            }
        }
 
        printf("%d\n",out.size());
        for(int i=0;i<out.size();i++){
            printf("%s %s %s\n",out[i].from.c_str(),out[i].to.c_str(),out[i].msg.c_str());
        }
    }
}

