import argparse
import logging
import os
import shutil
import subprocess
import sys
from typing import Optional
from urllib.request import urlretrieve

BUILD_PATH = "build"
BUILD_SLOTS = {
    # amd64, 386, arm, ppc64.
    "win-x86_64": {
        "flags": {
            "CMAKE_C_COMPILER": "x86_64-w64-mingw32-gcc",
            "CMAKE_CXX_COMPILER": "x86_64-w64-mingw32-g++",
            "AR": "x86_64-w64-mingw32-ar",

            "GOOS": "windows",
            "GOARCH": "amd64"
        },
        "testings_enabled": False
    },
    "win-aarch64": {
        "flags": {
            "CMAKE_C_COMPILER": "aarch64-w64-mingw32-gcc",
            "CMAKE_CXX_COMPILER": "aarch64-w64-mingw32-g++",
            "AR": "aarch64-w64-mingw32-ar",

            "GOOS": "windows",
            "GOARCH": "arm64"
        },
        "testings_enabled": False
    },
    "linux-x86_64": {
        "flags": {
            "CMAKE_C_COMPILER": "gcc",
            "CMAKE_CXX_COMPILER": "g++",
            "AR": "ar",

            "GOOS": "linux",
            "GOARCH": "amd64",
        },
        "testings_enabled": True
    },
    "linux-aarch64": {
        "flags": {
            "CMAKE_C_COMPILER": "aarch64-linux-gnu-gcc",
            "CMAKE_CXX_COMPILER": "aarch64-linux-gnu-g++",
            "AR": "aarch64-linux-gnu-ar",

            "GOOS": "linux",
            "GOARCH": "arm64"
        },
        "testings_enabled": False
    },
    "darwin-aarch64": {
        "flags": {
            "CMAKE_C_COMPILER": "gcc",
            "CMAKE_CXX_COMPILER": "g++",
            "AR": "ar",

            "GOOS": "darwin",
            "GOARCH": "arm64",
        },
        "testings_enabled": True
    },
    "darwin-x86_64": {
        "flags": {
            "CMAKE_C_COMPILER": "gcc",
            "CMAKE_CXX_COMPILER": "g++",
            "CMAKE_OSX_ARCHITECTURES": "x86_64",
            "AR": "ar",

            "SQLITE3_ADDITIONAL_FLAGS": "-target x86-64 ", 

            "GOOS": "darwin",
            "GOARCH": "amd64",
        },
        "testings_enabled": False
    },

}


def get_os() -> str:
    if sys.platform.startswith("linux"):
        return "linux"
    elif sys.platform.startswith("darwin"):
        return "darwin"
    elif sys.platform.startswith("win"):
        return "windows"
    else:
        raise ValueError("Unsupported operating system")


def setup_logger(
    name: Optional[str] = None, level: int = logging.DEBUG
) -> logging.Logger:
    log_format: str = "[%(asctime)s] [%(levelname)s] [%(name)s] - %(message)s"
    date_format: str = "%Y-%m-%d %H:%M:%S"

    logging.basicConfig(level=level, format=log_format, datefmt=date_format)

    return logging.getLogger(name or "BuildScript")


def get_build_flags(flags: dict) -> list:

    return [f"-D{key}={value}" for key, value in flags.items()]


def clean(p):
    if os.path.exists(p):
        shutil.rmtree(p)
        logger.info("Build directory cleaned.")


def build(build_tests: bool, slot: str, build_path: str):
    os.makedirs(build_path, exist_ok=True)

    logger.info(f"Configuring project ...")
    subprocess.run(
        [
            "cmake",
            "..",
            "-DBUILD_TESTS=ON" if build_tests else "-DBUILD_TESTS=OFF",
            "-DCMAKE_BUILD_TYPE=Release",
            *get_build_flags(BUILD_SLOTS[slot]["flags"])
        ],
        cwd=build_path,
        check=True,
        env=os.environ,
    )

    logger.info("Building project...")
    subprocess.run(
        ["cmake", "--build", "."], cwd=build_path, check=True, env=os.environ
    )


def move_binary(destination: str, build_path: str):
    # Search for files named VirtualShelf or VirtualShelf.*
    for root, _, files in os.walk(build_path):
        for file in files:
            if (
                file.startswith("VirtualShelf") and not "Tests" in file
            ):  # Matches "VirtualShelf" and "VirtualShelf.*"
                src = os.path.join(root, file)
                if not os.path.exists(destination):
                    os.makedirs(destination)
                shutil.move(src, os.path.join(destination, file))
                logger.info(f"Moved binary {file} to {destination}")


def find_executable(output_dir: str) -> Optional[str]:
    binary_name = (
        "VirtualShelf.exe" if sys.platform.startswith("win") else "VirtualShelf"
    )
    binary_path = os.path.join(output_dir, binary_name)
    if os.path.isfile(binary_path):
        return binary_path
    for root, _, files in os.walk(output_dir):
        for file in files:
            if file.startswith("VirtualShelf"):
                return os.path.join(root, file)
    return None


def is_git_installed():
    try:
        subprocess.run(
            ["git", "--version"],
            check=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
        )
        return True
    except subprocess.CalledProcessError:
        return False


def clone_with_git():
    subprocess.run(
        [
            "git",
            "clone",
            "--depth=1",
            "https://github.com/SqliteModernCpp/sqlite_modern_cpp.git",
            "sqlite_modern_cpp",
        ],
        check=True,
    )


def download_and_extract_zip():
    # Download zip file
    zip_path = "sqlite_modern_cpp.zip"
    urlretrieve(
        "https://github.com/SqliteModernCpp/sqlite_modern_cpp/archive/refs/heads/main.zip",
        zip_path,
    )

    # Extract zip file using shutil
    shutil.unpack_archive(zip_path, "sqlite_modern_cpp")

    # Clean up zip file
    os.remove(zip_path)


if __name__ == "__main__":
    logger = setup_logger()

    if not os.path.exists("./sqlite_modern_cpp/hdr"):
        logger.info("Cloning sqlite_modern_cpp")
        if is_git_installed():
            clone_with_git()
        else:
            download_and_extract_zip()

    parser = argparse.ArgumentParser(description="VirtualShelf Project Build Script")
    parser.add_argument(
        "--purge",
        "-p",
        action="store_true",
        help="Clean the build directory before building",
    )
    parser.add_argument(
        "--clear",
        "-c",
        action="store_true",
        help="Clean the build directory after building",
    )
    parser.add_argument(
        "--output-dir",
        "-o",
        type=str,
        help="Directory to move the binary after build",
        default=".",
    )
    parser.add_argument(
        "--run",
        "-r",
        help="Runs the binary file after the compile",
        action="store_true",
    )
    parser.add_argument(
        "--remove", "-rm", help="Removes the specified path", required=False, type=str
    )
    parser.add_argument("--test", "-t", help="Runs tests", action="store_true")

    parser.add_argument(
        "--slot",
        "-s",
        help="Build slots config",
        default=f"github-actions-{get_os()}",
        type=lambda x: next((i for i in BUILD_SLOTS.keys() if x.lower().strip() in i)),
    )
    parser.add_argument(
        "--build-path",
        "-b",
        type=str,
        help="Specify a custom build directory",
        default=BUILD_PATH,
    )

    args = parser.parse_args()
    if not args.slot:
        raise ValueError("Invalid slot")

    if args.purge:
        clean(args.build_path)
    
    if args.remove:
        for p in args.remove.split(","):
            if os.path.exists(p):
                logger.info("Removing %s", p)
                os.remove(p)
    t = BUILD_SLOTS[args.slot].get("testing_enabled")

    if t:
        logger.warning("Sorry but testing is not supported for %s!", args.slot)
    

    logger.info("Chosen slot: %s", args.slot)
    build(t, args.slot, args.build_path)
    if args.output_dir:
        move_binary(args.output_dir, args.build_path)

    if t:
        logger.info("Running tests...")
        subprocess.run(["ctest", "--output-on-failure"], check=True, cwd=args.build_path)
        logger.info("All tests were successfull")

    if args.clear:
        clean(args.build_path)

    if args.run:
        binary_path = find_executable(args.output_dir)
        if binary_path:
            subprocess.run([binary_path])
        else:
            logger.error("Executable not found.")
