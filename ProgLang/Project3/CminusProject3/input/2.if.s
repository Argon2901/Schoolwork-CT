.data
S1: .asciiz "Compelte"
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
li $8 0
add $8 $8 $gp
lw $9, 0($8)
li $8, 0
slt $10, $8, $9
beq $10 $0 L0
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
la $a0, S1
li $v0, 4
syscall
la $a0, newl
syscall
li $v0, 10
syscall
