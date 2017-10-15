for i in gen/*; do
	echo $i
	./quick_check.sh $i
done
