import os
import sys
import subprocess

TARGET_FOLDER = "DSA/Stl"

def get_changed_headers():
    """Gets the list of modified .hpp files in the specific folder."""
    base_ref = os.getenv('GITHUB_BASE_REF', 'main')
    cmd = ["git", "diff", "--name-only", f"origin/{base_ref}...HEAD"]
    result = subprocess.run(cmd, capture_output=True, text=True)
    files = result.stdout.splitlines()
    
    # Filter for .hpp files specifically inside the target folder
    return [f for f in files if f.startswith(f"{TARGET_FOLDER}/") and f.endswith('.hpp')]

def test_compile(header_file):
    """Creates a temporary main.cpp, includes the header, and compiles it."""
    if not os.path.isfile(header_file):
        return True # Skip deleted files

    temp_cpp = "temp_main_test.cpp"
    temp_obj = "temp_main_test.o"

    # 1. Create the temporary main.cpp file
    main_code = f"""
#include "{header_file}"
int main() {{
    return 0;
}}
    """
    with open(temp_cpp, "w") as f:
        f.write(main_code)

    # 2. Compile with g++ using -c (compile only, do not link)
    cmd = ["g++", "-c", temp_cpp]
    result = subprocess.run(cmd, capture_output=True, text=True)

    # 3. Clean up the temporary files
    if os.path.exists(temp_cpp):
        os.remove(temp_cpp)
    if os.path.exists(temp_obj):
        os.remove(temp_obj)

    # 4. Check for errors
    if result.returncode != 0:
        print(f"❌ Compilation failed for {header_file}:")
        print(result.stderr)
        return False
        
    return True

def main():
    headers = get_changed_headers()
    
    if not headers:
        print(f"✅ No .hpp files modified in '{TARGET_FOLDER}'. Skipping check.")
        sys.exit(0)

    failed_files = []
    
    for header in headers:
        print(f"Testing compilation for: {header}...")
        if not test_compile(header):
            failed_files.append(header)

    if failed_files:
        print(f"\n❌ {len(failed_files)} file(s) failed to compile.")
        sys.exit(1)
        
    print("\n✅ All modified header files compiled successfully!")

if __name__ == "__main__":
    main()
