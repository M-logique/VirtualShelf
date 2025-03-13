import shutil
import subprocess
import sys
from argparse import ArgumentParser
from os import name as os_name
from pathlib import Path
from urllib.request import urlretrieve

SQLITE3_DOWNLOAD_URL = "https://www.sqlite.org/2025/sqlite-amalgamation-3490100.zip"
ZIP_OUT = Path("sqlite3_out")
SQLITE_ARCHIVE = Path("sqlite3.zip")


def get_executable_alias(tool: str) -> str:
    return f"x86_64-w64-mingw32-{tool}" if os_name == "nt" else tool


def download_sqlite3():
    if not SQLITE_ARCHIVE.exists():
        print(f"Downloading SQLite3 from {SQLITE3_DOWNLOAD_URL}...")
        urlretrieve(SQLITE3_DOWNLOAD_URL, SQLITE_ARCHIVE)
    else:
        print("SQLite3 archive already exists. Skipping download.")

    ZIP_OUT.mkdir(exist_ok=True)
    shutil.unpack_archive(SQLITE_ARCHIVE, ZIP_OUT)


def run_command(cmd, cwd):
    try:
        subprocess.run(cmd, cwd=cwd, check=True, stdout=sys.stdout, stderr=sys.stderr)
    except subprocess.CalledProcessError as e:
        print(f"Error: {e}")
        sys.exit(1)


def build(output_path: Path):
    download_sqlite3()

    sqlite_c_file = next(ZIP_OUT.glob("**/sqlite3.c"))
    sqlite_dir = sqlite_c_file.parent
    print("Building sqlite3.o")
    run_command(
        [get_executable_alias("gcc"), "-c", "-o", "sqlite3.o", "sqlite3.c"], sqlite_dir
    )
    print("Building libsqlite3.a")
    run_command(
        [get_executable_alias("ar"), "rcs", "libsqlite3.a", "sqlite3.o"], sqlite_dir
    )

    shutil.move(sqlite_dir / "libsqlite3.a", output_path)
    print(f"SQLite3 static library saved to {output_path}")

    # Cleanup
    SQLITE_ARCHIVE.unlink(missing_ok=True)
    shutil.rmtree(ZIP_OUT, ignore_errors=True)


def main():
    arg_parser = ArgumentParser(description="Build SQLite3 static library for MinGW")
    arg_parser.add_argument(
        "--output", "-o", required=True, type=Path, help="Output path for libsqlite3.a"
    )

    args = arg_parser.parse_args()
    build(args.output)


if __name__ == "__main__":
    main()
