
;; bennett stice
;; 11/27/2023


        section         .data
firstPrompt:            db      "Enter first number: "
secondPrompt:           db      "Enter second number: "
output1:                db      "The GCD of "
output2:                db      " and "
output3:                db      " is "
output4:                db      "A "
buffer1:                resb    22
buffer2:                resb    22

        section         .text
        extern          printAX
        extern          printNL
        global          _start
_start:
        ;;  print first prompt
        mov             rax, 4
        mov             rbx, 1
        mov             rcx, firstPrompt
        mov             rdx, secondPrompt-firstPrompt
        int             0x80

        ;; read string into buffer
        mov             rax, 3
        mov             rbx, 0
        mov             rcx, buffer1
        mov             rdx, 22
        int             0x80

        push            rax     ;;save the size of the buffer you just inputed

        ;;  print second prompt
        mov             rax, 4
        mov             rbx, 1
        mov             rcx, secondPrompt
        mov             rdx, output1-secondPrompt
        int             0x80

        ;; read string into buffer
        mov             rax, 3
        mov             rbx, 0
        mov             rcx, buffer2
        mov             rdx, 22
        int             0x80


        push            rax     ;;save the size of the buffer you just inputed


        ;; make sure everything starts with zero then translate first buffer
        mov             rcx,0
        mov             rdx,0
        mov             rbx,0
        mov             bl,[buffer1]
translate1:

        sub             bl,0x30

        mov             rax,10
        mul             rdx
        add             rbx,rax
        mov             rdx,rbx
        inc             rcx

        mov             bl,[buffer1+rcx]

        cmp             bl,0xa
        jne             translate1
        mov             rax,rdx
        push            rax

        ;; make sure everything starts with zero then translate second buffer
        mov             rcx,0
        mov             rdx,0
        mov             rbx,0
        mov             bl,[buffer2]
translate2:

        sub             bl,0x30

        mov             rax,10
        mul             rdx
        add             rbx,rax
        mov             rdx,rbx
        inc             rcx

        mov             bl,[buffer2+rcx]

        cmp             bl,0xa
        jne             translate2
        mov             rax,rdx
        push            rax


        ;; load input int rcx and rax and then find GCD
        pop             rcx
        pop             rax
GCD:

        ;; if b=0, a is answer
        cmp             rcx,0
        je              done

        ;; handle recursion
        cmp             rax,rcx
        jl              less_than
        jge             greater_than

less_than:

        ;; if a<b, swap a and b
        push            rax
        mov             rax, rcx
        pop             rcx
        jmp             GCD

greater_than:

        ;; if a>=b, swap b into a and b= a%b
        mov             rdx,0
        push            rcx
        div             rcx
        mov             rcx,rdx
        pop             rax
        jmp             GCD

done:

        ;; push rax to be printed out later
        push            rax

        ;; print out first ouput statment
        mov             rax, 4
        mov             rbx, 1
        mov             rcx, output1
        mov             rdx, output2-output1
        int             0x80

        ;; set the correct length of first input
        pop             rbx
        pop             rcx
        pop            rdx
        push            rcx
        push            rbx
        dec             rdx

        ;; print out first input
        mov             rax, 4
        mov             rbx, 1
        mov             rcx, buffer1
        int             0x80

        ;; print out second ouput statment
        mov             rax, 4
        mov             rbx, 1
        mov             rcx, output2
        mov             rdx, output3-output2
        int             0x80

        ;; set the correct length of second input
        pop             rbx
        pop             rdx
        push            rbx
        dec             rdx

        ;; print out the second input
        mov             rax, 4
        mov             rbx, 1
        mov             rcx, buffer2
        int             0x80

        ;; print out third ouput statment
        mov             rax, 4
        mov             rbx, 1
        mov             rcx, output3
        mov             rdx, output4-output3
        int             0x80

        ;; set our rax to print and print it
        pop             rax
        call            printAX
        call            printNL

        ;; exit to linux
        mov             rax, 1
        mov             rbx, 0
        int             0x80
