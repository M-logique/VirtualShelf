import os
import sys

folder = sys.argv[1]
inf = os.environ.get("INF", "default")
name = os.environ.get("NAME", "binary")
files = ["VirtualShelf", "VirtualShelf.exe"]
for f in files:
    old = os.path.join(folder, f)
    if os.path.exists(old):
        _, ext = os.path.splitext(f)
        new = os.path.join(folder, f"{name}-{inf}{ext}")
        os.rename(old, new)
