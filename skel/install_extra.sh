#!/bin/bash

if [ ! -f /usr/local/bin/apt-cyg ]; then
    echo "============================"
    echo "Download and install apt-cyg"
    echo "============================"
    wget https://raw.githubusercontent.com/transcode-open/apt-cyg/master/apt-cyg -O apt-cyg
    chmod 755 apt-cyg
    install apt-cyg /usr/local/bin
    rm apt-cyg
fi