path=/home/osboxes/mails.txt
template=/home/osboxes/template.txt

while read -r line; do
	a=( $line )
	cp $template ${a[0]}${a[1]}.txt
	sed -i "s/JMENO/${a[0]}/g" ${a[0]}${a[1]}.txt
	sed -i "s/PRIJMENI/${a[1]}/g" ${a[0]}${a[1]}.txt
	sed -i "1s/^/${a[2]:1:-1}\n\n/" ${a[0]}${a[1]}.txt
done < "$path"
