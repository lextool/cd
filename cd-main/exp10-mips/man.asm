# MIPS assembly code to calculate the sum of two integers

.data
    # Data section
    num1: .word 5   # First integer
    num2: .word 7   # Second integer
    result: .word 0 # Variable to store the result

.text
    # Text section
    .globl main

main:
    # Load the first integer into register $t0
    lw $t0, num1
    # Load the second integer into register $t1
    lw $t1, num2
    # Add the two integers and store the result in register $t2
    add $t2, $t0, $t1
    # Store the result back to memory
    sw $t2, result

    # Exit the program
    li $v0, 10      # Load system call code for exit (10)
    syscall         # Perform system call
