# Part 1
# Part 1 Task 1
x = 2
y = 4

z = x
x = y
y = z
rm(z)
cat("x: ", x, ", y:", y)

# Part 1 Task 2
x = 3.5
y = "2.6"
z = 1.78
h = TRUE

class(x)
typeof(x)
class(y)
typeof(y)
class(z)
typeof(z)
class(h)
typeof(h)

h = as.integer(h)
class(h)
typeof(h)

y = as.numeric(y)
class(y)
typeof(y)

x = as.character(x)
class(x)

# Part 1 Task 3
dohod = 1573
dohod = log(1573)

# Part 1 Task 4
# Вариант 5
to_file = write(5, "text_file.txt")
from_file = as.numeric(readLines("text_file.txt"))
cat("Result: ", 2*from_file - 1)

#Part 2
#Part 2 Task 1
g = c(1, 0, 2, 3, 6, 8, 12, 15, 0, NA, NA, 9, 4, 16, 2, 0)
print(g[1])
print(g[length(g)])
print(g[3:5])
print(g[c(which(g == 2))])
print(g[(g > 4) & (!is.na(g))])
print(g[(g %% 3 == 0) & (!is.na(g))])
print(g[(g > 4) & (g %% 3 == 0) & (!is.na(g))])
print(g[((g < 1) | (g > 5)) & (!is.na(g))])
print(which(g == 0))
print(which((g >= 2) & (g <= 8)))
g = g[-which(g == 2)]
print(g[order(g, na.last = TRUE)])

#Part 2 Task 2
g = c(12, 984.243, TRUE, 1+6i, "NA_GOES_HERE")
g[length(g)] = NA

#Part 2 Task 3
g = c(NA, 23, 45, 2, NA, 94, 3, NA)
print(which(is.na(g)))

#Part 2 Task 4
print(sum(is.na(g)))

#Part 2 Task 5
g = c(1 : 100)

#Part 2 Task 6
counties = c("France", "Italy", "Spain")
periods = c(2017, 2018, 2019, 2020)
#????

#Part 2 Task 7
income = c(10000, 32000, 28000, 150000, 65000, 1573)

mean_func = function(v){
  sum = 0
  for (i in v){
    sum = sum + i
  }
  sum / length(v)
}

income_class = as.numeric(income >= mean_func(income))
print(income_class)

#Part 2 Task 8
# Вариант 5
N = 10
P = 2.32
v = c(1 : N)^2
write(x = v, file = "coords.txt", sep = '\n')

Lp_norm = function(v, p){
  sum = 0
  for (i in v){
    i = abs(i)^p
    sum = sum + i
  }
  sum^(1 / p)
} 

v_new = as.numeric(readLines(con = "coords.txt"))
write(Lp_norm(v_new, P), "result.txt")

#Part 2 Task 9
v_new = as.numeric(readLines(con = "coords.txt"))

diffs1 = 0
for (i in c(1 : (length(v_new)-1))){
  if(length(v_new) < 2){
    diffs1 = v_new[1] * -1
    break
  }
  diffs1[i] = v_new[i+1] - v_new[i]
}

diffs2 = 0
for (i in c(1 : (length(diffs1)-1))){
  diffs2[i] = diffs1[i+1] - diffs1[i]
}
save.image(file = ".RData")
savehistory()
rm(list = ls())
