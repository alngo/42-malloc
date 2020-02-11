#!/usr/bin/env bash
expected_exit_code=0
./42/run.sh ./units.out
if [ $? -ne $expected_exit_code ]; then
  echo "Unexpected exit code: $expected_exit_code expected but was $?"
  exit 1
fi
exit 0