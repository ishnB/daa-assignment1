# CS F364 DAA Assignment - Group 57

## [Website Link](https://daa-a1-grp57.netlify.app)

## Datasets

The datasets used in this project are available on the Stanford website:

1. [Email-Enron](https://snap.stanford.edu/data/email-Enron.html)
2. [AS-Skitter](https://snap.stanford.edu/data/as-Skitter.html)
3. [Wiki-Vote](https://snap.stanford.edu/data/wiki-Vote.html)

## Execution Instructions

### Bron-Kerbosch Degeneracy

#### Compilation
```sh
g++ -O3 <filename>.cpp -o <output_filename>.out
g++-14 -O3 -o bronkerbosch-final bronkerbosch-final.cpp
```

#### Execution
```sh
./bronkerbosch-final <textfilename.txt>
```

For faster execution using OpenMP:
```sh
g++-14 -O3 -fopenmp -o bronkerbosch-final bronkerbosch-final.cpp
```

### Arboricity

#### Compilation
```sh
g++-14 -std=c++17 -O3 -Wall -Wextra -o chiba_arbocity chiba_arbocity.cpp
```

#### Execution
```sh
./chiba_arbocity <dataset.txt> <output_file.txt> <timeout in ms>
```
To turn off the timeout, set it to `-1`:
```sh
./chiba_arbocity wiki-Vote.txt max_cliques.txt -1
```

### Tomita

#### Compilation
```sh
g++-14 -std=c++17 -O3 -o tomita tomita.cpp
```

#### Execution
```sh
./tomita <dataset.txt>
```

## Output Details

### Bron-Kerbosch (Sample Output)
```
=== Analysis Results ===
Total vertices: 8298
Total maximal cliques: 459002
Largest clique size: 17

=== Execution Times ===
Data loading time (ms): 50
Algorithm time (ms): 1710

=== Clique Size Distribution ===
Size 2: 8655 cliques
Size 3: 13718 cliques
...
Size 17: 23 cliques

Top 10 largest clique sizes:
17 17 17 17 17 17 17 17 17 17 
Cliques written to wiki-vote.txt.cliques.txt
```

### Tomita (Sample Output)
```
Reading graph from wiki-Vote.txt...
Graph loaded with 8298 nodes
Loading time: 26 ms
Starting clique enumeration...
Dataset: wiki-Vote.txt
Largest clique size: 17
Total number of maximal cliques: 459002
Execution time: 1897 ms
Clique size distribution:
2: 8655
3: 13718
...
17: 23
Results written to wiki-Vote-cliques.txt
```

### Arboricity (Sample Output)
```
Loading graph from email-Enron.txt...
Loaded graph with 36692 vertices and 367662 edges.
Graph loaded in 111.12 ms.
Finding maximal cliques...
Found 226859 maximal cliques.
Graph load time: 111.12 ms
Clique finding time: 44175.2 ms
Results written to max_cliques.txt
```

## Contributors

1. **Angad Bawa**  
   - Implemented the Arboricity-based algorithm based on the Chiba et al. (1985) paper.
   - Contributed to the report and analysis.

2. **Vibhanshu Bhagat**  
   - Implemented the Bron-Kerbosch algorithm based on the Eppstein et al. (2010) paper.
   - Contributed to the report and analysis.

3. **Ishan Barpanda**  
   - Implemented the CLIQUES algorithm based on the Tomita et al. (2006) paper.
   - Developed the project website.
   - Contributed to the report and analysis.
