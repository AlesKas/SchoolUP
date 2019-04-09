for i in {0000..9999}; do
	foto=fotky/XYZ${i}.jpg
	if [ -e $foto ]; then
		date=`cat $foto`
		file=`paste -d "/" <(echo $date | cut -f3 -d "/") <(echo $date | cut -f1 -d "/") <(echo $date | cut -f2 -d "/")`
		mkdir -p sorted/$file
		cp $foto sorted/$file/
	fi
done
