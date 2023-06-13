#!/bin/sh

set -xe

./output
time (./output) >&1 1>/dev/null
         
