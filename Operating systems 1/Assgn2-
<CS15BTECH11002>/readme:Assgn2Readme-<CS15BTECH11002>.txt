*****instructions for loading the kernel module and executing it****


        1.After writing c program ,you need to create a Makefile.txt using command in terminal "gedit Makefile"
        2.You need to build the linux module using this Makefile
        3.The Makefile contains the commands that build your code 
                The first line contains the source code.
                The second line contains the command to build it
                The third line contains command to delete the resources allocated to module after exiting.
        4.You have to go to root to build the module to get permissions
        5.To do this you need to type "sudo su " in terminal to go to root.
        6.Type your password.
        7.Now you can build your module ,just type "make" in terminal.
        8.Now build you module by typing "insmod Assgn2Src-<CS15BTECH11002>.ko"
        9.This inserts your module into the kernel.
        10.Now to see the output type "dmesg".
        11.After seeing the output to remove the module from kernel type "rmmod Assgn2Src-<CS15BTECH11002>.ko".