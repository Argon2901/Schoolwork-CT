.data
newl: .asciiz "\n"
.text
.globl main
main :
li $8, 1
sw $8, 0($gp)
li $8, 2
sw $8, 4($gp)
li $8, 3
sw $8, 8($gp)
li $8, 4
sw $8, 12($gp)
lw $8, 0($gp)
lw $9, 4($gp)
seq $10, $8, $9
move $a0, $10
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
lw $8, 0($gp)
lw $9, 0($gp)
sne $10, $8, $9
move $a0, $10
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
lw $8, 8($gp)
lw $9, 8($gp)
seq $10, $8, $9
move $a0, $10
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
lw $8, 8($gp)
lw $9, 12($gp)
sne $10, $8, $9
move $a0, $10
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
li $v0, 10
syscall
