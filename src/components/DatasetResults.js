import React from 'react';
import ResultsTable from './ResultsTable';
import { LineChart, Line, XAxis, YAxis, CartesianGrid, Tooltip, Legend, ResponsiveContainer, Label } from 'recharts';

const datasetInfo = {
  "Yeast": { vertices: 1116, edges: 2148 },
  "Netscience": { vertices: 1589, edges: 2742 },
  "As-733": { vertices: 1486, edges: 3172 },
  "Ca-HepTh": { vertices: 9877, edges: 25998 },
  "As-Caida": { vertices: 26475, edges: 106762 },
};

export default function DatasetResults({ title, results }) {
  return (
    <div className="mb-10">
      <h3 className="text-xl font-bold mb-4 text-green-700">{title}</h3>
      {Object.entries(results).map(([dataset, runs]) => {
        // Try to match dataset name to info (case-insensitive, ignore dashes)
        const infoKey = Object.keys(datasetInfo).find(
          key => key.replace(/[- ]/g, '').toLowerCase() === dataset.replace(/[- ]/g, '').toLowerCase()
        );
        const info = infoKey ? datasetInfo[infoKey] : null;
        return (
          <div key={dataset} className="mb-8">
            <h4 className="font-semibold text-lg mb-2 text-gray-800">{dataset}</h4>
            {info && (
              <div className="mb-2 text-sm text-gray-600">
                Vertices: <span className="font-mono">{info.vertices.toLocaleString()}</span> |
                Edges: <span className="font-mono">{info.edges.toLocaleString()}</span>
              </div>
            )}
            <div className="grid grid-cols-1 md:grid-cols-2 gap-4 mb-4">
              <div className="bg-white p-4 rounded shadow">
                <h5 className="font-semibold mb-2 text-green-700">Density vs h</h5>
                <ResponsiveContainer width="100%" height={200}>
                  <LineChart data={runs} margin={{ top: 10, right: 20, left: 0, bottom: 0 }}>
                    <CartesianGrid strokeDasharray="3 3" />
                    <XAxis dataKey="h">
                      <Label value="h" offset={-5} position="insideBottom" />
                    </XAxis>
                    <YAxis>
                      <Label value="Density" angle={-90} position="insideLeft" />
                    </YAxis>
                    <Tooltip />
                    <Legend />
                    <Line type="monotone" dataKey="density" stroke="#16a34a" strokeWidth={2} dot />
                  </LineChart>
                </ResponsiveContainer>
              </div>
              <div className="bg-white p-4 rounded shadow">
                <h5 className="font-semibold mb-2 text-green-700">Execution Time vs h</h5>
                <ResponsiveContainer width="100%" height={200}>
                  <LineChart data={runs} margin={{ top: 10, right: 20, left: 0, bottom: 0 }}>
                    <CartesianGrid strokeDasharray="3 3" />
                    <XAxis dataKey="h">
                      <Label value="h" offset={-5} position="insideBottom" />
                    </XAxis>
                    <YAxis>
                      <Label value="Time (s)" angle={-90} position="insideLeft" />
                    </YAxis>
                    <Tooltip />
                    <Legend />
                    <Line type="monotone" dataKey="time" stroke="#2563eb" strokeWidth={2} dot />
                  </LineChart>
                </ResponsiveContainer>
              </div>
            </div>
            <ResultsTable runs={runs} />
          </div>
        );
      })}
    </div>
  );
} 