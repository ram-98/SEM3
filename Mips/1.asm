
# ========== Data
.data
array : .word 6, 9, 7, 1, 5
# ========== Code 
.text
.globl  main
main:

addi $s3, $zero, 0    # i=0
addi $t1, $zero, 0   # $t1=0
addi $t2, $s0, 0       # $t2 stores the address of a[0]
lw $t3, array          # takes first element

LOOP:
slti $t0, $s3, 5          # $t0=1 if i < 5  
beq $t0, $t1, EXIT    # if i >= 5, exit from the loop
lw $t4, 0($t2)           # load a[i] to $t4
slt $t0, $t4, $t3       # $t0=1 if i < 5
beq $t0,$t1, SWAP        #Go to swap
CON:
addi $s3, $s3, 1       # i=i+1
addi $t2, $t2, 4        # increment address of a[] by 4 bytes, 1 ptr
j LOOP
SWAP:
add $t3,$zero, $t4
j CON
EXIT: 
# Print the result in $t3 
	li $v0,1		# load print_int in $v0
	move $a0,$t3		# $a0 = $t3
	syscall  

li $v0,10
syscall



#/////////the largest value is stored in register t3/////////////////////////////

