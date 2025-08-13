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
li $8 -4
add $8 $8 $sp
li $9, 3
sw $9, 0($8)
li $8 -4
add $8 $8 $sp
lw $9, 0($8)
sll $9 $9 2
add $8 $9 $gp
li $9 0
add $8 $8 $9
li $9, 7
sw $9, 0($8)
li $8 -4
add $8 $8 $sp
lw $9, 0($8)
sll $9 $9 2
add $8 $9 $gp
li $9 0
add $8 $8 $9
lw $9, 0($8)
move $a0, $9
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
li $8 -4
add $8 $8 $sp
li $9 -4
add $9 $9 $sp
lw $10, 0($9)
li $9, 2
add $11, $10, $9
sw $11, 0($8)
li $8 -4
add $8 $8 $sp
lw $9, 0($8)
sll $9 $9 2
add $8 $9 $gp
li $9 0
add $8 $8 $9
li $9, 22
sw $9, 0($8)
li $8, 5
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
