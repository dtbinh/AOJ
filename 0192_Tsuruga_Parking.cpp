
#define _USE_MATH_DEFINES
#define INF 10000000
#include <iostream>
#include <sstream>
#include <cmath>
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
typedef pair<int,int> P;

static const double eps = 1e-8;

class SPACE{
private:
	int mUpTime;
	int mLoTime;
	int mUpCar;
	int mLoCar;
	bool mUpUsed;
	bool mLoUsed;

public:
	SPACE() : mUpTime(0),mLoTime(0),mUpUsed(false),mLoUsed(false),mUpCar(0),mLoCar(0){}
	void setUpTime(int time){ mUpTime = time;}
	void setLoTime(int time){ mLoTime = time;}
	void setUpCar(int car){ mUpCar = car;}
	void setLoCar(int car){ mLoCar = car;}
	void setIsUpUsed(bool flag) { mUpUsed = flag;}
	void setIsLoUsed(bool flag) { mLoUsed = flag;}

	int getUpTime() const{ return mUpTime;}
	int getLoTime() const{ return mLoTime;}
	int getUpCar() const{ return mUpCar;}
	int getLoCar() const{ return mLoCar;}
	int isUpUsed() const{ return mUpUsed;}
	int isLoUsed() const{ return mLoUsed;}
};

class PARK{
private:
	class SPACE* mSpace;
	int mNum;
	int mParked;

	int getLeastDiffIdx(int src){
		int res=-1;
		int diff = INF;
		for(int i=0;i<mNum;i++){
			if(!mSpace[i].isUpUsed() && mSpace[i].isLoUsed()){
				if(diff > abs(mSpace[i].getLoTime()-src)){
					diff = abs(mSpace[i].getLoTime()-src);
					res = i;
				}
			}
		}

		return res;
	}

	int getLeastTime(){
		int minTime = INF;
		for(int i=0;i<mNum;i++){
			if(mSpace[i].isLoUsed()){
				minTime=min(mSpace[i].getLoTime() <= 0 ? minTime : mSpace[i].getLoTime(),minTime);
			}

			if(mSpace[i].isUpUsed()){
				minTime=min(mSpace[i].getUpTime() <= 0 ? minTime : mSpace[i].getUpTime(),minTime);
			}
		}

		return minTime;
	}

public:
	PARK() : mSpace(NULL),mNum(0),mParked(0) {}
	PARK(SPACE* space,int num){
		mSpace = space;
		mNum = num;
	}
	SPACE getSpace(int idx) const{
		return mSpace[idx];
	}

	bool parkCar(int time,int id){
		for(int i=0;i<mNum;i++){
			if(!mSpace[i].isLoUsed() && !mSpace[i].isUpUsed()){
				mSpace[i].setLoCar(id);
				mSpace[i].setLoTime(time);
				mSpace[i].setIsLoUsed(true);
				return true;
			}
		}

		int idx=-1;
		int pos=-1;
		int diff = INF;

		for(int i=0;i<mNum;i++){
			if(!mSpace[i].isUpUsed() && mSpace[i].getLoTime() >= time){
				if(diff > abs(mSpace[i].getLoTime()-time)){
					diff = abs(mSpace[i].getLoTime()-time);
					idx = i;
					pos = 0;
				}
			}

			else if(!mSpace[i].isLoUsed() && mSpace[i].getUpTime() >= time){
				if(diff > abs(mSpace[i].getUpTime()-time)){
					diff = abs(mSpace[i].getUpTime()-time);
					idx = i;
					pos = 1;
				}
			}
		}

		if(idx!=-1){
			if(pos == 0){
				mSpace[idx].setUpTime(mSpace[idx].getLoTime());
				mSpace[idx].setUpCar(mSpace[idx].getLoCar());
				mSpace[idx].setIsUpUsed(true);

				mSpace[idx].setLoTime(time);
				mSpace[idx].setLoCar(id);
				mSpace[idx].setIsLoUsed(true);
				return true;
			}
			else if(pos==1){
				mSpace[idx].setLoTime(time);
				mSpace[idx].setLoCar(id);
				mSpace[idx].setIsLoUsed(true);
				return true;
			}
		}

		diff = INF;

		for(int i=0;i<mNum;i++){
			if(!mSpace[i].isUpUsed() && mSpace[i].getLoTime() < time){
				if(diff > abs(mSpace[i].getLoTime()-time)){
					diff = abs(mSpace[i].getLoTime()-time);
					idx = i;
					pos = 0;
				}
			}

			else if(!mSpace[i].isLoUsed() && mSpace[i].getUpTime() < time){
				if(diff > abs(mSpace[i].getUpTime()-time)){
					diff = abs(mSpace[i].getUpTime()-time);
					idx = i;
					pos = 1;
				}
			}
		}

		if(idx!=-1){
			if(pos==0){
				mSpace[idx].setUpTime(mSpace[idx].getLoTime());
				mSpace[idx].setUpCar(mSpace[idx].getLoCar());
				mSpace[idx].setIsUpUsed(true);
				mSpace[idx].setLoTime(time);
				mSpace[idx].setLoCar(id);
				return true;
			}
			else if(pos==1){
				mSpace[idx].setLoTime(time);
				mSpace[idx].setLoCar(id);
				mSpace[idx].setIsLoUsed(true);
				return true;
			}
		}

		return false;
	}

	void subTime(int t){
		for(int i=0;i<mNum;i++){
			int utmp = mSpace[i].getUpTime();
			int ltmp = mSpace[i].getLoTime();
			if(mSpace[i].isUpUsed()) mSpace[i].setUpTime(utmp-t);
			if(mSpace[i].isLoUsed()) mSpace[i].setLoTime(ltmp-t);
		}
	}

	queue<int> outCar(){
		queue<int> res;
		for(int i=0;i<mNum;i++){

			if(mSpace[i].isLoUsed() && mSpace[i].getLoTime()<=0){
				res.push(mSpace[i].getLoCar());
				mSpace[i].setIsLoUsed(false);
				mSpace[i].setLoTime(0);

				if(mSpace[i].isUpUsed() && mSpace[i].getUpTime()<=0){
					res.push(mSpace[i].getUpCar());
					mSpace[i].setIsUpUsed(false);
					mSpace[i].setUpTime(0);
				}
			}
			else if(!mSpace[i].isLoUsed() && mSpace[i].isUpUsed()){
				if(mSpace[i].getUpTime()<=0){
					res.push(mSpace[i].getUpCar());
					mSpace[i].setIsUpUsed(false);
					mSpace[i].setUpTime(0);
				}
			}
		}
		return res;
	}

	int getParked(){
		int res=0;
		for(int i=0;i<mNum;i++){
			if(mSpace[i].isLoUsed()) res++;
			if(mSpace[i].isUpUsed()) res++;
		}

		return res;
	}

	void printState(){
		for(int i=0;i<mNum;i++){
			printf("space %d\n",i);
			printf("used=%d lower id=%d  remain time=%d\n",
				mSpace[i].isLoUsed(),mSpace[i].getLoCar(),mSpace[i].getLoTime());
			printf("used=%d upper id=%d  remain time=%d\n",
				mSpace[i].isUpUsed(),mSpace[i].getUpCar(),mSpace[i].getUpTime());			
		}
		printf("\n");
	}
};

int main(){

	int n,m;
	while(~scanf("%d %d",&m,&n)){
		if(m==n && n==0) break;
		int* car = new int[n+1];
		for(int i=1;i<=n;i++){
			scanf("%d",car+i);
		}
		SPACE* space = new SPACE[m];
		PARK park(space,m);

		queue<int> res;
		queue<P> que;

		for(int time=0,i=1;;time++){
			if(res.size() == n) break;

			if(time == 10 && i <= n){
				que.push(P(i,car[i]));
				i++;
				time=0;
			}

			while(!que.empty()){
				int id = que.front().first;
				int stay = que.front().second;				
				if(!park.parkCar(stay,id)) break;
				que.pop();
			}

			park.subTime(1);
			queue<int> tmp = park.outCar();
			while(!tmp.empty()){ res.push(tmp.front()); tmp.pop(); }
			
		}

		vector<int> ans;
		while(!res.empty()){
			ans.push_back(res.front());
			res.pop();
		}

		for(int i=0;i<ans.size();i++){
			printf("%d%s",ans[i],i==ans.size()-1 ? "\n" : " ");
		}

		delete[] car;
		delete[] space;
	}
}

