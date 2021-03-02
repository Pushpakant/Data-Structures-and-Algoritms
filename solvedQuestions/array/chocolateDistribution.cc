#define _USE_MATH_DEFINES
#pragma GCC optimize("Ofast,fast-math")

#include <bits/stdc++.h>

#define deb(x) cout << '\n' \
                    << #x << " = " << x << '\n'

inline void setup() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

#ifdef LOCAL_PROJECT  // run with -DLOCAL_PROJECT during compilation
    freopen("input.txt", "r", stdin);
#else
#ifndef ONLINE_JUDGE  // runs automatically for supported online judges
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
#endif
#endif
}

inline void solve();

int main(int argc, char* argv[]) {
    setup();

    long long t = 1;
    std::cin >> t;

    while (t--)
        solve();

    return 0;
}

//Compile: g++ -g -Wshadow -Wall main.cc -o a.exe -Ofast -Wno-unused-result
//Build: g++ -g -Wshadow -Wall main.cc -o a.exe -D_GLIBCXX_DEBUG
//Compile and run: g++ -g -Wshadow -Wall main.cc -o a.exe -Ofast -Wno-unused-result && ./a.exe

using namespace std;

//	https://practice.geeksforgeeks.org/problems/chocolate-distribution-problem/0

inline void solve() {
    int n;
    cin >> n;

    int* a = new int[n];

    for (int i = 0; i < n; ++i) cin >> a[i];

    int m;
    cin >> m;

    sort(a, a + n);

    int ans = INT_MAX;
    for (int i = 0; i < n - m + 1; ++i) ans = min(ans, a[i + m - 1] - a[i]);

    cout << ans << '\n';
}
