List
====

Doubly-linked list code and test-bench

Copyright (c) 2017 Zach Pfeffer

pfefferz@gmail.com

Overview
--------

Functions to insert, remove and count doubly linked-list elements and a
test bench to test the implementation. The functions are built to take lists and
elements and return status so that NULLs and invariant violations can be caught,
e.g. the prev and next pointer of a non-inserted element should point to that
element.

In addition, list elements only contain next and prev members. The user is meant
to use the CONTAINER_OF macro to get a pointer to the outer struct that would
contain a list element. CONTAINER_OF is implemented in test_list.c, its usage is
demonstrated and it has its own unit test.

ARRAY_SIZE is also implemented, demonstrated and unit tested.

Finally, Both CONTAINER_OF and ARRAY_SIZE should be in separate files, but in
the interest of file minimization, I've put them into test_list.c. I note this
because I wrote this to demonstrate good-ish implementation practices. If
something could be better, please let me know.  For instance, I've used Doxygen
to document the functions as opposed to
http://www.sphinx-doc.org/en/stable/domains.html. What are your thoughts?

Usage
-----

To build the list test bench type:
`make`

To run the list test bench type:
`./test_list`

See test_list.c to see how to use the functions.

References
----------

Referenced this when creating this file:
https://raw.githubusercontent.com/google/protobuf/master/README.md
I <3 protocol buffers!

I found the MIT license text at http://choosealicense.com/licenses/mit/ which I
found from https://github.com/blog/1530-choosing-an-open-source-license

The _ after the LIST_H_ came from:
https://google.github.io/styleguide/cppguide.html#The__define_Guard

The use of starting the first Doxygen Special Command after /** and using 2
spaces indent from * came from:
https://www.cs.cmu.edu/~409/doc/doxygen.html

I found the basic Makefile from:
An Introduction to GCC by Brian Gough ISBN 0-9541617-9-3

Most of this work was done so that I could become proficient with Vim. During
most of it I read (and reread) Vi IMproved-- Vim by Steve Oualline ISBN
0-7357-1001-5. I would recommend this book to learn Vim.
