import subprocess
import sys
import os

def get_changed_files():
    # Compares the current PR branch against the target branch (usually main)
    base_ref = os.getenv('GITHUB_BASE_REF', 'main')
    cmd = ["git", "diff", "--name-only", f"origin/{base_ref}...HEAD"]
    result = subprocess.run(cmd, capture_output=True, text=True)
    return result.stdout.splitlines()

def check_newline(file_path):
    if not os.path.isfile(file_path):
        return True
    with open(file_path, 'rb') as f:
        f.seek(0, os.SEEK_END)
        if f.tell() == 0:
            return True  # Ignore empty files
        f.seek(-1, os.SEEK_END)
        return f.read(1) == b'\n'

def main():
    files = get_changed_files()
    failed_files = []

    for file in files:
        # You can add logic here to skip certain file types (e.g., .png)
        if not check_newline(file):
            failed_files.append(file)

    if failed_files:
        print("❌ The following files are missing a trailing newline:")
        for f in failed_files:
            print(f"  - {f}")
        sys.exit(1) # This signals the GitHub Action to fail
    
    print("✅ All files passed the newline check!")

if __name__ == "__main__":
    main()
