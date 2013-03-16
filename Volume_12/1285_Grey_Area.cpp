
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
    int n,w;
 
    while(~scanf("%d %d",&n,&w)){
        if(n==0) break;
 
        map<int,int> freq;
        int last = 0;
        freq[0] = 0;
        for(int i=0;i<n;i++){
            int v;
            scanf("%d",&v);
             
            for(int i=0,j=0;i<=100;i+=w,j++){
                if(i <= v && v < i + w){
                    freq[j]++;
                    last = max(j,last);
                    break;
                }
            }
        }
 
 
        int maxv = 0;
        int num = 0;
        for(int i=0,j=0;i<=100;i+=w,j++){
            if(maxv < freq[j]){
                maxv = freq[j];
                num = freq[j];
            }
        }
 
        double used = 0.0;
        int idx = 0;
        for(double h = 1.0; h>=0-EPS; h-=1.0/last){
            used += h * freq[idx]/num;
            idx++;
        }
 
        used += 0.01;
 
        printf("%lf\n",used);
    }
}

