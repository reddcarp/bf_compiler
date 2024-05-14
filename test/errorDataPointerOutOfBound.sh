#!/bin/bash

OUTPUT_FILE=output.txt
BF_EXECUTABLE=$1

tearDown() {
    rm -f $OUTPUT_FILE
}

testErrorNoMatchingEndBracket() {
    ./bf_compiler ../test/bf_scripts/error_data_pointer_out_of_bound.bf out 
    ./out 2> ${OUTPUT_FILE}
    assertNotEquals 0 $?
    assertEquals 'Error: buffer underflow' "$( cat ${OUTPUT_FILE} )"
}

. shunit2