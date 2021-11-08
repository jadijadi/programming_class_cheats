#!/bin/bash

for word in `egrep "bit$" /usr/share/dict/words`; do
    wordbyte=`echo $word|sed 's/bit$/byte/'`

    img_url=`./dl_photo_from_google.py $word`
    wget $img_url -O temp.png
    convert temp.png -resize x200 temp.png
    magick montage -tile 1x temp.png top.png
    magick montage -tile 4x -title $wordbyte  temp.png temp.png temp.png temp.png temp.png temp.png temp.png temp.png  bottom.png
    magick montage -tile 1x -title $word top.png bottom.png -mode Concatenate output/$word.png
done