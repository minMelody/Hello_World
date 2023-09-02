## DESCRIPTION

A simple hexdump program, it accepts format specifications such as

```js
    -af: Address Format
    -bf: Byte Format
    -cf: Characters Format  // Printed all at once as a string
    -rs: Row Size
    -gs: Group Size         // Enter a 0 to disable grouping
```

## EXAMPLE

```
    -af "%04X " -bf "%02X " -cf " |%s|" -rs 16 -gs 8
```

Outputs:

```
    0000  4C 6F 72 65 6D 20 69 70  73 75 6D 20 64 6F 6C 6F  |Lorem ipsum dolo|
    0010  72 20 73 69 74 20 61 6D  65 74 2C 20 63 6F 6E 73  |r sit amet, cons|
    0020  65 63 74 65 74 75 72 20  61 64 69 70 69 73 63 69  |ectetur adipisci|
    0030  6E 67 20 65 6C 69 74 2C  20 73 65 64 20 64 6F 20  |ng elit, sed do |
    0040  65 69 75 73 6D 6F 64 20  74 65 6D 70 6F 72 20 69  |eiusmod tempor i|
    0050  6E 63 69 64 69 64 75 6E  74 20 75 74 20 6C 61 62  |ncididunt ut lab|
    0060  6F 72 65 20 65 74 20 64  6F 6C 6F 72 65 20 6D 61  |ore et dolore ma|
    0070  67 6E 61 20 61 6C 69 71  75 61 2E                 |gna aliqua.|
```

## LIMITATIONS

* Its best to keep byte formatting as 2 digits hex or the spacing could be off. A simple workaround might be formatting the characters `-cf ""` not printing them.