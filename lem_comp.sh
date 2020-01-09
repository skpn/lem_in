
if [ $# -lt 1 ]; then
	echo "missing arguments"
	exit 1
fi

exec="${1}"

echo "testing $exec"

for ((i=2; i<=$#; i++)); do
	file=${!i}
	if [ ! -f $file ]; then
		echo "$file does not exist"
		exit 1
	else
		echo -ne "\n ----  $file  ----  "
		./$exec < $file
		grep -m 1 "required" $file
	fi
done

