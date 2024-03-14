#include <iostream>
#include <vector>
#include <utility>
#include <stack>

using namespace std;

vector<vector<int>> find_scc(vector<pair<int, int>> edge_list, int node_count)
{
    // Generate adjacency list
    vector<vector<int>> adjacency_list(node_count);
    for (auto &edge : edge_list)
        adjacency_list[edge.first - 1].push_back(edge.second - 1);

    // Generate reverse pre-ordering
    stack<int> priority;
    vector<bool> visited(node_count, false);
    stack<int> dfs_stack;
    for (int i = 0; i < node_count; i++)
    {
        if (!visited[i])
        {
            dfs_stack.push(i);
            while (!dfs_stack.empty())
            {
                int current = dfs_stack.top();
                if (!visited[current])
                {
                    visited[current] = true;
                    for (auto &neighbor : adjacency_list[current])
                        if (!visited[neighbor])
                            dfs_stack.push(neighbor);
                }
                else
                {
                    dfs_stack.pop();
                    priority.push(current);
                }
            }
        }
    }

    // Generate reverse adjacency list
    vector<vector<int>> reverse_adjacency_list(node_count);
    for (auto &edge : edge_list)
        reverse_adjacency_list[edge.second - 1].push_back(edge.first - 1);

    // Generate SCCs
    visited = vector<bool>(node_count, false);
    vector<vector<int>> sccs;
    while (!priority.empty())
    {
        int current = priority.top();
        priority.pop();
        if (!visited[current])
        {
            vector<int> scc;
            dfs_stack.push(current);
            while (!dfs_stack.empty())
            {
                int current = dfs_stack.top();
                dfs_stack.pop();
                if (!visited[current])
                {
                    visited[current] = true;
                    scc.push_back(current);
                    for (auto &neighbor : reverse_adjacency_list[current])
                        if (!visited[neighbor])
                            dfs_stack.push(neighbor);
                }
            }
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