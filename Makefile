# MIT License
#
# Copyright (c) 2017 Zach Pfeffer
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

CC=gcc
CFLAGS=-Wall -g

all: run_test run_test_a run_test_so

run_test: test_list
	./$<

run_test_a: test_list_a
	./$<

run_test_so: test_list_so
	LD_LIBRARY_PATH=. ./$<

test_list: test_list.o list.o list.h

test_list_a: test_list.o list.h liblist.a
	$(CC) $< -L. -static -llist -o $@

test_list_so: test_list.o list.h liblist.so
	$(CC) $< -L. -llist -o $@

liblist.a: liblist.a(list.o)
	ranlib liblist.a

list-pic.o: list.c
	$(CC) -fPIC -c $< -o $@

liblist.so: list-pic.o
	$(CC) -shared -o $@ $<

clean:
	rm -f test_list test_list_a test_list_so test_list.o list.o liblist.a list-pic.o liblist.so
