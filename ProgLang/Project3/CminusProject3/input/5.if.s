.data
S5: .asciiz "b = "
S4: .asciiz "a = "
S3: .asciiz "b = "
S2: .asciiz "a = "
S1: .asciiz "enter b:"
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
la $a0, S1
li $v0, 4
syscall
la $a0, newl
syscall
li $8 4
add $8 $8 $gp
li $v0, 5
syscall
sw $v0, 0($8)
li $8 4
add $8 $8 $gp
lw $9, 0($8)
li $8 0
add $8 $8 $gp
lw $10, 0($8)
slt $8, $10, $9
beq $8 $0 L0
li $8 0
add $8 $8 $gp
lw $9, 0($8)
li $8, 0
slt $10, $8, $9
beq $10 $0 L1
la $a0, S2
li $v0, 4
syscall
la $a0, newl
syscall
li $8 0
add $8 $8 $gp
lw $9, 0($8)
move $a0, $9
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
j L2
L1:
la $a0, S3
li $v0, 4
syscall
la $a0, newl
syscall
li $8 4
add $8 $8 $gp
lw $9, 0($8)
move $a0, $9
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
L2:
j L3
L0:
li $8 0
add $8 $8 $gp
lw $9, 0($8)
li $8, 0
slt $10, $9, $8
beq $10 $0 L4
la $a0, S4
li $v0, 4
syscall
la $a0, newl
syscall
li $8 0
add $8 $8 $gp
lw $9, 0($8)
move $a0, $9
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
j L5
L4:
la $a0, S5
li $v0, 4
syscall
la $a0, newl
syscall
li $8 4
add $8 $8 $gp
lw $9, 0($8)
move $a0, $9
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
L5:
L3:
li $v0, 10
syscall
