#include "functions.h"

#include <gtest/gtest.h>

namespace
{
  // Tests a graph with one multi-node SCC
  TEST(StronglyConnectedComponents, OneSCC)
  {
    int node_count = 5;
    std::vector<std::pair<int, int>> edge_list = {
        {1, 3},
        {1, 4},
        {2, 1},
        {3, 2},
        {4, 5}};

    std::vector<std::vector<int>> expected =
        {{1, 2, 3}, {4}, {5}};

    std::vector<std::vector<int>> result = find_scc(node_count, edge_list);

    EXPECT_EQ(result, expected);
  }

  // Tests a graph with multiple multi-node SCCs
  TEST(StronglyConnectedComponents, MultipleSCCs)
  {
    int node_count = 8;
    std::vector<std::pair<int, int>> edge_list = {
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

    std::vector<std::vector<int>> expected =
        {{5}, {6, 7, 8}, {1, 3, 2}, {4}};

    std::vector<std::vector<int>> result = find_scc(node_count, edge_list);

    EXPECT_EQ(result, expected);
  }

  // Tests a graph with no edges
  TEST(StronglyConnectedComponents, NoEdges)
  {
    int node_count = 6;
    std::vector<std::pair<int, int>> edge_list = {};

    std::vector<std::vector<int>> expected =
        {{6}, {5}, {4}, {3}, {2}, {1}};

    std::vector<std::vector<int>> result = find_scc(node_count, edge_list);

    EXPECT_EQ(result, expected);
  }

  // Tests a graph with disconnected components
  TEST(StronglyConnectedComponents, DisconnectedComponents)
  {
    int node_count = 7;
    std::vector<std::pair<int, int>> edge_list = {
        {1, 2},
        {2, 3},
        {3, 1},
        {4, 5},
        {5, 6},
        {6, 4}};

    std::vector<std::vector<int>> expected =
        {{7}, {4, 6, 5}, {1, 3, 2}};

    std::vector<std::vector<int>> result = find_scc(node_count, edge_list);

    EXPECT_EQ(result, expected);
  }

  // Tests a graph with no nodes
  TEST(StronglyConnectedComponents, NoNodes)
  {
    int node_count = 0;
    std::vector<std::pair<int, int>> edge_list = {};

    std::vector<std::vector<int>> expected = {};

    std::vector<std::vector<int>> result = find_scc(node_count, edge_list);

    EXPECT_EQ(result, expected);
  }

  // Demonstrates test failure
  TEST(StronglyConnectedComponents, Fail)
  {
    int node_count = 0;
    std::vector<std::pair<int, int>> edge_list = {};

    std::vector<std::vector<int>> expected =
        {{1}};

    std::vector<std::vector<int>> result = find_scc(node_count, edge_list);

    EXPECT_EQ(result, expected);
  }
}
