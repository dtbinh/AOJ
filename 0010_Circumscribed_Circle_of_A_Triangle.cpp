
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>
using namespace std;

int main()
{
  double eps = 10e-7;
  double x1,y1,x2,y2,x3,y3;
  int T;
  scanf("%d",&T);
  for(int i=0;i<T;i++){
  scanf("%lf %lf %lf %lf %lf %lf",&x1,&y1,&x2,&y2,&x3,&y3);
  double a = pow(x2-x3,2.0)+pow(y2-y3,2.0);
  double b = pow(x3-x1,2.0)+pow(y3-y1,2.0);
  double c = pow(x1-x2,2.0)+pow(y1-y2,2.0);
  double a2 = sqrt(pow(x2-x3,2.0)+pow(y2-y3,2.0));
  double b2 = sqrt(pow(x3-x1,2.0)+pow(y3-y1,2.0));
  double c2 = sqrt(pow(x1-x2,2.0)+pow(y1-y2,2.0));
  double s = (a2+b2+c2)/2.0;
  double S = sqrt(s*(s-a2)*(s-b2)*(s-c2));
  double px = (a*(b+c-a) * x1 + b*(c+a-b) * x2 + c*(a+b-c) * x3) / (16.0*pow(S,2.0));
  double py = (a*(b+c-a) * y1 + b*(c+a-b) * y2 + c*(a+b-c) * y3) / (16.0*pow(S,2.0));
  double r = a2*b2*c2/(4.0*S);
  px += 0.00005 + eps;
  py += 0.00005 + eps;
  r += 0.00005 + eps;
  printf("%.3f %.3f %.3f\n",px,py,r);
  }
}

