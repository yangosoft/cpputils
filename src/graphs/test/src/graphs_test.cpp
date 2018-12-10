#include <limits.h>

#include <cpputils/graphs/graph.h>
#include <gtest/gtest.h>

#include <iostream>

namespace
{


TEST(ExampleGraphs, TestInstance)
{
    CppUtils::Graph<int> graph;


    CppUtils::GridWithWeights grid(10, 10);

    
    
    using L = CppUtils::GridLocation;
    
    grid.forests = std::set<CppUtils::GridLocation> {
        L{3, 4}, L{3, 5}, L{4, 1}, L{4, 2},
        L{4, 3}, L{4, 4}, L{4, 5}, L{4, 6},
        L{4, 7}, L{4, 8}, L{5, 1}, L{5, 2},
        L{5, 3}, L{5, 4}, L{5, 5}, L{5, 6},
        L{5, 7}, L{5, 8}, L{6, 2}, L{6, 3},
        L{6, 4}, L{6, 5}, L{6, 6}, L{6, 7},
        L{7, 3}, L{7, 4}, L{7, 5}
    };



    CppUtils::GridLocation start{1, 4};
    CppUtils::GridLocation goal{8, 5};
    std::map<CppUtils::GridLocation, CppUtils::GridLocation> mapCame;
    std::map<CppUtils::GridLocation, double> cost;
    AstarSearch(grid, start, goal, mapCame, cost);

    for ( auto e : mapCame )
    {
        std::cout << e.first.x << ", " << e.first.y << " -> " << e.second.x << ", " << e.second.y << std::endl;
    }
    
    std::cout << std::endl;
    for ( auto e : cost )
    {
        std::cout << e.first.x << ", " << e.first.y << " -> " << e.second << std::endl;
    }
    
    std::cout << std::endl;
    auto path = CppUtils::ReconstructPath(start, goal, mapCame);
     for ( auto e : path )
    {
        std::cout << e.x << ", " << e.y <<  std::endl;
    }
    

    EXPECT_TRUE(true);
}

};
