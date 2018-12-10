/* Original implementation came from https://www.redblobgames.com/pathfinding/a-star/implementation.html
 * This implementation has several changes.
 */

#ifndef __CPPUTILS_GRAPH_H
#define __CPPUTILS_GRAPH_H

#include <cstdint>

#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <vector>

namespace CppUtils
{

template<typename GraphIdType>
struct Graph {


    using NodeList = std::vector<GraphIdType>;
    using GraphType = std::map<GraphIdType, NodeList>;


    Graph() = default;
    GraphType edges;

    NodeList getNeighbors(GraphIdType id)
    {
        return edges[id];
    }

};

struct GridLocation {
    int32_t x;
    int32_t y;
};


struct SquareGrid {
    static std::array<GridLocation, 4> DIRS;

    int32_t m_width;
    int32_t m_height;
    std::set<GridLocation> m_walls;

    SquareGrid(int width_, int height_): m_width(width_), m_height(height_) {}

    bool inBounds(GridLocation id) const {
        return ((0 <= id.x) && (id.x < m_width) && (0 <= id.y) && (id.y < m_height));
    }

    bool passable(GridLocation id) const {
        return (m_walls.find(id) == m_walls.end());
    }

    using ListNeighbors = std::vector<GridLocation>;
    
    ListNeighbors getNeighbors(GridLocation id) const {
        ListNeighbors results;

        for (GridLocation dir : DIRS) {
            GridLocation next{id.x + dir.x, id.y + dir.y};
            if (inBounds(next) && passable(next)) {
                results.push_back(next);
            }
        }

        if ((id.x + id.y) % 2 == 0) {
            // aesthetic improvement on square grids
            std::reverse(results.begin(), results.end());
        }

        return results;
    }
};


template<typename T, typename priority_t>
struct PriorityQueue {

    using PQElement = std::pair<priority_t, T>;

    std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> m_elements;

    bool empty() const {
        return m_elements.empty();
    }

    void put(T item, priority_t priority) {
        m_elements.emplace(priority, item);
    }

    T get() {
        T best_item = m_elements.top().second;
        m_elements.pop();
        return best_item;
    }
};

std::array<GridLocation, 4> SquareGrid::DIRS = {GridLocation{1, 0}, GridLocation{0, -1}, GridLocation{-1, 0}, GridLocation{0, 1}};


bool operator == (GridLocation a, GridLocation b) {
    return a.x == b.x && a.y == b.y;
}

bool operator != (GridLocation a, GridLocation b) {
    return !(a == b);
}

bool operator < (GridLocation a, GridLocation b) {
    return std::tie(a.x, a.y) < std::tie(b.x, b.y);
}

template<typename Location, typename Graph>
void DijkstraSearch(Graph graph,  Location start,  Location goal,  std::map<Location, Location>& mapCameFrom,  std::map<Location, double>& mapCost)
{
    PriorityQueue<Location, double> frontier;
    frontier.put(start, 0);

    mapCameFrom[start] = start;
    mapCost[start] = 0;

    while (!frontier.empty()) {
        Location current = frontier.get();

        if (current == goal) {
            break;
        }

        auto lstNeighbors = graph.getNeighbors(current);
        std::for_each(lstNeighbors.begin(), lstNeighbors.end(), [&](auto next){
            double newCost = mapCost[current] + graph.cost(current, next);
            if ((mapCost.find(next) == mapCost.end()) || (newCost < mapCost[next])) {
                mapCost[next] = newCost;
                mapCameFrom[next] = current;
                frontier.put(next, newCost);
            }
        });
    }
}

double Heuristic(GridLocation a, GridLocation b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

template<typename Location, typename Graph>
void AstarSearch (Graph graph, Location start, Location goal,  std::map<Location, Location>& mapCame, std::map<Location, double>& mapCost)
{
    PriorityQueue<Location, double> frontier;
    frontier.put(start, 0);

    mapCame[start] = start;
    mapCost[start] = 0;

    while (!frontier.empty()) {
        Location current = frontier.get();

        if (current == goal) {
            break;
        }

        auto lstNeighbors = graph.getNeighbors(current);
        std::for_each(lstNeighbors.begin(), lstNeighbors.end(), [&](auto next){
            
            double newCost = mapCost[current] + graph.cost(current, next);
            if ((mapCost.find(next) == mapCost.end()) || (newCost < mapCost[next])) {
                mapCost[next] = newCost;
                double priority = newCost + Heuristic(next, goal);
                frontier.put(next, priority);
                mapCame[next] = current;
            }
            
        });
    }
}

struct GridWithWeights: SquareGrid {
    std::set<GridLocation> forests;
    GridWithWeights(int w, int h): SquareGrid(w, h) {}
    double cost(GridLocation from, GridLocation to) const {
        return forests.find(to) != forests.end()? 5 : 1;
    }
};




template<typename Location>
std::vector<Location> ReconstructPath(Location start, Location goal, std::map<Location, Location> mapCame) {
    std::vector<Location> path;
    Location current = goal;
    while (current != start) {
        path.push_back(current);
        current = mapCame[current];
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}

};
#endif /* __CPPUTILS_GRAPH_H */

