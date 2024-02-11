#!/bin/bash
./autobuild.sh

cd test &&
    make clean &&
    make &&
    ./EchoServer

