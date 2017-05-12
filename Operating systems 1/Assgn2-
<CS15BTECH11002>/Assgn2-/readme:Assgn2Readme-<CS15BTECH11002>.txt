*****instructions for loading the kernel module and executing it****


        1.After writing c program ,you need to create a Makefile.txt using command in terminal "gedit Makefile"
        2.You need to build the linux module using this Makefile
        ****
        	now copy paste the contents of my "Makefile" in that and save it .Now follow the below instructions and the 		program will work fine . 
        ****
        
        3.The Makefile contains the commands that build your code 
                The first line contains the source code.
                The second line contains the command to build it
                The third line contains command to delete the resources allocated to module after exiting.
        4.You have to go to root to build the module to get permissions
        5.To do this you need to type "sudo su " in terminal to go to root.
        6.Type your password.
        7.Now you can build your module ,just type "make" in terminal.
        8.Now build you module by typing "insmod 1.ko"
        9.This inserts your module into the kernel.
        10.Now to see the output type "dmesg".
        11.After seeing the output to remove the module from kernel type "rmmod 1.ko".
        12. IF u want tpye "ps -el "in terminal and verify my output with that as the command give the output of process 	running.
        13.
        
        -----------NOTE-------------------
        
        
         Sir , i have submitted a minute late because of wifi problem in hostel during the assignment time .So please i request u to consider this and give me marking . IF any furthur problems occur please mail me . I will respond as early as possible
