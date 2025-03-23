#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <chrono>

class Graph
{
private:
    int n;
    std::vector<std::vector<int>> adjacency;
    std::vector<std::unordered_set<int>> tempAdjacency;

public:
    Graph(int vertices) : n(vertices)
    {
        tempAdjacency.resize(n);
    }

    void addEdge(int u, int v)
    {
        if (u != v)
        {
            tempAdjacency[u].insert(v);
            tempAdjacency[v].insert(u);
        }
    }

    void finalize()
    {
        adjacency.resize(n);
        for (int i = 0; i < n; ++i)
        {
            adjacency[i].assign(tempAdjacency[i].begin(), tempAdjacency[i].end());
            std::sort(adjacency[i].begin(), adjacency[i].end());
        }
        tempAdjacency.clear();
    }

    const std::vector<int> &getNeighbors(int v) const
    {
        return adjacency[v];
    }

    int getVertexCount() const
    {
        return n;
    }

    std::vector<int> degeneracyOrdering() const
    {
        std::vector<int> ordering;
        ordering.reserve(n);
        std::vector<std::unordered_set<int>> remainingNeighbors(n);
        for (int i = 0; i < n; ++i)
        {
            remainingNeighbors[i] = {adjacency[i].begin(), adjacency[i].end()};
        }

        std::vector<int> degrees(n);
        for (int i = 0; i < n; ++i)
        {
            degrees[i] = remainingNeighbors[i].size();
        }

        std::vector<std::unordered_set<int>> buckets(n);
        for (int v = 0; v < n; ++v)
        {
            if (degrees[v] >= 0)
            {
                buckets[degrees[v]].insert(v);
            }
        }

        int currentDegree = 0;
        for (int i = 0; i < n; ++i)
        {
            while (currentDegree < n && buckets[currentDegree].empty())
            {
                ++currentDegree;
            }
            if (currentDegree >= n)
                break;

            auto it = buckets[currentDegree].begin();
            int v = *it;
            buckets[currentDegree].erase(it);
            ordering.push_back(v);

            for (int u : remainingNeighbors[v])
            {
                if (degrees[u] > currentDegree)
                {
                    buckets[degrees[u]].erase(u);
                    degrees[u]--;
                    buckets[degrees[u]].insert(u);
                    remainingNeighbors[u].erase(v);
                }
            }
            degrees[v] = -1;
        }
        return ordering;
    }
};

std::vector<int> intersect(const std::vector<int> &a, const std::vector<int> &b)
{
    std::vector<int> result;
    auto it_a = a.begin();
    auto it_b = b.begin();
    while (it_a != a.end() && it_b != b.end())
    {
        if (*it_a < *it_b)
            ++it_a;
        else if (*it_b < *it_a)
            ++it_b;
        else
        {
            result.push_back(*it_a);
            ++it_a;
            ++it_b;
        }
    }
    return result;
}

void BronKerboschPivot(const Graph &graph,
                       std::vector<int> P,
                       std::vector<int> R,
                       std::vector<int> X,
                       std::vector<std::vector<int>> &maximalCliques)
{
    if (P.empty() && X.empty())
    {
        if (R.size() >= 2)
        {
            maximalCliques.push_back(R);
        }
        return;
    }

    std::vector<int> PUX;
    PUX.reserve(P.size() + X.size());
    std::merge(P.begin(), P.end(), X.begin(), X.end(), std::back_inserter(PUX));

    if (PUX.empty())
        return;

    int pivot = PUX[0];
    size_t max_intersection = 0;

    for (int u : PUX)
    {
        const auto &neighbors = graph.getNeighbors(u);
        std::vector<int> intersection = intersect(P, neighbors);
        if (intersection.size() > max_intersection)
        {
            max_intersection = intersection.size();
            pivot = u;
        }
    }

    const auto &pivotNeighbors = graph.getNeighbors(pivot);
    std::vector<int> P_diff;
    std::set_difference(P.begin(), P.end(), pivotNeighbors.begin(), pivotNeighbors.end(),
                        std::back_inserter(P_diff));

    for (int v : P_diff)
    {
        std::vector<int> newR = R;
        auto insert_pos = std::lower_bound(newR.begin(), newR.end(), v);
        newR.insert(insert_pos, v);

        const auto &vNeighbors = graph.getNeighbors(v);
        std::vector<int> newP = intersect(P, vNeighbors);
        std::vector<int> newX = intersect(X, vNeighbors);

        BronKerboschPivot(graph, std::move(newP), std::move(newR), std::move(newX), maximalCliques);

        auto p_it = std::lower_bound(P.begin(), P.end(), v);
        if (p_it != P.end() && *p_it == v)
            P.erase(p_it);
        X.insert(std::upper_bound(X.begin(), X.end(), v), v);
    }
}

std::vector<std::vector<int>> BronKerboschDegeneracy(const Graph &graph)
{
    std::vector<std::vector<int>> maximalCliques;
    int n = graph.getVertexCount();
    auto ordering = graph.degeneracyOrdering();

    std::vector<int> position(n);
    for (int i = 0; i < n; ++i)
    {
        position[ordering[i]] = i;
    }

    std::vector<std::vector<int>> laterNeighbors(n), earlierNeighbors(n);
    for (int i = 0; i < n; ++i)
    {
        int v = ordering[i];
        const auto &neighbors = graph.getNeighbors(v);
        for (int u : neighbors)
        {
            if (position[u] > i)
            {
                laterNeighbors[v].push_back(u);
            }
            else
            {
                earlierNeighbors[v].push_back(u);
            }
        }
        std::sort(laterNeighbors[v].begin(), laterNeighbors[v].end());
        std::sort(earlierNeighbors[v].begin(), earlierNeighbors[v].end());
    }

    for (int i = 0; i < n; ++i)
    {
        int vi = ordering[i];
        std::vector<int> P = laterNeighbors[vi];
        std::vector<int> X = earlierNeighbors[vi];
        BronKerboschPivot(graph, P, {vi}, X, maximalCliques);
    }

    return maximalCliques;
}

Graph loadGraphFromEdgeList(const std::string &filename, bool zeroIndexed = true)
{
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Could not open file: " + filename);

    std::vector<std::pair<int, int>> edges;
    int maxVertex = -1;
    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#' || line[0] == '%')
            continue;
        std::istringstream iss(line);
        int u, v;
        if (iss >> u >> v)
        {
            if (!zeroIndexed)
            {
                u--;
                v--;
            }
            edges.push_back({u, v});
            maxVertex = std::max(maxVertex, std::max(u, v));
        }
    }

    Graph graph(maxVertex + 1);
    for (const auto &edge : edges)
        graph.addEdge(edge.first, edge.second);
    graph.finalize();
    return graph;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <edge_list_file> [zero_indexed=1]" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    bool zeroIndexed = (argc > 2) ? (std::string(argv[2]) == "1") : true;

    try
    {
        // Timing data collection
        auto startLoad = std::chrono::high_resolution_clock::now();
        Graph graph = loadGraphFromEdgeList(filename, zeroIndexed);
        auto endLoad = std::chrono::high_resolution_clock::now();

        auto startAlgo = std::chrono::high_resolution_clock::now();
        std::vector<std::vector<int>> maximalCliques = BronKerboschDegeneracy(graph);
        auto endAlgo = std::chrono::high_resolution_clock::now();

        // Process results
        std::vector<int> cliqueSizes;
        std::unordered_map<int, int> sizeDistribution;
        cliqueSizes.reserve(maximalCliques.size());

        for (const auto &clique : maximalCliques)
        {
            int size = clique.size();
            cliqueSizes.push_back(size);
            sizeDistribution[size]++;
        }

        std::sort(cliqueSizes.begin(), cliqueSizes.end(), std::greater<int>());

        // Output results
        std::cout << "\n=== Analysis Results ===" << std::endl;
        std::cout << "Total vertices: " << graph.getVertexCount() << std::endl;
        std::cout << "Total maximal cliques: " << maximalCliques.size() << std::endl;
        std::cout << "Largest clique size: " << (cliqueSizes.empty() ? 0 : cliqueSizes[0]) << std::endl;

        // Timing information
        auto load_time = std::chrono::duration_cast<std::chrono::milliseconds>(endLoad - startLoad);
        auto algo_time = std::chrono::duration_cast<std::chrono::milliseconds>(endAlgo - startAlgo);
        std::cout << "\n=== Execution Times ===" << std::endl;
        std::cout << "Data loading time (ms): " << load_time.count() << std::endl;
        std::cout << "Algorithm time (ms): " << algo_time.count() << std::endl;

        // Size distribution
        std::cout << "\n=== Clique Size Distribution ===" << std::endl;
        std::vector<std::pair<int, int>> distVec(sizeDistribution.begin(), sizeDistribution.end());
        std::sort(distVec.begin(), distVec.end());
        for (const auto &entry : distVec)
        {
            std::cout << "Size " << entry.first << ": " << entry.second << " cliques" << std::endl;
        }

        // Top cliques
        std::cout << "\nTop 10 largest clique sizes:" << std::endl;
        size_t printCount = std::min<size_t>(10, cliqueSizes.size());
        for (size_t i = 0; i < printCount; ++i)
            std::cout << cliqueSizes[i] << " ";
        std::cout << std::endl;

        // File output
        std::string outputFilename = filename + ".cliques.txt";
        std::ofstream outFile(outputFilename);
        if (outFile.is_open())
        {
            for (const auto &clique : maximalCliques)
            {
                for (int v : clique)
                    outFile << v << " ";
                outFile << std::endl;
            }
            std::cout << "\nCliques written to " << outputFilename << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}