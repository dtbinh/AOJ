
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
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
 
static const double EPS = 1e-8;
 
struct Land{
    short treasure;
    short bridge;
} island[25];
 
class mycmp{
public:
 
    bool operator()(struct Land L1,struct Land L2){
        return L1.bridge < L2.bridge;
    }
};
 
int main(){
    int n;
    while(~scanf("%d",&n)){
        if(n==0) break;
 
        for(int i=0;i<n;i++){
            int w,bridge;
            scanf("%d %d",&w,&bridge);
            island[i].bridge = bridge;
            island[i].treasure = w;
        }
 
        sort(island,island+n,mycmp());
 
        int sum=0;
        bool isok = true;
        for(int i=0;i<n;i++){
            sum += island[i].treasure;
            if(sum > island[i].bridge) isok = false;
        }
 
        printf("%sn",isok ? "Yes" : "No");
    }
}

