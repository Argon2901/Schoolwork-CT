.data
newl: .asciiz "\n"
.text
.globl main
main :
li $8, 0
sll $8 $8 2
add $9 $8 $gp
li $8 0
add $9 $9 $8
li $8, 32
sw $8, 0($9)
li $8, 1
sll $8 $8 2
add $9 $8 $gp
li $8 0
add $9 $9 $8
li $8, 11
sw $8, 0($9)
li $8, 2
sll $8 $8 2
add $9 $8 $gp
li $8 0
add $9 $9 $8
li $8, 111
sw $8, 0($9)
li $8, 3
sll $8 $8 2
add $9 $8 $gp
li $8 0
add $9 $9 $8
li $8, 88
sw $8, 0($9)
li $8, 4
sll $8 $8 2
add $9 $8 $gp
li $8 0
add $9 $9 $8
li $8, 11
sw $8, 0($9)
li $8, 5
sll $8 $8 2
add $9 $8 $gp
li $8 0
add $9 $9 $8
li $8, 44
sw $8, 0($9)
li $8, 6
sll $8 $8 2
add $9 $8 $gp
li $8 0
add $9 $9 $8
li $8, 33
sw $8, 0($9)
li $8, 7
sll $8 $8 2
add $9 $8 $gp
li $8 0
add $9 $9 $8
li $8, 33
sw $8, 0($9)
li $8, 8
sll $8 $8 2
add $9 $8 $gp
li $8 0
add $9 $9 $8
li $8, 22
sw $8, 0($9)
li $8, 9
sll $8 $8 2
add $9 $8 $gp
li $8 0
add $9 $9 $8
li $8, 77
sw $8, 0($9)
li $8, 10
sll $8 $8 2
add $9 $8 $gp
li $8 0
add $9 $9 $8
li $8, 45
sw $8, 0($9)
li $8, 11
sll $8 $8 2
add $9 $8 $gp
li $8 0
add $9 $9 $8
li $8, 65
sw $8, 0($9)
li $8, 12
sll $8 $8 2
add $9 $8 $gp
li $8 0
add $9 $9 $8
li $8, 76
sw $8, 0($9)
li $8, 13
sll $8 $8 2
add $9 $8 $gp
li $8 0
add $9 $9 $8
li $8, 87
sw $8, 0($9)
li $8, 14
sll $8 $8 2
add $9 $8 $gp
li $8 0
add $9 $9 $8
li $8, 34
sw $8, 0($9)
li $8 60
add $8 $8 $gp
li $9, 0
sw $9, 0($8)
L0:
li $8 60
add $8 $8 $gp
lw $9, 0($8)
li $8, 14
slt $10, $9, $8
beq $10 $0 L1
li $8 72
add $8 $8 $gp
li $9 60
add $9 $9 $gp
lw $10, 0($9)
sw $10, 0($8)
li $8 64
add $8 $8 $gp
li $9 60
add $9 $9 $gp
lw $10, 0($9)
li $9, 1
add $11, $10, $9
sw $11, 0($8)
L2:
li $8 64
add $8 $8 $gp
lw $9, 0($8)
li $8, 15
slt $10, $9, $8
beq $10 $0 L3
li $8 64
add $8 $8 $gp
lw $9, 0($8)
sll $9 $9 2
add $8 $9 $gp
li $9 0
add $8 $8 $9
lw $9, 0($8)
li $8 72
add $8 $8 $gp
lw $10, 0($8)
sll $10 $10 2
add $8 $10 $gp
li $10 0
add $8 $8 $10
lw $10, 0($8)
slt $8, $9, $10
beq $8 $0 L4
li $8 72
add $8 $8 $gp
li $9 64
add $9 $9 $gp
lw $10, 0($9)
sw $10, 0($8)
j L5
L4:
L5:
li $8 64
add $8 $8 $gp
li $9 64
add $9 $9 $gp
lw $10, 0($9)
li $9, 1
add $11, $10, $9
sw $11, 0($8)
j L2
L3:
li $8 68
add $8 $8 $gp
li $9 60
add $9 $9 $gp
lw $10, 0($9)
sll $10 $10 2
add $9 $10 $gp
li $10 0
add $9 $9 $10
lw $10, 0($9)
sw $10, 0($8)
li $8 60
add $8 $8 $gp
lw $9, 0($8)
sll $9 $9 2
add $8 $9 $gp
li $9 0
add $8 $8 $9
li $9 72
add $9 $9 $gp
lw $10, 0($9)
sll $10 $10 2
add $9 $10 $gp
li $10 0
add $9 $9 $10
lw $10, 0($9)
sw $10, 0($8)
li $8 72
add $8 $8 $gp
lw $9, 0($8)
sll $9 $9 2
add $8 $9 $gp
li $9 0
add $8 $8 $9
li $9 68
add $9 $9 $gp
lw $10, 0($9)
sw $10, 0($8)
li $8 60
add $8 $8 $gp
li $9 60
add $9 $9 $gp
lw $10, 0($9)
li $9, 1
add $11, $10, $9
sw $11, 0($8)
j L0
L1:
li $8 60
add $8 $8 $gp
li $9, 0
sw $9, 0($8)
L6:
li $8 60
add $8 $8 $gp
lw $9, 0($8)
li $8, 15
slt $10, $9, $8
beq $10 $0 L7
li $8 60
add $8 $8 $gp
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
li $8 60
add $8 $8 $gp
li $9 60
add $9 $9 $gp
lw $10, 0($9)
li $9, 1
add $11, $10, $9
sw $11, 0($8)
j L6
L7:
li $v0, 10
syscall
