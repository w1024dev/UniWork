  SIM = function(A, u0, f, n_iter = 10e5, eps = 10e-7){
    stopifnot(n_iter>0, epsilon>0, n>=2, is.numeric(A))
    max_Af = max(max(A), max(f))
    A = A / max_Af
    f = f / max_Af
    I = diag(nrow = nrow(A))
    B <- I - A
    uprev = u0
    u = B %*% uprev + f
    counter = 1
    while(max(abs(u - uprev)) > epsilon && counter < n_iter - 1) {
      uprev = u
      u = B %*% uprev + f
      counter = counter + 1
    }
    res = u
  }