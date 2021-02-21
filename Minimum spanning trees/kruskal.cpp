#include <bits/stdc++.h>

using namespace std;

// Reference for the dijoint union data structure:
// Atcoder

struct dsu {
public:
  dsu() {}
  dsu(int n): n(n), pr_sz(n, -1) {}
  bool same(int a, int b) {
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    return leader(a) == leader(b);
  }
  int leader(int a) {
    if (pr_sz[a] < 0) return a;
    return pr_sz[a] = leader(pr_sz[a]);
  }
  void merge(int a, int b) {
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    a = leader(a);
    b = leader(b);
    if (a == b) return;
    if (-pr_sz[a] < -pr_sz[b]) swap(a, b);
    pr_sz[a] += pr_sz[b];
    pr_sz[b] = a;
  }
private:
  int n;
  vector<int> pr_sz;
};

int main() {
  freopen("kruskal_sample_input.txt", "r", stdin);

  int V, E;
  cin >> V >> E;

  vector<pair<int, pair<int, int>>> edges(E); // weight, vertices 
  for (auto& edge: edges)
    cin >> edge.second.first >> edge.second.second >> edge.first;

  sort(edges.begin(), edges.end());

  int min_weight = 0;
  vector<pair<int, int>> tree_edges;

  dsu d(V);

  for (int i=0; i<E; i++) {
    if (! d.same(edges[i].second.first, edges[i].second.second)) {
      tree_edges.push_back(edges[i].second);
      d.merge(edges[i].second.first, edges[i].second.second);
      min_weight += edges[i].first;
    }
  }
  
  cout << "Min weight: " << min_weight << endl;
  cout << "Tree edges:\n";
  for (auto& edge: tree_edges) {
    cout << edge.first << ' ' << edge.second << endl;
  }
  return 0;
}
