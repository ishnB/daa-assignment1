import React from 'react';

export default function ResultsTable({ runs }) {
  return (
    <div className="overflow-x-auto">
      <table className="min-w-full bg-white shadow rounded-lg overflow-hidden">
        <thead className="bg-green-50">
          <tr>
            <th className="px-4 py-3 text-left text-sm font-semibold text-green-800">h</th>
            <th className="px-4 py-3 text-left text-sm font-semibold text-green-800">Nodes</th>
            <th className="px-4 py-3 text-left text-sm font-semibold text-green-800">Density</th>
            <th className="px-4 py-3 text-left text-sm font-semibold text-green-800">Execution Time (s)</th>
          </tr>
        </thead>
        <tbody className="divide-y divide-gray-200">
          {runs.map((run, i) => (
            <tr key={i} className="hover:bg-gray-50">
              <td className="px-4 py-3 text-sm text-gray-700">{run.h}</td>
              <td className="px-4 py-3 text-sm text-gray-700">{run.nodes}</td>
              <td className="px-4 py-3 text-sm text-gray-700">{run.density.toFixed(4)}</td>
              <td className="px-4 py-3 text-sm text-gray-700">{run.time.toFixed(6)}</td>
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  );
} 