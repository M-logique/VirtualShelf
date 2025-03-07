import subprocess
import os
import argparse
import shutil
import logging
import sys
from typing import Optional

BUILD_PATH = "build"


def setup_logger(
    name: Optional[str] = None, level: int = logging.DEBUG
) -> logging.Logger:
    log_format: str = "[%(asctime)s] [%(levelname)s] [%(name)s] - %(message)s"
    date_format: str = "%Y-%m-%d %H:%M:%S"

    logging.basicConfig(level=level, format=log_format, datefmt=date_format)

    return logging.getLogger(name or "BuildScript")


def clean():
    if os.path.exists(BUILD_PATH):
        shutil.rmtree(BUILD_PATH)
        logger.info("Build directory cleaned.")


def build(build_type):
    os.makedirs(BUILD_PATH, exist_ok=True)

    logger.info(f"Configuring project ({build_type} mode)...")
    subprocess.run(
        ["cmake", "..", f"-DCMAKE_BUILD_TYPE={build_type}"], cwd=BUILD_PATH, check=True
    )

    logger.info("Building project...")
    subprocess.run(["cmake", "--build", "."], cwd=BUILD_PATH, check=True)


def move_binary(destination: str):
    # Search for files named VirtualShelf or VirtualShelf.*
    for root, dirs, files in os.walk(BUILD_PATH):
        for file in files:
            if file.startswith(
                "VirtualShelf"
            ):  # Matches "VirtualShelf" and "VirtualShelf.*"
                src = os.path.join(root, file)
                if not os.path.exists(destination):
                    os.makedirs(destination)
                shutil.move(src, os.path.join(destination, file))
                logger.info(f"Moved binary {file} to {destination}")



def find_executable(output_dir: str) -> Optional[str]:
    binary_name = "VirtualShelf.exe" if sys.platform.startswith("win") else "VirtualShelf"
    binary_path = os.path.join(output_dir, binary_name)
    if os.path.isfile(binary_path):
        return binary_path
    for root, _, files in os.walk(output_dir):
        for file in files:
            if file.startswith("VirtualShelf"):
                return os.path.join(root, file)
    return None

if __name__ == "__main__":
    logger = setup_logger()

    parser = argparse.ArgumentParser(description="C++ Project Build Script")
    parser.add_argument(
        "--clean",
        "-c",
        action="store_true",
        help="Clean the build directory before building",
    )
    parser.add_argument(
        "--build-type",
        "-t",
        choices=["Debug", "Release"],
        default="Debug",
        help="Set the build type (default: Debug)",
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
        action="store_true"
    )
    parser.add_argument(
        "--remove",
        "-rm",
        help="Removes the specified path",
        required=False,
        type=str
    )

    args = parser.parse_args()

    if args.clean:
        clean()
    if args.remove:
        for p in args.remove.split(","):
            if os.path.exists(p):
                logger.info("Removing %s", p)
                os.remove(p)

    try:
        build(args.build_type)
        if args.output_dir:
            move_binary(args.output_dir)
    except subprocess.CalledProcessError as e:
        logger.error(f"Build failed with error: {e}")

    if args.run:
        binary_path = find_executable(args.output_dir)
        if binary_path:
            subprocess.run([binary_path])
        else:
            logger.error("Executable not found.")
