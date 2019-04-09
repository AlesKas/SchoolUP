path=/home/osboxes/mergeSlova
if [ $# -eq 1 ]; then
	path=$1
fi

sed -e :a -e N -e 's/-\n/ /' $path

exit 0
