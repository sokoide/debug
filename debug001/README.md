# README

## Debug001: 32bit binary

* `make` to build `debug001`
* `make run` to build and run`debug001`

```sh
scott@lab2:~/repo/sokoide/debug/debug001$ make run
chmod +x debug001
/home/scott/repo/sokoide/debug/debug001/debug001
name: /home/scott/repo/sokoide/debug/debug001/debug001
bar: 420
```

* `make debug` to run debug001 under gdb

```
scott@lab2:~/repo/sokoide/debug/debug001$ make debug
chmod +x debug001
gdb debug001
GNU gdb (Ubuntu 9.2-0ubuntu1~20.04.1) 9.2
...
(gdb) list
6       }
7
8       int bar(int a, int b)
9       {
10              int r = baz(a + b);
11              return r;
12      }
13
14      int baz(int c)
15      {
```

* breakpoint and examine

```sh
# set a break point at main
(gdb) b main
Breakpoint 1 at 0x124e: file main.c, line 20.

# run
(gdb) r
Starting program: /var/scott/repo/sokoide/debug/debug001/debug001

# break point hit
Breakpoint 1, main (argc=1, argv=0xffffd0a4) at main.c:20
20      {
(gdb) list
15      {
16              return c * 10;
17      }
18
19      int main(int argc, char** argv)
20      {
21              foo(argv[0]);
22              printf("bar: %d\n", bar(40, 2));
23
24              return 0;

# argc is 1
# check argv[0]
(gdb) print argv[0]
$1 = 0xffffd256 "/var/scott/repo/sokoide/debug/debug001/debug001"

 # check argv pointer 0xffffd0a4
(gdb) x/4w 0xffffd0a4
0xffffd0a4:     0xffffd256      0x00000000      0xffffd286      0xffffd296

# argv[0] = 0xffffd256
# argv[1] = 0x00000000
# check argv[0] in different formats
(gdb) x/4w 0xffffd256
0xffffd256:     0x7261762f      0x6f63732f      0x722f7474      0x2f6f7065
(gdb) x/s 0xffffd256
0xffffd256:     "/var/scott/repo/sokoide/debug/debug001/debug001"
```

* 32bit function parameter passing
* take a look at <https://en.wikipedia.org/wiki/X86_calling_conventions#cdecl>
* stack is used in `cdecl` calling convention in 32bit

```sh
# set breakpoint at bar
(gdb) b bar
Breakpoint 2 at 0x565561ff: file main.c, line 9.
(gdb) c
Continuing.
name: /var/scott/repo/sokoide/debug/debug001/debug001

Breakpoint 2, bar (a=40, b=2) at main.c:9
9       {
(gdb) list
4       {
5               printf("name: %s\n", name);
6       }
7
8       int bar(int a, int b)
9       {
10              int r = baz(a + b);
11              return r;
12      }
13

# check callstack
(gdb) bt
#0  bar (a=40, b=2) at main.c:9
#1  0x5655628b in main (argc=1, argv=0xffffd0a4) at main.c:22

# check how a and be are passed
# function main's stack frame is 1
(gdb) frame 1
#1  0x5655628b in main (argc=1, argv=0xffffd0a4) at main.c:22
22              printf("bar: %d\n", bar(40, 2));
(gdb) disass
Dump of assembler code for function main:
   0x5655624e <+0>:     endbr32
   0x56556252 <+4>:     lea    ecx,[esp+0x4]
   0x56556256 <+8>:     and    esp,0xfffffff0
   0x56556259 <+11>:    push   DWORD PTR [ecx-0x4]
   0x5655625c <+14>:    push   ebp
   0x5655625d <+15>:    mov    ebp,esp
   0x5655625f <+17>:    push   ebx
   0x56556260 <+18>:    push   ecx
   0x56556261 <+19>:    call   0x565560d0 <__x86.get_pc_thunk.bx>
   0x56556266 <+24>:    add    ebx,0x2d72
   0x5655626c <+30>:    mov    eax,ecx
   0x5655626e <+32>:    mov    eax,DWORD PTR [eax+0x4]
   0x56556271 <+35>:    mov    eax,DWORD PTR [eax]
   0x56556273 <+37>:    sub    esp,0xc
   0x56556276 <+40>:    push   eax
   0x56556277 <+41>:    call   0x565561cd <foo>
   0x5655627c <+46>:    add    esp,0x10
   0x5655627f <+49>:    sub    esp,0x8
   0x56556282 <+52>:    push   0x2
   0x56556284 <+54>:    push   0x28
   0x56556286 <+56>:    call   0x565561ff <bar>
=> 0x5655628b <+61>:    add    esp,0x10
   0x5655628e <+64>:    sub    esp,0x8
   0x56556291 <+67>:    push   eax
   0x56556292 <+68>:    lea    eax,[ebx-0x1fc6]
   0x56556298 <+74>:    push   eax
   0x56556299 <+75>:    call   0x56556070 <printf@plt>
   0x5655629e <+80>:    add    esp,0x10
   0x565562a1 <+83>:    mov    eax,0x0
   0x565562a6 <+88>:    lea    esp,[ebp-0x8]
   0x565562a9 <+91>:    pop    ecx
   0x565562aa <+92>:    pop    ebx
   0x565562ab <+93>:    pop    ebp
   0x565562ac <+94>:    lea    esp,[ecx-0x4]
   0x565562af <+97>:    ret
End of assembler dump.

# function bar's stack frame is 0
(gdb) frame 0
#0  bar (a=40, b=2) at main.c:9
9       {
(gdb) disass
Dump of assembler code for function bar:
=> 0x565561ff <+0>:     endbr32
   0x56556203 <+4>:     push   ebp
   0x56556204 <+5>:     mov    ebp,esp
   0x56556206 <+7>:     sub    esp,0x18
   0x56556209 <+10>:    call   0x565562b0 <__x86.get_pc_thunk.ax>
   0x5655620e <+15>:    add    eax,0x2dca
   0x56556213 <+20>:    mov    edx,DWORD PTR [ebp+0x8]
   0x56556216 <+23>:    mov    eax,DWORD PTR [ebp+0xc]
   0x56556219 <+26>:    add    eax,edx
   0x5655621b <+28>:    sub    esp,0xc
   0x5655621e <+31>:    push   eax
   0x5655621f <+32>:    call   0x5655622f <baz>
   0x56556224 <+37>:    add    esp,0x10
   0x56556227 <+40>:    mov    DWORD PTR [ebp-0xc],eax
   0x5655622a <+43>:    mov    eax,DWORD PTR [ebp-0xc]
   0x5655622d <+46>:    leave
   0x5655622e <+47>:    ret
End of assembler dump.

# the a, b args were passed using the stack (push 0x2, push 0x28) in main
# the a, b ares were received from the stack into eax and edx in bar

# run the remaining and check the result
(gdb) c
Continuing.
bar: 420
[Inferior 1 (process 365322) exited normally]
```

* clear all break points and confirm

```sh
(gdb) clear

(gdb) info b
Deleted breakpoint 2 No breakpoints or watchpoints.
```

* restart and change c passed in baz

```sh
(gdb) clear

(gdb) b baz
Deleted breakpoint 3 Breakpoint 4 at 0x5655622f: file main.c, line 15.
(gdb) info b
Num     Type           Disp Enb Address    What
4       breakpoint     keep y   0x5655622f in baz at main.c:15

(gdb) r
Starting program: /var/scott/repo/sokoide/debug/debug001/debug001
name: /var/scott/repo/sokoide/debug/debug001/debug001

Breakpoint 4, baz (c=42) at main.c:15
15      {

(gdb) bt
#0  baz (c=42) at main.c:15
#1  0x56556224 in bar (a=40, b=2) at main.c:10
#2  0x5655628b in main (argc=1, argv=0xffffd0a4) at main.c:22


# bar
(gdb) frame 1
#1  0x56556224 in bar (a=40, b=2) at main.c:10
10              int r = baz(a + b);
(gdb) disass
Dump of assembler code for function bar:
   0x565561ff <+0>:     endbr32
   0x56556203 <+4>:     push   ebp
   0x56556204 <+5>:     mov    ebp,esp
   0x56556206 <+7>:     sub    esp,0x18
   0x56556209 <+10>:    call   0x565562b0 <__x86.get_pc_thunk.ax>
   0x5655620e <+15>:    add    eax,0x2dca
   0x56556213 <+20>:    mov    edx,DWORD PTR [ebp+0x8]
   0x56556216 <+23>:    mov    eax,DWORD PTR [ebp+0xc]
   0x56556219 <+26>:    add    eax,edx
   0x5655621b <+28>:    sub    esp,0xc
   0x5655621e <+31>:    push   eax
   0x5655621f <+32>:    call   0x5655622f <baz>
=> 0x56556224 <+37>:    add    esp,0x10
   0x56556227 <+40>:    mov    DWORD PTR [ebp-0xc],eax
   0x5655622a <+43>:    mov    eax,DWORD PTR [ebp-0xc]
   0x5655622d <+46>:    leave
   0x5655622e <+47>:    ret
End of assembler dump.

# change it back to frame 0 (baz)
(gdb) frame 0
#0  baz (c=42) at main.c:15

# baz
(gdb) disass
Dump of assembler code for function baz:
=> 0x5655622f <+0>:     endbr32
   0x56556233 <+4>:     push   ebp
   0x56556234 <+5>:     mov    ebp,esp
   0x56556236 <+7>:     call   0x565562b0 <__x86.get_pc_thunk.ax>
   0x5655623b <+12>:    add    eax,0x2d9d
   0x56556240 <+17>:    mov    edx,DWORD PTR [ebp+0x8]
   0x56556243 <+20>:    mov    eax,edx
   0x56556245 <+22>:    shl    eax,0x2
   0x56556248 <+25>:    add    eax,edx
   0x5655624a <+27>:    add    eax,eax
   0x5655624c <+29>:    pop    ebp
   0x5655624d <+30>:    ret
End of assembler dump.

# step until 0x56556243 which gets the argument 42 (ebp+0x8 into edx)
(gdb) si
0x56556243      16              return c * 10;

# check the current register edx (is 42)
(gdb) info r
eax            0x56558fd8          1448447960
ecx            0x0                 0
edx            0x2a                42
...

# change edx = 100
(gdb) set $edx=100
(gdb) info r
eax            0x56558fd8          1448447960
ecx            0x0                 0
edx            0x64                100
...

# step some more instructions
# eax becomes 100
(gdb) si
0x56556245      16              return c * 10;
(gdb) info r
eax            0x64                100
ecx            0x0                 0
edx            0x64                100
...

# eax becomes 400 by shl 2
(gdb) si
0x56556248      16              return c * 10;
(gdb) info r
eax            0x190               400
ecx            0x0                 0
edx            0x64                100

# eax becomes 1000 after adding edx twice
# it executed below to make it x10
#  eax = edx
#  shl eax 2 (x4 -> 400)
#  edx += eax (100+400 -> 500)
#  eax += eax (500+500 -> 1000)

(gdb) si
0x5655624a      16              return c * 10;
(gdb) si
17      }
(gdb) info r
eax            0x3e8               1000
ecx            0x0                 0
edx            0x64                100

# continue and see it prints 1000
(gdb) c
Continuing.
bar: 1000
[Inferior 1 (process 367357) exited normally]
```
