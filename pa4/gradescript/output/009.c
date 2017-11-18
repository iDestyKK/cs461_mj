alloc i 64
alloc a 4
func main
localloc 4
localloc 4
localloc 8
bgnstmt 9
t1 := local 1
t2 := 2
t3 := t1 =i t2
bgnstmt 10
t4 := local 0
t5 := local 1
t6 := @i t5
t7 := t4 =i t6
bgnstmt 11
t8 := local 2
t9 := local 0
t10 := local 1
t11 := @i t10
t12 := t9 =i t11
t13 := cvf t12
t14 := t8 =f t13
fend
