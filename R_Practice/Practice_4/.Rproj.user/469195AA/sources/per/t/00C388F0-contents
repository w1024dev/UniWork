# Task 1
head(Ornstein)

# Task 2
str(Ornstein)

# Task 3
print(Ornstein[rowSums(is.na(Ornstein)) > 0,])

# Task 4
print(filter(Ornstein, assets >= 10000 & assets <= 20000))
print(filter(Ornstein, interlocks <= 30))
print(filter(Ornstein, sector == "TRN" & nation == "CAN"))

# Task 5
log_assets = log(Ornstein$assets)
frame = data.frame("log_assets" = log_assets, Ornstein)

# Task 6
na_rows = sample(1:9, 248, replace = TRUE)
na_cols = sample(1:5, 5)
na_rows[1:20]
for(i in c(1:248)){
  if(na_rows[i] > 4){
    if(i^2%%5 == 0){
      j = i^2%%5 + 1
    }
    else {
      j = i^2%%5
    }
      frame[i, j] = NA
    }
}
gg_miss_var(frame)
na_rows[1:30]

# Task 7
frame = na.omit(frame)
frame[1:30,]

# Task 8
write.dta(frame, "Firms.dta")
