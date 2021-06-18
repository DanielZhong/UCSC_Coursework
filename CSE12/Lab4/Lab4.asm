##########################################################################
# Created by: Zhong, Daniel
# CruzID: rzhong6
# 19 November 2020
#
# Assignment: Lab 4: Searching HEX
# CMPE 012, Computer Systems and Assembly Language
# UC Santa Cruz, Fall 2020
#
# Description: This program prints ¡®Hello world.¡¯ to the screen.
#
# Notes: This program is intended to be run from the MARS IDE.
##########################################################################
#pseudocode
#input arguments
#Save 8 into arguments to 8 different registers(t0-t7)
#Print "Integer value"
#Move 8 arguments to a0 and print it out with space after each arguments
#Print next line twice
#Print "integer values"
#Create s0 for position 1, s1 for position 10, and s3 for s0+16*s2 
#
#create loop
#Create s0 for position 1, s1 for position 10, and s3 for s0+16*s2 
#If smaller than 0x39(0x30-0x39), then minus 0x30
#Else(A,b,c,d etc.) then minus 55
#print s3 (s0+16*s2)
#Create s4 for storing max value
#If s3 greater than s4, then s4 = s3
#Repeat 8 times? Transfer or t0-t7 to decimal yet? if no go back to creat loop
#Print "Maximum value"
#Print s4
#End program



.data
 	Space: .asciiz " "
 	Program_Arguments: .asciiz "Integer values: \n"
 	Integer_Values:.asciiz "Integer values: \n"
 	Maximum_Value: .asciiz "Maximum Value: \n"
 	nextline: .asciiz "\n"

.text
li $v0, 4
la $a0, Program_Arguments
syscall 

lw $t0, 0($a1)
lw $t1, 4($a1)
lw $t2, 8($a1)
lw $t3, 12($a1)
lw $t4, 16($a1)
lw $t5, 20($a1)
lw $t6, 24($a1)
lw $t7, 28($a1)

move $a0, $t0
syscall
la $a0, Space
syscall 

move $a0, $t1
syscall 
la $a0, Space
syscall 

move $a0, $t2
syscall
la $a0, Space
syscall  

move $a0, $t3
syscall 
la $a0, Space
syscall 

move $a0, $t4
syscall 
la $a0, Space
syscall 

move $a0, $t5
syscall 
la $a0, Space
syscall 

move $a0, $t6
syscall 
la $a0, Space
syscall 

move $a0, $t7
syscall 
la $a0, Space
syscall 

la $a0, nextline
syscall 
syscall

la $a0, Integer_Values
syscall

# position 1
li $s0, 0
#position 10
li $s1, 0

#add position 1 and 10 together
li $s2, 0

#Max value
li $s3, 0

addi $t0, $t0, 2
lb $s1,0($t0)
addi $t0, $t0, 1
lb $s0, 0($t0)

#transfer to integer

bgt $s1, 0x39, check1
subi $s1, $s1, 0x30
check:
bgt $s0, 0x39, check2
subi $s0, $s0, 0x30
j finish
check1:
	subi $s1, $s1, 55
	j check
	
check2: 
	subi $s0, $s0, 55

		
finish: 
mul $s1, $s1, 16
add $s2, $s1, $s0

blt $s2, $s3, print
move $s3, $s2

print:
li $v0, 1
la $a0, ($s2)
syscall
li $v0, 4
la $a0, Space
syscall




#second number
addi $t1, $t1, 2
lb $s1,0($t1)
addi $t1, $t1, 1
lb $s0, 0($t1)

#transfer to integer

bgt $s1, 0x39, bcheck1
subi $s1, $s1, 0x30
bcheck:
bgt $s0, 0x39, bcheck2
subi $s0, $s0, 0x30
j bfinish
bcheck1:
	subi $s1, $s1, 55
	j bcheck
	
bcheck2: 
	subi $s0, $s0, 55

		
bfinish: 
mul $s1, $s1, 16
add $s2, $s1, $s0

blt $s2, $s3, bprint
move $s3, $s2

bprint:
li $v0, 1
la $a0, ($s2)
syscall
li $v0, 4
la $a0, Space
syscall

#Third number
addi $t2, $t2, 2
lb $s1,0($t2)
addi $t2, $t2, 1
lb $s0, 0($t2)

#transfer to integer

bgt $s1, 0x39, ccheck1
subi $s1, $s1, 0x30
ccheck:
bgt $s0, 0x39, ccheck2
subi $s0, $s0, 0x30
j cfinish
ccheck1:
	subi $s1, $s1, 55
	j ccheck
	
ccheck2: 
	subi $s0, $s0, 55

		
cfinish: 
mul $s1, $s1, 16
add $s2, $s1, $s0

blt $s2, $s3, cprint
move $s3, $s2

cprint:
li $v0, 1
la $a0, ($s2)
syscall
li $v0, 4
la $a0, Space
syscall

#Four number
addi $t3, $t3, 2
lb $s1,0($t3)
addi $t3, $t3, 1
lb $s0, 0($t3)

#transfer to integer

bgt $s1, 0x39, dcheck1
subi $s1, $s1, 0x30
dcheck:
bgt $s0, 0x39, dcheck2
subi $s0, $s0, 0x30
j dfinish
dcheck1:
	subi $s1, $s1, 55
	j dcheck
	
dcheck2: 
	subi $s0, $s0, 55

		
dfinish: 
mul $s1, $s1, 16
add $s2, $s1, $s0

blt $s2, $s3, dprint
move $s3, $s2

dprint:
li $v0, 1
la $a0, ($s2)
syscall
li $v0, 4
la $a0, Space
syscall

#Five number
addi $t4, $t4, 2
lb $s1,0($t4)
addi $t4, $t4, 1
lb $s0, 0($t4)

#transfer to integer

bgt $s1, 0x39, echeck1
subi $s1, $s1, 0x30
echeck:
bgt $s0, 0x39, echeck2
subi $s0, $s0, 0x30
j efinish
echeck1:
	subi $s1, $s1, 55
	j echeck
	
echeck2: 
	subi $s0, $s0, 55

		
efinish: 
mul $s1, $s1, 16
add $s2, $s1, $s0

blt $s2, $s3, eprint
move $s3, $s2

eprint:
li $v0, 1
la $a0, ($s2)
syscall
li $v0, 4
la $a0, Space
syscall


#Six number
addi $t5, $t5, 2
lb $s1,0($t5)
addi $t5, $t5, 1
lb $s0, 0($t5)

#transfer to integer

bgt $s1, 0x39, fcheck1
subi $s1, $s1, 0x30
fcheck:
bgt $s0, 0x39, fcheck2
subi $s0, $s0, 0x30
j ffinish
fcheck1:
	subi $s1, $s1, 55
	j fcheck
	
fcheck2: 
	subi $s0, $s0, 55

		
ffinish: 
mul $s1, $s1, 16
add $s2, $s1, $s0

blt $s2, $s3, fprint
move $s3, $s2

fprint:
li $v0, 1
la $a0, ($s2)
syscall
li $v0, 4
la $a0, Space
syscall

#Seven number
addi $t6, $t6, 2
lb $s1,0($t6)
addi $t6, $t6, 1
lb $s0, 0($t6)

#transfer to integer

bgt $s1, 0x39, gcheck1
subi $s1, $s1, 0x30
gcheck:
bgt $s0, 0x39, gcheck2
subi $s0, $s0, 0x30
j gfinish
gcheck1:
	subi $s1, $s1, 55
	j gcheck
	
gcheck2: 
	subi $s0, $s0, 55

		
gfinish: 
mul $s1, $s1, 16
add $s2, $s1, $s0

blt $s2, $s3, gprint
move $s3, $s2

gprint:
li $v0, 1
la $a0, ($s2)
syscall
li $v0, 4
la $a0, Space
syscall


#Eight number
addi $t7, $t7, 2
lb $s1,0($t7)
addi $t7, $t7, 1
lb $s0, 0($t7)

#transfer to integer

bgt $s1, 0x39, hcheck1
subi $s1, $s1, 0x30
hcheck:
bgt $s0, 0x39, hcheck2
subi $s0, $s0, 0x30
j hfinish
hcheck1:
	subi $s1, $s1, 55
	j hcheck
	
hcheck2: 
	subi $s0, $s0, 55

		
hfinish: 
mul $s1, $s1, 16
add $s2, $s1, $s0

blt $s2, $s3, hprint
move $s3, $s2

hprint:
li $v0, 1
la $a0, ($s2)
syscall
li $v0, 4
la $a0, Space
syscall

la $a0, nextline
syscall
syscall

la $a0, Maximum_Value
syscall

li $v0, 1
la $a0, ($s3)
syscall

li $v0, 4
la $a0, nextline
syscall 

li $v0, 10
syscall

