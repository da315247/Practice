library(jsonlite)
library(stringr)
library(plyr)

json_list = readLines("review.data")
frame <- as.data.frame(t(sapply(json_list, fromJSON)))

# Calculate how many words in a string
nwords <- function(string, pseudo=F){
  ifelse( pseudo, 
          pattern <- "\\S+", 
          pattern <- "[[:alpha:]]+" 
  )
  str_count(string, pattern)
}

#counts >100 word obj
hundredPlus = 0

bigList <- list()

index1=0
index2=0
index3=0
index4=0
index5=0

vector1<- vector()
vector2<- vector()
vector3<- vector()
vector4<- vector()
vector5<- vector()



for(i in 1:10001){
  if( nwords(frame[i, 3]) > 100){
    hundredPlus = hundredPlus + 1
    
    if(frame[i,4] == 1.0){
      vector1 <- c(vector1, frame[i,1])
    }
    
    if(frame[i,4] == 2.0){
      vector2 <- c(vector2, frame[i,1])
    }
    
    if(frame[i,4] == 3.0){
      vector3 <- c(vector3, frame[i,1])
    }
    
    if(frame[i,4] == 4.0){
      vector4 <- c(vector4, frame[i,1])
     
    }
    
    if(frame[i,4] == 5.0){
      vector5 <- c(vector5, frame[i,1])

    }
  }
}
 
df.data <- data.frame(vector1,vector2,vector3,vector4,vector5)

write.table(df.data, "output.txt", sep="\n", quote=TRUE, row.names=TRUE, col.names=TRUE)

print(hundredPlus)

