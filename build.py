#!/usr/bin/env python3

import os, os.path, sys

if os.getenv("cc") == None:
    if os.getenv("CC") == None:
        print("[WARN] Envoirment variable `cc`/`CC` isn't set!")
        CC = input("Which compiler Do you want to use? ")
        os.environ["cc"] = CC
    else:
        CC = str(os.getenv("CC"))
else:
    CC = str(os.getenv("cc"))

INPUT: str = "src/main.c"
CFLAGS: str = "-Wall -Wextra -O2 -ffunction-sections -fdata-sections -Wl,--gc-sections"
OUTPUT: str = ""
OUTPUT_DIR: str = "out"

if os.name == "nt":
    OUTPUT += f"{OUTPUT_DIR}/main.exe"
else:
    OUTPUT += f"{OUTPUT_DIR}/main"


def usage():
    print(f"Usage: {sys.argv[0]} <Sub Command>\n")
    print(
        "Sub commands:\n\tbuild:\n\t\tBuilds the project\n\trelease:\n\t\tBuilds the program in release mode\n\trun:\n\t\tBuilds the program and runs it"
    )


def build() -> int:
    if os.path.isdir(OUTPUT_DIR) == False:
        os.mkdir(OUTPUT_DIR)

    cmd = f"{CC} {INPUT} {CFLAGS} -ggdb -o {OUTPUT}"
    print(f"[CMD] {cmd}")
    out = os.system(cmd)
    return out


def release():
    if os.path.isdir(OUTPUT_DIR) == False:
        os.mkdir(OUTPUT_DIR)

    cmd = f"{CC} {INPUT} {CFLAGS},-s -o {OUTPUT}"
    print(f"[CMD] {cmd}")
    os.system(cmd)


def run():
    if build() == 0:
        print(f"[INFO] Running The program\n[CMD] ./{OUTPUT}\n----------------------")
        os.system(f"./{OUTPUT}")


def main(argc: int, argv: list):
    if argc < 2:
        usage()
        sys.exit(1)
    if argv[1] == "build":
        build()
        sys.exit(0)
    if argv[1] == "release":
        release()
        sys.exit(0)
    elif argv[1] == "run":
        run()
        sys.exit(0)
    elif argv[1] == "-h" or argv[1] == "--help":
        usage()
        sys.exit(0)
    else:
        print(f"Invalid Subcommand --- Use {argv[0]} -h || --help for help")
        sys.exit(1)


if __name__ == "__main__":
    main(len(sys.argv), sys.argv)
