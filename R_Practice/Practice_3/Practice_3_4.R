# Task 1
library(dplyr)
library(tidyr)
library(stringr)
imported_data = read.csv("https://raw.githubusercontent.com/CSSEGISandData/COVID-19/master/csse_covid_19_data/csse_covid_19_time_series/time_series_covid19_confirmed_global.csv")
str(imported_data)
imported_data = na.omit(imported_data)

int_data = select(imported_data, -c(Province.State, Country.Region, Lat, Long))

sum_p = apply(X = int_data, MARGIN = 1, sum)
mean_p = trunc(apply(X = int_data, MARGIN = 1, mean))
std_p = trunc(apply(X = int_data, MARGIN = 1, sd))

# Table 1
df_stats = data.frame("Country/Region" = imported_data$Country.Region,
                      "to_be_deleted" = imported_data$Province.State,
                      "Latitude" = imported_data$Lat, 
                      "Longtitude" = imported_data$Long, 
                      "Sum of all patients" = sum_p, 
                      "Mean number of patients" = mean_p, 
                      "Standard deviation of mean" = std_p)
df_stats = df_stats %>% unite(col = "Country/Region Province.State", 
                              Country.Region,
                              to_be_deleted,
                              sep = " ")
head(df_stats)

days = colnames(int_data)
days = str_replace_all(days, "X", "")
days = strsplit(days, ".", fixed = TRUE)

convert_to_date = function(v){
  v = as.numeric(v)
  date_str = paste(v[3]+2000, v[1], v[2], sep = "-")
  as.Date(date_str, format = "%Y-%m-%d")
}

# Time scale
days = lapply(days, convert_to_date)

# Table 2
df_final = t(int_data)
colnames(df_final) = df_stats$`Country/Region Province.State`

df_final = data.frame("Date" = as.Date(unlist(days)), df_final)
rownames(df_final) = NULL

# Export
if(!dir.exists("data_output")){
  dir.create("data_output")
}

library(openxlsx)
write.table(x = df_stats, file = "data_output/df_stats.txt", row.names = FALSE)
write.csv(x = df_stats, file = "data_output/df_stats.csv", row.names = FALSE)
write.xlsx(x = df_stats, file = "data_output/df_stats.xlsx", rowNames = FALSE)
