.data
    array: .space 40      # Define an array of 10 integers, each 4 bytes
    index: .word 2         # Index of the element to be assigned
    value: .word 100      # Value to be assigned

.text
    .globl main

main:
    # Load the base address of the array into register $a0
    la $a0, array

    # Load the index into register $t0
    lw $t0, index

    # Load the value to be assigned into register $t1
    lw $t1, value

    # Calculate the memory address of the element to be assigned
    # The address is base address + index * size of each element
    sll $t0, $t0, 2       # Multiply the index by 4 (each integer is 4 bytes)
    add $t0, $t0, $a0     # Add the base address to the indexed offset

    # Store the value at the calculated memory address
    sw $t1, 0($t0)        # Store the value at offset 0 from the address in $t0

    # Exit the program
    li $v0, 10            # Load system call code for exit (10)
    syscall               # Perform system call
