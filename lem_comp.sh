
if [ $# -lt 1 ]; then
	echo "missing arguments"
	exit 1
fi

exec="${1}"

echo "testing $exec"

idx=1
while [ $idx -lt "$#" ] ; do
	idx=$(($idx+1))
	file=${!idx}
	echo "----  $file  ----"
	if [ ! -f $file ]; then
		echo "file does not exist"
		exit 1
	else
		time ./$exec < $file > output
		grep -m 1 "required" $file
		echo -ne "$exec number of lines: "
		cat output | grep "^L.*$" | wc -l
	fi
done

