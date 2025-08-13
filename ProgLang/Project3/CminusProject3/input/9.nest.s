.data
newl: .asciiz "\n"
.text
.globl main
main :
li $8 0
add $8 $8 $gp
li $9, 0
sw $9, 0($8)
L0:
li $8 0
add $8 $8 $gp
lw $9, 0($8)
li $8, 50
slt $10, $9, $8
beq $10 $0 L1
li $8 4
add $8 $8 $gp
li $9, 0
sw $9, 0($8)
L2:
li $8 4
add $8 $8 $gp
lw $9, 0($8)
li $8, 10
slt $10, $9, $8
beq $10 $0 L3
li $8 0
add $8 $8 $gp
lw $9, 0($8)
li $8 4
add $8 $8 $gp
lw $10, 0($8)
add $8, $9, $10
move $a0, $8
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
li $8 4
add $8 $8 $gp
li $9 4
add $9 $9 $gp
lw $10, 0($9)
li $9, 2
add $11, $10, $9
sw $11, 0($8)
j L2
L3:
li $8 8
add $8 $8 $gp
li $9, 0
li $10 4
add $10 $10 $gp
lw $11, 0($10)
sub $10, $9, $11
sw $10, 0($8)
L4:
li $8 8
add $8 $8 $gp
lw $9, 0($8)
li $8 4
add $8 $8 $gp
lw $10, 0($8)
sne $8, $9, $10
beq $8 $0 L5
li $8 8
add $8 $8 $gp
lw $9, 0($8)
move $a0, $9
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
li $8 8
add $8 $8 $gp
li $9 8
add $9 $9 $gp
lw $10, 0($9)
li $9, 1
add $11, $10, $9
sw $11, 0($8)
j L4
L5:
li $8 0
add $8 $8 $gp
li $9 0
add $9 $9 $gp
lw $10, 0($9)
li $9, 10
add $11, $10, $9
sw $11, 0($8)
j L0
L1:
li $v0, 10
syscall
