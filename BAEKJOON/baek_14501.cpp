#include <cstdio>
#include <algorithm>

using namespace std;

int main() {

    int time[17] = { 0, };
    int pay[17] = { 0, };
    int n, i;
    int ans = 0;

    scanf("%d", &n);

    for (i = 1; i <= n; i++) scanf("%d %d", &time[i], &pay[i]);

    for (i = n; i >= 1; i--) {
        if (i + time[i] > n + 1) pay[i] = pay[i + 1];
        else {
            pay[i] = max(pay[i + 1], pay[i] + pay[i + time[i]]);
            ans = max(ans, pay[i]);
        }
    }

    printf("%d\n", ans);

    return 0;
}