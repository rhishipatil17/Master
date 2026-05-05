import json
import os
import sys
import subprocess

def get_local_commit_count():
    """Fallback method to count commits if run locally instead of GitHub Actions."""
    base_ref = os.getenv('GITHUB_BASE_REF', 'main')
    # Counts commits on your current branch that are not on the main branch
    cmd = ["git", "rev-list", "--count", f"origin/{base_ref}...HEAD"]
    result = subprocess.run(cmd, capture_output=True, text=True)
    
    if result.returncode != 0:
        print(f"❌ Error running git command. Ensure origin/{base_ref} exists.")
        sys.exit(1)
        
    return int(result.stdout.strip())

def main():
    # GitHub Actions automatically populates this environment variable
    event_path = os.getenv('GITHUB_EVENT_PATH')
    
    # --- GitHub Actions Mode ---
    if event_path and os.path.exists(event_path):
        with open(event_path, 'r') as f:
            event_data = json.load(f)
        
        # Extract the exact commit count from the PR metadata
        if 'pull_request' in event_data:
            commit_count = event_data['pull_request']['commits']
        else:
            print("✅ Not a pull request event. Skipping check.")
            sys.exit(0)
            
    # --- Local Testing Mode ---
    else:
        print("⚠️ GITHUB_EVENT_PATH not found (running locally). Falling back to git CLI.")
        commit_count = get_local_commit_count()

    # --- Validation Logic ---
    print(f"Found {commit_count} commit(s).")

    if commit_count > 1:
        print("❌ Error: This Pull Request contains multiple commits.")
        print("To fix this, please squash your commits into a single commit.")
        print(f"Hint: You can use `git rebase -i HEAD~{commit_count}` locally, then force push.")
        sys.exit(1)
        
    if commit_count == 0:
        print("❌ Error: No commits found. This is unusual.")
        sys.exit(1)
        
    print("✅ Success: Exactly 1 commit found!")

if __name__ == "__main__":
    main()
