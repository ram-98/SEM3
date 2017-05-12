    
# ========== Data
.data
array : .word 15, 7  #The two numbers divided into 32 and 32 bit in any manner
# ========== Code 
.text
.globl  main
main:
la $s0, array
addi $s3, $zero, 0    # i=0
addi $t1, $zero, 1   # $t1=1, constant for comparing
addi $t2, $s0, 0       # $t2 stores the address of a[0]
lw $t3, 0($t2)          # takes first element
add $a0,$zero,$t3   # going to function
jal LOOP      # call procedure
add $t5,$zero,$v0      # Result getting to t5
addi $t2, $t2, 4        # increment address of a[] by 4 bytes, 1 ptr
lw $t4, 0($t2)          # takes second element
add $a0,$zero,$t4   # second function call for another 32 bit
jal LOOP      # call procedure
add $t5,$zero,$v0      # Final Result
j EXIT
function:                   # Our function
    LOOP:                   
    and $s3, $t1, $a0       #and ing 1 and the input argument ,result stored in s3
    beq $s3, $t1, ADD       # Go to ADD to increase if s3 is 1
    CON:                    
    srl $a0, $a0, 1         #right shift by 1
    beq $a0, $zero, HAI     #GO to HAI and end the function if  all the digits in binary are checked
    j LOOP

    ADD:                    #increase count of 1's
    addi $s1, $s1, 1       # i=i+1      
    j CON                   #jump back to where u have left
    HAI:
    add $v0,$0,$s1      # Result
    jr $ra              # return (Copy $ra to PC)

EXIT: 
li $v0,10
syscall



#/////////the output  is stored in register t5/////////////////////////////

