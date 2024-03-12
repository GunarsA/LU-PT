#include <iostream>
#include <utility>
#include <vector>
#include <stack>
#include <map>

using namespace std;

void priority_dfs(map<int, vector<int>> &adjacency_list, map<int, bool> &visited, stack<int> &priority, int current)
{
    visited[current] = true;
    for (auto &neighbor : adjacency_list[current])
        if (!visited[neighbor])
            priority_dfs(adjacency_list, visited, priority, neighbor);
    priority.push(current);
}

void dfs(map<int, vector<int>> &adjacency_list, map<int, bool> &visited, vector<int> &scc, int current)
{
    visited[current] = true;
    scc.push_back(current);
    for (auto &neighbor : adjacency_list[current])
        if (!visited[neighbor])
            dfs(adjacency_list, visited, scc, neighbor);
}

vector<vector<int>> find_scc(vector<pair<int, int>> edge_list, int node_count)
{
    // Generate adjacency list
    map<int, vector<int>> adjacency_list;
    map<int, bool> visited;
    for (auto &edge : edge_list) {
        adjacency_list[edge.first].push_back(edge.second);
        visited[edge.first] = false;
    }

    // Generate reverse pre-ordering
    stack<int> priority;
    for (auto &edge : adjacency_list)
        if (!visited[edge.first])
            priority_dfs(adjacency_list, visited, priority, edge.first);

    // Generate reverse adjacency list
    map<int, vector<int>> reverse_adjacency_list;
    for (auto &edge : edge_list)
        reverse_adjacency_list[edge.second].push_back(edge.first);

    // Generate SCCs
    vector<vector<int>> sccs;
    for (auto &edge : visited) edge.second = false;
    while (!priority.empty())
    {
        int current = priority.top();
        priority.pop();
        if (!visited[current])
        {
            vector<int> scc;
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

    vector<pair<int, int>> edge_list = {
        {8, 3},
        {8, 4},
        {2, 8},
        {3, 2},
        {4, 5}};

    auto sccs = find_scc(edge_list, node_count);

    for (auto &scc : sccs)
    {
        for (auto &node : scc)
            cout << node << " ";
        cout << endl;
    }

    return 0;
}