##########################################################################
# Created by:	Zhong, Ruijun(Daniel)
# 		RZHONG6
# 		6 February 2020
#
# Assignment: Lab 5: Functions and Graphics
# CSE 12, Computer Systems and Assembly Language
# UC Santa Cruz, Fall 2020
#
# Description: This program print and draw the pattern from Lab5_f20_test.asm
#
# Notes: This program is intended to be run from the MARS IDE.
##########################################################################

## Macro that stores the value in %reg on the stack 
##  and moves the stack pointer.
.macro push(%reg)
	subi $sp $sp 4
	sw %reg 0($sp)
.end_macro 

# Macro takes the value on the top of the stack and 
#  loads it into %reg then moves the stack pointer.
.macro pop(%reg)
	lw %reg 0($sp)
	addi $sp $sp 4	
.end_macro



#Pesudocode:
#save input into x, and arithmetic right to get rid of 00yy
#then save input into y, and arithmetic left and shift right

# Macro that takes as input coordinates in the format
# (0x00XX00YY) and returns 0x000000XX in %x and 
# returns 0x000000YY in %y
.macro getCoordinates(%input %x %y)
	move %x, %input 
	srl %x, %x, 16
	move %y, %input
	sll %y, %y, 16
	srl %y, %y, 16
.end_macro

#pesudocode 
#move x into output, and arimthic shift left and then add y into output

# Macro that takes Coordinates in (%x,%y) where
# %x = 0x000000XX and %y= 0x000000YY and
# returns %output = (0x00XX00YY)
.macro formatCoordinates(%output %x %y)
move %output, %x
sll %output, %output, 16
add %output, %output, %y
.end_macro 


.data
originAddress: .word 0xFFFF0000



.text
j done
    
done: nop
	li $v0 10 
	syscall

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#  Subroutines defined below
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pesudocode

# load 0xFFFF0000 into t0
# if t0 is not equal to 0xfffffffc, then add 4 bits and save t0 value to a0(will move to next pixel and print color)
#*****************************************************
#Clear_bitmap: Given a color, will fill the bitmap display with that color.
#   Inputs:
#    $a0 = Color in format (0x00RRGGBB) 
#   Outputs:
#    No register outputs
#    Side-Effects: 
#    Colors the Bitmap display all the same color
#*****************************************************
clear_bitmap: nop
	li $t0, 0xFFFF0000
	
loop:	
	add $t0,$t0, 4
	sw $a0, 0($t0)
	bne $t0, 0xFFFFFFFC, loop
 	jr $ra
 	

#pesudocode
#use macro to get x and y and save both values to t1 and t2
#load 0xFFFF0000 into a0
# use the format y times 128 times 4 bits plus x times 4 bits to get the new address
#add it to a0
#a0 memory address save it to a1 memory address
#*****************************************************
# draw_pixel:
#  Given a coordinate in $a0, sets corresponding value
#  in memory to the color given by $a1	
#-----------------------------------------------------
#   Inputs:
#    $a0 = coordinates of pixel in format (0x00XX00YY)
#    $a1 = color of pixel in format (0x00RRGGBB)
#   Outputs:
#    No register outputs
#*****************************************************
draw_pixel: nop
	getCoordinates ($a0, $t1, $t2)
	bgt $t1, 0x0000FF, error
	bgt $t2, 0x0000FF, error
	li $a0, 0xFFFF0000
	mul $t2, $t2, 4
	mul $t2, $t2, 128
	mul $t1, $t1, 4
	add $t3, $t2, $t1
	add $a0, $a0, $t3
	sw $a1, 0($a0)	
	
error:
	jr $ra

#pesudocode
#load 0xFFFF0000 into a0
# use the format y times 128 times 4 bits plus x times 4 bits to get the new address
#load a0 value into v0 and return v0
#*****************************************************
# get_pixel:
#  Given a coordinate, returns the color of that pixel	
#-----------------------------------------------------
#   Inputs:
#    $a0 = coordinates of pixel in format (0x00XX00YY)
#   Outputs:
#    Returns pixel color in $v0 in format (0x00RRGGBB)
#*****************************************************
get_pixel: nop
	getCoordinates ($a0, $t3, $t4)
	li $a0, 0xFFFF0000
	mul $t3, $t3, 4
	mul $t4, $t4, 128
	mul $t4, $t4, 4
	add $t5, $t4, $t3
	add $a0, $a0, $t5
	lw $v0, 0($a0)
	jr $ra

#pesudocode
#call macor get corrdinates to get width and height t6 and t7, and get x and y value t1 t2
# move t1 value into t3(t3 can reset x during next column)
#move a2 into a1 because we need to call draw pixel function, but draw pixel used a1 not a2
# create t8 for row counter and t9 for column counter
# when t8 counter is not equal to width, then create loop to drawpixel
#when t8 is equal to width, then go to next column and reset t1 to t3 value and continue back to row loop to print drawpixel
# when t9(column counter) is equal to height, then end the loop and end this function
#*****************************************************
#draw_rect: Draws a rectangle on the bitmap display.
#	Inputs:
#		$a0 = coordinates of top left pixel in format (0x00XX00YY)
#		$a1 = width and height of rectangle in format (0x00WW00HH)
#		$a2 = color in format (0x00RRGGBB) 
#	Outputs:
#		No register outputs
#*****************************************************
draw_rect: nop
	push ($ra)
	getCoordinates ($a1, $t6, $t7)
	getCoordinates ($a0, $t1, $t2)	
	move $t3, $t1
	move $a1, $a2
	li $t8, 0
	li $t9, 1
	
row:
	
	beq $t8, $t6, column
	
	formatCoordinates($a0, $t1, $t2)
	push ($t1)
	push ($t2)
	push($t3)
	jal draw_pixel
	pop ($t3)
	pop ($t2)
	pop ($t1)
	addi $t1, $t1, 1
	addi $t8, $t8, 1
	j row
column:
	
	beq $t9, $t7, next

	move $t1, $t3
	move $t8, $zero
	addi $t9, $t9, 1
	addi $t2, $t2, 1
	j row
next:	
	pop ($ra)
 	jr $ra


#pesudocode
#follow the pesudocode in google doc
#***********************************************
# draw_diamond:
#  Draw diamond of given height peaking at given point.
#  Note: Assume given height is odd.
#-----------------------------------------------------
# draw_diamond(height, base_point_x, base_point_y)
# 	for (dy = 0; dy <= h; dy++)
# 		y = base_point_y + dy
#
# 		if dy <= h/2
# 			x_min = base_point_x - dy
# 			x_max = base_point_x + dy
# 		else
# 			x_min = base_point_x - floor(h/2) + (dy - ceil(h/2)) = base_point_x - h + dy
# 			x_max = base_point_x + floor(h/2) - (dy - ceil(h/2)) = base_point_x + h - dy
#
#   	for (x=x_min; x<=x_max; x++) 
# 			draw_diamond_pixels(x, y)
#-----------------------------------------------------
#   Inputs:
#    $a0 = coordinates of top point of diamond in format (0x00XX00YY)
#    $a1 = height of the diamond (must be odd integer)
#    $a2 = color in format (0x00RRGGBB)
#   Outputs:
#    No register outputs
#***************************************************
draw_diamond: nop
	push ($ra)
	getCoordinates ($a0, $t6, $t7)
	#$s6 is basepoint x, $s7 is basepoint y
	li $t1, 0
	# S1 is xmin
	li $t2, 0
	#s2 is xmax
	li $t3, 0
	#s3 is dy
	li $t4, 0
	#s4 is y
	div $t5, $a1, 2
	#$s5 is heigh/2
	move $t0, $a1
	#s0 is height
	move $a1, $a2
	
gobackhere:	
	bgt $t3, $t0, gohere
	add $t4, $t7, $t3
	
	bgt $t3, $t5, else
	sub $t1, $t6, $t3
	add $t2, $t6, $t3
	j pass
else:
	sub $t1, $t6, $t0
	add $t1, $t1, $t3
	add $t2, $t6, $t0
	sub $t2, $t2, $t3

pass:
	move $t9, $t1
	#t9 is x
	addi $t3, $t3, 1
	
printloop:
	
	bgt $t9, $t2, gobackhere
	formatCoordinates($a0, $t9, $t4)
	push ($t1)
	push ($t2)
	push($t3)
	push ($t4)
	push ($t5)
	push($t6)
	push ($t7)
	push ($t8)
	push($t0)
	jal draw_pixel
	pop ($t0)
	pop ($t8)
	pop ($t7)
	pop ($t6)
	pop ($t5)
	pop ($t4)
	pop ($t3)
	pop ($t2)
	pop ($t1)	
	addi $t9, $t9, 1
	j printloop
		
gohere:	
	pop ($ra)
	jr $ra
	
