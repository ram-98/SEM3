.data
mylabel:
.asciiz "hello world\n"

.globl main
.text

main:
la $a0, mylabel
addi $v0, $0, 4 # set command to print
syscall
li $v0, 10
syscall

