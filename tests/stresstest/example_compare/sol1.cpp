#include <bits/stdc++.h>
using namespace std;

#define uid(a, b) uniform_int_distribution<int>(a, b)(rng) 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int32_t main() {
    int n; cin >> n;
    // una volta su 100 stampera' la soluzione sbagliata
    cout << n + (uid(1, 100) == 1) << endl;
}
