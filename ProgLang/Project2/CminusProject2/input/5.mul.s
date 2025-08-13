.data
newl: .asciiz "\n"
.text
.globl main
main :
li $8, 10
li $9, 20
mult $8, $9
mfhi $10
mflo $10
move $a0, $10
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
li $8, 7
sw $8, 0($gp)
li $9, 3
sw $9, 8($gp)
li $10, 4
sw $10, 12($gp)
lw $11, 0($gp)
lw $12, 8($gp)
mult $11, $12
mfhi $13
mflo $13
lw $11, 12($gp)
mult $13, $11
mfhi $12
mflo $12
sw $12, 4($gp)
lw $11, 4($gp)
move $a0, $11
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
li $v0, 10
syscall
