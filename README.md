# dupe_finder
A utility to identify duplicate files

## Prerequisite: qlibc
See [Install](https://github.com/wolkykim/qlibc/blob/master/INSTALL.md) for [qlibc](https://github.com/wolkykim/qlibc)
```
git clone https://github.com/wolkykim/qlibc.git /tmp/qlibc
cd /tmp/qlibc
./configure
make
sudo make install
```

## Compile the code
```
./compile.sh
```

## Find files and feed dupe_find using stdin
```
find /etc -type f | ./dupe_find.exe | sort
```
