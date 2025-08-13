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
lw $13, 4($gp)
add $14, $12, $13
lw $12, 8($gp)
lw $13, 12($gp)
mult $12, $13
mfhi $15
mflo $15
add $12, $14, $15
move $a0, $12
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
lw $12, 0($gp)
lw $13, 12($gp)
lw $14, 0($gp)
sub $15, $13, $14
lw $13, 8($gp)
div $15, $13
mfhi $14
mflo $14
add $13, $12, $14
lw $12, 4($gp)
add $14, $13, $12
move $a0, $14
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
li $v0, 10
syscall
