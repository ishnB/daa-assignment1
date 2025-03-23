#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <chrono>
#include <limits>
#include <iomanip>

using NodeId = int;

struct Graph {
    std::vector<std::vector<NodeId>> adj;
    int n; 

    Graph(int vertices) : n(vertices) {
        adj.resize(vertices);
    }

    void addEdge(NodeId u, NodeId v) {

        if (u != v && u >= 0 && u < n && v >= 0 && v < n) { 
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }

    void sortAndDeduplicateAdjacencies() {
        for (auto& neighbors : adj) {
            std::sort(neighbors.begin(), neighbors.end());

            auto last = std::unique(neighbors.begin(), neighbors.end());
            neighbors.erase(last, neighbors.end());
        }
    }

    static Graph loadFromFile(const std::string& filename, double& loadTime) {
        auto startLoad = std::chrono::high_resolution_clock::now();

        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return Graph(0);
        }

        std::string line;
        NodeId maxNodeId = -1;

        while (std::getline(file, line)) {

            if (line.empty() || line[0] == '#' || line[0] == '%') {
                continue;
            }

            std::istringstream iss(line);
            NodeId u, v;
            if (iss >> u >> v) {
                maxNodeId = std::max(maxNodeId, std::max(u, v));
            }
        }

        Graph graph(maxNodeId + 1);

        file.clear();
        file.seekg(0, std::ios::beg);

        int edgeCount = 0;
        while (std::getline(file, line)) {

            if (line.empty() || line[0] == '#' || line[0] == '%') {
                continue;
            }

            std::istringstream iss(line);
            NodeId u, v;
            if (iss >> u >> v) {
                graph.addEdge(u, v);
                edgeCount++;
            }
        }

        std::cout << "Loaded graph with " << graph.n << " vertices and " << edgeCount << " edges." << std::endl;

        graph.sortAndDeduplicateAdjacencies();

        auto endLoad = std::chrono::high_resolution_clock::now();
        loadTime = std::chrono::duration<double, std::milli>(endLoad - startLoad).count();

        return graph;
    }
};

class HybridCliqueSearcher {
public:
    HybridCliqueSearcher(const Graph& g) : G(g) {

        std::vector<std::pair<int, NodeId>> degreeMap;
        for (NodeId i = 0; i < G.n; ++i) {
            degreeMap.push_back({static_cast<int>(G.adj[i].size()), i});
        }

        std::sort(degreeMap.begin(), degreeMap.end());

        position.resize(G.n);
        vertexOrder.resize(G.n);
        for (int i = 0; i < G.n; ++i) {
            NodeId v = degreeMap[i].second;
            position[v] = i;
            vertexOrder[i] = v;
        }
    }

    std::vector<std::vector<NodeId>> findMaximalCliques(int maxSize = -1, int timeout = -1) {
        maximalCliques.clear();
        std::vector<NodeId> clique;
        std::vector<NodeId> candidates;

        for (NodeId v : vertexOrder) {
            if (!G.adj[v].empty()) {
                candidates.push_back(v);
            }
        }

        std::vector<NodeId> excluded;
        startTime = std::chrono::high_resolution_clock::now();
        this->maxSize = maxSize;
        this->timeoutMs = timeout;
        timedOut = false;

        hybridCliqueSearch(clique, candidates, excluded, 0);
        return maximalCliques;
    }

    int getTotalCliquesFound() const {
        return maximalCliques.size();
    }

    bool hasTimedOut() const {
        return timedOut;
    }

private:
    const Graph& G;
    std::vector<int> position;
    std::vector<NodeId> vertexOrder;
    std::vector<std::vector<NodeId>> maximalCliques;
    const int DENSE_THRESHOLD = 100; 
    int maxSize; 
    int timeoutMs; 
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    bool timedOut;

    bool isTimedOut() {
        if (timeoutMs <= 0) return false;
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
        if (elapsed >= timeoutMs) {
            timedOut = true;
            return true;
        }
        return false;
    }

    bool lexicoTest(const std::vector<NodeId>& clique, NodeId v) {
        for (NodeId u : clique) {
            if (position[u] > position[v]) {

                bool adjacent = std::binary_search(G.adj[v].begin(), G.adj[v].end(), u);
                if (!adjacent) {
                    return false;
                }
            }
        }
        return true;
    }

    NodeId choosePivot(const std::vector<NodeId>& candidates, const std::vector<NodeId>& excluded) {
        NodeId pivot = -1;
        int minPos = std::numeric_limits<int>::max();

        for (NodeId u : candidates) {
            if (position[u] < minPos) {
                minPos = position[u];
                pivot = u;
            }
        }

        for (NodeId u : excluded) {
            if (position[u] < minPos) {
                minPos = position[u];
                pivot = u;
            }
        }

        return pivot;
    }

    bool isAdjacent(NodeId u, NodeId v) {
        return std::binary_search(G.adj[u].begin(), G.adj[u].end(), v);
    }

    void computeNeighborsIntersection(NodeId v, const std::vector<NodeId>& vertices, std::vector<NodeId>& result) {
        result.clear();
        const auto& neighbors = G.adj[v];

        for (NodeId u : vertices) {
            if (std::binary_search(neighbors.begin(), neighbors.end(), u)) {
                result.push_back(u);
            }
        }
    }

    double calculateDensity(const std::vector<NodeId>& vertices) {
        if (vertices.size() <= 1) return 0.0;

        int edges = 0;
        for (size_t i = 0; i < vertices.size(); ++i) {
            for (size_t j = i + 1; j < vertices.size(); ++j) {
                if (isAdjacent(vertices[i], vertices[j])) {
                    edges++;
                }
            }
        }

        int maxPossibleEdges = vertices.size() * (vertices.size() - 1) / 2;
        return static_cast<double>(edges) / maxPossibleEdges;
    }

    bool isDense(const std::vector<NodeId>& candidates) {

        if (candidates.size() > DENSE_THRESHOLD) {
            return true;
        }

        return false;
    }

    void hybridCliqueSearch(std::vector<NodeId>& clique, std::vector<NodeId>& candidates, 
                           std::vector<NodeId>& excluded, int depth) {

        if (isTimedOut()) {
            return;
        }

        if (maxSize > 0 && static_cast<int>(clique.size()) >= maxSize) {
            maximalCliques.push_back(clique);

            if (maximalCliques.size() % 100000 == 0) {
                auto currentTime = std::chrono::high_resolution_clock::now();
                auto elapsed = std::chrono::duration<double, std::milli>(currentTime - startTime).count();
                std::cout << "Found " << maximalCliques.size() << " cliques so far. Time elapsed: " 
                          << std::fixed << std::setprecision(2) << elapsed << " ms" << std::endl;
            }

            return;
        }

        if (candidates.empty() && excluded.empty()) {
            maximalCliques.push_back(clique);

            // if (maximalCliques.size() % 10000 == 0) {
            //     auto currentTime = std::chrono::high_resolution_clock::now();
            //     auto elapsed = std::chrono::duration<double, std::milli>(currentTime - startTime).count();
            //     std::cout << "Found " << maximalCliques.size() << " cliques so far. Time elapsed: " 
            //               << std::fixed << std::setprecision(2) << elapsed << " ms" << std::endl;
            // }

            return;
        }

        bool useBK = isDense(candidates);

        if (useBK) {

            NodeId pivot = choosePivot(candidates, excluded);
            std::vector<NodeId> candidatesToProcess = candidates; 

            for (NodeId v : candidatesToProcess) {

                if (pivot != -1 && std::binary_search(G.adj[pivot].begin(), G.adj[pivot].end(), v)) {
                    continue;
                }

                clique.push_back(v);

                std::vector<NodeId> newCandidates, newExcluded;
                computeNeighborsIntersection(v, candidates, newCandidates);
                computeNeighborsIntersection(v, excluded, newExcluded);

                hybridCliqueSearch(clique, newCandidates, newExcluded, depth + 1);

                if (isTimedOut()) {
                    return;
                }

                clique.pop_back();
                candidates.erase(std::remove(candidates.begin(), candidates.end(), v), candidates.end());
                excluded.push_back(v);
            }
        } else {

            std::vector<NodeId> candidatesToProcess = candidates; 

            for (NodeId v : candidatesToProcess) {

                if (!lexicoTest(clique, v)) {
                    continue;
                }

                clique.push_back(v);

                std::vector<NodeId> newCandidates;
                computeNeighborsIntersection(v, candidates, newCandidates);

                std::vector<NodeId> newExcluded;
                computeNeighborsIntersection(v, excluded, newExcluded);

                hybridCliqueSearch(clique, newCandidates, newExcluded, depth + 1);

                if (isTimedOut()) {
                    return;
                }

                clique.pop_back();
                candidates.erase(std::remove(candidates.begin(), candidates.end(), v), candidates.end());
                excluded.push_back(v);
            }
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <graph_file> <output_file> [max_clique_size] [timeout_ms]" << std::endl;
        std::cerr << "  graph_file: Path to the graph file in email-Enron.txt format" << std::endl;
        std::cerr << "  output_file: Path to the output file for results" << std::endl;
        std::cerr << "  max_clique_size: Optional. Maximum size of cliques to find (-1 for no limit)" << std::endl;
        std::cerr << "  timeout_ms: Optional. Timeout in milliseconds (-1 for no timeout)" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::string outputFilename = argv[2];
    int maxSize = (argc > 3) ? std::stoi(argv[3]) : -1;
    int timeout = (argc > 4) ? std::stoi(argv[4]) : -1;

    double loadTime;
    std::cout << "Loading graph from " << filename << "..." << std::endl;
    Graph g = Graph::loadFromFile(filename, loadTime);
    if (g.n == 0) {
        std::cerr << "Failed to load graph or empty graph." << std::endl;
        return 1;
    }
    std::cout << "Graph loaded in " << loadTime << " ms." << std::endl;

    std::cout << "Finding maximal cliques..." << std::endl;
    HybridCliqueSearcher searcher(g);

    auto startCliques = std::chrono::high_resolution_clock::now();
    auto cliques = searcher.findMaximalCliques(maxSize, timeout);
    auto endCliques = std::chrono::high_resolution_clock::now();
    double cliqueTime = std::chrono::duration<double, std::milli>(endCliques - startCliques).count();

    std::unordered_map<int, int> sizeDistribution;
    for (const auto& clique : cliques) {
        sizeDistribution[clique.size()]++;
    }

    std::ofstream outFile(outputFilename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open output file " << outputFilename << std::endl;
        return 1;
    }

    outFile << "# Hybrid Maximal Clique Algorithm Results\n";
    outFile << "# Input graph: " << filename << "\n";
    outFile << "# Vertices: " << g.n << "\n";

    int totalEdges = 0;
    for (const auto& adj : g.adj) {
        totalEdges += adj.size();
    }
    outFile << "# Edges: " << totalEdges/2 << "\n"; 

    outFile << "# Time to load graph: " << std::fixed << std::setprecision(2) << loadTime << " ms\n";
    outFile << "# Time to find cliques: " << std::fixed << std::setprecision(2) << cliqueTime << " ms\n";

    if (searcher.hasTimedOut()) {
        outFile << "# Note: Algorithm timed out after " << timeout << " ms\n";
    }

    outFile << "\n# Total maximal cliques found: " << cliques.size() << "\n\n";

    outFile << "# Clique size distribution:\n";
    std::vector<std::pair<int, int>> sortedSizes(sizeDistribution.begin(), sizeDistribution.end());
    std::sort(sortedSizes.begin(), sortedSizes.end());

    for (const auto& [size, count] : sortedSizes) {
        outFile << "# Size " << size << ": " << count << " cliques\n";
    }
    outFile << "\n";

    outFile << "# List of all maximal cliques (one per line):\n";
    for (const auto& clique : cliques) {
        for (size_t i = 0; i < clique.size(); ++i) {
            outFile << clique[i];
            if (i < clique.size() - 1) {
                outFile << " ";
            }
        }
        outFile << "\n";
    }

    outFile.close();

    std::cout << "Found " << cliques.size() << " maximal cliques." << std::endl;
    std::cout << "Graph load time: " << loadTime << " ms" << std::endl;
    std::cout << "Clique finding time: " << cliqueTime << " ms" << std::endl;
    std::cout << "Results written to " << outputFilename << std::endl;

    return 0;
}