.data
array: .word 6, 10, 7, 1, 5
.text
main:
la $s0, array
add $t2, $s0, $zero
lw $t3, 0($t2)          
LOOP:
slti $t0, $s3, 5         
beq $t0, $t1, EXIT    
lw $t4, 0($t2)           
slt $t0, $t4, $t3       
beq $t0, $t1, SWAP       
CON:
addi $s3, $s3, 1       
addi $t2, $t2, 4        
j LOOP
SWAP:
add $t3, $zero, $t4
j CON
EXIT: 
li $v0, 10
syscall
