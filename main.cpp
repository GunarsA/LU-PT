#include "function.h"

#include <iomanip>

using namespace std;

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
    vector<vector<int>> output = find_scc(node_count, edge_list);
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

    test_case(5, "A graph with no nodes",
              0,
              {},
              {});

    return 0;
}