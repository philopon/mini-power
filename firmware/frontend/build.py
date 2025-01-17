import subprocess

subprocess.check_call(["npm", "run", "build"], shell=True, cwd="frontend")
