func="
sine
tanh
expPow
modG
Pol5
Pol4
"
for arg in $func
do
	./mkDatacards_run2.py --workdir new --function $arg --bias true --CATS 3,6
done
