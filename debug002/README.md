# README

## Debug002: 64bit binary

* `make` to build `debug002`
* `make run` to build and run`debug002`
* `make debug` to run debug002 under gdb

```sh
scott@lab2:~/repo/sokoide/debug/debug002$ make debug
chmod +x debug002
gdb debug002
...
(gdb) b main
Breakpoint 1 at 0x11b6: file main.c, line 25.

(gdb) r
Starting program: /var/scott/repo/sokoide/debug/debug002/debug002

Breakpoint 1, main (argc=0, argv=0x7fffffffdf10) at main.c:25
25      {

# breakpoint hit
# check argv[0] -> can't check now.
(gdb) print argv[0]
$1 = 0x1 <error: Cannot access memory at address 0x1>

# why? -> argc is 0, the argv pointer is not set at this point

# si to this point
(gdb) disass
Dump of assembler code for function main:
   0x00005555555551b6 <+0>:     endbr64
   0x00005555555551ba <+4>:     push   rbp
   0x00005555555551bb <+5>:     mov    rbp,rsp
   0x00005555555551be <+8>:     sub    rsp,0x10
   0x00005555555551c2 <+12>:    mov    DWORD PTR [rbp-0x4],edi
   0x00005555555551c5 <+15>:    mov    QWORD PTR [rbp-0x10],rsi
=> 0x00005555555551c9 <+19>:    mov    rax,QWORD PTR [rbp-0x10]

# check argv[0] and argc
(gdb) print argv[0]
$1 = 0x7fffffffe23a "/var/scott/repo/sokoide/debug/debug002/debug002"
(gdb) print argc
$2 = 1
```

* Parameter passing
* take a look at <https://en.wikipedia.org/wiki/X86_calling_conventions#System_V_AMD64_ABI>
* RDI, RSI, RDX, RCX, R8, R9 are used for the first 6 integer parameters

```sh
(gdb) disass main
Dump of assembler code for function main:
=> 0x00005555555551b6 <+0>:     endbr64
   0x00005555555551ba <+4>:     push   rbp
   0x00005555555551bb <+5>:     mov    rbp,rsp
   0x00005555555551be <+8>:     sub    rsp,0x10
   0x00005555555551c2 <+12>:    mov    DWORD PTR [rbp-0x4],edi
   0x00005555555551c5 <+15>:    mov    QWORD PTR [rbp-0x10],rsi
   0x00005555555551c9 <+19>:    mov    rax,QWORD PTR [rbp-0x10]
   0x00005555555551cd <+23>:    mov    rax,QWORD PTR [rax]
   0x00005555555551d0 <+26>:    mov    rdi,rax
   0x00005555555551d3 <+29>:    call   0x555555555149 <foo>
   0x00005555555551d8 <+34>:    mov    esi,0x2
   0x00005555555551dd <+39>:    mov    edi,0x28
   0x00005555555551e2 <+44>:    call   0x555555555174 <bar>
   0x00005555555551e7 <+49>:    mov    esi,eax
   0x00005555555551e9 <+51>:    lea    rdi,[rip+0xe1e]        # 0x55555555600e
   0x00005555555551f0 <+58>:    mov    eax,0x0
   0x00005555555551f5 <+63>:    call   0x555555555050 <printf@plt>
   0x00005555555551fa <+68>:    mov    eax,0x0
   0x00005555555551ff <+73>:    leave
   0x0000555555555200 <+74>:    ret

# take a look at these 2 lines
mov    rdi,rax
call   0x555555555149 <foo>

# check rdi by setting a breakpint there
# don't miss '*' after 'b'
(gdb) b *0x00005555555551d3
Breakpoint 3 at 0x5555555551d3: file main.c, line 26.
(gdb) c
Continuing.

Breakpoint 3, 0x00005555555551d3 in main (argc=1, argv=0x7fffffffdf18) at main.c:26
26              foo(argv[0]);
(gdb) disass
Dump of assembler code for function main:
   0x00005555555551b6 <+0>:     endbr64
   0x00005555555551ba <+4>:     push   rbp
   0x00005555555551bb <+5>:     mov    rbp,rsp
   0x00005555555551be <+8>:     sub    rsp,0x10
   0x00005555555551c2 <+12>:    mov    DWORD PTR [rbp-0x4],edi
   0x00005555555551c5 <+15>:    mov    QWORD PTR [rbp-0x10],rsi
   0x00005555555551c9 <+19>:    mov    rax,QWORD PTR [rbp-0x10]
   0x00005555555551cd <+23>:    mov    rax,QWORD PTR [rax]
   0x00005555555551d0 <+26>:    mov    rdi,rax
=> 0x00005555555551d3 <+29>:    call   0x555555555149 <foo>
   0x00005555555551d8 <+34>:    mov    esi,0x2
   0x00005555555551dd <+39>:    mov    edi,0x28
   0x00005555555551e2 <+44>:    call   0x555555555174 <bar>
   0x00005555555551e7 <+49>:    mov    esi,eax
   0x00005555555551e9 <+51>:    lea    rdi,[rip+0xe1e]        # 0x55555555600e
   0x00005555555551f0 <+58>:    mov    eax,0x0
   0x00005555555551f5 <+63>:    call   0x555555555050 <printf@plt>
   0x00005555555551fa <+68>:    mov    eax,0x0
   0x00005555555551ff <+73>:    leave
   0x0000555555555200 <+74>:    ret
End of assembler dump.

# check rdi
(gdb) x/s $rdi
0x7fffffffe243: "/var/scott/repo/sokoide/debug/debug002/debug002"

# do the same for bar
(gdb) b bar
Breakpoint 4 at 0x555555555174: file main.c, line 14.
(gdb) c
Continuing.
name: /var/scott/repo/sokoide/debug/debug002/debug002

Breakpoint 4, bar (a=21845, b=1431654769) at main.c:14
14      {
(gdb) disass
Dump of assembler code for function bar:
=> 0x0000555555555174 <+0>:     endbr64
   0x0000555555555178 <+4>:     push   rbp
   0x0000555555555179 <+5>:     mov    rbp,rsp
   0x000055555555517c <+8>:     sub    rsp,0x20
   0x0000555555555180 <+12>:    mov    DWORD PTR [rbp-0x14],edi
   0x0000555555555183 <+15>:    mov    DWORD PTR [rbp-0x18],esi
   0x0000555555555186 <+18>:    mov    edx,DWORD PTR [rbp-0x14]
   0x0000555555555189 <+21>:    mov    eax,DWORD PTR [rbp-0x18]
   0x000055555555518c <+24>:    add    eax,edx
   0x000055555555518e <+26>:    mov    edi,eax
   0x0000555555555190 <+28>:    call   0x55555555519d <baz>
   0x0000555555555195 <+33>:    mov    DWORD PTR [rbp-0x4],eax
   0x0000555555555198 <+36>:    mov    eax,DWORD PTR [rbp-0x4]
   0x000055555555519b <+39>:    leave
   0x000055555555519c <+40>:    ret
End of assembler dump.

# check rdi and rsi
(gdb) info r
rax            0x36                54
rbx            0x555555555210      93824992236048
rcx            0x0                 0
rdx            0x0                 0
rsi            0x2                 2
rdi            0x28                40

# change rdi 98
(gdb) set $rdi=98
(gdb) c
Continuing.
bar: 1000
[Inferior 1 (process 371807) exited normally]

# it printed 1000 which is (98+2) * 10
...
```
