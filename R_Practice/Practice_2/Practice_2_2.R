# Task 1
A = diag(c(4, 9), nrow = 2, ncol = 2)
rownames(A) = c("eq1", "eq2")
colnames(A) = c("x1", "x2")

# Task 2
eigen_values = eigen(A)
eigen_values

# Task 3
I = diag(1, nrow = 2, ncol = 2)
B = I - A

# Task 4
f = c(4, 2)
u = c(0.2, -0.3)

# Task 5
# ????
u_result = solve(A, f)
print(u_result)
# or??
print(A %*% u)
print(f)

# Task 6
u_iter = matrix(u)
for (i in c(1:6)){
  u_iter = cbind(u_iter, (B%*%u_iter[,i])+f)
}

# Task 7
#???
u_iter[,7]
u_result
task_7_res = u_iter[,7] - u_result

# Task 8
m = max(A)
A = A / m
f = f / m

#Task 9
eigen_values = eigen(A)
eigen_values

I = diag(1, nrow = 2, ncol = 2)
B = I - A

u_result_2 = solve(A, f)

u_iter_2 = matrix(u)
for (i in c(1:6)){
  u_iter_2 = cbind(u_iter_2, (B%*%u_iter_2[,i])+f)
}

u_iter_2[,6]
u_result_2
task_9_res = u_iter_2[,6] - u_result_2

#Task 10
task_7_res
task_9_res
