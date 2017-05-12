    

JumpTable:  .word C1 
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
addi     $s3, $s3, 0



slt $t3, $s2, $zero # if k< 0 then $t3 = 1 else $t3=0
bne $t3, $zero, EXIT # if k< 0 then EXIT
slti $t3, $s2, 3  # if k<3 then $t3 = 1 else $t3=0
beq $t3, $zero, EXIT

la      $t5, JumpTable     # load start address of the Jumptable
add     $t2, $t2, $t2     #getting nxt address if k=1 or 2
add     $t2, $t2, $t2
add     $t5, $t5, $t2       # add offset to table address
lw      $t4, 0($t5)                # load the address stored 
jr      $t4                    #  jump to address

C1: add $s3, $s0, $s1                   # l = i + j
    j EXIT
C2: sub $s3, $s0, $s1                    # l = i - j
    j EXIT
C3: 
    loop:
    slt $t0, $s3, $s2
    beq $t0,$zero,end
    add $s3, $s1, $s1
    j loop  
    end:                 # l = i * j
    j EXIT

EXIT: 
li $v0,10
syscall

