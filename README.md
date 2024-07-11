# APIProject2023

### What is this?

This is one of my bachelor degree projects.
In my university there are three projects that contribute to my final score (up to 6 points).

This one in particular is the final project from the course 'Algoritmi E Principi Dell'Informatica' so the project is about programming and data structures.

Professor: Martinenghi Davide

**Score**: 30L/30

| Score       | Memory  | Time  |       Result       |
|-------------|--------:|------:|:------------------:|
| 18          | 128 MiB | 19 s  | :white_check_mark: |
| 21          | 118 MiB | 15 s  | :white_check_mark: |
| 24          | 108 MiB | 10 s  | :white_check_mark: |
| 27          |  98 MiB |  6 s  | :white_check_mark: |
| 30          |  88 MiB |  4 s  | :white_check_mark: |
| 30L         |  78 MiB |  1 s  | :white_check_mark: |

### Tools used

| Description         | Strumento                                  |
|---------------------|--------------------------------------------|
| IDE                 | [VSCode](https://code.visualstudio.com/)   |
| Compilatore         | [gcc](https://gcc.gnu.org/)                |
| Misurazione memoria | [Valgrind - Massif](https://valgrind.org/) |
| Sistema operativo   | MacOS                                      |


### Try it yourself!

If you want to try it yourself, I leave the [presentation](Presentation.pdf) and the [specification](Specification.pdf) files.

To get perfect score you need to run test case [108](Tests/open_108.txt) and have the ouput in under a second and with less than 78 MB of memory used.

### How to run tests

To run test on your code you need three simple steps (example with test 1):
1. Compile the program with the command `make your_c_file`
2. Run the program with the command `./your_c_file > output.txt < Tests/test_1.txt`
3. Check the difference between your `output.txt` and the test output `test_1.output.txt`

## Contact

If you have contributions, need support, have suggestions, or just want to get in touch with the me, send me an [email](mailto:picamirko02@gmail.com)!

## License

This software is licensed under the terms of the MIT license.
See [LICENSE](LICENSE) for more details.
