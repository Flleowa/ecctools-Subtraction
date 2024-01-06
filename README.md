## keydivision

This is just a proof of concept program just to show how we can divide publickeys.

The result from exact divisions is the same like any decimal number but if the division is not exact the result will be in an unknow place in the curve

Example of use: Divide a publickey bewteen 4 three times in a row:


```./keydivision -p 03a301697bdfcd704313ba48e51d567543f2a182031efd6915ddc07bbcc4e16070 -n 3 -d 4```

Output:

```
03f694cbaf2b966c1cc5f7f829d3a907819bc70ebcc1b229d9e81bda2712998b10
02e80fea14441fb33a7d8adab9475d7fab2019effb5156a792f1a11778e3c0df5d
033ab6bde10cd3ac0cd06883fa66f0b0e3eb1309c0534b812286e2a30ca540db99
```

explanation:
the target publickey `03a301697bdfcd704313ba48e51d567543f2a182031efd6915ddc07bbcc4e16070` have privatekey `0x1000000000000000000000000000000`

each line of the output are the result of divide the publickey by 4 lets to check this example with keymath

