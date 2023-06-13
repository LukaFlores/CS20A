
#!/bin/sh

set -xe

make test

time (make) >&1 1>/dev/null
         
