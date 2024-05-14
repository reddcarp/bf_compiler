#!/bin/bash

OUTPUT_FILE=output.txt
BF_EXECUTABLE=$1

tearDown() {
    rm -f $OUTPUT_FILE
}

testHelloWorld() {
    ./bf_compiler ../test/bf_scripts/hello_world.bf out
    ./out > ${OUTPUT_FILE}
    assertEquals 0 $?
    assertEquals 'Hello World!' "$( cat ${OUTPUT_FILE} )"
}

. shunit2