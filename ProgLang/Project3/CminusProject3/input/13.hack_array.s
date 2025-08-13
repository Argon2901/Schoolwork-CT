.data
newl: .asciiz "\n"
.text
.globl main
main :
li $8 0
add $8 $8 $gp
li $9, 3
sw $9, 0($8)
li $8 4
add $8 $8 $gp
li $9, 4
sw $9, 0($8)
li $8 8
add $8 $8 $gp
li $9, 5
sw $9, 0($8)
li $8 52
add $8 $8 $gp
li $9, 13
sw $9, 0($8)
li $8 56
add $8 $8 $gp
li $9, 14
sw $9, 0($8)
li $8 60
add $8 $8 $gp
li $9, 15
sw $9, 0($8)
li $8 4
add $8 $8 $gp
li $9, 0
li $10 0
add $10 $10 $gp
lw $11, 0($10)
sub $10, $9, $11
sw $10, 0($8)
li $8 4
add $8 $8 $gp
lw $9, 0($8)
sll $9 $9 2
add $8 $9 $gp
li $9 12
add $8 $8 $9
lw $9, 0($8)
move $a0, $9
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
li $8, 11
sll $8 $8 2
add $9 $8 $gp
li $8 12
add $9 $9 $8
lw $8, 0($9)
move $a0, $8
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
li $8 60
add $8 $8 $gp
lw $9, 0($8)
move $a0, $9
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
li $8, 12
sll $8 $8 2
add $9 $8 $gp
li $8 12
add $9 $9 $8
li $8, 100
sw $8, 0($9)
li $8 60
add $8 $8 $gp
lw $9, 0($8)
move $a0, $9
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
li $v0, 10
syscall
