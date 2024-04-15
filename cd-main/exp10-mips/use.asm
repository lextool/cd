.data
    # Data section
    prompt1: .asciiz "Enter the first integer: "
    prompt2: .asciiz "Enter the second integer: "
    result_msg: .asciiz "The sum is: "

.text
    # Text section
    .globl main

main:
    # Print prompt for the first integer
    li $v0, 4           # Load system call code for printing string (4)
    la $a0, prompt1    # Load address of the first prompt string into $a0
    syscall             # Print the prompt

    # Read the first integer from user input
    li $v0, 5           # Load system call code for reading integer (5)
    syscall             # Read the integer
    move $t0, $v0       # Move the read integer to $t0

    # Print prompt for the second integer
    li $v0, 4           # Load system call code for printing string (4)
    la $a0, prompt2    # Load address of the second prompt string into $a0
    syscall             # Print the prompt

    # Read the second integer from user input
    li $v0, 5           # Load system call code for reading integer (5)
    syscall             # Read the integer
    move $t1, $v0       # Move the read integer to $t1

    # Calculate the sum
    add $t2, $t0, $t1   # Add the two integers and store the result in $t2

    # Print the result message
    li $v0, 4           # Load system call code for printing string (4)
    la $a0, result_msg # Load address of the result message into $a0
    syscall             # Print the result message

    # Print the sum
    li $v0, 1           # Load system call code for printing integer (1)
    move $a0, $t2       # Move the sum to $a0
    syscall             # Print the sum

    # Exit the program
    li $v0, 10          # Load system call code for exit (10)
    syscall             # Perform system call
