#!/usr/bin/env bash

bin='showip'
dstdir=${PREFIX_DIR:-/usr/local/bin}

current_step=0
total_steps=0

bold_color="\x1b[1m"
blue_color="\x1b[0;34m"
red_color="\x1b[0;31m"
purple_color="\x1b[0;35m"
reset_color="\x1b[0m"
reset_bold_color="${reset_color}${bold_color}"

function print_info() {
	echo -e "${bold_color}[${purple_color}$current_step${reset_bold_color}/${purple_color}$total_steps${reset_bold_color}]${reset_color} $1"
}

function print_done() {
	if [ $? -gt 0 ];then
		print_info "${red_color}${bold_color}Abort${reset_color}"
	else
		print_info "${bold_color}Done${reset_color}"
	fi
}

function install_it() {
	sudo install -m755 out/Default/$bin $dstdir/$bin
}

function build_it() {
  ninja
}

function setup() {
	if [ -d out ];then
		if [ $total_steps -eq 0 ];then
			total_steps=1
		fi
		current_step=$(($current_step + 1))

		print_info "Installing ${blue_color}$bin${reset_color} in ${blue_color}$dstdir${reset_color}"
		install_it

		print_done
		exit 0
	else
		total_steps=2
		current_step=$(($current_step + 1))

		print_info "Building ${blue_color}$bin${reset_color}"
		build_it

		print_done

		setup
  fi
}

setup
