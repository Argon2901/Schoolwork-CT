.data
newl: .asciiz "\n"
.text
.globl main
main :
li $8 4
add $8 $8 $gp
li $9, 1
sw $9, 0($8)
L0:
li $8 4
add $8 $8 $gp
lw $9, 0($8)
li $8, 10
sle $10, $9, $8
beq $10 $0 L1
li $8 0
add $8 $8 $gp
li $9, 1
sw $9, 0($8)
L2:
li $8 0
add $8 $8 $gp
lw $9, 0($8)
li $8, 10
sle $10, $9, $8
beq $10 $0 L3
li $8 0
add $8 $8 $gp
lw $9, 0($8)
li $8 4
add $8 $8 $gp
lw $10, 0($8)
mult $9, $10
mfhi $8
mflo $8
move $a0, $8
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
li $8 0
add $8 $8 $gp
li $9 0
add $9 $9 $gp
lw $10, 0($9)
li $9, 1
add $11, $10, $9
sw $11, 0($8)
j L2
L3:
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
li $v0, 10
syscall
