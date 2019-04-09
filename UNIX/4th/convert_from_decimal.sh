maxdelka=2
number=$1
soustava=$2
string="0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ@_"

function convert_from_decimal {
if [ $soustava -gt 0 ] || [ $soustava -le 64 ]; then
	delka=$((${#1} - 1))
	vystup="" 
	while [ $maxdelka -gt 0 ]; do
		
		zbytek=$(($number % $soustava))
		cislo=${string:${zbytek}:1}
		vystup=$cislo$vystup
		
		number=$(($number / $soustava))	
		if [ $number -eq 0 ]; then
			break
		fi
	done
	echo -e $vystup
else
	echo "Neznama soustava\n"
fi
}

convert_from_decimal
exit