#include <iostream>
#include <utility>
#include <vector>
#include <stack>

using namespace std;

void priority_dfs(vector<vector<int>> &adjacency_list, vector<bool> &visited, stack<int> &priority, int current)
{
    visited[current] = true;
    for (auto &neighbor : adjacency_list[current])
        if (!visited[neighbor])
            priority_dfs(adjacency_list, visited, priority, neighbor);
    priority.push(current);
}

void dfs(vector<vector<int>> &adjacency_list, vector<bool> &visited, vector<int> &scc, int current)
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
    vector<vector<int>> adjacency_list(node_count);
    for (auto &edge : edge_list)
        adjacency_list[edge.first - 1].push_back(edge.second - 1);

    // Generate reverse pre-ordering
    stack<int> priority;
    vector<bool> visited(node_count, false);
    for (int i = 0; i < node_count; i++)
        if (!visited[i])
            priority_dfs(adjacency_list, visited, priority, i);

    // Generate reverse adjacency list
    vector<vector<int>> reverse_adjacency_list(node_count);
    for (auto &edge : edge_list)
        reverse_adjacency_list[edge.second - 1].push_back(edge.first - 1);

    // Generate SCCs
    vector<vector<int>> sccs;
    visited = vector<bool>(node_count, false);
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
    vector<pair<int, int>> edge_list = {
        {1, 3},
        {1, 4},
        {2, 1},
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