#include<iostream>
#include<vector>
#include<string.h>

using namespace std;

int N;
int nums[21];
bool check[2000001];
int answer;

void combination(int n, int r, int ret[21], int i, int next) {

    if (r == i) {
        int sum = 0;
        for (int j = 0; j < r; j++) {
            sum += nums[ret[j]];
        }
        check[sum] = true;
        return;
    }

    if (next >= n) return;

    ret[i] = next;
    combination(n, r, ret, i + 1, next + 1);
    combination(n, r, ret, i, next + 1);
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    memset(check, false, sizeof(check));
    for (int i = 0; i < N; i++) {
        cin >> nums[i];
        check[nums[i]] = true;
    }

    for (int i = 1; i <= N; i++) {
        int res[21];
        combination(N, i, res, 0, 0);
    }
    
    for (int i = 1; i < 2000001; i++) {
        if (!check[i]) {
            cout << i;
            break;
        }
    }

    return 0;
}
