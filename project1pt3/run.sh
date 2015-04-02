#! /bin/bash

./parser tests/test$1 >& out
diff out tests/test$1_correct
