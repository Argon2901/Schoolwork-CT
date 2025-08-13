.data
S0: .asciiz "enter a:"
newl: .asciiz "\n"
.text
.globl main
main :
la $a0, S0
li $v0, 4
syscall
la $a0, newl
syscall
li $8 0
add $8 $8 $gp
li $v0, 5
syscall
sw $v0, 0($8)
li $8 8
add $8 $8 $gp
li $9, 0
sw $9, 0($8)
li $8 4
add $8 $8 $gp
li $9, 0
sw $9, 0($8)
L0:
li $8 4
add $8 $8 $gp
lw $9, 0($8)
li $8 0
add $8 $8 $gp
lw $10, 0($8)
sle $8, $9, $10
li $9 4
add $9 $9 $gp
lw $10, 0($9)
li $9, 100
sle $11, $10, $9
sne $8, $8, $0
sne $11, $11, $0
and $9, $8, $11
beq $9 $0 L1
li $8 8
add $8 $8 $gp
li $9 8
add $9 $9 $gp
lw $10, 0($9)
li $9 4
add $9 $9 $gp
lw $11, 0($9)
add $9, $10, $11
sw $9, 0($8)
li $8 4
add $8 $8 $gp
li $9 4
add $9 $9 $gp
lw $10, 0($9)
li $9, 1
add $11, $10, $9
sw $11, 0($8)
j L0
L1:
li $8 8
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
