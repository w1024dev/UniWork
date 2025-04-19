library(dplyr)
id = 1:3
country = c("Flatland", "Wonderland", "Sphereland")
craziness = c(20, 15, 18)
region_type = c("A", "B", "A")
author = c("Abbot", "Carrol", "Burger")
size = c(10, 100, 30)
m = cbind(id, country, craziness, region_type, author, size)
df = as.data.frame(m)
df$id = as.numeric(df$id)
df$craziness = as.numeric(df$craziness)
df$region_type = as.factor(df$region_type)
df$size = as.numeric(df$size)

apply(df, 2, class)
rm(list = ls())

id = 1:3
country = c("Flatland", "Wonderland", "Sphereland")
craziness = c(20, 15, 18)
region_type = c("A", "B", "A")
author = c("Abbot", "Carrol", "Burger")
size = c(10, 100, 30)
m = cbind(id, country, craziness, region_type, author, size)
df = as.data.frame(m)

df$id = as.numeric(df$id)
df$craziness = as.numeric(df$craziness)
df$region_type = as.factor(df$region_type)
df$size = as.numeric(df$size)


# Task 1
class_count = function(df){
  res = c("numeric" = 0, "factor" = 0, "character" = 0)
  for (i in colnames(df)){
    if(is.numeric(df[, i])){
      res["numeric"] = res["numeric"] + 1
    }
    else if(is.factor(df[, i])){
      res["factor"] = res["factor"] + 1
    }
    else if(is.character(df[, i])){
      res["character"] = res["character"] + 1
    }
  }
  res
}


class_count(df)

# Вопрос
for (i in df[1,]){ # ??????
  print(class(i))
}

print(apply(df, MARGIN = 2, FUN = class)) # ?????

# Task 2
num_export = function(df, new_df){
  new_df <<- df %>% select_if(is.numeric)
}


num_export(df, new_df)
new_df

# Task 3
# apply функции не использовались, смотреть выше

# Task 4
vector_median = function(v){
  if(is.numeric(v)){
    return (median(v))
  }
  else{
    print("Vector is not numeric, cannot compute the median")
  }
}
vector_median(c(1,2,3))
vector_median(as.factor(c(1,2,3)))
rm(list = ls())
