.data
S0: .asciiz "input an integer:"
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
lw $8, 0($gp)
move $a0, $8
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
li $8, 1
move $a0, $8
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
li $8, 1
li $9, 2
add $10, $8, $9
move $a0, $10
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
li $v0, 10
syscall
