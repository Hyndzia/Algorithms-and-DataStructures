#pragma once
#include<iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

struct Node {
    double a;
    double b;
};

struct Edge {
    int x;
    int y;
    double weight;
};

struct Graph {
    std::vector<Node> nodes;
    std::vector<Edge> edges;
    int n;
    int e;
    Graph(int n, int e, std::vector<Edge> edges) : n(n), e(e), edges(edges) {}
    Graph(const std::string& path) {
        std::ifstream data;
        data.open(path);
        if (data.is_open()) {
            data >> n;
            for (int i = 0; i < n; i++) {
                Node node;
                data >> node.a;
                data >> node.b;
                nodes.push_back(node);
            }
            data >> e;
            for (int i = 0; i < e; i++) {
                Edge edge;
                data >> edge.x;
                data >> edge.y;
                data >> edge.weight;
                edges.push_back(edge);
            }

        }
        else throw std::errc::no_such_file_or_directory;
        data.close();
    }

    double sum() {
        double sum = 0.0;
        if (edges.empty()) return 0.0;
        for (const auto& edges : edges) {
            sum += edges.weight;
        }
        return sum;
    }

    std::string stats() {
        std::ostringstream s;
        s << "Nodes count (n) = " << n << "\n";
        s << "Edges count (e) = " << e << "\n";
        s << "Sum of all edges weight = " << sum() << "\n";
        return s.str();
    }

};

struct UnionFind {
    std::vector<int> parent;
    std::vector<int> rank;
    unsigned int cnt;

    UnionFind(const int n) {
        parent.resize(n);
        rank.resize(n);
        cnt = 0;

        for (int i = 0; i < n; i++) {
            parent.at(i) = i;
            rank.at(i) = 0;
        }
    }
    void union_uf(int i, int j) {
        parent.at(j) = i;
        rank.at(i)++;
    }
    void union_by_rank(int i, int j) {
        if (rank.at(i) < rank.at(j)) {
            parent.at(i) = j;
        }
        else if (rank.at(j) < rank.at(i)) {
            parent.at(j) = i;
        }
        else {
            parent.at(j) = i;
            rank.at(i)++;
        }
    }
    int find(int i) {
        ++cnt;
        if (i == parent.at(i)) return i;
        else return find(parent.at(i));
    }
    int find_path_compression(int i) {
        ++cnt;
        if (i == parent.at(i)) return i;
        int root = find_path_compression(parent.at(i));
        if (root != parent.at(i)) parent.at(i) = root;
        return root;
    }
};

void merge_edges(std::vector<Edge>& vec, std::vector<Edge>& l, std::vector<Edge>& r) {
    if (vec.size() < 2) return;
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int tmp = 0;
    while (i < l.size() && j < r.size()) {
        if (l.at(i).weight < r.at(j).weight) {
            vec.at(tmp) = l.at(i);
            i++;
        }
        else {
            vec.at(tmp) = r.at(j);
            j++;
        }
        tmp++;
    }
    while (i < l.size()) {
        vec.at(tmp) = l.at(i);
        i++;
        tmp++;
    }
    while (j < r.size()) {
        vec.at(tmp) = r.at(j);
        j++;
        tmp++;
    }
}
void mergeSort_edges(std::vector<Edge>& v) {
    if (v.size() < 2) return;
    unsigned int mid = v.size() / 2;
    std::vector<Edge> l(v.begin(), v.begin() + mid);
    std::vector<Edge> r(v.begin() + mid, v.end());
    mergeSort_edges(l);
    mergeSort_edges(r);
    merge_edges(v, l, r);
}

Graph MST_Kruskal(Graph graph, const bool u_flag, const bool f_flag) {

    std::vector<Edge> MST;
    UnionFind UF(graph.n);

    auto t1 = std::chrono::steady_clock::now();
    mergeSort_edges(graph.edges);
    auto t2 = std::chrono::steady_clock::now();
    std::cout << "Sorting time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms\n";

    t1 = std::chrono::steady_clock::now();
    for (const auto& edge : graph.edges) {
        int i_root, j_root;

        if (f_flag) {
            i_root = UF.find_path_compression(edge.x);
            j_root = UF.find_path_compression(edge.y);
        }
        else {
            i_root = UF.find(edge.x);
            j_root = UF.find(edge.y);
        }

        if (i_root != j_root) {
            MST.push_back(edge);
            if (u_flag) UF.union_by_rank(i_root, j_root);
            else UF.union_uf(i_root, j_root);
        }
    }
    t2 = std::chrono::steady_clock::now();


    std::cout << "Time of main loop: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms\n";
    std::cout << "Find count: " << UF.cnt << "\n";

    return Graph(graph.n, MST.size(), MST);
}

bool operator<(const Edge& e1, const Edge& e2) {
    return e1.weight < e2.weight;
}
bool operator>(const Edge& e1, const Edge& e2) {
    return e1.weight < e2.weight;
}