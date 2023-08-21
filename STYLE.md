## Fennec | C Style Guide

### Indentation
#### Scope
Any code within a keyword bound scope must be indented by 4 spaces for every additional scope.
Tabs should be avoided.
```c
/* okay */
int function() {
    for (;;) {
        ...
    }
}

/* not okay */
int function() {
while (1) {
  printf("%d", 1);
}}
```

#### Multiline Functions
When defining multiline function definitions, or performing mulitline function calls, if the arguments of the function exceed 80 characters then each argument may be placed in its own line, but must be indented 4 spaces from the start of the function call.

Furthermore, in the case of multiple line function calls, the arguments must start on the line **after** the call to the function.

These same rules apply to macros.
```c
/* okay */
some_func_call(
    argument1,
    argument2
);
/* not okay */
some_func_call(argument1,
argument2,
    argument3, argument4,
  argument5);
```
#### Arrays
When defining arrays, if you choose to initialize the array, if the elements exceed 10 on one line, or they exceed 80 characters, they must be moved to the next line below the first opening `{` and each consecutive element must occupy its own line.

*Please note that arrays preferably should be defined with a size limit like `#define MAX_CAP 20`*
```c
/* okay */
int arr[5] = { 1, 2, 3, 4, 5 };
int arr[11] = {
    1,
    ...
    11
};
/* not okay */
int arr[11] = { 1, 2, ..., 10, 11 };
```
---
### Functions
- Functions that are defined in header files must be prefixed with the name of the project they are a part of, followed by an `_`.
- If they do not take any arguments, they must take the argument `void` instead.
- When defining prototypes, the arguments to the function should not specify a name. Instead, the naming of the arguments should be done in the implementation.
- When defining prototypes, the same rules for indentation apply as specified above.
- Functions should always have a snake-case name
- The first function implementation bracket must be on the same line as the function prototype, but when closing the function the closing bracket must occupy its own line, and have no indentation unless it conflicts with any rules from above
- Names must **not** begin with `_` or `__` as these are reserved for the C compiler
- When calling a function, there must be no space between the function name and the start of the first bracket

These rules also apply for defining macros.
*Please note, macros must be defined in **upper case** but each word must still be separateed by an `_`*
```c
/* okay */
int project_func(void) { ... }
void project_func2(int, int);
...
void project_func2(int x, int y) {
    ...
}

/* not okay */
void _function(int x,
    int z) {
while (1) {
...}}
```
---
### Variables
When defining variables:
- Snake case names must be used
- No capital letters should be used in the name
- Global variables should be avoided at all costs
- If you do choose to use global variables, prefix them with the name of your file plus an `_`
- If the definition of the variable is longer than 80 characters, it may be moved to the next line, however must be prefixed with 4 spaces plus the current indentation level.
- Variable names must **not** be prefixed with `_` or `__` as these are reserved for the C  compiler
```c
/* okay */
int x = 20;
int header_x = 30;

/* not okay */
int __x_err = 3;
int
    value =
    12;
```
#### Pointers
When defining pointers, begin your asterisks at the start of the identifier.
For example, use `int *x;` not `int* x;`
#### Global Variables
When defining global variables (only if you absolutely need to) define them as `static` if they are only used in that translation unit. Furthermore, do not initialize the variable. Instead, move your initialization to an `init` function.
```c
/* okay */
static int avoid_me;
...
void init(void) {
    avoid_me = 42;
}

/* not okay */
int GlOBaL_VAR = 3;
```
#### Constants
If you require a constant, you must prefix the variables type with `const`. In addition, the identifier of the variable must be in upper case and have an `_` between words.
I also recommend using macros instead of constants if you use them in multiple places.
```c
/* okay */
const float THREE_HALVES = 1.5f;
#define THREE_HALVES 1.5f

/* not okay */
float constant_val = 3.5f;
```
---
### Structures and Unions
When defining structures and unions, always use `typedef` before your structure definition. When naming your structures and unions, use camel case and prefix the name of the structure with the project that structure is a part of.

#### Members
- Must be in byte size order (saves on structure size)
- Should not be prefixed with `m_`
- Do not have to follow regular variable naming conventions, just have to be in snake case
- Members of the same type must be defined on seperate lines
```c
/* okay */
typedef struct {
    char smallest;
    char second_smallest;
    int third_smallest;
    long largest;
} Project_Struct;

/* not okay */
union some_union {
    int val1;
    char VAL_2;
    short _v3;
};
```
---
### Enums
Enums follow the exact same naming conventions as `struct` and `union`, but each member should be defined in upper case.

```c
/* okay */
typedef enum {
    VAL_1,
    VAL_2,
    VAL_3
} Project_Enum;

/* not okay */
typedef enum
{
    v1,
    V_2,
    _v3
} Enum;
```
---
### Comments
Comments should always be written in the multiline style unless they are short enough to fit in one line
#### When annotating functions

If you have a function prototype, you should annotate what the function does and why it is there, along with a list of the arguments and their purposes.

Here is a list of directives and what they are used for:
- `@description` the description of the function
- `@argument` an argument provided to the function
- `@returns` what the function returns and what it can be used for*

This step can be foregone if the function is obvious in what it does, for example the function in the example below would not necessarily need to be annotated since it is relatively self descriptive.

```c
/*
 * @description:
 * adds several numbers together
 * 
 * @argument: x first number provided to the function
 * @argument: y number to add to the first number
 *
 * @returns: the sum of the two numbers
 */
int add(int x, int y) {
    return x + y;
}
```
It is important to not comment *what* your code is doing. It is instead important to comment *why* the code does what it is doing.
