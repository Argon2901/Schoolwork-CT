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
slt $10, $8, $9
sw $10, 16($gp)
lw $8, 16($gp)
li $9, 1
sne $8, $8, $0
sne $9, $9, $0
and $10, $8, $9
move $a0, $10
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
lw $8, 12($gp)
lw $9, 8($gp)
slt $10, $9, $8
move $a0, $10
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
lw $8, 12($gp)
lw $9, 8($gp)
slt $10, $9, $8
seq $10, $10, $0
move $a0, $10
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
li $8, 0
lw $9, 0($gp)
lw $10, 4($gp)
slt $11, $9, $10
lw $9, 8($gp)
lw $10, 12($gp)
sne $12, $9, $10
sne $11, $11, $0
sne $12, $12, $0
and $9, $11, $12
or $10, $8, $9
sne $10, $10, $0
move $a0, $10
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
li $v0, 10
syscall
