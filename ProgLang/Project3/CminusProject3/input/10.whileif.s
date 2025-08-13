.data
S0: .asciiz "Enter a:"
newl: .asciiz "\n"
.text
.globl main
main :
la $a0, S0
li $v0, 4
syscall
la $a0, newl
syscall
li $8 8
add $8 $8 $gp
li $v0, 5
syscall
sw $v0, 0($8)
li $8 8
add $8 $8 $gp
lw $9, 0($8)
li $8, 2
div $9, $8
mfhi $10
mflo $10
li $8, 2
mult $10, $8
mfhi $9
mflo $9
li $8 8
add $8 $8 $gp
lw $10, 0($8)
seq $8, $9, $10
beq $8 $0 L0
li $8 4
add $8 $8 $gp
li $9, 1
sw $9, 0($8)
li $8 0
add $8 $8 $gp
li $9, 0
sw $9, 0($8)
L1:
li $8 4
add $8 $8 $gp
lw $9, 0($8)
li $8 8
add $8 $8 $gp
lw $10, 0($8)
sle $8, $9, $10
beq $8 $0 L2
li $8 0
add $8 $8 $gp
li $9 0
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
j L1
L2:
j L3
L0:
li $8 4
add $8 $8 $gp
li $9, 1
sw $9, 0($8)
li $8 0
add $8 $8 $gp
li $9, 1
sw $9, 0($8)
L4:
li $8 4
add $8 $8 $gp
lw $9, 0($8)
li $8 8
add $8 $8 $gp
lw $10, 0($8)
sle $8, $9, $10
beq $8 $0 L5
li $8 0
add $8 $8 $gp
li $9 0
add $9 $9 $gp
lw $10, 0($9)
li $9 4
add $9 $9 $gp
lw $11, 0($9)
mult $10, $11
mfhi $9
mflo $9
sw $9, 0($8)
li $8 4
add $8 $8 $gp
li $9 4
add $9 $9 $gp
lw $10, 0($9)
li $9, 1
add $11, $10, $9
sw $11, 0($8)
j L4
L5:
L3:
li $8 0
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
