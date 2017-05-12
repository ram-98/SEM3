
# ========== Data
.data
str1 : .asciiz "enter -> 1 for A.P. , any other number for Randomization of sequence\n"
str2 : .asciiz "enter size of sequence:\n"
str3 : .asciiz "enter first integer of sequence:\n"  
str4 : .asciiz "enter common difference:\n"
str5 : .asciiz "the no of comparisions are   ---"

SIZE : .word 4
STYPE : .word 4
init : .word 4
cd : .word 4
array: .space 600
mylabel:
.asciiz "\n"

# ========== Code 
.text
.globl  main
main:
    addi $s6, $zero, 0      #for counting comparisions
    la $a0, str1 
    li $v0, 4
    syscall
    li $v0, 5
    syscall
    la $t0, STYPE
    sw $v0, 0($t0)
    la $t1, SIZE        #array

    la $a0, str2
    li $v0, 4
    syscall
    li $v0, 5
    syscall
    sw $v0, 0($t1)
    addi $t7, $zero , 1
    lw $s1, 0($t0)
    la $t1, SIZE
    lw $s2, 0($t1)          #size
    beq $s1, $t7, AP
    j Rand

AP :
    la $a0, str3
    li $v0, 4
    syscall
    li $v0, 5
    syscall
    la $t6, init
    sw $v0, 0($t6)
    la $a0, str4
    li $v0, 4
    syscall
    li $v0, 5
    syscall
    la $t6, cd
    sw $v0, 0($t6)
    la $t0, init
    lw $s0, 0($t0)          #intial
    la $t0, cd               #cd
    lw $s1, 0($t0)
    addi $t0, $zero, 0
    j loopAP


    loopAP :
    slt $t3, $t0, $s2
    beq $t3, $zero, next
    la $t5, array
    sll $t3, $t0, 2
    add $t5, $t5, $t3       #next array element
    mul $t1, $t0, $s1       #cd
    add $t6, $t1, $s0       #term 
    sw $t6, 0($t5)
    addi $t0, $t0, 1
    j loopAP

Rand :
    addi $s4, $zero, 41
    addi $t0, $zero, 0
    j Randloop
    Randloop :
        slt $t3, $t0, $s2
        beq $t3, $zero, next
        la $t5, array
        sll $t3, $t0, 2
        add $t5, $t5, $t3
        sll $t2, $s4, 13
        xor $s4, $s4, $t2
        srl $t3, $s4, 17
        xor $s4, $s4, $t3
        sll $t6, $s4, 5
        xor $s4, $s4, $t6

        sw $s4, 0($t5)
        addi $t0, $t0, 1
        j Randloop

next:

la $s0, array
la $a1, SIZE
lw $a1, 0($a1)
addi $t7, $s0, 0
addi $s0, $s0, 4
addi $s5, $s0, 0
addi $s3, $zero, 1    # i=1
addi $t1, $zero, 0   # $t1=0

firstloop:
slt $t0, $s3, $a1          # 1st loop $t0=1 if i < SIZE  
beq $t0, $t1, set  # if i >= 5, exit from the loop
lw $t2, 0($s5)
addi $s1, $s5, 0
addi $s2, $s3, 0

secondloop:             
addi $s1, $s1, -4           #2nd loop
lw $t3, 0($s1)
slt $t4, $zero, $s2
beq $s2, $zero, decrease 
comeback:
slt $t5, $t2, $t3
and $t6, $t4, $t5 
bne $t6, $t1, SWAP         #Go to SWAP
addi $s6, $s6, 1
sll $a0, $s2, 2
add $a0, $t7, $a0
sw $t2, 0($a0)
addi $s3, $s3, 1
addi $s5, $s5, 4
j firstloop

SWAP:
sll $a0, $s2, 2         #swapping
add $a0, $t7, $a0
addi $s6, $s6, 1
sw $t3, 0($a0)
addi $s2, $s2, -1
j secondloop

decrease:
addi $s6, $s6, -1
j comeback

set:
    addi $s3, $zero, 0
    la $t3, SIZE
    lw $t2, 0($t3)
        
    la $a0, str5 
    li $v0, 4
    syscall
    li $v0, 1
    addi $a0, $s6, 0
    syscall
   la $a0, mylabel
    addi $v0, $zero, 4 
    syscall 
    j print

print:
    addi $s3, $s3, 1
    lw $t0, 0($t7)
    li $v0, 1
    move $a0, $t0
    syscall
    la $a0, mylabel
    addi $v0, $zero, 4 # set command to print
    syscall
    addi $t7, $t7, 4
    slt $t0, $s3, $t2          # $t0=1 if i < 5  
     bne $t1, $t0, print 
     j exit

exit:
     li $v0, 10
    syscall


