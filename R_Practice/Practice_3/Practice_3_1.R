names = c("Jane", "Michael", "Mary", "George")
ages = c(8, 6, 28, 45)
gender = c(0, 1, 0, 1)

# Task 1
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

# Task 2
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
