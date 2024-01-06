# <h1 align="center"> Subtracting from the Public Key </a>


## Available commands

-p   We write our public key from which we will subtract. (For single subtraction)

-i   We enter our text file, which contains our public keys. Each key must be written on a new line. (For multiple subtraction)

-n   Specify a number how many times we are going to subtract from the public key.

-s   Specify the number that we are going to subtract from the public key. This number will be subtracted as many times as you specify in the -n command.

-o   Specify the name of the file where the results will be saved. If you do not specify, a file will be created with the name of the public key from which we subtract. If we subtract from several keys at once, a separate file will be created for each key and the results will be written there. If we specify which file to write to, the results for each key will be written in order in the file. There will be a line gap between different keys in the results. The recording order will be exactly the same as the order of the keys.


## Examples of using

In this example, we subtract only one key, without specifying the output to a file, we will get the result on the command line. One of these addresses will be 1 range below the primary key.
For example, this public key has a private key 22382facd0 from puzzle 38. Subtracting 68719476736 from it 16 times, we get 16 keys and one of them will already have a private key 2382facd0.

Subtraction -p 03c060e1e3771cbeccb38e119c2414702f3f5181a89652538851d2e3886bdd70c6 -n 16 -s 68719476736

022732ffc6b2b5406cf0cff831c1b019a1e2cf879e888fef90203579ae41263523

0208bb8486cc8d9ee04f43f05e5b2f2aa1dd372324516b1b313774a37f1ad9a660

029a0195a9f1e8edd9965bffd734a4fd36a7885a6c47fb3cc4e5056b32f8fc9245

0366a3bc12f644d61b94556e3b773dc0bdc450d921a615b8d32c453847fe7e0898

021f9766f0f91e41a5541b5726d603953af7ceee9fe91999f21da2f0123a213bf1<br/>
036ca2a20965d3cdfe26415e753d374c37a81426c64c6c91309687b07165193f06
02236c902863387caf33f55f936d1683cbe41219bc61b4087c69814be163cdc6ce
0239fd7ab8efa2664d405df32376533fc1647671cf00093e604b26cab135e4d82d
021311a461d9492d518115fa288f8601eac1a04561d8b92b84bba246459d15464b
037ea576d2d9562b5bd4c78ddee8d86464912aed127457657b5ca2503591e9011b
027a4a6fb9b4e5434616f2fc9900cd1bbba7b839a5b74fcf830769b93172eb4457
03cee3ca194a3d14bbbdc648b840110b3236c2476b85ef9a5819a37e7deaf61d94
037bd1a2ec9cc8323d3c16caa6599e95c3aacba2463af68373e09d822b46071cdf
03a909a4dc08ff2b4abdaa4fdff2fdedefe81f8e4c5a66c13571fd04886536d641
02c4283f3d0993613a6a0418b488163868c4f597609fbdda89a0e33a2a076ea2f4
02a5953ab4ad411b0a382a32dbc8765383572e8f493704fa64fe04d1ee64c1bed7


Subtraction -i pub.txt -n 16 -s 68719476736 -o new_pub.txt


