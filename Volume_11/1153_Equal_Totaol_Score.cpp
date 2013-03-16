
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
 
const int tx[] = {0,1,0,-1};
const int ty[] = {1,0,-1,0};
 
char stage[20][20];
 
int main(){
    int m,n;
    while(~scanf("%d %d",&m,&n)){
        if(m==n && n==0) break;
        vector<int> t;
        vector<int> h;
        int sumt=0,sumh=0;
        for(int i=0;i<m;i++){
            int num;
            scanf("%d",&num);
            t.push_back(num);
            sumt+=num;
        }
 
        for(int i=0;i<n;i++){
            int num;
            scanf("%d",&num);
            h.push_back(num);
            sumh+=num;
        }
 
        P res = P(-1,-1);
        int minv = numeric_limits<int>::max();
        for(int i=0;i<t.size();i++){
            for(int j=0;j<h.size();j++){
                if(sumt - t[i] + h[j] == sumh - h[j] + t[i]){
                    if(minv > h[j] + t[i]){
                        res = P(t[i],h[j]);
                        minv = t[i]+h[j];
                    }
                }
            }
        }
        if(res.first==-1) printf("%d\n",-1);
        else printf("%d %d\n",res.first,res.second);
    }
}

