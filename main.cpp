#include <iostream>
#include <utility>
#include <vector>
#include <stack>

using namespace std;

/**
 * Performs a depth-first search (DFS) on a graph represented by an adjacency list,
 * and pushes the visited nodes onto a stack in a priority order.
 *
 * @param adjacency_list The adjacency list representation of the graph.
 * @param visited A boolean vector indicating whether a node has been visited or not.
 * @param priority A stack to store the visited nodes in a priority order.
 * @param current The current node being visited.
 */
void priority_dfs(vector<vector<int>> &adjacency_list, vector<bool> &visited, stack<int> &priority, int current)
{
    visited[current] = true;
    for (auto &neighbor : adjacency_list[current])
        if (!visited[neighbor])
            priority_dfs(adjacency_list, visited, priority, neighbor);
    priority.push(current);
}

/**
 * Performs a depth-first search (DFS) on the given adjacency list,
 * and generates a vector of nodes in the strongly connected component (SCC).
 *
 * @param adjacency_list The adjacency list representing the graph.
 * @param visited A vector of boolean values indicating whether a node has been visited or not.
 * @param scc A vector to store the nodes in the strongly connected component (SCC).
 * @param current The current node being visited.
 */
void dfs(vector<vector<int>> &adjacency_list, vector<bool> &visited, vector<int> &scc, int current)
{
    visited[current] = true;
    scc.push_back(current);
    for (auto &neighbor : adjacency_list[current])
        if (!visited[neighbor])
            dfs(adjacency_list, visited, scc, neighbor);
}

/**
 * Finds the strongly connected components (SCCs) in a directed graph.
 *
 * @param edge_list The list of edges in the graph represented as pairs of nodes.
 * The first element of the pair is the source node and the second element is the destination node.
 * Nodes are 1-indexed and should be in the range [1, node_count].
 * @param node_count The total number of nodes in the graph.
 * @return A vector of vectors, where each inner vector represents a SCC.
 */
vector<vector<int>> find_scc(vector<pair<int, int>> edge_list, int node_count)
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
            priority_dfs(adjacency_list, visited, priority, i);

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
            dfs(reverse_adjacency_list, visited, scc, current);
            sccs.push_back(scc);
        }
    }

    return sccs;
}

void print_mismatch(vector<vector<int>> &expected, vector<vector<int>> &got)
{
    cout << "Expected:" << endl;
    for (auto &scc : expected)
    {
        for (auto &node : scc)
            cout << node << " ";
        cout << endl;
    }

    cout << "Got:" << endl;
    for (auto &scc : got)
    {
        for (auto &node : scc)
            cout << node << " ";
        cout << endl;
    }
}

int main()
{
    // --------------- Test case 1 ---------------
    int node_count = 5;
    vector<pair<int, int>> edge_list = {
        {1, 3},
        {1, 4},
        {2, 1},
        {3, 2},
        {4, 5}};

    vector<vector<int>> sccs = find_scc(edge_list, node_count);

    vector<vector<int>> expected_sccs = {
        {1, 2, 3},
        {4},
        {5}};

    if (sccs == expected_sccs)
        cout << "1st test case passed" << endl;
    else
    {
        cout << "1st test case failed" << endl;

        print_mismatch(expected_sccs, sccs);
    }

    // --------------- Test case 2 ---------------
    node_count = 8;
    edge_list = {
        {1, 2},
        {2, 3},
        {2, 4},
        {3, 1},
        {3, 4},
        {5, 6},
        {5, 7},
        {6, 8},
        {7, 6},
        {8, 7}};

    sccs = find_scc(edge_list, node_count);

    expected_sccs = {
        {5},
        {6, 7, 8},
        {1, 3, 2},
        {4},
    };

    if (sccs == expected_sccs)
        cout << "2nd test case passed" << endl;
    else
    {
        cout << "2nd test case failed" << endl;

        print_mismatch(expected_sccs, sccs);
    }

    // --------------- Test case 3 ---------------
    node_count = 6;
    edge_list = {};

    sccs = find_scc(edge_list, node_count);

    expected_sccs = {
        {6},
        {5},
        {4},
        {3},
        {2},
        {1}
    };

    if (sccs == expected_sccs)
        cout << "3rd test case passed" << endl;
    else
    {
        cout << "3rd test case failed" << endl;

        print_mismatch(expected_sccs, sccs);
    }

    return 0;
}