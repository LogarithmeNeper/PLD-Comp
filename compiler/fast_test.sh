DESTNAME=$1
SOURCENAME=$2

./ifcc $SOURCENAME >asm-pld.s
gcc -o $DESTNAME asm-pld.s
./exe

echo retcode=$?

# forward exit status of the compiler
exit $retcode
