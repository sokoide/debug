# README

## Debug005: Attaching to a hanging process

* make a binary by `make`
* run it by `./debug005`(hangs)
* attach a gdb to it
* find thread 1 is waiting on other threads and thread 2 is sleeping (hang simulation)

```sh
make
./debug005

# in another shell, do this only once
echo 0 | sudo tee -a  /proc/sys/kernel/yama/ptrace_scope
# then attach to the debug005 process
ps -ef|grep debug005
gdb -p $pid #or gdb -> at $pid

$ gdb -p 444137
Attaching to process 444137
[New LWP 444139]
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
__pthread_clockjoin_ex (threadid=139996889827072, thread_return=thread_return@entry=0x7ffc22f41160, clockid=clockid@entry=0, abstime=abstime@entry=0x0, block=block@entry=true) at pthread_join_common.c:145
145     pthread_join_common.c: No such file or directory.
(gdb) info threads
Id   Target Id                                     Frame
* 1    Thread 0x7f5391636740 (LWP 444137) "debug005" __pthread_clockjoin_ex (threadid=139996889827072, thread_return=thread_return@entry=0x7ffc22f41160, clockid=clockid@entry=0, abstime=abstime@entry=0x0, block=block@entry=true) at pthread_join_common.c:145
2    Thread 0x7f5390e34700 (LWP 444139) "debug005" 0x00007f539171623f in __GI___clock_nanosleep (clock_id=clock_id@entry=0, flags=flags@entry=0, req=0x7f5390e33ec0, rem=0x0) at ../sysdeps/unix/sysv/linux/clock_nanosleep.c:78

# check thread2's callstack
(gdb) thread 2
[Switching to thread 2 (Thread 0x7f5390e34700 (LWP 444139))]
#0  0x00007f539171623f in __GI___clock_nanosleep (clock_id=clock_id@entry=0, flags=flags@entry=0, req=0x7f5390e33ec0, rem=0x0) at ../sysdeps/unix/sysv/linux/clock_nanosleep.c:78
78      ../sysdeps/unix/sysv/linux/clock_nanosleep.c: No such file or directory.
(gdb) bt
#0  0x00007f539171623f in __GI___clock_nanosleep (clock_id=clock_id@entry=0, flags=flags@entry=0, req=0x7f5390e33ec0, rem=0x0) at ../sysdeps/unix/sysv/linux/clock_nanosleep.c:78
#1  0x00007f53916cdc87 in thrd_sleep (time_point=<optimized out>, remaining=<optimized out>) at thrd_sleep.c:27
#2  0x00005633a36283b5 in threadEntry2 ()
#3  0x00007f53918336da in start_thread (arg=<optimized out>) at pthread_create.c:474
#4  0x00007f5391758133 in clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95

(gdb) thread 1
[Switching to thread 1 (Thread 0x7f5391636740 (LWP 444137))]
#0  __pthread_clockjoin_ex (threadid=139996889827072, thread_return=thread_return@entry=0x7ffc22f41160, clockid=clockid@entry=0, abstime=abstime@entry=0x0, block=block@entry=true) at pthread_join_common.c:145
145     pthread_join_common.c: No such file or directory.
(gdb) bt
#0  __pthread_clockjoin_ex (threadid=139996889827072, thread_return=thread_return@entry=0x7ffc22f41160, clockid=clockid@entry=0, abstime=abstime@entry=0x0, block=block@entry=true) at pthread_join_common.c:145
#1  0x00007f5391840b7e in thrd_join (thr=<optimized out>, res=0x0) at thrd_join.c:25
#2  0x00005633a36281cf in main ()
```

