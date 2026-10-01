# c_unnit

C-unnit is a testing library for C.

It currently provides two testing approaches:
- Unit testing with simple assertions and test lifecycle functions.
- Property-based testing with generated inputs and repeated property checks.

## Building

### Examples
Build all examples with:
```
make exemples
```
The executables are generated in the `out/` directory.
To remove the generated files:
```
make clean
```

### Using C-Unnint in a test file

To use C-Unnit in your own test file, include the header:

```c
#include "c_unnit.h"
```

Then compile your test file together with the C-Unnit implementation:

```
gcc -Iinclude -o my_tests my_tests.c src/c_unnit.c -lm
```

You can then run your tests with:

```
./my_tests
```

For property-based testing, also include `c_unnit_ppt.h` and compile `c_unnit_ppt.c`:

```
gcc -Iinclude -o my_tests my_tests.c src/c_unnit.c src/c_unnit_ppt.c -lm
```

## Unit testing

A test is a function taking a `void *` parameter and returning and `int`.
```c
int my_test(void *params) {
    ASSERT_EQUALS(2 + 3 == 5);

    return 0;
}
```

A return value of `0`indicates succes. A Non-zero return value indicates failure.

### Add tests

Tests are added to a TestList, they can be registered using `ADD_TEST` macro:

```c
struct TestList *tests = create_test_list();
ADD_TEST(tests, my_test);
run_tests(tests, NULL, NULL);
free_test_list(tests);
```

The test name is automatically obtained from the function name.

### Assertions

C-Unnit currently provides the following assertions:

| Assertion                         | Description                                   | Example                                         |
| --------------------------------- | --------------------------------------------- | ----------------------------------------------- |
| `ASSERT_TRUE(expression)`         | Checks that an expression evaluates to true.  | `ASSERT_TRUE(5 == 2 + 3);`                      |
| `ASSERT_FALSE(expression)`        | Checks that an expression evaluates to false. | `ASSERT_FALSE(5 == 3 + 3);`                     |
| `ASSERT_NULL(pointer)`            | Checks that a pointer is `NULL`.              | `int *ptr = NULL;`<br>`ASSERT_NULL(ptr);`       |
| `ASSERT_NOT_NULL(pointer)`        | Checks that a pointer is not `NULL`.          | `int value = 42;`<br>`ASSERT_NOT_NULL(&value);` |
| `ASSERT_EQUALS(actual, expected)` | Checks that two values are equal.             | `int x = 5;`<br>`ASSERT_EQUALS(x, 2 + 3);`      |

When an assertion fails, C-Unnit reports the assertion, the source file and the line where the assertion failed.

For example:
```
[ASSERT_EQUALS] expected {x} == {2 + 3} but it was not (example.c:15)
```

### Test lifecycle

C-Unnit supports optional `beforeEach`and `afterEach` functions. Which are executed for every tests in the `TestList`.

A beforeEach function can create parameters that are passed to the test:
```c
void *before_each() { 
    int *value = malloc(sizeof(int)); 
    *value = 42; 
    return value; 
}
```

The test receives these parameters through its argument:
```c
int test_value(void *params)
{
    int *value = params;

    ASSERT_EQUALS(*value, 42);

    return 0;
}
```

The afterEach function can then release the allocated resources:
```c
void after_each(void *params)
{
    free(params);
}
```

## Property-based testing

C-Unnit provides a not finished simple property-based testing API.

Instead of manually specifying test cases, a property is executed against automatically generated inputs.

```c
int property(int x) { 
    ASSERT_EQUALS(add_zero(x), x); 
    return 0; 
}
```

A generator is responsible for producing the input:
```c
int generate_int();
```

The property and generator can then be registered together:

```c
struct TestPPTList *list = create_property_list();

append_property(
    list,
    property,
    "x + 0 == x",
    generate_int
);

run_properties(list);

free_property_list(list);
```

The library generates values and executes the property repeatedly.