# Densest Subgraph Discovery Algorithms - Frontend

This project provides a clean, modern HTML+CSS frontend to showcase and compare the results of two densest subgraph discovery algorithms (Algorithm 1: Exact, and Algorithm 4: CoreExact) on various graph datasets.

## Features
- **Algorithm Overview**: Brief descriptions and complexity of Algorithm 1 and Algorithm 4.
- **Results Table**: For each dataset and h value (3, 4, 5), shows:
  - Densest subgraph size (number of nodes)
  - Density
  - Execution time
- **Responsive Design**: Looks great on both desktop and mobile.
- **Easy Navigation**: Switch between algorithm overview and results with a single click.

## File Structure
```
frontend/
  index.html      # Main HTML file (landing page, algorithms, results)
  style.css       # Modern, responsive CSS styling
  res1.json       # Results for Algorithm 1 (Exact)
  res4.json       # Results for Algorithm 4 (CoreExact)
  README.md       # This file
```

## How to Run
1. **Clone or Download** this repository/folder.
2. **Open `index.html`** in your web browser (no server required, just double-click or drag into browser).
   - Make sure `res1.json` and `res4.json` are in the same folder as `index.html`.
3. **Navigate** using the "Algorithms" and "Results" buttons at the top.

## Data Format
- Results are loaded from `res1.json` and `res4.json`.
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

## Credits
- **Assignment**: DAA - Maximal Clique Enumeration (Group 57)
- **Frontend**: HTML, CSS, and vanilla JS (no frameworks required)
- **Design**: Inspired by modern dashboard UIs and your assignment requirements

---

For any questions or improvements, feel free to contact the authors or submit a pull request! 