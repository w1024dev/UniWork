# Task 1
m = matrix(3, nrow = 3, ncol = 4)
print(m)
m[1, 3] = 4
m[2, 1] = 1
m[3, 2] = NA
m[3, 4] = 1
print(m)

# Task 2
a = c(1, 3, 4, 9, NA)
b = c(5, 6, 7, 0, 2)
c = c(9, 10, 13, 1, 20)

m_rows = cbind(a, b, c)
rownames(m_rows) = paste0("row", 1:5)
colnames(m_rows) = paste0("col", 1:3)
print(m_rows)
m_cols = rbind(a, b, c)
rownames(m_cols) = paste0("row", 1:3)
colnames(m_cols) = paste0("col", 1:5)
print(m_cols)

# Task 3
names = c("Jane", "Michael", "Mary", "George")
ages = c(8, 6, 28, 45)
gender = c(0, 1, 0, 1)
m_diverse = cbind(names, ages, gender)
print(m_diverse)
is.character(m_diverse[,2])
is.character(m_diverse[,3])
m_diverse = cbind(m_diverse, as.numeric(m_diverse[,2])^2)
print(m_diverse)

# Task 4
info = list(names, ages, gender)

print(info[[1]][2])

print(info[[3]])

names(info) = c("name", "age", "gender")
print(info$name)

info$drinks = c("juice", "tea", "rum", "coffee")
print(info)

new_entry = c("John", "2", "1", "milk")
for(i in 1:4){
  info[[i]] = c(info[[i]], new_entry[i])
}

# Task 5
s = "a, b, c, d"
let = strsplit(s, ",")
class(let)
unlist(let)

index = "0,72;0,38;0,99;0,81;0,15;0,22;0,16;0,4;0,24"
index_split = strsplit(index, ";")
I = unlist(index_split)
I = gsub(",", ".", I)
I = as.numeric(I)
print(I)
