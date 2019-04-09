path=/home/osboxes/sloupce
if [ $# -eq 1 ]; then
	path=$1
fi

sed -i 's/^\([^\t]*\t\)\([^\t]*\t\)/\2\1/' $path
cat $path
exit 0
