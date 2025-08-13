.data
newl: .asciiz "\n"
.text
.globl main
main :
li $8 0
add $8 $8 $gp
li $9, 0
sw $9, 0($8)
li $8 4
add $8 $8 $gp
li $9 0
add $9 $9 $gp
lw $10, 0($9)
li $9, 2
sub $11, $10, $9
sw $11, 0($8)
li $8 0
add $8 $8 $gp
lw $9, 0($8)
beq $9 $0 L0
li $8, 1
move $a0, $8
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
j L1
L0:
li $8, 0
move $a0, $8
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
L1:
li $8 4
add $8 $8 $gp
lw $9, 0($8)
beq $9 $0 L2
li $8 0
add $8 $8 $gp
lw $9, 0($8)
beq $9 $0 L3
li $8, 0
move $a0, $8
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
j L4
L3:
li $8, 1
move $a0, $8
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
L4:
j L5
L2:
li $8, 0
move $a0, $8
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
L5:
li $v0, 10
syscall
