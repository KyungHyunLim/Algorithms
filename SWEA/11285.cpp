#include<iostream>
#include<math.h>
using namespace std;
/*
int main(int argc, char** argv)
{
    int test_case;
    int T;

    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case)
    {
        int N;
        cin >> N;

        int score = 0;
        for (int i = 0; i < N; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            float e = sqrt(x * x + y * y);
            e > 200 ? score += 0 : score += (11 - (int)(e * 0.05));
        }
        printf("#%d %d\n", test_case, score);
    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
*/
int main(int argc, char** argv)
{
    int test_case;
    int T;

    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case)
    {
        int N;
        cin >> N;

        int score = 0;
        for (int i = 0; i < N; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            float e = sqrt(x * x + y * y);

            if (e <= 20) score += 10;
            else if (e <= 40) score += 9;
            else if (e <= 60) score += 8;
            else if (e <= 80) score += 7;
            else if (e <= 100) score += 6;
            else if (e <= 120) score += 5;
            else if (e <= 140) score += 4;
            else if (e <= 160) score += 3;
            else if (e <= 180) score += 2;
            else if (e <= 200) score += 1;
        }
        printf("#%d %d\n", test_case, score);
    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}

/*
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
const int dy[4]={0,-1,0,1},dx[4]={1,0,-1,0};

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
*/