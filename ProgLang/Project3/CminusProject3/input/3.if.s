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
li $8 0
add $8 $8 $gp
li $v0, 5
syscall
sw $v0, 0($8)
li $8 0
add $8 $8 $gp
lw $9, 0($8)
beq $9 $0 L0
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
move $a0, $9
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
j L1
L0:
li $8 4
add $8 $8 $gp
li $9 0
add $9 $9 $gp
lw $10, 0($9)
sw $10, 0($8)
li $8 4
add $8 $8 $gp
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
