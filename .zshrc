  export ZSH="/home/rasarex/.oh-my-zsh"
  eval $(dircolors ~/.dir_colors)

ZSH_THEME="sunrise"
HIST_STAMPS="dd/mm/yyyy"

plugins=(
  git
  extract
)

source $ZSH/oh-my-zsh.sh

# Preferred editor for local and remote sessions
 if [[ -n $SSH_CONNECTION ]]; then
   export EDITOR='vim'
 else
   export EDITOR='mvim'
 fi

alias vim='nvim'
alias g++='g++ -Werror=vla'
alias gcc='gcc -Werror=vla'
alias clang='clang -Werror=vla'
