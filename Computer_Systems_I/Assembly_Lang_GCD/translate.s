translate:


        ;;;;;;;;;;;use rsi

        mov             al,10
        mul             dl
        ;call            printAX
        add             bl,al
        mov             dl,bl
        inc             rcx

        mov             bl,[buffer1+rcx];;;;;;;;;;;;loop here

        cmp             bl,0xa
        jne             translate1
        mov             rax,rdx
        push            rax



        ret
