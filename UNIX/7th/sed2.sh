path=/home/osboxes/html.txt

if [ $# -eq 1 ]; then
	path=$1
fi

sed -n 's/.*href="\([^"]*\).*/\1/p' $path
exit 0
