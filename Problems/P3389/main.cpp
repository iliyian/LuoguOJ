// date: 2024-03-08 12:41:17
// tag: 高斯消元

#include <bits/stdc++.h>
#define eps 1e-10
using namespace std;

bool eq(double x, double y) {
  return abs(x - y) < eps;
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  freopen("main.in", "r", stdin);
  freopen("main.out", "w", stdout);

  int n;
  cin >> n;
  vector a(n + 1, vector<double>(n + 2));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n + 1; j++) {
      cin >> a[i][j];
    }
  }
  int r = 1;
  for (int c = 1; c <= n; c++) {
    int t = r;
    for (int i = r + 1; i <= n; i++) {
      if (abs(a[i][c]) > abs(a[t][c])) {
        t = i;
      }
    }
    if (eq(a[t][c], 0)) {
      continue;
    }
    swap(a[t], a[r]);
    for (int i = c + 1; i <= n + 1; i++) {
      a[r][i] /= a[r][c];
    }
    a[r][c] /= a[r][c];
    for (int i = 1; i <= n; i++) {
      if (i != r) {
        double t = a[i][c];
        // 注意是r
        for (int j = r; j <= n + 1; j++) {
          a[i][j] -= t * a[r][j];
        }
      }
    }
    r++;
  }
  for (int i = n; i >= 1; i--) {
    for (int j = i - 1; j >= 1; j--) {
      a[j][n + 1] -= a[j][i] * a[i][n + 1];
    }
  }
  if (r <= n) {
    cout << "No Solution\n";
    return 0;
  }
  for (int i = 1; i <= n; i++) {
    cout << fixed << setprecision(2) << a[i][n + 1] << '\n';
  }

  return 0;
}