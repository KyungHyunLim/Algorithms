#include<iostream>
#include<vector>
#include<string.h>
#include<queue>
#include<cstring>

using namespace std;

char signs[4] = { 'D', 'S', 'L', 'R' };
bool check[10001];
int A, B;

int calc(int s, int A) {
    int le, qu;
    switch (s)
    {
    case 0: // D
        A *= 2;
        if (A > 9999) return (A % 10000);
        return A;
    case 1: // S
        if (A == 0) return 9999;
        A -= 1;
        return A;
    case 2: // L
        le = A % 1000;
        qu = A / 1000;
        A = (le * 10) + qu;
        return A;
    case 3: // R
        le = A % 10;
        qu = A / 10;
        A = (le * 1000) + qu;
        return A;
    }
}

void solve() {
    queue<pair<int,string>> q;
    q.push(make_pair(A,""));
    check[A] = true;

    while (!q.empty()) {
        int n = q.front().first;
        string s = q.front().second;
        q.pop();

        if (n == B) {
            cout << s << endl;
            return;
        }

        for (int i = 0; i < 4; i++) {
            int next_n = calc(i, n);
            if (!check[next_n]) {
                check[next_n] = true;
                q.push(make_pair(next_n, s + signs[i]));
            }
        }
    }
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int T;
    cin >> T;
    
    for (int test_case = 0; test_case < T; test_case++){
        cin >> A >> B;
        solve();
        memset(check, false, sizeof(check));
    }

    return 0;
}
