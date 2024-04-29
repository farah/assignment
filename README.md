To execute your program on a Mac using the test files you've provided, follow these steps:

1. **Compile the Program**:
   Open Terminal and navigate to the directory containing your C program (`program.c`). Compile the program using `clang` by running:
   ```bash
   clang -g -o program program.c
   ```
   This command compiles `program.c` and generates an executable named `program`. The `-g` option is used to include debug information in the executable, which is helpful for debugging.

2. **Run the Program with Input Redirection**:
   To execute your program using one of the test files (for example, `test0.txt`), you can use input redirection (`<`) to feed the test file into your program:
   ```bash
   ./program < test0.txt
   ```
   This command runs the executable `program` and inputs data from `test0.txt`.

3. **Check Output**:
   The output of your program will be displayed in the terminal. If your program is supposed to write output to a file or perform other actions, you'll need to check the respective outputs as specified in your program.

4. **Using Different Test Files**:
   To test with another file, such as `test1.txt`, simply replace `test0.txt` with `test1.txt` in the command:
   ```bash
   ./program < test1.txt
   ```

This process allows you to test your program with various input files by redirecting file content as standard input to your program. It's a common method for testing programs that are designed to process sequential data input.