

array : .word C1
        .word C2
        .word C3
# ========== Code 
.text
.globl  main
main:
addi     $s0, $s0, 6
addi     $s1, $s1, 4
addi     $s2, $s2, 0
addi     $t2, $s2, 0

slt $t3, $s2, $zero # if k< 0 then $t3 = 1 else $t3=0
bne $t3, $zero, EXIT # if k< 0 then EXIT
slti $t3, $s2, 3  # if k<3 then $t3 = 1 else $t3=0
beq $t3, $zero, EXIT

la      $t0, array     # load start address of the array
add     $t2, $t2, $t2
add     $t2, $t2, $t2
add     $t0, $t0, $t2 # add offset to table address
lw   $t4, 0($t0)   # load the address stored 
jr      $t1           #  jump to address

C1:
add $s3, $s0, $s1 # l = i + j
j EXIT
C2:
sub $s3, $s0, $s1 # l = i - j
j EXIT
C3:     
add $s3, $s0, $s1 # l = i * j
j EXIT

EXIT: 
li $v0,10
syscall

