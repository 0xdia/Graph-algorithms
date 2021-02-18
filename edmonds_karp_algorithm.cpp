#include <bits/stdc++.h>

using namespace std;

#define all(X) X.begin() X.end()

int N, M;                         // number of vertices, number of edges
vector<vector<pair<int, int>>> G; // Actual graph 
vector<vector<int>> R;            // Residual network 
                                     
long int max_flow_value = 0l;

pair<int, int> augment(vector<pair<int, int>>& U, vector<bool>& vis) {
  if (U.empty())
    return {0, 0};

  vector<pair<int, int>> V;

  for (int i=0; i<U.size(); i++) {
    if (R[U[i].first][N-1] > 0) {
      int cp = min(U[i].second, R[U[i].first][N-1]);
      R[U[i].first][N-1] -= cp;
      R[N-1][U[i].first] += cp;
      return {cp, U[i].first};
    }

    for (int j=0; j<N-1; j++) {
      if (vis[j] || R[U[i].first][j] <= 0) 
        continue;

      vis[j] = true; 
      V.push_back({j, min(R[U[i].first][j], U[i].second)});
    }
  }

  pair<int, int> a = augment(V, vis);

  for (int i=0; i<U.size(); i++) {
    if (R[U[i].first][a.second] > 0) {
      R[U[i].first][a.second] -= a.first;
      R[a.second][U[i].first] += a.first;
      return {a.first, U[i].first};
    }
  }

  return {0, 0};
}

void find_max_flow() {
  while (true) {
    vector<bool> vis(N, false);
    vector<pair<int, int>> cur(1, {0, INT_MAX});
    vis[0] = true;

    pair<int, int> add = augment(cur, vis);

    if (add.first == 0) 
      break;
    max_flow_value += add.first;
    // add.second is the source, always.
  }

  // set the max flow in the actual graph
  for (int i=0; i<N; i++) {
    for (int j=0; j<N; j++) {
      if (G[i][j].first == -1) continue;

      G[i][j].first = R[j][i];
    }
  }
}

int main() {
  freopen("sample_input_edmonds_karp.txt", "r", stdin);

  cin >> N >> M;

  G.assign(N, vector<pair<int ,int>>(N, {-1, 0}));
  R.assign(N, vector<int>(N, -1));

  for (int i=0; i<M; i++) {
    int u, v, c;
    cin >> u >> v >> c;
    G[u][v] = {0, c};
    R[u][v] = c;
    R[v][u] = 0;
  }

  find_max_flow(); 
  
  printf("The value of a max flow is: %ld\n", max_flow_value);
  cout << "The max flow (format: 'from: (to, edge flow / edge capacity)'\n";
  for (int i=0; i<N-1; i++) {
    printf("%d: ", i);
    for (int j=0; j<N; j++) {
      if (G[i][j].first == -1)
        continue;
      printf("(%d, %d/%d) ", j, G[i][j].first, G[i][j].second);
    }
    puts("");
  }

  return 0;
}
