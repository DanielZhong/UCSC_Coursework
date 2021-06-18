##########################################################################
# Created by: Zhong, Ruijun(Daniel)
# rzhong6
# 7 November 2020
#
# Assignment: Lab 3: ASCII-risks (Asterisks)
# Cse12, Computer Systems and Assembly Language
# UC Santa Cruz, Fall 2020
#
# Description: This program is intended to print variable-sized ASCII diamonds and a sequence of embedded numbers.
#
# Notes: This program is intended to be run from the MARS IDE.
##########################################################################

##########################################################################
#pseudocode:
#loop
#ask for userinput
#if greater than 0
#continue

#for i in height of triangle
#	tabloop
#	print tab
#	if tab counter finish, go to numberloop
#	
#	numberloop
#	print number
#	number counter
#	if second time enter numberloop jump to nextline
#	go to starloop
#	
#	
#	starloop
#	print star
#	if star counter finish go back to numberloop
#	
#	nextline loop
#		nectline
#		star counter +2
#		tab counter -1
#		number counter+1
#		go back to tabloop
#exitloop
#close program
##########################################################################

.data
 	Height: .asciiz "Enter the height of the pattern (must be greater than 0):	 "
 	Error: .asciiz "Invalid Entry! \n"
 	Stars: .asciiz "\t*"
 	Tabs: .asciiz "\t"
 	Next_Line: .asciiz "\n"
.text

Start:
	#print height
	li $v0, 4
	la $a0, Height
	syscall
	#ask for userinput
	li $v0, 5
	syscall

	#error check loop
	Check_Error:
	bgt $v0, $zero,Continue
	li $v0, 4
	la $a0, Error
	syscall
	j Start
	

Continue:
	#save userinput to t0
	add $t0, $t0, $v0
	
	addi $t1, $t1, 1
	addi $t5, $t5, 1
	
	#numbers of stars (t2)
	sub $t2, $t2, 1
		
	#numbers of tabs ($t4)
	subi $t4, $t0, 1
	
	#check second enter
	li $t6, 0
	#NumberCounter
	li $t7, 0
	
Loop:
	#Tab counter
	add $t3, $0, $t4
	#star counter
	add $s0, $0, $t2
	blt $t0, $t1,ExitLoop
Tabloop:
	ble  $t3, 0, NumberLoop
	li $v0, 4
	la $a0, Tabs
	syscall
	subi $t3, $t3, 1
	j Tabloop
NumberLoop: 
	bne $t6, 1, ABCLoop
	li $v0, 4
	la $a0, Tabs
	syscall
ABCLoop:
	addi $t7, $t7, 1
	li $v0, 1
	la $a0, ($t7)
	syscall
	beq $t7, 1, NextLineLoop
	addi $t6, $t6, 1
	beq $t6, 2, NextLineLoop
StarLoop:
	ble, $s0, 0, NumberLoop
	li $v0, 4
	la $a0, Stars
	syscall
	subi $s0, $s0, 1
	j StarLoop
	
NextLineLoop: 
	li $v0, 4
	la $a0, Next_Line
	syscall
	li $t6, 0
	subi $t4, $t4, 1
	addi $t2, $t2, 2
	addi $t1, $t1, 1
	subi $s0, $s0, 1
	j Loop
	
ExitLoop:
	li $v0, 10
	syscall



		
