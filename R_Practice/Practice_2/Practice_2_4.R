cars_matrix = as.matrix(cars)

# Task 1
cars_speed = cbind(matrix(1, nrow = nrow(cars_matrix)),
                   cars_matrix[,1])
cars_speed[1:10,]

# Task 2
cars_dist = cars_matrix[,2]

# Task 3
alpha = solve(t(cars_speed)%*%cars_speed) %*% t(cars_speed) %*% cars_dist
alpha

# Task 4
class(alpha)
alpha = as.vector(alpha)

# Task 5
alpha_c = alpha[1]
alpha_x = alpha[2]
cat("alpha_c =", alpha_c, "\nalpha_x =", alpha_x)

# Task 6
cars_speed_lm = cars_matrix[,1]
cars_speed_lm

# Task 7
cars_dist_lm = alpha_c + cars_speed_lm * alpha_x

# Task 8
dist_residuals = cars_dist_lm - cars_dist

# Task 9
dist_res_mean = sum(dist_residuals)/length(dist_residuals)
dist_res_std_dev = sqrt(sum((dist_residuals - dist_res_mean)^2)/length(dist_residuals))

# Task 10
cars_dist_lm

# Task 11
cat("mean =", dist_res_mean, "\nstd_dev =", dist_res_std_dev)
