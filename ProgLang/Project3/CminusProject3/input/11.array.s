.data
newl: .asciiz "\n"
.text
.globl main
main :
li $8, 3
sll $8 $8 2
add $9 $8 $gp
li $8 0
add $9 $9 $8
li $8, 4
sw $8, 0($9)
li $8, 3
sll $8 $8 2
add $9 $8 $gp
li $8 0
add $9 $9 $8
lw $8, 0($9)
move $a0, $8
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
li $v0, 10
syscall
