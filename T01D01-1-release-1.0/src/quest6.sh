#!/bin/bash

cd ai_help
chmod +x keygen.sh
./keygen.sh
cd key
ls
find . -type f -name "file*" -exec rm -v {} \;
cd ..
chmod +x unifier.sh
./unifier.sh

