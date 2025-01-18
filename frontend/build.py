import subprocess

subprocess.run("npm run build", shell=True, cwd="frontend", check=True)
