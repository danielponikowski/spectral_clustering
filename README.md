# Spectral Clustering
My own implementation of spectral clustering algorithm on R using Rcpp elements.

### Mnn(X,M):

This function computes matrix (S) of nerest neighbours which have indexes of M nearest neighbours for each observation.

X - matrix of observations in rows. 

M - number of neighbours.

### Mnn_graph(S)

This function transform result of Mnn function to graph matrix and randomly connect separable parts of graph.

S - numeric matrix.

### Laplacian_eigen(G,k)

First we compute Laplacian of matrix G, that is a matrix L = D - G where D is diagonal with degrees of vertices in graph G. Then we compute matrix E which columns consist of eigenvectors corresponding to 2, 3, ... k+1 smallest eigenvalues and return matrix E.

G - numeric matrix

k - number of clusters 

### spectral_clustering(X, k, M) 

Function linking above function and does kmeans algorytm on result Laplacia_eigen function. It returns cluster labels for each row in X.

X - matrix of observation in rows

k - number of clusters

M - number of neighbours

