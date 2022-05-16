# README

## About

* Debug examples
* Please use Linux

## Prereq

* The example uses Intel format. Please add below (at least `set disassembly intel`) in ~/.gdbinit

```sh
cat > ~/.gdbinit
set auto-load safe-path /
set disassembly intel
set startup-with-shell off
```

## Samples

* Debug001: 32bit binary debugging basics
* Debug002: 64bit binary debugging basics
* Debug003: Thread debugging
* Debug004: Symbols
* Debug005: Attaching to a hanging app
* Debug006: Reading a memory dump

