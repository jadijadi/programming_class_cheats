# Gif Hider

A program to hide your gifs
> It can be used for other files as well under MAX_FILE_SIZE (1Mb)

You can encrypt any of your files with a secret key and decrypt it again with the same secret key

## Build

`$ gcc gif_hider.c -o gif_hider`

## Run

`$ ./gif_hider <FILE_NAME> <SECRET_KEY>`

> Secret key is an hexadecimal number between **0** to **255** or **0x0** to **0xFF**
