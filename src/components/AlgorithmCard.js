import React from 'react';

export default function AlgorithmCard({ name, description, timeComplexity, features }) {
  return (
    <div className="bg-white rounded-lg shadow-md p-6 hover:shadow-lg transition-shadow">
      <h3 className="text-xl font-bold text-green-700 mb-2">{name}</h3>
      <p className="text-gray-700 mb-4">{description}</p>
      <ul className="list-disc ml-5 text-gray-700">
        {features.map((feature, index) => (
          <li key={index} className="mb-1">{feature}</li>
        ))}
      </ul>
    </div>
  );
} 