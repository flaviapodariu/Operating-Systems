* Adaug la sfarsitul fisierului syscalls.master noua functie de sistem
    >  `cd /sys/kern`
    > 
    > `nano syscalls.master`
* Dupa modificarea syscalls.master, regenerez fisierele C 
    > `cd /sys/kern && make syscalls`

![syscalls.master file](https://github.com/flaviapodariu/Operating-Systems/tree/main/Labs/Lab3/sys_HelloWord/syscalls.master.png)

* Scriu definitia functiei de sistem in sys_generic.c
    > `cd /sys/kern/` 
    > 
    > `nano sys_generic.c` 

![sys_generic.c file](https://github.com/flaviapodariu/Operating-Systems/tree/main/Labs/Lab3/sys_HelloWord/sys.generic.c.png)

* Inainte de a apela functia trebuie sa recompilez kernel-ul

* Apelez functia cu `syscall(ID, nume_functie)`

![syscall](https://github.com/flaviapodariu/Operating-Systems/tree/main/Labs/Lab3/sys_HelloWord/rulare.png)

✅ Output-ul este pe fond albastru, deci am resuit sa fac switch-ul de la user mode la kernel mode.

