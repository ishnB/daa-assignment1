# Densest Subgraph Discovery Algorithms - Frontend (React + Tailwind)

**Live Demo:** [https://daa-a2-grp57.netlify.app]

This project provides a modern React + Tailwind CSS frontend to showcase and compare the results of two densest subgraph discovery algorithms (Algorithm 1: Exact, and Algorithm 4: CoreExact) on various graph datasets.

## Features
- **Algorithm Overview**: Brief descriptions and complexity of Algorithm 1 and Algorithm 4.
- **Results Table**: For each dataset and h value (3, 4, 5), shows:
  - Densest subgraph size (number of nodes)
  - Density
  - Execution time
- **Visual Graphs**: Interactive line charts for Density vs h and Execution Time vs h (using [Recharts](https://recharts.org/)).
- **Dataset Info**: Number of vertices and edges for each dataset, displayed above results.
- **Responsive Design**: Looks great on both desktop and mobile (Tailwind CSS).
- **Easy Navigation**: Switch between algorithm overview and results with a single click.

## File Structure
```
frontend/
  public/
    index.html         # React entry point
  src/
    components/        # React components (AlgorithmCard, DatasetResults, ResultsTable)
    data/              # JSON result files (res1.json, res4.json)
    App.js             # Main app logic
    index.js           # React entry
    index.css          # Tailwind CSS imports
  package.json         # Project dependencies and scripts
  tailwind.config.js   # Tailwind config
  postcss.config.js    # PostCSS config
  README.md            # This file
```

## How to Run
1. **Install dependencies**:
   ```bash
   cd frontend
   npm install
   ```
2. **Start the development server**:
   ```bash
   npm start
   ```
   The app will open at [http://localhost:3000](http://localhost:3000).

## Data Format
- Results are loaded from `src/data/res1.json` and `src/data/res4.json`.
- Each file is a JSON object with dataset names as keys and an array of results for each h value.

Example:
```json
{
  "Netscience": [
    { "h": 3, "nodes": 20, "density": 57, "time": 0.0136 },
    { "h": 4, "nodes": 20, "density": 242.25, "time": 0.0104 },
    { "h": 5, "nodes": 20, "density": 775.2, "time": 0.0102 }
  ],
  ...
}
```

## Dataset Info
Displayed above each dataset's results:
| Name       | Vertices | Edges   |
|------------|---------:|--------:|
| Yeast      |   1,116  |  2,148  |
| Netscience |   1,589  |  2,742  |
| As-733     |   1,486  |  3,172  |
| Ca-HepTh   |   9,877  | 25,998  |
| As-Caida   |  26,475  |106,762  |

## Credits
- **Assignment**: DAA - Maximal Clique Enumeration (Group 57)
- **Frontend**: React, Tailwind CSS, Recharts
- **Design**: Inspired by modern dashboard UIs and assignment requirements

---

For any questions or improvements, feel free to contact the authors or submit a pull request! 