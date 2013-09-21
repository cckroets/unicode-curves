unicode-curves
==============

Pictures available in the 'examples' directory.

Draw unicode curves such as Hilbert, Koch, Dragon, of any order. 

Compile all files. The executable will output each character in integer form. 

Use unicode.ss to convert the output to unicode.

Compile program:
> g++ -o curves *cpp

Output unicodes:
> ./curves > codes.txt

Convert unicodes to characters:
> racket unicode.ss < codes.txt > curve.txt

Now curve.txt will look like this:

![alt tag](https://raw.github.com/cckroets/unicode-curves/master/examples/Hilbert.png)
