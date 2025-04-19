summary_file = function(nfile, option, 
                        n_elem, n_rows, n_cols,
                        row_sums,
                        col_sums,
                        sum_main_diag,
                        sum_middle_row = 0,
                        sum_middle_col = 0
                        ){
  write(paste("number of matrix elements:", n_elem), file = nfile)
  write(paste("number of rows:", n_rows), file = nfile, append = TRUE)
  write(paste("number of cols:", n_cols), file = nfile, append = TRUE)
  write(paste("sum of main diag elements:", sum_main_diag), file = nfile, append = TRUE)
  if (option){
    write(paste("sum of middle row elements:", sum_middle_row), file = nfile, append = TRUE)
    write(paste("sum of middle column elements:", sum_middle_col), file = nfile, append = TRUE)
  }
  write(paste("row sums:", paste(row_sums, collapse = " ")), file = nfile, append = TRUE)
  write(paste("col sums:", paste(col_sums, collapse = " ")), file = nfile, append = TRUE)
}


surface_matrix = function(step1 = 1, dekart_begin1 = -5, dekart_end1 = 5,
                          step2 = step1, dekart_begin2 = dekart_begin1, dekart_end2 = dekart_end1,
                          nfile, is_square = 1){
  # Задание сеточной поверхности
  x = seq(from = dekart_begin1, to = dekart_end1, by = step1)
  y = seq(from = dekart_begin2, to = dekart_end2, by = step2)
  
  # Задание двумерной функции на координатной сетке
  surface_matrix = outer(X = x, 
                         Y = y,
                         FUN = function(x,y) Re(exp(-1i * 0.5 * x * y)))
  dimnames(surface_matrix) = list(x, y)
  
  n_elem = length(surface_matrix)
  n_rows = nrow(surface_matrix)
  n_cols = ncol(surface_matrix)
  sum_main_diag = sum(diag(surface_matrix))
  
  if (n_rows %% 2 == 0){
    middle_index1 = n_rows%/%2
  }
  else{
    middle_index1 = n_rows%/%2+1
  }
  if (n_cols %% 2 == 0){
    middle_index2 = n_cols%/%2
  }
  else{
    middle_index2 = n_cols%/%2+1
  }
  
  sum_middle_row = sum(surface_matrix[middle_index1,])
  sum_middle_col = sum(surface_matrix[,middle_index2])
  row_sums = apply(X = surface_matrix, MARGIN = 1, FUN = sum)
  col_sums = apply(X = surface_matrix, MARGIN = 2, FUN = sum)
  
  summary_file(nfile, is_square, 
               n_elem, n_rows, n_cols,
               row_sums, col_sums,
               sum_main_diag,
               sum_middle_row,
               sum_middle_col)
}


# Task 1
surface_matrix(nfile = "summary.txt")

# Task 2
begin = as.numeric(readline(prompt = "begin: "))
end = as.numeric(readline(prompt = "end: "))
step = as.numeric(readline(prompt = "step: "))


surface_matrix(dekart_begin1 = begin, dekart_end1 = end, step1 = step, 
               nfile = "summary2.txt", is_square = 0)
# Task 3
x = c(-4, 16, 2, 5, 125, 5)
write(x, file = "inputs.txt", sep = "\n")

data = as.numeric(readLines(con = "inputs.txt"))

surface_matrix(dekart_begin1 = data[1], dekart_end1 = data[2], step1 = data[3],
               dekart_begin2 = data[4], dekart_end2 = data[5], step2 = data[6],
               nfile = "summary3.txt", is_square = 0)
