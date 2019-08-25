set nocompatible

" Enable file type detection. (language-dependent indenting)
filetype plugin indent on

" Various options
set backspace=2 " Make backspace work like other apps
set ttimeoutlen=0 " No delay when switching from INSERT to NORMAL mode
set showcmd " Show current command in status line
set number " Show line numbers
set noerrorbells visualbell t_vb= " Disable error bell

" Space and tabs
set expandtab " Change tab to space
set tabstop=4 " Nb space to replace a tab
set softtabstop=4 " Backspace will automatically delete 4 spaces if its a tabulation
set shiftwidth=4 " Space inserted when shift right (>) is pressed

" Mouse
set mouse=a " Enable mouse use in all modes
set ttymouse=xterm2

" Font and syntax highlighting
syntax on
colorscheme solarized
set background=dark
if &term == "screen" " Needed in tmux to support 256 colors
    set t_Co=256
endif

" File explorer (invoke with :Lexplorer)
let g:netrw_browse_split=4 " Open file in last split
let g:netrw_winsize=-28 " Netrw split default size

" Persistent undo
set undofile
set undodir=~/.vim/undodir
