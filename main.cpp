#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;         // a* z chata

const int INF = 1e9;

struct Data {
    int n, x, y;
};

bool comparatorX(const Data &a, const Data &b) {
    return a.x < b.x;
}

bool comparatorY(const Data &a, const Data &b) {
    return a.y < b.y;
}

int heuristic(const Data &a, const Data &b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

int a_star(int n, vector<vector<pair<int, int>>> &graph, vector<Data> &dane, int start, int end) {
    vector<int> dist(n, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    dist[start] = 0;
    pq.push({0 + heuristic(dane[start], dane[end]), start});

    while (!pq.empty()) {
        int v = pq.top().second;
        pq.pop();

        if (v == end) return dist[v];

        for (const auto &[to, weight] : graph[v]) {
            int newDist = dist[v] + weight;
            if (newDist <= dist[to]) {
                dist[to] = newDist;
                pq.push({newDist + heuristic(dane[to], dane[end]), to});
            }
        }
    }

    return INF;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Data> dane(n);

    for (int i = 0; i < n; i++) {
        cin >> dane[i].x >> dane[i].y;
        dane[i].n = i;
    }

    int s, d;
    cin >> s >> d;

    vector<vector<pair<int, int>>> graph(n);

    sort(dane.begin(), dane.end(), comparatorX);
    for (int j = 0; j < n - 1; j++) {
        int dist = abs(dane[j + 1].x - dane[j].x);
        graph[dane[j].n].push_back({dane[j + 1].n, dist});
        graph[dane[j + 1].n].push_back({dane[j].n, dist});
    }

    sort(dane.begin(), dane.end(), comparatorY);
    for (int j = 0; j < n - 1; j++) {
        int dist = abs(dane[j + 1].y - dane[j].y);
        graph[dane[j].n].push_back({dane[j + 1].n, dist});
        graph[dane[j + 1].n].push_back({dane[j].n, dist});
    }

    cout << a_star(n, graph, dane, s, d) << "\n";

    return 0;
}