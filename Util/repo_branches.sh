#!/bin/bash

echo "Git Repositories & Submodules Status"
echo "===================================="

# Find all .git directories (repos) and files (submodules) recursively
find . -name ".git" 2>/dev/null | sort | while read -r git_dir; do
    # Strip the '/.git' suffix to get the repository's root path
    repo_path=$(dirname "$git_dir")

    # Remove the leading './' for a cleaner terminal output
    display_path="${repo_path#./}"

    # Handle the case where the script is run directly inside a repo
    [ "$display_path" = "." ] && display_path="(current directory)"

    # Get the actively checked-out branch name
    branch=$(git -C "$repo_path" branch --show-current 2>/dev/null)

    # If the branch name is empty, it is likely a detached submodule
    if [ -z "$branch" ]; then
        hash=$(git -C "$repo_path" rev-parse --short HEAD 2>/dev/null)

        if [ -n "$hash" ]; then
            branch="(detached at $hash)"
        else
            branch="(uninitialized)"
        fi
    fi

    printf "\e[34m%-40s\e[0m | \e[32m%s\e[0m\n" "$display_path" "$branch"
done
