#! /bin/bash

######################################################################
### default configuration
######################################################################

OMPenable="yes"
libDir="lib"

######################################################################
### tools functions
######################################################################

#_____________________________________________________________________
# Special color characters, value only if this is the correct file
# descriptor (1)
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
	c_under="\033[4m";
	c_end="\033[0m";
else
	c_default="";  c_black="";   c_red="";    c_green=""; c_yellow="";
	c_blue="";     c_magenta=""; c_cyan="";   c_lgray=""; c_dgray="";
	c_lred="";     c_lgreen=""; c_lyellow=""; c_lblue="";
	c_lmagenta=""; c_lcyan="";  c_white="";   c_bold="";  c_under="";
	c_end="";
fi

#_____________________________________________________________________
# usage
# display information about the install script and exit the process
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

	${c_bold}--disable-OMP${c_end}
		Disable OMP in the compilation (by default it is enable)

	${c_bold}--installLib-path${c_end}=[${c_under}PATH${c_end}]
		Set the path of the library folder, by default is set to lib
		in the current folder
"

	exit 418;
}

#_____________________________________________________________________
# display_exe
# display information about the current operation and the state at its
# end. 
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
# display_info
# display information about... something
# 0 -> ok
# 1 -> info
# 2 -> warn
# 3 -> err
# 4 -> yes
# 5 -> no
function display_info ()
{
	local test_str="$1"
	local test_state="$2"
	
	# set size of terminal
	local nb_cols=80
	if [[ -t 1 ]]; then
		nb_cols=`tput cols`
	fi

	# display the text and spaces
	echo -ne "${test_str} ";
	for i in `seq $(( ${nb_cols} - 8 - ${#test_str}%${nb_cols} ))`; do
		echo -n "."
	done;

	# display state
	case "${test_state}" in
		0 )
			echo -e " ${c_bold}[ ${c_green}ok${c_default} ]${c_end}" ;;
		1 )
			echo -e " ${c_bold}[${c_cyan}info${c_default}]${c_end}" ;;
		2 )
			echo -e " ${c_bold}[${c_yellow}warn${c_default}]${c_end}" ;;
		3 )
			echo -e " ${c_bold}[${c_lred}err${c_default} ]${c_end}" ;;
		4 )
			echo -e " ${c_bold}[${c_lblue}yes${c_default} ]${c_end}" ;;
		5 )
			echo -e " ${c_bold}[ ${c_magenta}no${c_default} ]${c_end}" ;;
	esac
}


######################################################################
### installation functions
######################################################################


#_____________________________________________________________________
# test_OMP
# test if OMP feature is enable
function test_OMP ()
{
	function write_OMP_test () {
		echo "#include <omp.h>"
		echo "int main (int,char**) { return 0; }"
	}

	write_OMP_test > test_conf_OMP.cxx

	local isOMPenable=$(g++ -fopenmp test_conf_OMP.cxx -lgomp  2>&1 | wc -l | awk '{ print $1 }')
	touch a.out

	rm a.out test_conf_OMP.cxx

	display_exe "        OMP is enable" "$isOMPenable"
}

#_____________________________________________________________________
# compilation
# make the obj and lib directories, and compile the library with make
function compilation ()
{
	display_info "Begin compilation process" 1

	function __compilation_make_obj_directory () {
		mkdir -p obj
	}
	function __compilation_make_lib_directory () {
		mkdir -p lib
	}

	if [ ! -d obj ]; then
		display_exe "        Make the object directory" __compilation_make_obj_directory
	fi
	if [ ! -d lib ]; then
		display_exe "        Make the lib directory" __compilation_make_lib_directory
	fi

	display_exe "        Compilation the library" make
}

#_____________________________________________________________________
# environment_var
# write the file to source with correct environment variables
function environment_var ()
{
	display_info "Prepare environment variables" 1

	local source_file="$1"

	if [[ -z $source_file ]]; then
		source_file="thiscqder.sh"
	fi

	function __environment_var_file () {
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

	__environment_var_file > ${source_file}

	[[ -f ${source_file} ]]
	display_exe "        Write source file" $?
}

#_____________________________________________________________________
# display_final_info
# display information to congratulate at the end of the install process
function display_final_info ()
{
	local source_file="$1"

	if [[ -z $source_file ]]; then
		source_file="thiscqder.sh"
	fi

	echo -e "
${c_bold}CQDER library${c_end} compiled. You can now use it into your code.
Source ${PWD}/${source_file} in your \$HOME/.$(echo ${SHELL} | awk -F / '{ print $NF }')rc to finalize installation.

echo \"source ${PWD}/${source_file}\" >> \$HOME/.$(echo ${SHELL} | awk -F / '{ print $NF }')rc
	"
}

#_____________________________________________________________________
function install_process ()
{
	local omp="$1"
	local source_file="cqder_env.sh"

	if [[ $omp =~ "no" ]]; then
		display_info "Checking for omp.h" 5
	else
		display_info "Checking for omp.h" 4
		test_OMP
	fi
	compilation
	environment_var ${source_file}
	display_final_info ${source_file}
}



######################################################################
### calls the correct option
######################################################################

#_____________________________________________________________________
# loop and switch an all arguments, usage function is priority
for arg in "$@"; do
	case $arg in
		-h|-help|--help|-info|--info )
			usage ;;
		--disable-OMP )
			OMPenable="no" ;;
		--installLib-path=* )
			libDir="${arg//--InstallLib-path=/}" ;;
	esac
done

# call the complete install procedure
install_process $OMPenable


exit 0

EOF
######################################################################
%DATA
