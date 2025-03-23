## Group - 57
CS F364 DAA Assignment Readme File

The website link : https://daa-a1-grp57.netlify.app

File Structure

There are 3 components in this zip file:

1) algorithms/:
  - Contains the implemented algorithms
2) website/
  - Contains the webpage's source code.
3) Final Report for the Assignment


Datasets:
The data sets are available on the Stanford websites:-
1. https://snap.stanford.edu/data/email-Enron.html
2. https://snap.stanford.edu/data/as-Skitter.html
3. https://snap.stanford.edu/data/wiki-Vote.html

Execution Instructions:
1.Run the following command (replace `<filename>` with the name of the algorithm file and `<output_filename>` with your desired executable name)
	For bronkerboschDegenracy:

   g++ -O3 <filename>.cpp -o <output_filename>.out
   g++-14 -O3 -o bronkerbosch-final bronkerbosch-final.cpp
   
   For Arboricity:
      Compilation 
         g++-14 -std=c++17 -O3 -Wall -Wextra -o chiba_arbocity chiba_arbocity.cpp
      Execution 
        ./chiba_arbocity <dataset.txt> <output_file.txt> <timeout in ms> 
        we turn off timeout by setting it to -1 
        ./chiba_arbocity wiki-Vote.txt max_cliques.txt -1
    For Tomita:
      Compilation 
         g++-14 -std=c++17 -O3 -o tomita tomita.cpp 
      Execution 
        ./tomita <dataset.txt>

(**Additional info**: 
1. `-O3` ensures maximum optimization in the generated executable
2. g++-14 -O3 -fopenmp -o bronkerbosch-final bronkerbosch-final.cpp can be used for faster implementation of the BKBDegeneracy code with OpenMP implementation)


2. Execute the compiled program:
   ./bronkerbosch-final <textfilename.txt>   

Pls ensure that text file is (eg:wiki-Vote.txt) is in the same directory as the compiled executable

5. You may encounter some statements printed on the output terminal before the final results like the following. Post-which the entire output will be printed (expected time submitted in report may vary based on system configuration/specifications)

Bron (sample output ):

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
Size 4: 27292 cliques
Size 5: 48416 cliques
Size 6: 68872 cliques
Size 7: 83266 cliques
Size 8: 76732 cliques
Size 9: 54456 cliques
Size 10: 35470 cliques
Size 11: 21736 cliques
Size 12: 11640 cliques
Size 13: 5449 cliques
Size 14: 2329 cliques
Size 15: 740 cliques
Size 16: 208 cliques
Size 17: 23 cliques

Top 10 largest clique sizes:
17 17 17 17 17 17 17 17 17 17 
Cliques written to wiki-vote.txt.cliques.txt

Tomita (sample output)

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
4: 27292
5: 48416
6: 68872
7: 83266
8: 76732
9: 54456
10: 35470
11: 21736
12: 11640
13: 5449
14: 2329
15: 740
16: 208
17: 23
Results written to wiki-Vote-cliques.txt


Arboricity (sample output):
   Loading graph from email-Enron.txt...
   Loaded graph with 36692 vertices and 367662 edges.
   Graph loaded in 111.12 ms.
   Finding maximal cliques...
   Found 226859 maximal cliques.
   Graph load time: 111.12 ms
   Clique finding time: 44175.2 ms
   Results written to max_cliques.txt


Contributors:

1. Angad Bawa
   Contributed to the implementation of the Arboricity based algorithm based on the Chiba et al. (1985) paper and corresponding report with analysis

2. Vibhanshu Bhagat
   Contributed to the implementation of the Bron-Kerbosch algorithm based on the Eppstein et al. (2010) paper and corresponding report with analysis

3. Ishan Barpanda
   Contributed to the implementation of the CLIQUES algorithm based on the Tomita et al. (2006) paper, developed the project website and corresponding report with analysis.
