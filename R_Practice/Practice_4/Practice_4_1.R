# Task 1
library(xlsx)
library(dplyr)

table = read.xlsx(file = "GAZ.xlsx", sheetIndex = 1)
table = table %>% select(-NA.)
l = select(table, "дата.замера")

l = strsplit(l[,1], "/", fixed = TRUE)
for(i in c(1:length(l))){
  if(length(l[[i]]) == 1){
    l[[i]] = as.Date(as.numeric(l[[i]]), origin = "1900-01-01")
  }
  else{
    l[[i]] = as.Date(paste(l[[i]][1], l[[i]][2], l[[i]][3], sep="-"), format = "%d-%m-%Y")
  }
}
l = data.frame("дата.замера" = as.Date(unlist(l)), select(table, -"дата.замера"))

# Task 2
l$Ртр.МПа = as.numeric(table$Ртр.МПа)
l$газ.м3.сут = as.numeric(table$газ.м3.сут)
l$конд.т.м3.сут = as.numeric(table$конд.т.м3.сут)
l$вода.м3.сут = as.numeric(table$вода.м3.сут)

l[l == ""] = NA
l[l == 0] = NA
l = na.omit(l)
table = l

# Task 3
to_kelvin = function(n){
  n + 273.15
}

table$Туст..С = lapply(as.numeric(table$Туст..С), FUN = to_kelvin)
table = table %>% rename("Температура.(К)" = "Туст..С")

# Task 4
table$ID = factor(table$ID, ordered = TRUE)
table$Куст = factor(table$Куст, ordered = TRUE)
table$Группа = factor(table$Группа, ordered = TRUE)

# Task 5
table = table %>% mutate("газ/конденсат" = газ.м3.сут/конд.т.м3.сут)
table = table %>% mutate("газ/вода" = газ.м3.сут/вода.м3.сут)
table = table %>% mutate("вода/конденсат" = вода.м3.сут/конд.т.м3.сут)

# Task 6
table.2018 = table %>% filter(as.POSIXlt(дата.замера)$year + 1900 == 2018)

# Task 7
table.ID.111 = table %>% filter(ID == 111)

# Task 8
ids_to_remove = table %>%
  group_by(ID) %>%
  summarise(max_water = max(вода.м3.сут)) %>% 
  filter(max_water > 2) %>%
  pull(ID)

table.water = table %>% filter(!(ID %in% ids_to_remove))

# Task 9
table.sum.mats = table %>% mutate("sum_mats" = газ.м3.сут + вода.м3.сут + конд.т.м3.сут)

ids_to_remove = table.sum.mats %>%
  group_by(ID) %>%
  summarise(min_mats = min(sum_mats)) %>% 
  filter(min_mats < 1000) %>%
  pull(ID)

table.sum.mats = table %>% filter(!(ID %in% ids_to_remove))

# Task 10
table.best.bushes = table.2018

temp = table.best.bushes %>% select(Группа,газ.м3.сут)
temp = pivot_wider(temp, names_from = Группа, values_from = газ.м3.сут)
temp = data.frame(lapply(temp, function(x) {
  return (sum(unlist(x)))
}))
print(colnames(temp)[max.col(temp, ties.method = "first")])

# Task 11
table.bush = table.2018

temp = table.bush %>% select(Куст, вода.м3.сут)
temp = pivot_wider(temp, names_from = Куст, values_from = вода.м3.сут)
temp = data.frame(lapply(temp, function(x) {
  return (sum(unlist(x)))
}))
print(colnames(temp)[max.col(temp, ties.method = "first")])

# Task 12
table.bush = table
table.bush = table.bush %>% mutate("нефть/вода" = Ртр.МПа/вода.м3.сут)
temp = table.bush %>% select(Куст, "нефть/вода")
temp = pivot_wider(temp, names_from = Куст, values_from = "нефть/вода")
temp = data.frame(lapply(temp, function(x) {
  return (mean(unlist(x)))
}))
print(colnames(temp)[max.col(temp, ties.method = "first")])
