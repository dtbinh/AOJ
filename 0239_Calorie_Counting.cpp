
#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#include <cstdio>
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
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;
 
struct Data{
    int idx;
    int p;
    int q;
    int r;
    int cal;
};
 
int main(){
    int n;
    while(~scanf("%d",&n)){
        if(n==0) break;
 
        vector<Data> food;
        for(int i=0;i<n;i++){
            int idx,p,q,r;
            //calc 4 9 4
            scanf("%d %d %d %d",&idx,&p,&q,&r);
            Data d = {idx,p,q,r,4*p+9*q+4*r};
            food.push_back(d);
        }
 
        int P,Q,R,C;
        scanf("%d %d %d %d",&P,&Q,&R,&C);
        vector<int> canEat;
        for(int i=0;i<food.size();i++){
            if(food[i].p <= P && food[i].q <= Q
                && food[i].r <= R && food[i].cal <= C){
                    canEat.push_back(food[i].idx);
            }
        }
 
        if(canEat.size() == 0) printf("NA\n");
        else{
            for(int i=0;i<canEat.size();i++){
                printf("%d\n",canEat[i]);
            }
        }
    }
}

