#define MAX(A,B) A > B ? A : B;

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    int arr[1000001];
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    
    vector<int> list;
    for (int i = 0; i < N; i++) {
        auto& a = arr[i];

        if (list.size() == 0) list.push_back(a);
        else if (a < list[0]) list[0] = a;
        else if (a > list.back()) list.push_back(a);
        else {
            auto it = upper_bound(list.begin(), list.end(), a - 1);
            *it = a;
        }
    }

    cout << list.size();

    return 0;
}