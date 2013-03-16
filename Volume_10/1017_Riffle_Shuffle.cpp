
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
typedef pair <int,P > PP;
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;
 
int main(){
    int n,r;    
    while(~scanf("%d %d",&n,&r)){
        if(n==0) break;
        deque<int> A;
        deque<int> B;
        deque<int> C;
 
        for(int i=0;i<n;i++){
            C.push_back(i);
        }
 
        for(int i=0;i<r;i++){
            int c;
            scanf("%d",&c);
 
            for(int j=0;j<n/2;j++){
                B.push_back(C[j]);
            }
            for(int j=n/2;j<n;j++){
                A.push_back(C[j]);
            }
            C.clear();
            while(!A.empty() || !B.empty()){
                for(int j=0;j<c;j++){
                    if(A.empty()) break;
 
                    C.push_back(A.front());
                    A.pop_front();
                }
 
                for(int j=0;j<c;j++){
                    if(B.empty()) break;
                    C.push_back(B.front());
                    B.pop_front();
                }
            }
 
        }
 
 
        printf("%d\n",C.back());
    }
}

