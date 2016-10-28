#! /bin/bash

#_____________________________________________________________________
# Special color characters, value only if this is the correct file descriptor (1)
if [[ -t 1 ]]; then
	# sepecial color characters
	c_default="\033[39m";
	c_black="\033[30m";
	c_red="\033[31m";
	c_green="\033[32m";
	c_yellow="\033[33m";
	c_blue="\033[34m";
	c_magenta="\033[35m";
	c_cyan="\033[36m";
	c_lgray="\033[37m";
	c_dgray="\033[90m";
	c_lred="\033[91m";
	c_lgreen="\033[92m";
	c_lyellow="\033[93m";
	c_lblue="\033[94m";
	c_lmagenta="\033[95m";
	c_lcyan="\033[96m";
	c_white="\033[97m";
	c_bold="\033[1m";
	c_end="\033[0m";
else
	c_default="";
	c_black="";
	c_red="";
	c_green="";
	c_yellow="";
	c_blue="";
	c_magenta="";
	c_cyan="";
	c_lgray="";
	c_dgray="";
	c_lred="";
	c_lgreen="";
	c_lyellow="";
	c_lblue="";
	c_lmagenta="";
	c_lcyan="";
	c_white="";
	c_bold="";
	c_end="";
fi

#_____________________________________________________________________
function usage ()
{
	echo -e "
${c_bold}NAME${c_end}
	$0 - installation script for CQDER project.

${c_bold}SYNOPSIS${c_end}
	${c_bold}$0${c_end} [OPTION]

${c_bold}DESCRIPTION${c_end}
	Compile CQDER library.

	${c_bold}-h${c_end}, ${c_bold}--help${c_end}, ${c_bold}--info${c_end}
		See the help (this is what are you doing now !)

"

	exit 418;
}

#_____________________________________________________________________
function display_exe ()
{
	local test_str="$1"
	local test_exe="$2"
	
	# set size of terminal
	local nb_cols=80
	if [[ -t 1 ]]; then
		nb_cols=`tput cols`
	fi

	local result

	# test if second parameter is an integer
	if [[ "${test_exe}" =~ ^-?[0-9]+$ ]]; then
		result=${test_exe}
	else
		$test_exe
		result=$?
	fi

	# display the text and spaces
	echo -ne "${test_str} ";
	for i in `seq $(( ${nb_cols} - 8 - ${#test_str}%${nb_cols} ))`; do
		echo -n "."
	done;

	# display ok or fail
	if [[ $result -eq 0 ]]; then
		echo -e " ${c_bold}[ ${c_green}ok${c_default} ]${c_end}"
	else
		echo -e " ${c_bold}[${c_red}fail${c_default}]${c_end}"
		exit $result
	fi
}

#_____________________________________________________________________
function compilation ()
{
	function __compilation_make_directory ()
	{
		mkdir -p obj
	}

	if [ ! -d obj ]; then
		display_exe "Make the object directory" __compilation_make_directory
	fi

	display_exe "Compilation the library" make
}

#_____________________________________________________________________
function environment_var ()
{
	local source_file="$1"

	function __environment_var_file ()
	{
		local export_; local equal_;

		if [[ $SHELL =~ "csh" ]]; then
			export_="setenv"
			equal_=" "
		else
			export_="export"
			equal_="="
		fi
		
		echo -e "#! $(which $SHELL)

${export_} cqder_PATH${equal_}${PWD}

if [[ -z \$LD_LIBRARY_PATH ]]; then
	${export_} LD_LIBRARY_PATH${equal_}\${cqder_PATH}/lib
else
	${export_} LD_LIBRARY_PATH${equal_}\${LD_LIBRARY_PATH}:\${cqder_PATH}/lib
fi
"
	}

	__write_shellrc_file > ${source_file}

	[[ -f ${source_file} ]]
	display_exe "Write source file" $?
}

#_____________________________________________________________________
function display_final_info ()
{
	local source_file="$1"

	echo -e "
${c_bold}CQDER library${c_end} compiled. You can now use it into your code.
Source ${PWD}/${source_file} in your \$HOME/.$(echo ${SHELL} | awk -F / '{ print $NF }')rc to finalize installation.

echo \"source ${PWD}/class_env.sh\" >> \$HOME/.$(echo ${SHELL} | awk -F / '{ print $NF }')rc
	"
}


for arg in "$@"; do
	case $arg in
		-h|-help|--help|-info|--info )
			usage ;;
	esac
done

#compilation
environment_var "thiscqder.sh"
display_final_info

exit 0

EOF
