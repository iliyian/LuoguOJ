#include <bits/stdc++.h>
#define N 100005
#define ls p << 1
#define rs p << 1 | 1
using namespace std;

int siz[N], pa[N], dfn[N], top[N], dep[N], rnk[N], son[N], cnt = 0, n, q;
int a[N], d[N << 2];

vector<vector<int>> g;

void dfs1(int u) {
  siz[u] = 1;
  for (int v : g[u]) {
    if (dep[v]) continue;
    dep[v] = dep[u] + 1;
    pa[v] = u;
    dfs1(v);
    siz[u] += siz[v];
    if (siz[v] > siz[son[u]]) son[u] = v;
  }
}

void dfs2(int u, int t) {
  top[u] = t;
  ++cnt;
  dfn[u] = cnt, rnk[cnt] = u;
  if (!son[u]) return;
  dfs2(son[u], t);
  for (int v : g[u])
    if (son[u] != v && pa[u] != v)
      dfs2(v, v);
}

void pushup(int p) {
  d[p] = max(d[ls], d[rs]);
}

void build(int s, int t, int p) {
  if (s == t) {
    d[p] = -1;
    return;
  }
  int mid = s + (t - s >> 1);
  build(s, mid, ls);
  build(mid + 1, t, rs);
  pushup(p);
}

void modify(int x, int s, int t, int p) {
  if (s <= x && x <= t) {
    d[p] = s;
    return;
  }
  int mid = s + (t - s >> 1);
  if (x <= mid) modify(x, s, mid, ls);
  if (x > mid) modify(x, mid + 1, t, rs);
}

int query(int l, int r, int s, int t, int p) {
  if (l <= s && t <= r) return d[p];
  int mid = s + (t - s >> 1), ans = -1;
  if (l <= mid) ans = max(ans, query(l, r, s, mid, ls));
  if (r > mid) ans = max(ans, query(l, r, mid + 1, t, rs));
  return ans;
}

int hldquery(int x, int y) {
  int ans = -1;
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) swap(x, y);
    ans = max(ans, query(dfn[top[x]], dfn[x], 1, n, 1));
    if (ans != -1) return ans;
    x = pa[top[x]];
  }
  if (dep[x] > dep[y]) swap(x, y);
  ans = max(ans, query(dfn[x], dfn[y], 1, n, 1));
  return ans;
}

int main() {
  ios::sync_with_stdio(false); cin.tie(0);
  freopen("data.in", "r", stdin);
  cin >> n >> q;
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
  }
  dep[1] = 1;
  dfs1(1);
  dfs2(1, 1);
  build(1, n, 1);
  modify(1);
  for (int i = 0; i < q; i++) {
    char op;
    int x;
    cin >> op >> x;
    if (op == 'C') modify()
    else cout << rnk[hldquery(1, x)] << '\n';
  }
}