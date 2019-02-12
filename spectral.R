library(Rcpp)

sourceCpp("spectral_aux.cpp")

skupienie <- function(S,n){
  odwiedzone <- which(S[n,] > 0)
  as.vector(odwiedzone)
}


Mnn_graph <- function(S){
  G <- Mnn_graph_cpp(S)
  n <- nrow(G)
  nieodwiedzone <- matrix(1:n,ncol = n)
  odwiedzone <- skupienie(G,1)
  while (sum(nieodwiedzone) != 0){
  for (i in odwiedzone){
    odwiedzone <- unique(c(odwiedzone,skupienie(G,i)))
  }
  length(odwiedzone)
  nieodwiedzone[,odwiedzone] <- 0
  if (sum(nieodwiedzone) > 0 ){
  wierzcholek <- sample(odwiedzone,1)
  wierzcholek2 <- sample(which(nieodwiedzone > 0),1)
  G[wierzcholek,wierzcholek2] <- 1
  G[wierzcholek2,wierzcholek] <- 1
  }
  odwiedzone <- c(odwiedzone,wierzcholek2)
  length(odwiedzone)
  }
  G
}




Laplacian_eigen <- function(G,k){
  stopnie <- diag(rowSums(G))
  evL <- eigen(stopnie - G,symmetric = TRUE)
  evL$vectors[,(ncol(evL$vectors)-k+1):ncol(evL$vectors)]
}

spectral_clustering <- function(X,k,M){
  kmeans(Laplacian_eigen(Mnn_graph(Mnn(X = X,M = M)),k = k),centers = k)
}





