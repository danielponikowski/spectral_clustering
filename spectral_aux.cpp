#include <Rcpp.h>
using namespace Rcpp;

// This is a simple example of exporting a C++ function to R. You can
// source this function into an R session using the Rcpp::sourceCpp 
// function (or via the Source button on the editor toolbar). Learn
// more about Rcpp at:
//
//   http://www.rcpp.org/
//   http://adv-r.had.co.nz/Rcpp.html
//   http://gallery.rcpp.org/
//

// [[Rcpp::export]]
NumericMatrix Mnn(NumericMatrix X,int M){
  int n = X.nrow();
  int m = X.ncol();
  NumericVector y = NumericVector(m);
  NumericVector z = NumericVector(M);
  NumericMatrix S = NumericMatrix(n,n);
  NumericMatrix result = NumericMatrix(n,M);
  for (int i=0; i<n; ++i)
    for (int j = 0; j<n; ++j){
      S(i,j) += sqrt(sum((X(i,_)-X(j,_))*(X(i,_)-X(j,_))));      
    };
  for (int l=0;l<n;++l){
    y = S(l,_);
    S(l,_) = match(S(l,_), clone(y).sort());
  };
  for (int i=0; i<n;++i){
    for (int j=0; j<n;++j)
      if ( S(i,j) <= M + 1 && S(i,j) > 0)
        S(i,j) = S(i,j) - 1;
      else 
        S(i,j) = 0;};
  for (int i=0;i<n;++i){
    for (int j=0;j<n;++j)
      if (S(i,j) > 0 && result(i,S(i,j)-1) == 0)
        result(i,S(i,j)-1) = j+1;
      else if (S(i,j) > 0 && result(i,S(i,j)-1) != 0)
        result(i,S(i,j)) = j+1;      
  };
  return result;
} 

// [[Rcpp::export]]
NumericMatrix Mnn_graph_cpp(NumericMatrix S){
  int n = S.nrow();
  int m = S.ncol();
  NumericMatrix G = NumericMatrix(n,n);
  for (int i=0;i<n;++i)
    for (int j=0;j<m;++j){
      G(i,S(i,j)) = 1;
      G(S(i,j),i) = 1;
    };
  return G;
}

// You can include R code blocks in C++ files processed with sourceCpp
// (useful for testing and development). The R code will be automatically 
// run after the compilation.
//


