# mini_shell_wip
oops i deleted readme somewhere along the line

to do:

1. Put all ARGs into a  matrix (**str)
2. Copy the info of fileout inside str_out_1
3. Pipe str_out1 and str_out2
4. Collect the answer in a file_final
5. Copy info str_final in Matrix
6. Repeat all

************************************
link the functions that we didn't have to redo ourselves (ls, sh, cat, wc)
brainstorm the structure of execute_function
pipe operator
redirections (</>)
append (>>)
heredoc (<<)
error handling needs string outputs associated with different error outputs
testing, lots of it

that might be all.

CD:
cd 								--> O
cd .. 							--> O
cd . 							--> O
cd /Users 						--> O
cd // 							--> O
cd '//' 						--> O
cd ////// 						--> O
cd ./././ 						--> O
cd / 							--> O
cd '/////' 2>/dev/null			--> O
cd '/etc' 						--> O
cd '/var' 						--> O
cd "$PWD/file_tests"			--> O
cd "doesntexist"				--> O
cd "doesntexist" 2>/dev/null	--> O
cd ../../..						--> O
cd ..							--> O
cd ..							--> O
cd ?							--> O
cd +							--> O
cd _							--> O
cd bark bark					--> O
cd '/'							--> O
cd $PWD/file_tests				--> O
cd $OLDPWD/something			--> O
cd ~							--> X
ECHO:
echo							--> O
echo echo						--> O
eCho							--> O
eChO							--> O
eCHO							--> O
ECHO							--> O
echo rhobebou					--> O
echo stop barking				--> O
echo "bonjour"					--> O
echo bonjour					--> O
echo 'bonjour'					--> O
echo -n bonjour					--> O
echo -nn bonjour				--> O
echo -n -n -n bonjour			--> O
echo "-n" bonjour				--> O
echo -n"-n" bonjour				--> X
echo "-nnnn" bonjour			--> O
echo "-n -n -n"-n bonjour		--> O
echo "-n '-n'" bonjour			--> O
echo ~							--> X
echo "~"						--> O
echo '~'						--> O
echo ~123						--> X
echo 123~						--> O
echo ~/123						--> X
echo ~/123/456					--> X
echo $USER						--> O
echo "$USER"					--> O
echo "'$USER'"					--> X
echo " '$USER' "				--> X
echo text"$USER"				--> O
echo text"'$USER'" ' $USER '    --> X 
echo "text"  "$USER"  "$USER"   --> O
echo '       $USER     '        --> O
echo        text "$USER"      "$USER"text   --> O
echo ''''''''''$USER''''''''''  --> X
echo """"""""$USER""""""""      --> X
echo $USER'$USER'text oui oui   oui oui $USER oui   $USER ''    --> O
echo $USER '' $USER $USER '' $USER '' $USER -n $USER    --> O
echo ' \' ' \'                  --> O
echo '\" ' " \"\""              --> O
echo \\\" \\\" \\\" \\\"\\\"\\\" \\\'\\\'\\\'   --> O
echo "$USER""$USER""$USER"      --> O
echo text"$USER"test            --> O
echo '$USER' "$USER" "text \' text" --> O
echo '$USER'                    --> O
echo $USER " "                  --> O 
echo "$USER""Users/$USER/file""'$USER'"'$USER'  --> X
echo "$USER$USER$USER"          --> O
echo '$USER'"$USER"'$USER'      --> O
echo '"$USER"''$USER'"""$USER"  --> X
echo " $USER "'$PWD'            --> O
echo " $USER \$ "'$PWD'         --> X
echo $USER=4                    --> O
echo $USER=thallard             --> O
echo $USER                      --> O
echo $?                         --> ? **idk if this actually works**
echo $USER213                   --> O
echo $USER$12USER$USER=4$USER12 --> X
echo $USER $123456789USER $USER123456789    --> X
echo $USER $9999USER $8888USER $7777USER    --> X
echo $USER $USER9999 $USER8888 $USER7777    --> O
echo $USER $USER9999 $USER8888 $USER7777 "$USER"    --> O
echo "$USER=12$USER"            --> O
echo "$9USER" "'$USER=12$SOMETHING'"    --> X
echo $PWD/file                  --> O
echo "$PWD/file"                --> O
echo "text" "text$USER" ... "$USER" --> O
echo $PWD                       --> O
EXIT: **exits should return unique exit codes so idk about this yet**
exit 0 0
exit 42 42
exit -42 -24
exit 42
exit 42 53 68
exit 259
exit -12030
exit --1239312
exit ++++1203020103
exit +0
exit ++++++0
exit -----0
exit azerty
exit kewkwqke
exit a
exit z
exit "1"
exit "2"
exit "+102"
exit "1230"
exit "+++1230"
exit "1"23
exit "2"32"32"
exit "'42'"
exit '42'"42"42
exit +'42'"42"42
exit -'42'"42"42
exit 9223372036854775807
exit 9223372036854775808
exit -4
exit wrong
exit wrong_command
exit something
exit 1
exit -1
exit 42
exit 0
exit --000
exit +++++++000
exit ++++3193912939
exit ---31232103012
exit "something"
exit q
exit help
exit export
exit echo
exit cd ..
exit 0 0
exit something somethingv2
exit 42 42 42 42 42
exit echo something
exit exit
EXPORT:
env | grep "_="                 --> O
export | grep "SHLVL"           --> O
export | grep "OLDPWD"          --> O
export | grep "PWD"             --> O
export $?                       --> X **need to print error**
export TEST                     --> O
export TEST=                    --> O **note that this makes an empty var**
export TEST=123                 --> O
export ___TEST=123              --> O
export --TEST=123               --> X
export ""=""                    --> X
export ''=''                    --> X
export "="="="                  --> X
export '='='='                  --> X
export TE\\\ST=100              --> X **need to print error** 
export TE-ST=100                --> X 
export -TEST=100                --> X
export TEST-=100                --> X
export _TEST=100                --> O
export | grep "SHLVL"           --> O
export TEST                     --> O
export ==========               --> X
export 1TEST=                   --> X **need to print error**
export TEST                     --> O
export ""=""                    --> X
export TES=T=""                 --> X
export TE+S=T=""                --> X **need to print error** 
export TES\\\\T=123             --> X **need to print error**
export TES.T=123                --> X **need to print error**
export TES\\\$T=123             --> X **need to print error**
export TES\\\\T                 --> X **need to print error**
export TES.T=123                --> X **need to print error**
export TES+T=123                --> X **need to print error**
export TES=T=123                --> X **need to print error**
export TES}T=123                --> X **need to print error**
export TES{T=123                --> X **need to print error**
export TES-T=123                --> X
export -TEST=123                --> X
export _TEST=123                --> O
export TES_T=123                --> O
export TEST_=123                --> O
export TE*ST=123                --> X **need to print error**
export TES#T=123                --> X **need to print error**
export TES@T=123                --> X **need to print error**
export TES!T=123                --> X **need to print error**
export TES$?T=123               --> X **need to print error**
export =============123         --> X
export +++++++=123              --> X
export ________=123             --> O
export export                   --> O
export echo                     --> O
export pwd                      --> O
export cd                       --> O
export export                   --> O
export unset                    --> O
export sudo                     --> O
export TES^T=123                --> X **need to print error**
export TES!T=123                --> X **need to print error**
export TES\~T=123               --> X **need to print error**
export TEST+=100                --> X **need to print error**
PIPES:
env | grep "_="                 --> O
env | grep "SHLVL"              --> O
echo oui | cat -e               --> O
echo oui | echo non | echo something | grep oui --> O
echo oui | echo non | echo something | grep non --> O
echo oui | echo non | echo something | grep something   --> O
cd .. | echo "something"        --> X **cd moves the user**
cd .. | echo "something"        --> X **cd moves the user**
cd / | echo "something"         --> X **cd moves the user**
cd .. | pwd                     --> X **cd moves the user**
ifconfig | grep ":"             --> O
ifconfig | grep nothing         --> X **printing error wrongly**
whoami | grep $USER             --> O
whoami | grep $USER > tmp/file  --> X **printing error wrongly**
whoami | cat -e | cat -e > tmp/file --> X **printing error wrongly**
cat Makefile | grep "FLAGS"     --> O
cat Makefile | cat -e | cat -e  --> O
cat Makefile | grep "FLAGS" | grep "FLAGS" | cat -e --> O
export TEST=123 | cat -e | cat -e   --> O
unset TEST | cat -e             --> X **unset shouldnt work here**
echo test | cat -e | cat -e | cat -e    --> O
whereis ls | cat -e | cat -e > test --> O
echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e   --> O
ls -la | grep "."               --> O
whereis grep > tmp/file         --> O
ls -la > tmp/file               --> O
UNSET:
unset                           --> O
export TEST=100                 --> O
unset doesntexist               --> O
unset PWD                       --> O
unset OLDPWD                    --> O
unset PATH                      --> O
unset TES\\\\T                  --> X **need to print error**
unset TES;T                     --> X **need to print error**
unset TES.T                     --> X **need to print error**
unset TES+T                     --> X **need to print error**
unset TES=T                     --> X **need to print error**
unset TES}T                     --> X **need to print error**
unset TES{T                     --> X **need to print error**
unset TES-T                     --> X **need to print error**
unset -TEST                     --> X **need to print error**
unset _TEST                     --> O
unset TES_T                     --> O
unset TEST_                     --> O
unset TE*ST                     --> X **need to print error**
unset TES#T                     --> X **need to print error**
unset TES@T                     --> X **need to print error**
unset TES!T                     --> X **need to print error**
unset TES$?T                    --> O
unset ============              --> X **need to print error**
unset +++++++                   --> X **need to print error**
unset ________                  --> O
unset export                    --> O
unset echo                      --> O
unset pwd                       --> O
unset cd                        --> O
unset unset                     --> O
unset sudo                      --> O
unset TES^T                     --> X **need to print error**
unset TES!T                     --> X **need to print error**
unset TES\~T                    --> X **need to print error**