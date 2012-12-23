
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <cmath>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
 
using namespace std;
 
 
int main()
{
 
    vector<pair<int,string> > res;
 
    while(1){
        int n;
        map<int,int> time;
        map<string,vector<int> > man;
        map<string,int> rank;
        cin >> n;
 
        if(n==0) goto end;
 
        for(int i=0;i<n;i++)
        {
            string name;
            cin >> name;
            int m;
            cin >> m;
            if(m==0) rank[name]=0;
            for(int j=0;j<m;j++)
            {
                int t;
                cin >> t; 
                time[t]++;
                man[name].push_back(t);
            }
        }
 
        for(map<string,vector<int> >::iterator it = man.begin();it != man.end();it++)
        {
            for(int i=0;i<it->second.size();i++)
            {
                rank[it->first]+=n-time[it->second[i]]+1;
            }
        }
 
        int respts = numeric_limits<int>::max();;
        string resname;
 
        for(map<string,int>::iterator it = rank.begin();it != rank.end();it++)
        {
            if(it->second < respts)
            {
                respts = it->second;
                resname = it->first;
            }
        }
 
        res.push_back(pair<int,string>(respts,resname));
    }
 
    end:;
    for(int i=0;i<res.size();i++)
    {
        cout << res[i].first << " " << res[i].second << endl;
    }
 
    return 0;
 
}

