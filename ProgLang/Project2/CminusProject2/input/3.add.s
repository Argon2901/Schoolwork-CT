.data
newl: .asciiz "\n"
.text
.globl main
main :
li $8, 10
li $9, 20
add $10, $8, $9
move $a0, $10
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
li $8, 1
sw $8, 0($gp)
li $9, 3
sw $9, 8($gp)
li $10, 4
sw $10, 12($gp)
lw $11, 0($gp)
lw $12, 8($gp)
add $13, $11, $12
lw $11, 12($gp)
add $12, $13, $11
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
