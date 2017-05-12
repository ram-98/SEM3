#include<linux/module.h>                 //HEADER FOR DOING MODULE RELATED PROGRAMMING
#include<linux/sched.h>                  //HEADER FILE FOR SCHEDULING PARAMETERS
#include<linux/init.h>                   //INITIALISATION OF MODULE
#include <linux/kernel.h>                //HEADER FILE FOR DEALING WITH KERNELS



static int functn_init (void) {
    struct task_struct *task;                            //task_struct IS A STRUCTURE WHICH CONTAINS ALL THE DETAILS OFPROCESS
    for_each_process(task) {
        printk(" state -%lu	",task->state);              //PRINTING PROCESS STATE
         printk(" pid -%lu	",task->pid);                 //PRINTING PROCESS ID
         printk(" name -%s	\n",task->comm);                //PRINTING PROCESS NAME
     }
    return 0;
}

static void func_exit (void) {
}
  
module_init(functn_init);               //INITIALISING THE KERNEL MODULE
module_exit(func_exit);                 //REMOVING THE MODULE INJECTED INTO THE KERNEL
