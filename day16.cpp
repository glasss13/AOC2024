#include <bits/stdc++.h>

#include <limits>
#include <queue>

#include "utils.hpp"

using namespace std;

struct Node {
    int r, c, dr, dc;

    bool operator==(const Node& other) const {
        return r == other.r && c == other.c && dr == other.dr && dc == other.dc;
    }

    bool operator<(const Node& other) const {
        return tuple<int, int, int, int>(r, c, dr, dc) <
               tuple<int, int, int, int>(other.r, other.c, other.dr, other.dc);
    }
};

struct node_hash {
    size_t operator()(const Node& node) const {
        size_t out = 0;

        out |= ((size_t)node.r << 56);
        out |= ((size_t)node.c << 48);
        out |= (node.dr << 8);
        out |= (node.dc);

        return out;
    }
};

unordered_map<Node, vector<pair<Node, int>>, node_hash> parse_graph(
    const vector<string>& g) {
    unordered_map<Node, vector<pair<Node, int>>, node_hash> adj_list;

    for (int i = 0; i < g.size(); ++i) {
        for (int j = 0; j < g[0].size(); ++j) {
            if (g[i][j] == '#') continue;
            for (auto [dr, dc] : DIRS) {
                for (auto [dr2, dc2] : DIRS) {
                    if (dr == -dr2 && dc == -dc2) continue;

                    if (g[i + dr2][j + dc2] != '#') {
                        if (dr == dr2 && dc == dc2) {
                            adj_list[Node{i, j, dr, dc}].emplace_back(
                                Node{i + dr2, j + dc2, dr2, dc2}, 1);
                        } else {
                            adj_list[Node{i, j, dr, dc}].emplace_back(
                                Node{i, j, dr2, dc2}, 1000);
                        }
                    }
                }
            }
        }
    }

    return adj_list;
}

unordered_map<Node, int, node_hash> djikstra(
    const unordered_map<Node, vector<pair<Node, int>>, node_hash>& adj_list,
    const vector<Node>& sources) {
    priority_queue<pair<Node, int>> pq;
    unordered_map<Node, int, node_hash> dists;

    for (auto src_node : sources) {
        dists[src_node] = 0;
        pq.emplace(src_node, 0);
    }

    while (!pq.empty()) {
        auto [node, dist] = pq.top();
        pq.pop();
        if (!adj_list.contains(node)) continue;

        for (auto [adj_node, adj_weight] : adj_list.at(node)) {
            int node_dist = dists.contains(adj_node)
                                ? dists[adj_node]
                                : numeric_limits<int>::max();

            int new_dist = dist + adj_weight;
            if (new_dist < node_dist) {
                dists[adj_node] = new_dist;
                pq.emplace(adj_node, new_dist);
            }
        }
    }

    return dists;
}

ll part1(vector<string> lines) {
    int init_r = lines.size() - 2;
    int init_c = 1;

    int target_r = 1;
    int target_c = lines[0].size() - 2;

    auto adj_list = parse_graph(lines);

    auto dists = djikstra(adj_list, {Node(init_r, init_c, 0, 1)});

    int target_dist = numeric_limits<int>::max();
    for (auto [a, b] : DIRS) {
        if (dists.contains({target_r, target_c, a, b})) {
            target_dist =
                min(target_dist, dists[Node{target_r, target_c, a, b}]);
        }
    }

    return target_dist;
}

ll part2(vector<string> lines) {
    int init_r = lines.size() - 2;
    int init_c = 1;

    int target_r = 1;
    int target_c = lines[0].size() - 2;

    auto adj_list = parse_graph(lines);

    auto dists = djikstra(adj_list, {Node(init_r, init_c, 0, 1)});
    vector<Node> target_srcs;
    for (auto [dr, dc] : DIRS) {
        target_srcs.emplace_back(target_r, target_c, dr, dc);
    }
    auto dists2 = djikstra(adj_list, target_srcs);

    int target_dist = numeric_limits<int>::max();
    for (auto [a, b] : DIRS) {
        if (dists.contains({target_r, target_c, a, b})) {
            target_dist =
                min(target_dist, dists[Node{target_r, target_c, a, b}]);
        }
    }

    set<pair<int, int>> res;
    for (auto& [node, dist] : dists) {
        int dr, dc;
        if (node.dr == 0) {
            dr = 0;
            dc = -node.dc;
        } else {
            dr = -node.dr;
            dc = 0;
        }
        if (!dists2.contains(Node{node.r, node.c, dr, dc})) continue;

        auto x = dists2[Node{node.r, node.c, dr, dc}];
        if (dist + x == target_dist) {
            res.emplace(node.r, node.c);
        }
    }

    return res.size();
}

int main(int argc, char** argv) {
    ifstream file =
        argc == 1 ? ifstream("inputs/day16.txt") : ifstream("sample.txt");

    string line;
    vector<string> lines;
    string full_input;
    while (std::getline(file, line)) {
        lines.push_back(line);
        full_input += line;
    }

    auto p1_start = chrono::high_resolution_clock::now();
    auto p1 = part1(lines);
    auto p2_start = chrono::high_resolution_clock::now();
    auto p2 = part2(lines);
    auto p2_end = chrono::high_resolution_clock::now();
    cout << "part1: " << p1 << '\n';
    cout << "part2: " << p2 << '\n';

    auto p1_time =
        chrono::duration_cast<chrono::microseconds>(p2_start - p1_start);
    auto p2_time =
        chrono::duration_cast<chrono::microseconds>(p2_end - p2_start);
    cout << "part1(µs): " << p1_time.count() << '\n';
    cout << "part2(µs): " << p2_time.count() << '\n';
}
