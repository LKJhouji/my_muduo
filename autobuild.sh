#!/bin/bash

set -e  #在执行过程中发生错误，会立即终止脚本执行

# 如果没有build目录，创建该目录
if [ ! -d `pwd`/build ]; then
    mkdir `pwd`/build
fi

rm -rf `pwd`/build/*

cd `pwd`/build &&
    cmake .. && 
    make

cd ..

rm -rf /usr/include/my_muduo 
rm -f /usr/lib/libmy_muduo.so

if [ ! -d /usr/include/my_muduo ]; then
    mkdir /usr/include/my_muduo
fi

for header in `ls *.h`; 
do
    cp $header /usr/include/my_muduo
done

cp `pwd`/lib/libmy_muduo.so /usr/lib

ldconfig    # 更新库文件的缓存，以便共享库可以被动态链接器快速查找

