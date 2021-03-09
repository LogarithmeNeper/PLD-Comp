SOURCENAME=$1

./ifcc $SOURCENAME >asm-pld.s
gcc -o exe-pld asm-pld.s
./exe-pld

echo retcode=$?

# forward exit status of the compiler
exit $retcode
