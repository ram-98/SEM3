#  Sort a list of numbers using insertion sort.

# -----
#	Arguments:
#	$a0 - starting address of the list
#	$a1 - list length

#	Returns:
#	n/a

.globl insertionSort
.ent insertionSort
insertionSort:
#	YOUR CODE GOES HERE
	 move  $t0, $a0		# t0=list
  
	li	$t1, 1			 # i=1
	lw	$t2, ($a1)		# t2=len
	sub $t2, $t2, 1		# t2=len-1
  
forloop:
	bne $t1, $t2, endforlp
	mul $t3, $t1, 4
	addu $t3, $t3, $a0
	lw  $t5, ($t3)		# value=arr[i] $t5=value
	subu $t6, $t1, 1	# j = i - 1  $t6 = j
  
	whileloop:
		blt $t6, 0, donewhilelp  # j>=0 exit while loop
		mul $t8, $t6, 4
		addu $t0, $t8, $a0
		lw $t8, ($t0)   # $t8=arr[j]
		bge $t8, $t5, donewhilelp # arr[j] > value exit while loop		
		add $t7, $t6, 1	# j+1
		mul $t7, $t7, 4
		addu $t7, $t7, $a0 # $t7=arr[j+1]
		sw $t8, ($t7)		# arr[j+1]=arr[j]
		sub $t6, $t6, 1	 # j = j -1
		b	whileloop
	donewhilelp:
	add $t7, $t6, 1
	mul $t7, $t7, 4
	addu $t7, $t7, $a0 #$7=arr[j+1]
	sw $t5, ($t7)   # arr[j+1] = value
	add $t1, $t1, 1  # i++
	b forloop
endforlp:
	
	jr	$ra
.end insertionSort
