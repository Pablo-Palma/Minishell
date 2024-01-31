#!/bin/bash

check_command() {
    command=$1
    echo "Executing: $command"

    bash -c "$command" > bash_output.txt

    ./minishell -c "$command" > minishell_output.txt

    if diff -q bash_output.txt minishell_output.txt > /dev/null; then
        echo "OK:  '$command'"
    else
        echo "KO:  '$command'"
    fi

    echo "-------------------------------------"
}

commands=(
    'echo "A" && echo "B" || echo "C"'
    '(echo "A" && echo "B") || echo "C"'
    '(echo "A" && (echo "B" || echo "C")) || echo "D"'
    '(false && echo "B") || echo "C"'
    'echo "A" | grep "A" && echo "Success" || echo "Fail"'
    '(echo "A" && echo "B" | grep "B") || echo "C"'
    '(nonexistentcommand && echo "B") || echo "Fallback"'
    'true && false || echo "Recovered"'
)

for cmd in "${commands[@]}"; do
    check_command "$cmd"
done

rm bash_output.txt minishell_output.txt

