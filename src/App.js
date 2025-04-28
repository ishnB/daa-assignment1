import React, { useState } from 'react';
import AlgorithmCard from './components/AlgorithmCard';
import DatasetResults from './components/DatasetResults';
import res1 from './data/res1.json';
import res4 from './data/res4.json';

function App() {
  const [activeSection, setActiveSection] = useState('algorithms');

  return (
    <div className="min-h-screen bg-gray-50 text-gray-900">
      <header className="py-8 text-center bg-white shadow">
        <h1 className="text-4xl font-bold mb-2">Densest Subgraph Discovery Algorithms</h1>
        <p className="text-lg text-gray-600">Comparison of various graph algorithms for finding densest subgraphs</p>
        <nav className="mt-4">
          <button 
            onClick={() => setActiveSection('algorithms')}
            className={`px-4 py-2 mx-2 rounded-md ${activeSection === 'algorithms' ? 'bg-green-600 text-white' : 'bg-gray-200 text-gray-800'}`}
          >
            Algorithms
          </button>
          <button 
            onClick={() => setActiveSection('results')}
            className={`px-4 py-2 mx-2 rounded-md ${activeSection === 'results' ? 'bg-green-600 text-white' : 'bg-gray-200 text-gray-800'}`}
          >
            Results
          </button>
        </nav>
      </header>

      <main className="max-w-5xl mx-auto p-6">
        {activeSection === 'algorithms' && (
          <section className="mb-10">
            <h2 className="text-2xl font-semibold mb-4">Algorithms Overview</h2>
            <div className="grid grid-cols-1 md:grid-cols-2 gap-6">
              <AlgorithmCard
                name="Algorithm 1 (Exact)"
                description="A flow-based exact algorithm for densest subgraph with h-cliques."
                features={[
                  "Binary search with flow network",
                  "Handles h-cliques",
                  "Guaranteed optimal"
                ]}
              />
              <AlgorithmCard
                name="Algorithm 4 (CoreExact)"
                description="A core-based exact algorithm with pruning and tighter bounds."
                features={[
                  "Uses core decomposition",
                  "Prunes search space",
                  "Much faster for large graphs"
                ]}
              />
            </div>
          </section>
        )}

        {activeSection === 'results' && (
          <section>
            <h2 className="text-2xl font-semibold mb-4">Results</h2>
            <div className="grid grid-cols-1 md:grid-cols-2 gap-8">
              <DatasetResults
                title="Algorithm 1 Results"
                results={res1}
              />
              <DatasetResults
                title="Algorithm 4 Results"
                results={res4}
              />
            </div>
          </section>
        )}
      </main>

      <footer className="text-center text-gray-500 py-4 mt-8">
        <p>DAA Assignment &mdash;Densest Subgraph Discovery Algorithms &copy; 2025</p>
      </footer>
    </div>
  );
}

export default App; 