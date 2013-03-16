
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
 
void dfs(map<char,int>& co,map<char,int>::iterator it,map<char,bool>& pre,int visited,int sum,map<int, map<int,int> >& result){
 
    if(it==co.end()){
        result[sum][visited]++;
        return;
    }
 
    for(int i=0;i<=9;i++){       
        if(visited & (1<<i)) continue;
        if(i==0 && pre[it->first]) continue;
 
        sum += it->second * i;
        it++;
        visited |= (1<<i);
        dfs(co,it,pre,visited,sum,result);
        visited &= ~(1<<i);
        it--;
        sum -= it->second * i;
    }
}
 
int main(){
    int n;
    while(~scanf("%d",&n)){
        if(n==0) break;
        int count = 0;
        map<char,int> coefficient;
        map<char,bool> prefix; // prefix or not
        for(int i=0;i<n;i++){
            string str;
            cin >> str;
            if(str.size() > 1) prefix[str[0]] = true;
            for(int j=str.size()-1,k=1;j>=0;j--,k*=10){
                if(i!=n-1) coefficient[str[j]] += k;
                else coefficient[str[j]] -= k;
            }
        }
     
        map<char,int> co_front;
        map<char,int> co_rear;
 
        int ub=0;
        map<char,int>::iterator cit;
        for(cit = coefficient.begin(); cit != coefficient.end();cit++){
            if(ub >= coefficient.size()/2) break;
            co_front[cit->first] = cit->second;
            ub++;
        }
 
        for(; cit != coefficient.end();cit++){
            co_rear[cit->first] = cit->second;
        }
 
        map<int,map<int,int> > result_front;
        map<int,map<int,int> > result_rear;
 
        dfs(co_front,co_front.begin(),prefix,0,0,result_front);
        dfs(co_rear,co_rear.begin(),prefix,0,0,result_rear);
 
        int res=0;
        for(map<int,map<int,int> >::iterator it = result_front.begin(); it != result_front.end(); it++){
             
            map<int,map<int,int> >::iterator it2;
 
            if((it2 = result_rear.find(-(it->first))) != result_rear.end()){
                for(map<int,int>::iterator sit = it->second.begin(); sit != it->second.end(); sit++){
                    for(map<int,int>::iterator sit2 = it2->second.begin(); sit2 != it2->second.end(); sit2++){
                        if(!(sit->first & sit2->first)) res+=sit->second * sit2->second;
                    }
                }
            }
        }
 
 
        printf("%d\n",res);
    }
}

