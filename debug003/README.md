# README

## Debug003: 64bit thread debugging

* `make` to build `debug003`
* `make run` to build and run`debug003`
* `make debug` to run debug003 under gdb

```sh
make debug
(gdb) r
Starting program: /var/scott/repo/sokoide/debug/debug003/debug003
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
[New Thread 0x7ffff7da1700 (LWP 443175)]
[t:7ffff7da1700] Hello, I'm a new thread
[t:7ffff7da1700] sleeping
[New Thread 0x7ffff75a0700 (LWP 443176)]
[t:7ffff75a0700] Hello, I'm a new thread
[t:7ffff75a0700] sleeping
[main] wainting for thread 0 to complete...

# type ctrl-c to break
^C
Thread 1 "debug003" received signal SIGINT, Interrupt.
__pthread_clockjoin_ex (threadid=140737351653120, thread_return=thread_return@entry=0x7fffffffddb0, clockid=clockid@entry=0, abstime=abstime@entry=0x0, block=block@entry=true) at pthread_join_common.c:145
145     pthread_join_common.c: No such file or directory.

(gdb) info threads
  Id   Target Id                                     Frame
* 1    Thread 0x7ffff7da2740 (LWP 443171) "debug003" __pthread_clockjoin_ex (threadid=140737351653120, thread_return=thread_return@entry=0x7fffffffddb0, clockid=clockid@entry=0, abstime=abstime@entry=0x0, block=block@entry=true) at pthread_join_common.c:145
  2    Thread 0x7ffff7da1700 (LWP 443175) "debug003" 0x00007ffff7e8223f in __GI___clock_nanosleep (clock_id=clock_id@entry=0, flags=flags@entry=0, req=0x7ffff7da0ed0, rem=0x0) at ../sysdeps/unix/sysv/linux/clock_nanosleep.c:78
  3    Thread 0x7ffff75a0700 (LWP 443176) "debug003" 0x00007ffff7e8223f in __GI___clock_nanosleep (clock_id=clock_id@entry=0, flags=flags@entry=0, req=0x7ffff759fed0, rem=0x0) at ../sysdeps/unix/sysv/linux/clock_nanosleep.c:78

(gdb) thread 2
[Switching to thread 2 (Thread 0x7ffff7da1700 (LWP 443175))]
#0  0x00007ffff7e8223f in __GI___clock_nanosleep (clock_id=clock_id@entry=0, flags=flags@entry=0, req=0x7ffff7da0ed0, rem=0x0) at ../sysdeps/unix/sysv/linux/clock_nanosleep.c:78
78      ../sysdeps/unix/sysv/linux/clock_nanosleep.c: No such file or directory.

(gdb) bt
#0  0x00007ffff7e8223f in __GI___clock_nanosleep (clock_id=clock_id@entry=0, flags=flags@entry=0, req=0x7ffff7da0ed0, rem=0x0) at ../sysdeps/unix/sysv/linux/clock_nanosleep.c:78
#1  0x00007ffff7e39c87 in thrd_sleep (time_point=<optimized out>, remaining=<optimized out>) at thrd_sleep.c:27
#2  0x00005555555552ca in threadEntry (dummy=0x0) at main.c:18
#3  0x00007ffff7f9f6da in start_thread (arg=<optimized out>) at pthread_create.c:474
#4  0x00007ffff7ec4133 in clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95
```

