The files in this folder are specifically for this component's documentation and unit-testing purposes.

The NetBeans project is set up to use Cygwin build tools and to link against the CUnit library package available from Cygwin. I have not tested this edition of the library from Ubuntu, as it would require a different project file, but otherwise it "should" work as long as the prerequisites are met.

**Prerequisites for running these unit tests "out of the box"**:
* NetBeans set up for C/C++ development. I used v8.2, but have done some testing w/ v10 (available in Ubuntu 18 LTS' repos) and v11.x and have not noted any problems.
* CUnit. I find the easiest way to acquire this, is to use Cygwin and simply add the CUnit package.

