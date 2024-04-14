#include <gtest/gtest.h>

#include "function.h"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions)
{
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

TEST(StronglyConnectedComponents, BasicAssertions)
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

  std::vector<std::vector<int>> result = find_scc(edge_list, node_count);

  EXPECT_EQ(result, expected);
}
