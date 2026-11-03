sed 's/[ \t]*$//' $1 > $1__.tmp
cat $1__.tmp > $1
rm $1__.tmp
