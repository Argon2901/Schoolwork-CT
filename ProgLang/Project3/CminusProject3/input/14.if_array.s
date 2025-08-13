.data
S1: .asciiz "out of bound!"
S0: .asciiz "enter i ="
newl: .asciiz "\n"
.text
.globl main
main :
la $a0, S0
li $v0, 4
syscall
la $a0, newl
syscall
li $8 400
add $8 $8 $gp
li $v0, 5
syscall
sw $v0, 0($8)
li $8 400
add $8 $8 $gp
lw $9, 0($8)
li $8, 0
slt $10, $9, $8
li $8 400
add $8 $8 $gp
lw $9, 0($8)
li $8, 100
sle $11, $8, $9
or $8, $10, $11
sne $8, $8, $0
beq $8 $0 L0
la $a0, S1
li $v0, 4
syscall
la $a0, newl
syscall
j L1
L0:
li $8 400
add $8 $8 $gp
lw $9, 0($8)
sll $9 $9 2
add $8 $9 $gp
li $9 0
add $8 $8 $9
li $9 400
add $9 $9 $gp
lw $10, 0($9)
li $9, 2
mult $10, $9
mfhi $11
mflo $11
sw $11, 0($8)
li $8, 5
sll $8 $8 2
add $9 $8 $gp
li $8 0
add $9 $9 $8
li $8, 5
sw $8, 0($9)
li $8 400
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
L1:
li $v0, 10
syscall
