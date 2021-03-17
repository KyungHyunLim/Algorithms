#include<iostream>
#include<vector>

using namespace std;

int N, K;
int nums[49];

void combination(int n, int r, int ret[13], int i, int next) {

    if (r == i) {
        for (int j = 0; j < r; j++) {
            cout << nums[ret[j]];
            if (j != r - 1) cout << " ";
        }
        cout << endl;
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

    while (true) {
        cin >> N;
        if (N == 0) break;
        for (int i = 0; i < N; i++) {
            cin >> nums[i];
        }

        int res[13];
        combination(N, 6, res, 0, 0);
        cout << endl;
    }  

    return 0;
}
