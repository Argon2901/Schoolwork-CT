.data
S4: .asciiz "m = "
S3: .asciiz "l = "
S2: .asciiz "k = "
S1: .asciiz "j = "
S0: .asciiz "i = "
newl: .asciiz "\n"
.text
.globl main
main :
la $a0, S0
li $v0, 4
syscall
la $a0, newl
syscall
li $v0, 5
syscall
sw $v0, 0($gp)
la $a0, S1
li $v0, 4
syscall
la $a0, newl
syscall
li $v0, 5
syscall
sw $v0, 4($gp)
la $a0, S2
li $v0, 4
syscall
la $a0, newl
syscall
li $v0, 5
syscall
sw $v0, 8($gp)
la $a0, S3
li $v0, 4
syscall
la $a0, newl
syscall
li $v0, 5
syscall
sw $v0, 12($gp)
la $a0, S4
li $v0, 4
syscall
la $a0, newl
syscall
li $v0, 5
syscall
sw $v0, 16($gp)
lw $8, 8($gp)
lw $9, 4($gp)
lw $10, 12($gp)
add $11, $9, $10
slt $9, $8, $11
lw $8, 0($gp)
lw $10, 8($gp)
sne $11, $8, $10
seq $11, $11, $0
sne $9, $9, $0
sne $11, $11, $0
and $8, $9, $11
sw $8, 20($gp)
lw $8, 20($gp)
move $a0, $8
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
lw $8, 0($gp)
lw $9, 12($gp)
mult $8, $9
mfhi $10
mflo $10
lw $8, 4($gp)
lw $9, 8($gp)
mult $8, $9
mfhi $11
mflo $11
slt $8, $11, $10
li $9, 1
lw $10, 16($gp)
sle $11, $9, $10
or $9, $8, $11
sne $9, $9, $0
move $a0, $9
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
lw $8, 8($gp)
lw $9, 12($gp)
mult $8, $9
mfhi $10
mflo $10
lw $8, 4($gp)
lw $9, 8($gp)
add $11, $8, $9
lw $8, 12($gp)
add $9, $11, $8
slt $8, $9, $10
lw $9, 0($gp)
lw $10, 4($gp)
sne $11, $9, $10
sne $8, $8, $0
sne $11, $11, $0
and $9, $8, $11
lw $8, 12($gp)
lw $10, 20($gp)
slt $11, $10, $8
or $8, $9, $11
sne $8, $8, $0
move $a0, $8
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
lw $8, 12($gp)
lw $9, 4($gp)
div $8, $9
mfhi $10
mflo $10
lw $8, 0($gp)
sub $9, $10, $8
lw $8, 16($gp)
slt $10, $8, $9
lw $8, 8($gp)
lw $9, 12($gp)
lw $11, 20($gp)
mult $9, $11
mfhi $12
mflo $12
add $9, $8, $12
lw $8, 12($gp)
lw $11, 8($gp)
lw $12, 20($gp)
mult $11, $12
mfhi $13
mflo $13
add $11, $8, $13
sne $8, $9, $11
sne $10, $10, $0
sne $8, $8, $0
and $9, $10, $8
move $a0, $9
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
li $v0, 10
syscall
