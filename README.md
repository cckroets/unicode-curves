unicode-curves
==============

Pictures available in the 'examples' directory.

Draw unicode curves such as Hilbert, Koch, Dragon, of any order. 

Compile all files. The executable will output each character in integer form. 

Use unicode.ss to convert the output to unicode.

$ g++ *cpp
$ ./a.out > t1
$ racket unicode.ss < t1 > hilbert.exe

