path=/home/osboxes/radky
if [ $# -eq 1 ]; then
	path=$1
fi

sed -n '10,20p;10!G;h;20p' $path
exit 0
