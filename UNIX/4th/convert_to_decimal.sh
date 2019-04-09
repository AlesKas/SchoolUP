vstup=$1
pocet=0
soustava=$2
string="123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ@_"
vystup=0

function convert_to_decimal() {
delka=$((${#1} - 1))
if [ $soustava -gt 0 ] && [ $soustava -le 64 ]; then
	while [ $pocet -le $delka ]; do
		znak=${1:pocet:1}
		i=$(echo $(expr index "$string" "$znak")) 
		zaklad=$(($soustava ** $(($delka - $pocet))))
		vystup=$((vystup + $(($zaklad * $i)) ))
		pocet=$(($pocet + 1))		
	done
	echo -e $vystup
fi
}
convert_to_decimal $vstup
exit