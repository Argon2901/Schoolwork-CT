.data
newl: .asciiz "\n"
.text
.globl main
main :
li $8, 1
sw $8, 0($gp)
li $9, 2
sw $9, 4($gp)
li $10, 3
sw $10, 8($gp)
li $11, 4
sw $11, 12($gp)
lw $12, 0($gp)
li $13, 7
add $14, $12, $13
sw $14, 16($gp)
lw $12, 16($gp)
move $a0, $12
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
lw $12, 12($gp)
li $13, 5
sub $15, $12, $13
sw $15, 20($gp)
lw $12, 20($gp)
move $a0, $12
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
lw $12, 4($gp)
lw $13, 8($gp)
mult $12, $13
mfhi $16
mflo $16
lw $12, 12($gp)
mult $16, $12
mfhi $13
mflo $13
move $a0, $13
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
lw $12, 4($gp)
lw $13, 8($gp)
mult $12, $13
mfhi $16
mflo $16
lw $12, 12($gp)
sub $13, $16, $12
move $a0, $13
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
lw $12, 0($gp)
lw $13, 4($gp)
add $16, $12, $13
lw $12, 8($gp)
lw $13, 12($gp)
mult $12, $13
mfhi $17
mflo $17
add $12, $16, $17
move $a0, $12
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
lw $12, 8($gp)
lw $13, 12($gp)
mult $12, $13
mfhi $16
mflo $16
lw $12, 4($gp)
div $16, $12
mfhi $13
mflo $13
lw $12, 0($gp)
sub $16, $13, $12
move $a0, $16
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
lw $12, 0($gp)
lw $13, 4($gp)
add $16, $12, $13
lw $12, 8($gp)
lw $13, 0($gp)
lw $17, 16($gp)
mult $13, $17
mfhi $18
mflo $18
add $13, $12, $18
mult $16, $13
mfhi $12
mflo $12
lw $13, 20($gp)
div $12, $13
mfhi $16
mflo $16
move $a0, $16
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
li $v0, 10
syscall
