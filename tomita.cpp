#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <sstream>
#include <unordered_set>
// #include "/opt/homebrew/opt/libomp/include/omp.h"

using namespace std;

class Graph {
private:
    int n;
    vector<vector<int>> adj; 

public:
    Graph(int vertices) : n(vertices), adj(vertices) {}

    void addEdge(int u, int v) {
        // cout << "Adding edge " << u << " " << v << endl;
        if (u != v) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }

    void preprocessGraph() {
        for (auto& neighbors : adj) {
            sort(neighbors.begin(), neighbors.end());
            neighbors.erase(unique(neighbors.begin(), neighbors.end()), neighbors.end());
        }
    }

    const vector<int>& getNeighbors(int v) const {
        return adj[v];
    }

    int getVertexCount() const {
        return n;
    }
    vector<int> intersect(const vector<int>& a, const vector<int>& b) const {
        vector<int> result;
        auto it_a = a.begin();
        auto it_b = b.begin();
        
        while (it_a != a.end() && it_b != b.end()) {
            if (*it_a < *it_b) {
                ++it_a;
            } else if (*it_b < *it_a) {
                ++it_b;
            } else {
                result.push_back(*it_a);
                ++it_a;
                ++it_b;
            }
        }
        return result;
    }

    vector<int> getIntersection(const vector<int>& set, int q) const {
        return intersect(set, adj[q]);
    }

    int findPivot(const vector<int>& SUBG, const vector<int>& CAND) const {
        int u = SUBG[0];
        int max_size = 0;
        
        for (int v : SUBG) {
            vector<int> intersection = intersect(CAND, adj[v]);
            int size = intersection.size();
            
            if (size > max_size) {
                max_size = size;
                u = v;
            }
        }
        return u;
    }

    vector<int> getCandMinusGamma(const vector<int>& CAND, int u) const {
        vector<int> result;
        for (int v : CAND) {
            // cout << "Search: " << binary_search(adj[u].begin(), adj[u].end(), v) << " " << endl;
            if (!binary_search(adj[u].begin(), adj[u].end(), v)) {
                result.push_back(v);
            }
        }
        return result;
    }

    void EXPAND(vector<int>& SUBG, vector<int>& CAND, vector<int>& FINI, vector<int>& Q, 
               int& maxCliqueSize, int& totalCliques, vector<int>& cliqueSizes) {
        if (SUBG.empty()) {
            maxCliqueSize = max(maxCliqueSize, (int)Q.size());
            if (Q.size() > 1) {
                totalCliques++;
            }
            cliqueSizes[Q.size()]++;
            return;
        }

        int u = findPivot(SUBG, CAND);
        vector<int> ext_u = getCandMinusGamma(CAND, u);
        
        for (int q : ext_u) {
            Q.push_back(q);
            // cout << "Adding " << q << " to Q" << " ";
            vector<int> SUBGq = getIntersection(SUBG, q);
            vector<int> CANDq = getIntersection(CAND, q);
            vector<int> FINIq = getIntersection(FINI, q);
            
            EXPAND(SUBGq, CANDq, FINIq, Q, maxCliqueSize, totalCliques, cliqueSizes);
            
            Q.pop_back();
            auto it = lower_bound(CAND.begin(), CAND.end(), q);
            if (it != CAND.end() && *it == q) {
                CAND.erase(it);
            }
            auto insert_pos = upper_bound(FINI.begin(), FINI.end(), q);
            FINI.insert(insert_pos, q);
        }
    }

    void CLIQUES(int& maxCliqueSize, int& totalCliques, vector<int>& cliqueSizes) {
        vector<int> SUBG(n), CAND(n), Q, FINI;
        for (int i = 0; i < n; i++) SUBG[i] = CAND[i] = i;
        EXPAND(SUBG, CAND, FINI, Q, maxCliqueSize, totalCliques, cliqueSizes);
    }
};

Graph readGraph(const string& filename, int& n, int& m) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open file: " + filename);
    }
    string line;
    n = 0;
    m = 0;
    vector<pair<int, int>> edges;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#' || line[0] == '%') {
            if (line.find("Nodes:") != string::npos) {
                sscanf(line.c_str(), "# Nodes: %d Edges: %d", &n, &m);
            }
            continue;
        }
        
        int u, v;
        stringstream ss(line);
        if (ss >> u >> v) {
            edges.push_back({u, v});
            n = max(n, max(u, v) + 1);
        }
    }
    
    Graph G(n);
    for (const auto& edge : edges) {
        G.addEdge(edge.first, edge.second);
    }
    
    G.preprocessGraph();
    return G;
}

int main(int argc, char* argv[]) {
    string dataset = argc > 1 ? argv[1] : "wiki-Vote.txt";
    
    try {
        int n = 0, m = 0;
        cout << "Reading graph from " << dataset << "..." << endl;
        
        auto startLoadTime = chrono::high_resolution_clock::now();
        Graph G = readGraph(dataset, n, m);
        auto endLoadTime = chrono::high_resolution_clock::now();
        
        cout << "Graph loaded with " << n << " nodes" << endl;
        cout << "Loading time: " 
             << chrono::duration_cast<chrono::milliseconds>(endLoadTime - startLoadTime).count()
             << " ms" << endl;

        int maxCliqueSize = 0;
        int totalCliques = 0;
        vector<int> cliqueSizes(n+1, 0);

        cout << "Starting clique enumeration..." << endl;
        auto start = chrono::high_resolution_clock::now();
        G.CLIQUES(maxCliqueSize, totalCliques, cliqueSizes);
        auto end = chrono::high_resolution_clock::now();

        auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);

        cout << "Dataset: " << dataset << endl;
        cout << "Largest clique size: " << maxCliqueSize << endl;
        cout << "Total number of maximal cliques: " << totalCliques << endl;
        cout << "Execution time: " << elapsed.count() << " ms" << endl;

        cout << "Clique size distribution:" << endl;
        for (int i = 2; i <= n; i++) {
            if (cliqueSizes[i] > 0) {
                cout << i << ": " << cliqueSizes[i] << endl;
            }
        }
        string outputFilename = dataset + "-cliques.txt";
        ofstream outFile(outputFilename);
        if (outFile.is_open()) {
            outFile << "# Clique size distribution:" << endl;
            for (int i = 1; i <= n; i++) {
                if (cliqueSizes[i] > 0) {
                    outFile << i << ": " << cliqueSizes[i] << endl;
                }
            }
            outFile << "# Largest clique size: " << maxCliqueSize << endl;
            outFile << "# Total number of maximal cliques: " << totalCliques << endl;
            cout << "Results written to " << outputFilename << endl;
        }
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
