function basename() {
	path=$1
	if [ -d $path ] && [ ${#path} -ne 1 ] && [ "${path:${#path} - 1}" == "/" ]; then
		path=${path%?}
	fi
	
	path=`echo $path | tr "/" "\n" | tail -n 1 | tr "\n" "/"`
	path=${path:0:-1}

	if [ "$path" == "" ]; then
		file="/"
	fi

	echo $path
}

basename $1