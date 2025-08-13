.data
newl: .asciiz "\n"
.text
.globl main
main :
li $8, 1
sw $8, 0($gp)
li $8, 0
sw $8, 4($gp)
lw $8, 0($gp)
move $a0, $8
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
lw $8, 4($gp)
seq $8, $8, $0
move $a0, $8
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
lw $8, 4($gp)
move $a0, $8
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
lw $8, 0($gp)
seq $8, $8, $0
move $a0, $8
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
li $v0, 10
syscall
