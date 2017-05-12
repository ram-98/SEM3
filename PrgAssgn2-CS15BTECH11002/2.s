.data
array: .word 6, 9, 7, 1, 5
array1: .word 11, 12
array2: .word 13, 14
.text
main:
bne $t4, $t3, jump
la $s1, array
la $s2, array1
la $s7, array2
lw $s3, 4($s1)
lw $s4, 4($s2)
addi $t3, $zero, 112
addi $t4, $zero, 113
sw $t3, 12($s1)
sw $t4, 4($s2)
jump:
lw $t5, 12($s1)	
lw $t6, 4($s2)
lw $a0, 0($s7)	
lw $a1, 4($s7)

ori $t1, $t2, 2

li $v0, 10
syscall
