#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
LIGHT_BLUE='\033[1;34m'
PURPLE='\033[01;35m'
NC='\033[0m'

check_command() {
	test_id=$1
    command=$2
	echo -e "${YELLOW}Executing Test #${NC} ${PURPLE}${test_id}${NC} ${YELLOW}: $command${NC}"

    bash -c "$command" > bash_output.txt
    ./minishell -c "$command" > minishell_output.txt

    if diff -q bash_output.txt minishell_output.txt > /dev/null; then
		echo -e "${GREEN}OK: Test #${test_id}${NC}"
    else
		echo -e "${RED}KO: Test #${test_id}${NC}"
    fi

    echo "-------------------------------------"
}

print_title() {
    title=$1
    echo -e "\n${LIGHT_BLUE}**************************************************"
    echo -e "* $title"
    echo -e "**************************************************${NC}\n"
}

print_title "Testing Basic Commands"
basic_commands=(
    "echo Hello World"
    "echo '     Hello     World'"
    ""
	" "
	"		"
	"/bin/ls"
	"/bin/ls -l"
	"/bin/ls /"
	"/bin/ls /etc"
	"/usr/bin/find /etc -type f -name 'hosts'"
	"/bin/cat /etc/hosts"
	"echo $(date)"
    "/bin/cat Makefile"
    "/bin/ls Makefile"
    "/bin/ls Makefile -l"
)

for cmd in "${basic_commands[@]}"; do
    check_command "$cmd"
done

print_title "Testing Echo Commands"
echo_commands=(
	"1 echo Hello World"
    "2 echo"
    "3 echo -n Hello World"
    "4 echo -n"
    "5 echo -n -n -n Hello World"
    "6 echo -nnn Hello World"
    "7 echo -n -nx Hello World"
    "8 echo -nx -n Hello World"
    "9 echo    Hello    World"

)

for cmd in "${echo_commands[@]}"; do
    test_id=$(echo $cmd | cut -d' ' -f1)
    command=$(echo $cmd | cut -d' ' -f2-)
    check_command "$test_id" "$command"
done

print_title "Testing Sequential Operators"
sequential_commands=(
    'echo "A" && echo "B" || echo "C"'
    '(echo "A" && echo "B") || echo "C"'
    '(echo "A" && (echo "B" || echo "C")) || echo "D"'
    '(false && echo "B") || echo "C"'
    'echo "A" | grep "A" && echo "Success" || echo "Fail"'
    '(echo "A" && echo "B" | grep "B") || echo "C"'
    '(nonexistentcommand && echo "B") || echo "Fallback"'
    'true && false || echo "Recovered"'
	'echo 1 && (echo 2 || echo 3) | echo 4'
    'echo 1 && (echo 2 && (echo 3 && echo4) && echo 5)'
    'echo 1 && (echo 2 && (echo 3 && echo4) || echo 5)'
    'echo 1 && (echo 2 && (echo 3 || echo4) && echo 5)'
    'echo 1 && (echo 2 || (echo 3 && echo4) && echo 5)'
    'echo 1 && (echo 2 || (echo 3 || echo4) && echo 5)'
)

for cmd in "${sequential_commands[@]}"; do
    check_command "$cmd"
done

rm bash_output.txt minishell_output.txt
