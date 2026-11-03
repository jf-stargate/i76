#!/usr/bin/env python3
"""Run CTest-registered executable tests under Memcheck or Helgrind.

A missing Valgrind executable or a selected test failure is fatal.  Helgrind
without registered threaded tests is explicitly reported as not applicable.
"""

import argparse
import json
import pathlib
import shutil
import subprocess
import sys


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--build-dir", type=pathlib.Path, required=True)
    parser.add_argument("--tool", choices=("memcheck", "helgrind"), required=True)
    args = parser.parse_args()

    build_dir = args.build_dir.resolve()
    discovery = subprocess.run(
        ["ctest", "--test-dir", str(build_dir), "--show-only=json-v1"],
        capture_output=True, text=True, check=False,
    )
    if discovery.returncode != 0:
        print(discovery.stderr, file=sys.stderr)
        return discovery.returncode

    tests = json.loads(discovery.stdout)["tests"]
    chosen = [
        test for test in tests
        if args.tool in next((prop.get("value", []) for prop in test.get("properties", [])
                              if prop.get("name") == "LABELS"), [])
    ]
    if not chosen:
        if args.tool == "helgrind":
            print("Helgrind: not applicable (no threaded test cases registered)")
            return 0
        print("error: no Memcheck-labeled tests registered", file=sys.stderr)
        return 2

    valgrind = shutil.which("valgrind")
    if valgrind is None:
        print("error: valgrind is required for the selected diagnostic suite", file=sys.stderr)
        return 2

    log_dir = build_dir / "valgrind" / args.tool
    log_dir.mkdir(parents=True, exist_ok=True)
    settings = (
        ["--leak-check=full", "--show-leak-kinds=all",
         "--errors-for-leak-kinds=definite,possible", "--track-origins=yes"]
        if args.tool == "memcheck" else ["--history-level=full"]
    )
    failures = 0
    for test in chosen:
        properties = {prop["name"]: prop["value"] for prop in test.get("properties", [])}
        if "WILL_FAIL" in properties and properties["WILL_FAIL"]:
            print(f"error: ineligible expected-failure test {test['name']}", file=sys.stderr)
            return 2
        command = test.get("command", [])
        if not command:
            print(f"error: test {test['name']} has no executable", file=sys.stderr)
            return 2
        cwd = pathlib.Path(properties.get("WORKING_DIRECTORY", str(build_dir)))
        timeout = float(properties.get("TIMEOUT", 180))
        log_path = log_dir / (test["name"].replace("/", "_") + ".log")
        run = [valgrind, "--tool=" + args.tool, *settings, "--error-exitcode=99", *command]
        try:
            result = subprocess.run(run, cwd=cwd, capture_output=True, text=True,
                                    timeout=timeout, check=False)
            log_path.write_text(result.stdout + "\n" + result.stderr, encoding="utf-8")
            passed = result.returncode == 0
        except subprocess.TimeoutExpired as error:
            log_path.write_text(str(error), encoding="utf-8")
            passed = False
        print(("PASS" if passed else "FAIL") + f" {test['name']} ({log_path})")
        failures += 0 if passed else 1
    return 0 if failures == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
