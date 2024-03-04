#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

const int INF = INT_MAX;

map<char, vector<pair<char, int>>> graph;

void addEdge(char u, char v, int w) {
    graph[u].push_back({v, w});
    graph[v].push_back({u, w});
}

void uniformCostSearch(char start, char goal) {
    priority_queue<pair<int, char>, vector<pair<int, char>>, greater<pair<int, char>>> pq;
    map<char, int> dist;
    map<char, char> parent;

    for (auto node : graph) {
        dist[node.first] = INF;
    }

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        char u = pq.top().second;
        pq.pop();

        if (u == goal) {
            break;
        }

        for (auto neighbor : graph[u]) {
            char v = neighbor.first;
            int w = neighbor.second;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[goal] == INF) {
        cout << "No path found from " << start << " to " << goal << endl;
    } else {
        cout << "Shortest path from " << start << " to " << goal << " is:" << endl;
        char node = goal;
        while (node != start) {
            cout << node << " <- ";
            node = parent[node];
        }
        cout << start << endl;
        cout << "Cost: " << dist[goal] << endl;
    }
}

int main() {
    addEdge('A', 'B', 3);
    addEdge('A', 'C', 1);
    addEdge('A', 'S', 1);
    addEdge('B', 'D', 3);
    addEdge('C', 'D', 1);
    addEdge('C', 'G', 3);
    addEdge('D', 'G', 3);
    addEdge('S', 'G', 12);

    uniformCostSearch('A', 'G');

    return 0;
}
