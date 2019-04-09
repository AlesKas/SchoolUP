function dirname() {
	path=$1
	if [ -d $path ] && [ ${#path} -ne 1 ]; then
		path=${path%?}
	fi
	dir=`echo $path | tr "/" "\n" | head -n -1 | tr "\n" "/"`

	if [ ${#dir} -gt 1 ]; then
		dir=${dir%?}
	fi
	
	if [ "$dir" == "" ]; then
		dir="."
	fi

	echo $dir

}

dirname $1