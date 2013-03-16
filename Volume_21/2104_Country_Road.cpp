
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
    int t;
    while(~scanf("%d",&t)){
        for(int i=0;i<t;i++){
            int n,k;
            scanf("%d %d",&n,&k);
 
            int homes[100000];
            for(int j=0;j<n;j++){
                scanf("%d",&homes[j]);
            }
 
            vector<int> diff;
            for(int j=0;j+1<n;j++){
                diff.push_back(homes[j+1]-homes[j]);
            }
             
            sort(diff.begin(),diff.end(),greater<int>());
 
            int len = homes[n-1]-homes[0];
 
            for(int j=0;j<k-1 && j < diff.size();j++){
                len -= diff[j];
            }
 
            printf("%d\n",len);
        }
    }
}

