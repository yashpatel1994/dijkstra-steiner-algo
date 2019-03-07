dijkstra-steiner-algo
-------
This is an implementation of Dijkstra-Steiner Algorithm [1] for finding shortest rectilinear Steiner tree for 3D Hanan grid graphs with future costs in rutime <a href="https://www.codecogs.com/eqnedit.php?latex=$\mathcal{O}\left(3^{k}&space;n&plus;2^{k}(n&space;\log&space;n&plus;m)\right)$" target="_blank"><img src="https://latex.codecogs.com/gif.latex?$\mathcal{O}\left(3^{k}&space;n&plus;2^{k}(n&space;\log&space;n&plus;m)\right)$" title="$\mathcal{O}\left(3^{k} n+2^{k}(n \log n+m)\right)$" /></a>. It was written for an exercise assignment of the [Chip Design lecture (SS 2017)](http://www.or.uni-bonn.de/lectures/ss17/chipss17.html) held by Prof. Stephan Held at Research Institute for Discrete Mathematics, University of Bonn.

The implementation adheres with the observations mentioned in the article, that is:

* A binary heap is used instead of a Fibonacci heap.

* The terminal sets are represented by bitsets using bijection <a href="https://www.codecogs.com/eqnedit.php?latex=$2^{R}&space;\rightarrow\left\{0,&space;\dots,&space;2^{|R|}-1\right\}$" target="_blank"><img src="https://latex.codecogs.com/gif.latex?$2^{R}&space;\rightarrow\left\{0,&space;\dots,&space;2^{|R|}-1\right\}$" title="$2^{R} \rightarrow\left\{0, \dots, 2^{|R|}-1\right\}$" /></a>, where <a href="https://www.codecogs.com/eqnedit.php?latex=R" target="_blank"><img src="https://latex.codecogs.com/gif.latex?R" title="R" /></a> is the terminal set. 

* For each vertex in the graph, an array containing labels <a href="https://www.codecogs.com/eqnedit.php?latex=(v,&space;I)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?(v,&space;I)" title="(v, I)" /></a> with <a href="https://www.codecogs.com/eqnedit.php?latex=l(v,I)&space;<&space;\infty" target="_blank"><img src="https://latex.codecogs.com/gif.latex?l(v,I)&space;<&space;\infty" title="l(v,I) < \infty" /></a> is maintained together with a hash table storing index for each label in the array, if it exists. This enables quick access to the existing labels (that is, traversing can be done in linear time).

* The algorithm highly depends upon the quality of valid lower bound. More precisely, the larger the lower bound is, the faster the algorithm is. Hence, to optimize the running time, lower bounds such as bounding box of terminals and 1-tree lower bounds are implemented. In general, 1-tree lower bound exploits the fact that they can be used to computer lower bounds on minimum cost of the tour, which is at most twice as expensive as minimum cost Steiner tree.

Compile
-------
`cmake . && make programming_task`

Usage
-----
`./programming_task instance_file`

Tests
-----
Requires an installation of the Boost Unit Test Framework that is discoverable by cmake.

`cmake . && make tests`   
`./tests`

References
-----
[1]: Hougardy, S., Silvanus, J., & Vygen, J. (2017). Dijkstra meets Steiner: a fast exact goal-oriented Steiner tree algorithm. Mathematical Programming Computation, 9(2), 135-202.