.text
main:
addi $t0, $zero, 4
add $t1, $zero, $t0
addi $t2, $t0, 2
sub $t3, $t2, $t0
mul $t4, $t3, $t1
beq $zero, $zero, JUMP
mul $t4, $t3, $t1
JUMP:
and $s0, $t3, $zero
andi $s1, $t3, 1
or $s2, $t3, $t0
ori $s3, $zero, 1
bne $s0, $s2, JUMP2
mul $s7, $t3, $t1
JUMP2:
nor $s6, $zero, $zero

halt
