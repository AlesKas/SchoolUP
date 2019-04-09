for i in {0001..1000}; do
	day=$(($RANDOM%30 + 1))
	month=$(($RANDOM%11 + 1))
	year=$(($RANDOM%3000 + 1))
	echo $month/$day/$year > $i
done
