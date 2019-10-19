export VISUAL=vim
export EDITOR=$VISUAL
export SHELL=bash
export CC=x86_64-w64-mingw32-gcc
export CXX=x86_64-w64-mingw32-g++

# Completion
if [ -f /usr/share/bash-completion/bash_completion ]; then
    . /usr/share/bash-completion/bash_completion
fi

# Colors
if [[ $TERM == *256color ]]; then
    eval `dircolors ~/.dircolors`
    alias ls="ls --color"
    alias grep='grep --color=auto'
fi

# Disable XON/XOFF flow control, to avoid collision of Ctrl-s (useful with Ctrl-r)
stty -ixon

# Increase history
export HISTFILESIZE=5000
