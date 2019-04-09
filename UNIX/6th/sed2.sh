path=/home/osboxes/nadpisy
if [ $# -eq 1 ]; then
	path=$1
fi

sed -e 's/[^0-9]*//' -e 's/[0-9]\+\.*/ /g' $path
exit 0
