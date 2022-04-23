#!/bin/bash -f
if [[ $# -ne 2 ]] 
then
  echo "enter 2 files as argument as ./lab.sh <file1> <file2>"  #for checking the number of arguments and showing the correct way of input
else
  if [[ ! -f "$1" ]]
  then
    echo "$1 not found"   #if the first argument is not a file
    exit
  elif [[ ! -f "$2" ]]
  then
    echo >> $2
    echo "As the $2 file don't exist, I will create it" #if the second argument is not a file then we will create one
  fi
  awk -F "," '{print $1 " " $2 " " $3 " " $5 " " $6 " " $7 " " $10 " " $11}' $1 > $2  #print the coulmns required in part 1
  echo "">>$2
  echo "Highest degree - Bachelor: " >>$2       
  awk -F "," '{if($3=="Bachelor'\''s") print $1}' $1 >> $2    #print the colleges with highest degree bachelors
  echo "">>$2
  echo "Geography: Average Admission Rate" >>$2       
  #array1 has the sum of admission rate of each college in particular geopgraphy
  #cnt has the number of colleges in  the particular geography
  awk -F "," 'FNR == 1 {next}   
              BEGIN{}
              {array1[$6]=array1[$6]+$7}    
              {cnt[$6]=cnt[$6]+1} 
              {array2[$1]=$16}
              END{for (key in array1) { print key":" array1[key]/cnt[key] }}' $1>>$2 #print the average admission rate of each college in each geography
  echo "">>$2
  echo "Top 5 MedianEarnings Colleges: ">>$2    #print the top 5 colleges with highest median earnings
  awk -F "," '{print substr($16, 1, length($16)-1) " " $1}' $1 | sort -k1,1 -nr |awk -F " " '{first = $1; $1 = ""; print $0; }'| awk '{ if(NR<6) print substr($0,2)}'>> $2
fi