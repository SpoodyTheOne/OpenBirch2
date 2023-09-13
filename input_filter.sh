sed -e 's/\/\/.*(FIXME | BUG):*/\/\/\/ \\bug/' $1 | sed -e 's/\/\/.*TODO:*/\/\/\/ \\todo/'
