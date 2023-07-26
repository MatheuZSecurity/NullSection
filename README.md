# NullSection

NullSection is an Anti-Reversing tool that applies a technique that overwrites the section header with nullbytes.

### Install

```
git clone https://github.com/MatheuZSecurity/NullSection
cd nullsection
gcc nullsection.c -o nullsection
./nullsection
```

### Advantage

When running nullsection on any ELF, it could be .ko rootkit, after that if you use Ghidra/IDA to parse ELF functions, nothing will appear no function to parse in the decompiler for example, even if you run readelf -S / path /to/ elf the following message will appear "There are no sections in this file."

Make good use of the tool!

#### Note

```
We are not responsible for any damage caused by this tool, use the tool intelligently and for educational purposes only.
```
