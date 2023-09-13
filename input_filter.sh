sed -e 's/\/\/.*FIXME:*/\/\/\/ \\bug/' $1 | sed -e 's/\/\/.*TODO:*/\/\/\/ \\todo/'
