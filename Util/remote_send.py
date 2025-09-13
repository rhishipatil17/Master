import os
import sys
import paramiko
from scp import SCPClient
from enum import Enum

#ssh connection details
remote_host = "10.205.105.69"
remote_port = 22
username = "rhishi"
private_key_path = "./id_rsa"

#remote file operation bit positions
no_permission_change = 0
create_dir = 1
flags = ["h", "n", "c"]

file_mod = 0        #operation to be done on remote
file_pos = 1        #position of path of local file
path_pos = 2        #position of path of remote
remote_path = "Dev"

if len(sys.argv) <= 1:
    print("Error: No file name provided")
    sys.exit(1)

#checking all flags
if sys.argv[1].startswith("-"):
    given_flags = sys.argv[1][1:]
    for x in given_flags:
        if x not in flags:
            print("Error: unknown flag")
            sys.exit(1)

    file_pos = 2
    path_pos = 3
    if "h" in sys.argv[1]:
        print("Description: This script will send the specified file to a remote system through ssh and give it execute permissions\n"
              "Usage: python3 remote_send.py [option] <local_file_path> <remote_path>\n"
              "[option]\n"
              "-h : help\n"
              "-n : do not set execute permission after sending the file\n"
              "-c : create the remote path directory if it does not exist\n"
              "\n"
              "<local_file_path> : (necessary) local file file that needs to be sent\n"
              "<remote_path>     : path in remote system where the file needs to be sent, default: Dev/\n"
              "                    if path is provided, Dev/ will always be appended to it"
        )
        sys.exit(1)
    if "n" in sys.argv[1]:
        file_mod |= 1 << no_permission_change
    if "c" in sys.argv[1]:
        file_mod |= 1 << create_dir
    # print("file mod: ", hex(file_mod))
    # print("create_dir: ", (file_mod >> create_dir)&1)
    # print("no per change: ", (file_mod >> no_permission_change)&1)

    if len(sys.argv) <= 2:
        print("Error: No file name provided")
        sys.exit(1)

#getting all paths
local_file = sys.argv[file_pos]

if local_file.find("/") != -1:
    local_path, file_name = local_file.rsplit("/",maxsplit=1)
else:
    file_name = local_file

if len(sys.argv) > path_pos:
    if sys.argv[path_pos].find("Dev/") != -1:
        remote_path = sys.argv[path_pos]
    else:
        remote_path = remote_path + "/" + sys.argv[path_pos]
remote_path += "/"
print(f"Remote path: {remote_path}")

remote_file = remote_path + file_name

#checking if file exists in local
if not os.path.exists(local_file):
    print(f"Error: Local file not found: {local_file}")
    sys.exit(1)

# print(f"Local file: {local_file}")
# print(f"Remote file: {remote_file}")

#ssh setup
private_key = paramiko.RSAKey.from_private_key_file(private_key_path)
ssh = paramiko.SSHClient()
ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())

try:
    ssh.connect(
        hostname=remote_host,
        port=remote_port,
        username=username,
        pkey=private_key
    )
    print("SSH connection successfully established")

    sftp = ssh.open_sftp()

    #checking if remote path exists
    try:
        sftp.stat(remote_path)
    except FileNotFoundError:
        if (file_mod >> create_dir) & 1:
            print(f"Creating remote path: {remote_path}")
            sftp.mkdir(remote_path)
        else:
            print(f"Error: Remote path not found: {remote_path}")
            sys.exit(1)

    #send file to remote
    sftp.put(local_file, remote_file)
    print("File successfully sent")

    if (~file_mod >> no_permission_change)&1:
        #changing file permissions in remote
        sftp.chmod(remote_file, 0o744)
        print("Permission successfully changed")

except Exception as e:
    print(f"Error: {e}")

finally:
    ssh.close()