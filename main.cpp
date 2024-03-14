#include <iostream>
#include <utility>
#include <vector>
#include <stack>

#include <iomanip>

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
vector<vector<int>> find_scc(vector<pair<int, int>> edge_list,
                             int node_count)
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

// --------------------------------- Testing ---------------------------------

/**
 * Executes a test case for finding strongly connected components (SCC).
 *
 * @param id The ID of the test case.
 * @param description The description of the test case.
 * @param node_count The number of nodes in the graph.
 * @param edge_list The list of edges in the graph represented as pairs of nodes.
 * @param expected_output The expected output, which is a list of SCCs represented as vectors of nodes.
 */
void test_case(
    int id,
    string description,
    int node_count,
    vector<pair<int, int>> edge_list,
    vector<vector<int>> expected_output)
{
    vector<vector<int>> output = find_scc(edge_list, node_count);
    cout << "Test case " << id << " - " << setw(40) << left << description;
    if (output == expected_output)
        cout << "PASSED✅" << endl;
    else
    {
        cout << "FAILED❌" << endl;

        cout << "Expected: ";
        for (auto &scc : expected_output)
        {
            cout << "[";
            for (auto &node : scc)
                cout << node << " ";
            cout << "]";
        }
        cout << endl;

        cout << "Got: ";
        for (auto &scc : output)
        {
            cout << "[";
            for (auto &node : scc)
                cout << node << " ";
            cout << "]";
        }
        cout << endl;
    }
}

int main()
{
    test_case(1, "A graph with one multi-node SCC",
              5,
              {{1, 3}, {1, 4}, {2, 1}, {3, 2}, {4, 5}},
              {{1, 2, 3}, {4}, {5}});

    test_case(2, "A graph with multiple multi-node SCCs",
              8,
              {{1, 2}, {2, 3}, {2, 4}, {3, 1}, {3, 4}, {5, 6}, {5, 7}, {6, 8}, {7, 6}, {8, 7}},
              {{5}, {6, 7, 8}, {1, 3, 2}, {4}});

    test_case(3, "A graph with no edges",
              6,
              {},
              {{6}, {5}, {4}, {3}, {2}, {1}});

    test_case(4, "A graph with disconnected components",
              7,
              {{1, 2}, {2, 3}, {3, 1}, {4, 5}, {5, 6}, {6, 4}},
              {{7}, {4, 6, 5}, {1, 3, 2}});

    test_case(5, "A graph with no edges",
              6,
              {},
              {{6}, {5}, {4}, {3}, {2}, {1}});

    test_case(6, "A graph with no nodes",
              0,
              {},
              {});

    return 0;
}