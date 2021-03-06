#include <cstdio>
#include <cstring>
const int N = 520;
int a[N + 5], b[N + 5], ta[N + 5], tb[N + 5];
bool vis[N + 5];
long long m[N + 5], c[N + 5];
long long exgcd(long long a, long long b, long long &x, long long &y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }
    long long res = exgcd(b, a % b, y, x);
    y -= a/b*x;
    return res;
}
long long mod(long long a, long long b) {
    long long res = a % b;
    if (res < 0) res += b;
    return res;
}
void solve(int n) {
    memset(vis, false, sizeof(vis));
    int cnt = 0;
    for (int i = 1; i <= n; ++i)
        if (!vis[i]) {
            int num = 0, t = i;
            while (!vis[t]) {
                vis[t] = true;
                ta[++num] = t;
                tb[num] = b[t];
                t = a[t];
            }
            bool same = false;
            for (int i = 1; i <= num; ++i)
                if (tb[i] == ta[1]) {
                    same = true;
                    int j = i, k = 1;
                    do {
                        if (tb[j] != ta[k]) same = false;
                        j = j % num + 1;
                        k = k % num + 1;
                    } while (i != j);
                    t = i;
                    break;
                }
            if (!same) {
                printf("-1\n");
                return;
            }
            m[++cnt] = num;
            c[cnt] = (num - t + 1) % num;
        }
    n = cnt;
    long long ans = c[1], LCM = m[1];
    for (int i = 2; i <= n; ++i) {
        long long x, y, g = exgcd(LCM, m[i], x, y);
        if ((c[i] - ans) % g) {
            printf("-1\n");
            return;
        }
        ans = mod(ans + LCM*mod((c[i] - ans)/g*x, m[i]/g), LCM/g*m[i]);
        LCM = LCM/g*m[i];
    }
    printf("%I64d\n", ans);
    return;
}
int main() {
    int n;
    while (scanf("%d", &n), n) {
        for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        for (int i = 1; i <= n; ++i) scanf("%d", &b[i]);
        solve(n);
    }
    return 0;
}
