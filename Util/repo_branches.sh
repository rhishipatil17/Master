#!/bin/bash

echo "Git branches in nested directories......"

for dir in */*/; do
    if [ -d "${dir}.git" ]; then
        repo_path="${dir%/}"
        branch=$(git -C "$dir" branch -show-current 2>/dev/null)

        if [ -z "$branch" ]; then
            branch=$(git -C "$dir" rev-parse --abbrev-ref HEAD 2>/dev/null)
        fi

        printf "\e[34m%-40s\e[0m | \e[32m%s\e[0m\n" "$repo_path" "$branch"
    fi
done
