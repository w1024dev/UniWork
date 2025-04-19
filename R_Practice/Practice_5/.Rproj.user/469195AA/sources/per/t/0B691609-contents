{if ("quantmod" %in% rownames(installed.packages()) == FALSE) {
  install.packages("quantmod") }
library(quantmod)
if ("stringr" %in% rownames(installed.packages()) == FALSE) {
  install.packages("stringr") }
library(stringr)}

# Task 1
downloadable_stocks <- c("NVDA", "^IXIC")

# Функция получения фреймов с данными
quantmod::getSymbols(Symbols = downloadable_stocks,
                     src = "yahoo",
                     from = as.Date.character("1900-01-01"))

df <- data.frame(get(downloadable_stocks[1]))

# Применяем регулярное выражение для поиска и удаления ненужных символов
downloadable_stocks <- stringr::str_remove(downloadable_stocks, "[:punct:\\^]")
rm(list = downloadable_stocks)

# Task 2
#Arithmetic
arifm = function(xt, xt_left, xt_right){
  log((xt_left + xt_right)/(2*xt))
}

#Geometric
geom = function(xt, xt_left, xt_right){
  log((xt_left * xt_right)/(xt^2))
}

#Harmonic
garm = function(xt, xt_left, xt_right){
  log((2*x_left*x_right)/(xt*(x_left+x_right)))
}


out_of_trend = function(x, dt, method = c("Arifm", "Geom", "Garm")){
  #Исключительные случаи
  if(length(x) < 3 | 
     !is.numeric(x) |
     !is.numeric(dt) |
     dt > ceiling(length(x) / 2 - 1)){
    print("Error: an argument is inapplicable")
    return()
  }
  #Поднять на минимальный элемент
  x = x + min(x) + 1
  
  y = c()
  if(length(method) == 3){
    method = "Arifm"
  }
  
  i = dt+1
  while(i <= length(x)-dt){
    switch(method, 
      "Arifm" = {y = append(y, arifm(x[i], x[i-dt], x[i+dt]))},
      "Geom" = {y = append(y, geom(x[i], x[i-dt], x[i+dt]))},
      "Garm" = {y = append(y, garm(x[i], x[i-dt], x[i+dt]))}
      )
    i = i+1
  }
  return(y)
}

# Task 3
t = seq(0, 10, 0.1)
x = 2*t + 3 + sin(2*t)

print(mean(x))
xn = out_of_trend(x, 5)
print(mean(xn))
plot(1:length(x), x, type="l")
plot(1:length(xn), xn, type="l")

# Task 4
alter.johns = function(y){
  t = 1
  a = c()
  while(t <= floor(length(y)/2)){
    i = 1
    summ = 0
    while(i <= length(y)-t){
      summ = summ + abs(y[i+t] - y[i])
      i = i+1
    }
    summ = summ / (length(y)-t)
    a = append(a, summ)
    t = t+1
  }
  return(a)
}

# Task 5
xn_fluctuations = alter.johns(xn)
plot(1:length(xn_fluctuations), xn_fluctuations, type="l")

# Task 6
head(df)

plot(1:nrow(df), df$NVDA.Close, type="l")
nvda_without_trend = out_of_trend(df$NVDA.Close, 500)
plot(1:length(nvda_without_trend), nvda_without_trend, type="l")
nvda_fluctuations = alter.johns(nvda_without_trend)
plot(1:length(nvda_fluctuations), nvda_fluctuations, type="l")

rm (list = ls())
