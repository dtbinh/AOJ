
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
 
int main(){
    int n;
    while(~scanf("%d",&n)){
        int pages[50];
        for(int i=0;i<n;i++){
            scanf("%d",pages+i);
        }
 
        vector<P> pset;
        for(int i=0;i<n;){
            int start = i;
            int end = i;
            for(int j=i+1;j<n;){
                if(abs(pages[j] - pages[j-1])>1){
                    i=j;
                    break;
                }
                else{
                    end = j;
                    j++;
                }
            }
            pset.push_back(P(pages[start],pages[end]));
            i=end+1;
        }
 
        for(int i=0;i<pset.size();i++){
            if(pset[i].first != pset[i].second){
                printf("%d-%d%s",pset[i].first,pset[i].second,i==pset.size()-1 ? "n" : " ");
            }
            else
            {
                printf("%d%s",pset[i].first,i==pset.size()-1 ? "n" : " ");
            }
        }
    }
}

