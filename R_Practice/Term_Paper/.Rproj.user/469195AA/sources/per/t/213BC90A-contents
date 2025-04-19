# Импорт данных
data <- read.csv("salesdaily.csv")
head(data)
str(data)

# Обработка данных
if ("dplyr" %in% rownames(installed.packages()) == FALSE){
  install.packages("dplyr")
}
library(dplyr)

data.monthly <- data
data.monthly <- data.monthly %>% group_by(Year, Month) %>% summarize("monthly_mean" = mean(M01AB))
data.monthly <- data.monthly %>% mutate("date" = as.Date(paste(Year, Month, "01", sep = "-")))
data.monthly <- data.frame(date = data.monthly$date, monthly_mean = data.monthly$monthly_mean)

data.ts.monthly = ts(data.monthly$monthly_mean, start = c(2014, 1), frequency = 12)

summary(data.ts.monthly)

plot(data.ts.monthly, 
     main = "Данные о ежедневных продажах препаратов группы M01AB",
     xlab = "Дата",
     ylab = "Ежедневные продажи")
grid()

# Основная программа
if ("ggplot2" %in% rownames(installed.packages()) == FALSE){
  install.packages("ggplot2")
}
if ("forecast" %in% rownames(installed.packages()) == FALSE){
  install.packages("forecast")
}
library(ggplot2)
library(forecast)

ggtsdisplay(data.ts.monthly)
dev.new()
ggtsdisplay(diff(data.ts.monthly))
mean(diff(data.ts.monthly))

decomposed.multiplicative <- decompose(data.ts.monthly, type = "multiplicative")
decomposed.additive <- decompose(data.ts.monthly, type = "additive")

# Сравнение трендов
plot(decomposed.multiplicative$trend,
     main = "Сравнение компонент тренда",
     ylab = "Значения тренда", 
     xlab = "Время", 
     col = "red", 
     ylim = range(c(0, 7)))
lines(decomposed.multiplicative$x)
lines(decomposed.additive$trend, col = "blue")
grid()
legend("bottomleft", 
       legend = c("Additive trend", "Multiplicative trend"), 
       col = c("blue", "red"), 
       pch = c(19, 17), 
       bty = "o")

# Сравнение сезонных компонент
dev.new()
plot(decomposed.multiplicative$seasonal, 
     main = "Сравнение сезонных компонент",
     ylab = "Значения сезонной компоненты", 
     xlab = "Время", 
     col = "red", 
     ylim = range(c(-1, 1.3)))
lines(decomposed.additive$seasonal, col = "blue")
grid()
legend("bottomleft", 
       legend = c("Additive trend", "Multiplicative trend"), 
       col = c("blue", "red"), 
       pch = c(19, 17), 
       bty = "o")

# Сравнение случайных компонент
dev.new()
plot(decomposed.multiplicative$random, 
     ylab = "Значения случайной компоненты", 
     xlab = "Время",
     col = "red", 
     ylim = range(c(-1, 1.3)))
lines(decomposed.additive$random, col = "blue")
grid()
legend("bottomleft", 
       legend = c("Additive trend", "Multiplicative trend"), 
       col = c("blue", "red"), 
       pch = c(19, 17), 
       bty = "o")

# Сохранение нового файла
x = decomposed.additive$x
trend = decomposed.additive$trend
seasonal = decomposed.additive$seasonal
random = decomposed.additive$random
decomposed.additive.df = data.frame(x, trend, seasonal, random)

x = decomposed.multiplicative$x
trend = decomposed.multiplicative$trend
seasonal = decomposed.multiplicative$seasonal
random = decomposed.multiplicative$random
decomposed.multiplicative.df = data.frame(x, trend, seasonal, random)

print(decomposed.multiplicative.df[1:7,])
print(decomposed.multiplicative.df[68:70,])

write.csv(decomposed.additive.df, file = "decomposed_additive.csv", row.names = FALSE)
write.csv(decomposed.multiplicative.df, file = "decomposed_multiplicative.csv", row.names = FALSE)
