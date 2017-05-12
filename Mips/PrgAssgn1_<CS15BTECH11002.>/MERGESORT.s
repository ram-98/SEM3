
.data
str1 : .asciiz "enter -> 1 for A.P. , any other number for Randomization of sequence\n"
str2 : .asciiz "enter size of sequence:\n"
str3 : .asciiz "enter first integer of sequence:\n"  
str4 : .asciiz "enter common difference:\n"
str5 : .asciiz "the no of comparisions are   ---"
str6 : .asciiz "the original sequence is \n"
SIZE : .word 4
STYPE : .word 4
init : .word 4
cd : .word 4
array: .space 600
arr : .space 600


mylabel:
.asciiz "\n"
.text
.globl main
main:                               #taking input from user
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

AP :                            #generating ap seqence 
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
    beq $t3, $zero, setprint1
    la $t5, array
    sll $t3, $t0, 2
    add $t5, $t5, $t3       #next array element
    mul $t1, $t0, $s1       #cd
    add $t6, $t1, $s0       #term 
    sw $t6, 0($t5)
    addi $t0, $t0, 1
    j loopAP

Rand :                           #generating random sequence
    addi $s4, $zero, 7
    addi $t0, $zero, 0
    j Randloop
    Randloop :
        slt $t3, $t0, $s2
        beq $t3, $zero, setprint1
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
   #                            #here the main program starts 
    la $t0, SIZE
    addi  $t6, $zero, 0         #count for comparisions
    lw $s6, 0($t0)
    addi $a1, $s6 , -1
    addi $a2, $zero, 0
    addi $s3, $zero, 0
    # call to mergeSort here
    jal mergesort               #call to mergesort
    j setprint                  # after finishing print
setprint1:                          #printing original array
    addi $s3, $zero, 0
    addi $t1, $zero, 1
    la $t3, SIZE
    lw $t2, 0($t3)
    la $t7, array
    la $a0, str6 
    li $v0, 4
    syscall
   la $a0, mylabel
    addi $v0, $zero, 4 
    syscall 
    j print1
print1:
    addi $s3, $s3, 1
    lw $t0, 0($t7)
    li $v0, 1
    move $a0, $t0
    syscall
    la $a0, mylabel
    addi $v0, $zero, 4 # set command to print
    syscall
    addi $t7, $t7, 4
    slt $t0, $s3, $t2       # $t0=1 if i < SIZE  
     beq $t1, $t0, print1
     j next
    
mergesort:                      # recursively calling mergesort
    # merge subprogram here
    addi $sp, $sp, -16
    sw $ra, 0($sp)
    sw $a2, 4($sp)
    sw $a1, 8($sp)
    beq $a2, $a1, mergesortend
    add $a1, $a1, $a2
    srl $a1, $a1 , 1
    sw $a1, 12($sp)
    jal mergesort
    lw $a2, 12($sp)
    addi $a2, $a2, 1
    lw $a1, 8($sp)
    jal mergesort
    lw $a1, 4($sp)       #start
    lw $a2, 12($sp)      #middle
    lw $a3, 8($sp)      #end
    jal merge 
    j mergesortend

merge:                              #merging subarrays using  temp array "arr"
    # merge subprogram here 
    # a1low, a2mid,a3hi
    addi $t0, $a1, 0        # start  in t0
    move $t2, $t0
    move $t1, $a2
    addi $t1, $t1, 1        #mid + 1 in t1 
    la $s0, array           # original array in s0
    la $s6, arr             #temp array in s6
    sll $t3, $a1, 2
    add $s1, $t3, $s0       #1st element position in array1
    #move $s3, $s1
    add $s3, $t3, $s6       #1st element position in temparray
    sll $t3, $t1, 2++
    add $s2, $s0, $t3       #1st element position in array2

    loop1:
    slt $t4, $a2, $t0
    bne $t4, $zero, loop2
    slt $t4, $a3, $t1
    bne $t4, $zero, loop2
    lw $s4, 0($s1)
    lw $s5, 0($s2)
    slt $t3, $s4, $s5
    addi $t6, $t6, 1
    bne $t3, $zero, if
    sw $s5, 0($s3)
    addi $s2, $s2, 4
    addi $t1, $t1, 1
    addi $s3, $s3, 4
    addi $t2, $t2, 1
    j loop1
    if :

    sw $s4, 0($s3)
    addi $s1, $s1, 4
    addi $t0, $t0, 1
    addi $s3, $s3, 4
    addi $t2, $t2, 1
    j loop1
    loop2:
    slt $t3, $a2, $t0
    bne $t3, $zero, loop3
    lw $s4, 0($s1)
    sw $s4, 0($s3)
    addi $s1, $s1, 4
    addi $t0, $t0, 1
    addi $s3, $s3, 4
    addi $t2, $t2, 1
    j loop2
    loop3 :
    slt $t3, $a3,$t1
    bne $t3, $zero, loop4
    lw $s5, 0($s2)
    sw $s5, 0($s3)
    addi $s2, $s2, 4
    addi $t1, $t1, 1
    addi $s3, $s3, 4
    addi $t2, $t2, 1
    j loop3
    loop4:
    slt $t3, $a3, $a1
    bne $zero, $t3, finishmerge
    la $t0, array
    la $t1, arr
    sll $t3, $a1, 2
    add $t0, $t0, $t3
    add $t1, $t1, $t3
    lw $t5, 0($t1)
    sw $t5, 0($t0)
    
    addi $a1, $a1, 1
    j loop4

    finishmerge:
    jr $ra
mergesortend:
    lw $ra, 0($sp)
    addi $sp, $sp, 16
    jr $ra
setprint:                           #finally printing original array
    addi $s3, $zero, 0
    addi $t1, $zero, 1
    la $t3, SIZE
    lw $t2, 0($t3)
    la $t7, array
    la $a0, str5 
    li $v0, 4
    syscall
    li $v0, 1
    addi $a0, $t6, 0
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
    slt $t0, $s3, $t2       # $t0=1 if i < SIZE  
     beq $t1, $t0, print
     j exit
exit:
    li $v0, 10 # system call to exit the program
    syscall
