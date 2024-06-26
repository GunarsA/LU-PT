#include <iostream>
#include <utility>
#include <vector>
#include <stack>

using namespace std;

// --------------------------------- Algorithm ---------------------------------

/**
 * A helper function that performs a depth-first search (DFS) on a graph represented by an adjacency list,
 * and pushes the visited nodes onto a stack in a priority order.
 *
 * @param adjacency_list The adjacency list representation of the graph.
 * @param visited A boolean vector indicating whether a node has been visited or not.
 * @param priority A stack to store the visited nodes in a priority order.
 * @param current The current node being visited.
 */
void _priority_dfs(vector<vector<int>> &adjacency_list,
                   vector<bool> &visited,
                   stack<int> &priority,
                   int current)
{
    visited[current] = true;
    for (auto &neighbor : adjacency_list[current])
        if (!visited[neighbor])
            _priority_dfs(adjacency_list, visited, priority, neighbor);
    priority.push(current);
}

/**
 * A helper function that performs a depth-first search (DFS) on the given adjacency list,
 * and generates a vector of nodes in the strongly connected component (SCC).
 *
 * @param adjacency_list The adjacency list representing the graph.
 * @param visited A vector of boolean values indicating whether a node has been visited or not.
 * @param scc A vector to store the nodes in the strongly connected component (SCC).
 * @param current The current node being visited.
 */
void _dfs(vector<vector<int>> &adjacency_list,
          vector<bool> &visited,
          vector<int> &scc,
          int current)
{
    visited[current] = true;
    scc.push_back(current);
    for (auto &neighbor : adjacency_list[current])
        if (!visited[neighbor])
            _dfs(adjacency_list, visited, scc, neighbor);
}

/**
 * The main function that finds the strongly connected components (SCCs) in a directed graph.
 *
 * @param edge_list The list of edges in the graph represented as pairs of nodes.
 * The first element of the pair is the source node and the second element is the destination node.
 * Nodes are 1-indexed and should be in the range [1, node_count].
 * @param node_count The total number of nodes in the graph.
 * @return A vector of vectors, where each inner vector represents a SCC.
 */
vector<vector<int>> find_scc(int node_count,
                             vector<pair<int, int>> edge_list)
{
    // Generate adjacency list
    vector<vector<int>> adjacency_list(node_count + 1);
    for (auto &edge : edge_list)
        adjacency_list[edge.first].push_back(edge.second);

    // Generate reverse pre-ordering
    stack<int> priority;
    vector<bool> visited(node_count, false);
    for (int i = 1; i <= node_count; i++)
        if (!visited[i])
            _priority_dfs(adjacency_list, visited, priority, i);

    // Generate reverse adjacency list
    vector<vector<int>> reverse_adjacency_list(node_count + 1);
    for (auto &edge : edge_list)
        reverse_adjacency_list[edge.second].push_back(edge.first);

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
            _dfs(reverse_adjacency_list, visited, scc, current);
            sccs.push_back(scc);
        }
    }

    return sccs;
}