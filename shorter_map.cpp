#include <iostream>
#include <utility>
#include <vector>
#include <stack>
#include <map>

using namespace std;

template <typename T>
void priority_dfs(map<T, vector<T>> &adjacency_list, map<T, bool> &visited, stack<T> &priority, T current)
{
    visited[current] = true;
    for (auto &neighbor : adjacency_list[current])
        if (!visited[neighbor])
            priority_dfs(adjacency_list, visited, priority, neighbor);
    priority.push(current);
}

template <typename T>
void dfs(map<T, vector<T>> &adjacency_list, map<T, bool> &visited, vector<T> &scc, T current)
{
    visited[current] = true;
    scc.push_back(current);
    for (auto &neighbor : adjacency_list[current])
        if (!visited[neighbor])
            dfs(adjacency_list, visited, scc, neighbor);
}

template <typename T>
vector<vector<T>> find_scc(vector<pair<T, T>> edge_list, int node_count)
{
    // Generate adjacency list
    map<T, vector<T>> adjacency_list;
    map<T, bool> visited;
    for (auto &edge : edge_list) {
        adjacency_list[edge.first].push_back(edge.second);
        visited[edge.first] = false;
    }

    // Generate reverse pre-ordering
    stack<T> priority;
    for (auto &edge : adjacency_list)
        if (!visited[edge.first])
            priority_dfs(adjacency_list, visited, priority, edge.first);

    // Generate reverse adjacency list
    map<T, vector<T>> reverse_adjacency_list;
    for (auto &edge : edge_list)
        reverse_adjacency_list[edge.second].push_back(edge.first);

    // Generate SCCs
    vector<vector<T>> sccs;
    for (auto &edge : visited) edge.second = false;
    while (!priority.empty())
    {
        T current = priority.top();
        priority.pop();
        if (!visited[current])
        {
            vector<T> scc;
            dfs(reverse_adjacency_list, visited, scc, current);
            sccs.push_back(scc);
        }
    }

    return sccs;
}

int main()
{
    int node_count = 5;
    // vector<pair<int, int>> edge_list = {
    //     {1, 3},
    //     {1, 4},
    //     {2, 1},
    //     {3, 2},
    //     {4, 5}};

    // vector<pair<int, int>> edge_list = {
    //     {8, 3},
    //     {8, 4},
    //     {2, 8},
    //     {3, 2},
    //     {4, 5}};
    vector<pair<char, char>> edge_list = {
        {'a', 'c'},
        {'a', 'd'},
        {'b', 'a'},
        {'c', 'b'},
        {'d', 'e'}};

    auto sccs = find_scc(edge_list, node_count);

    for (auto &scc : sccs)
    {
        for (auto &node : scc)
            cout << node << " ";
        cout << endl;
    }

    return 0;
}