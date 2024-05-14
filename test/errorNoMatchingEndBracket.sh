#!/bin/bash

OUTPUT_FILE=output.txt
BF_EXECUTABLE=$1

tearDown() {
    rm -f $OUTPUT_FILE
}

testErrorNoMatchingEndBracket() {
    ./bf_compiler ../test/bf_scripts/error_no_matching_end_bracket.bf out 2> ${OUTPUT_FILE}
    assertNotEquals 0 $?
    assertEquals 'Error: missing corresponding `]`' "$( cat ${OUTPUT_FILE} )"
}

. shunit2