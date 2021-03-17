/*---------------------------------------------------------
다트게임
시간초과 문제 해결
---------------------------------------------------------*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <cstring>
#include <utility>
#include <queue>
#include <stack>
#include <functional>
#include <set>
#include <map>
#include <cassert>
#include <cmath>
 
using namespace std;
typedef long long lli;
typedef pair<int,int> ip;
typedef pair<lli,int> lip;
 
inline double ABS(double a) {
    return a<0?-a:a;
}
inline double POWER(double a) {
    return a*a;
}
inline lli ABS(lli a) {
    return a<0?-a:a;
}
inline int ABS(int a) {return a<0?-a:a;}
inline lli POWER(lli a) { return a*a; }
inline int POWER(int a) { return a*a; }
inline lli GCD(lli a,lli b) {
    while(b) {
        lli tmp=a%b;a=b;b=tmp;
    }
    return a;
}
inline int GCD(int a,int b) {
    while(b) {
        int tmp=a%b;a=b;b=tmp;
    }
    return a;
}
const double EPS=1e-9;
const int MOD=1e9+7;
const lli INF=1e15;
 
int main() {
    int test;
    scanf("%d",&test);
    for(int test_case =1; test_case<=test; test_case++){
        int x,y,sum=0,n;
        scanf("%d",&n);
        for(int i=0;i<n;i++) {
            scanf("%d%d",&x,&y);
            for(int i=1;i<=10;i++) {
                if(POWER(x)+POWER(y)<=POWER(20*i)) {
                    sum+=(11-i);
                    break;
                }
            }
        }
        printf("#%d %d\n", test_case, sum);
    }
 
    return 0;
}
