# Task 1
library(randomNames)

# Task 2
set.seed(1234)
names = randomNames(100, which.names = "first", ethnicity = 4)

# Task 3
ages = sample(16:75, 100, replace = TRUE)
views = c("right", "left", "moderate", "indifferent")
polit = sample(views, 100, replace = TRUE)

respondents = data.frame(ages, views, polit)
head(respondents)

# Task 4
respondents = data.frame("id" = 1:100, respondents)

# Task 5
age_bracket = filter(respondents, ages>=25 & ages<=30)
age_bracket_percentage = as.numeric(round(count(age_bracket)/count(respondents)*100, digits = 1))

# Task 6
polit_views = as.factor(polit)
respondents = cbind(respondents, "polit_views" = polit_views)
