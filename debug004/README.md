# README

## Debug004: -g or -O

* notice that source file path and line nubmer is not added if `-g` is not specified

```sh
(gdb) bt
#0  __pthread_clockjoin_ex (threadid=140737351653120, thread_return=thread_return@entry=0x7fffffffddc0, clockid=clockid@entry=0, abstime=abstime@entry=0x0, block=block@entry=true) at pthread_join_common.c:145
#1  0x00007ffff7facb7e in thrd_join (thr=<optimized out>, res=0x0) at thrd_join.c:25
#2  0x00005555555553e7 in main ()
(gdb) thread 2
[Switching to thread 2 (Thread 0x7ffff7da1700 (LWP 415293))]
#0  0x00007ffff7e8223f in __GI___clock_nanosleep (clock_id=clock_id@entry=0, flags=flags@entry=0, req=0x7ffff7da0e90, rem=0x0) at ../sysdeps/unix/sysv/linux/clock_nanosleep.c:78
78      ../sysdeps/unix/sysv/linux/clock_nanosleep.c: No such file or directory.
(gdb) bt
#0  0x00007ffff7e8223f in __GI___clock_nanosleep (clock_id=clock_id@entry=0, flags=flags@entry=0, req=0x7ffff7da0e90, rem=0x0) at ../sysdeps/unix/sysv/linux/clock_nanosleep.c:78
#1  0x00007ffff7e39c87 in thrd_sleep (time_point=<optimized out>, remaining=<optimized out>) at thrd_sleep.c:27
#2  0x0000555555555305 in foo3 ()
#3  0x00005555555552be in foo2 ()
#4  0x00005555555552a9 in foo1 ()
#5  0x0000555555555295 in threadEntry ()
#6  0x00007ffff7f9f6da in start_thread (arg=<optimized out>) at pthread_create.c:474
#7  0x00007ffff7ec4133 in clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95
```

* with `-g -O0`

```sh
(gdb) thread 2
[Switching to thread 2 (Thread 0x7ffff7da1700 (LWP 415602))]
#0  0x00007ffff7e8223f in __GI___clock_nanosleep (clock_id=clock_id@entry=0, flags=flags@entry=0, req=0x7ffff7da0e90, rem=0x0) at ../sysdeps/unix/sysv/linux/clock_nanosleep.c:78
78      ../sysdeps/unix/sysv/linux/clock_nanosleep.c: No such file or directory.
(gdb) bt
#0  0x00007ffff7e8223f in __GI___clock_nanosleep (clock_id=clock_id@entry=0, flags=flags@entry=0, req=0x7ffff7da0e90, rem=0x0) at ../sysdeps/unix/sysv/linux/clock_nanosleep.c:78
#1  0x00007ffff7e39c87 in thrd_sleep (time_point=<optimized out>, remaining=<optimized out>) at thrd_sleep.c:27
#2  0x0000555555555305 in foo3 () at main.c:32
#3  0x00005555555552be in foo2 () at main.c:28
#4  0x00005555555552a9 in foo1 () at main.c:26
#5  0x0000555555555295 in threadEntry (thrd_id=0x7fffffffddf4) at main.c:18
#6  0x00007ffff7f9f6da in start_thread (arg=<optimized out>) at pthread_create.c:474
#7  0x00007ffff7ec4133 in clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95
```

* Try it with `-O2` or `-g -O2`
* strip all symbols by `make strip`

```sh
make strip
make debug
...
(gdb) r
...

(gdb) info threads
  Id   Target Id                                     Frame
* 1    Thread 0x7ffff7da2740 (LWP 470661) "debug004" __pthread_clockjoin_ex (threadid=140737351653120, thread_return=thread_return@entry=0x7fffffffddd0, clockid=clockid@entry=0, abstime=abstime@entry=0x0, block=block@entry=true) at pthread_join_common.c:145
  2    Thread 0x7ffff7da1700 (LWP 470665) "debug004" 0x00007ffff7e8223f in __GI___clock_nanosleep (clock_id=clock_id@entry=0, flags=flags@entry=0, req=0x7ffff7da0ec0, rem=0x0) at ../sysdeps/unix/sysv/linux/clock_nanosleep.c:78
  3    Thread 0x7ffff75a0700 (LWP 470666) "debug004" 0x00007ffff7e8223f in __GI___clock_nanosleep (clock_id=clock_id@entry=0, flags=flags@entry=0, req=0x7ffff759fec0, rem=0x0) at ../sysdeps/unix/sysv/linux/clock_nanosleep.c:78
(gdb) thread 2
[Switching to thread 2 (Thread 0x7ffff7da1700 (LWP 470665))]
#0  0x00007ffff7e8223f in __GI___clock_nanosleep (clock_id=clock_id@entry=0, flags=flags@entry=0, req=0x7ffff7da0ec0, rem=0x0) at ../sysdeps/unix/sysv/linux/clock_nanosleep.c:78
78      ../sysdeps/unix/sysv/linux/clock_nanosleep.c: No such file or directory.
(gdb) bt
#0  0x00007ffff7e8223f in __GI___clock_nanosleep (clock_id=clock_id@entry=0, flags=flags@entry=0, req=0x7ffff7da0ec0, rem=0x0) at ../sysdeps/unix/sysv/linux/clock_nanosleep.c:78
#1  0x00007ffff7e39c87 in thrd_sleep (time_point=<optimized out>, remaining=<optimized out>) at thrd_sleep.c:27
#2  0x0000555555555395 in ?? ()
#3  0x00007ffff7f9f6da in start_thread (arg=<optimized out>) at pthread_create.c:474
#4  0x00007ffff7ec4133 in clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95
```
