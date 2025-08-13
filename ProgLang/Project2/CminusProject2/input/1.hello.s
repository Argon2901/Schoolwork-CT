.data
S1: .asciiz "How are you?"
S0: .asciiz "Hello world!"
newl: .asciiz "\n"
.text
.globl main
main :
la $a0, S0
li $v0, 4
syscall
la $a0, newl
syscall
la $a0, S1
li $v0, 4
syscall
la $a0, newl
syscall
li $8, 5
move $a0, $8
li $v0 1
syscall
la $a0, newl
li $v0, 4
syscall
li $v0, 10
syscall
