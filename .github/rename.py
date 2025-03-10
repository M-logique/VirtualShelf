import os, sys
folder = sys.argv[1]
arch = os.environ.get("ARCH", "default")
files = ["VirtualShelf", "VirtualShelf.exe"]
for f in files:
    old = os.path.join(folder, f)
    if os.path.exists(old):
        base, ext = os.path.splitext(f)
        new = os.path.join(folder, f"{base}-{arch}{ext}")
        os.rename(old, new)