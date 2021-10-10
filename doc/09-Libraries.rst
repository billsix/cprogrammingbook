.. _libraries:

Libraries
=========

Introduction
------------

There is no doubt that the C89 Standard Committee's decision
to define a set of library routines will prove
to be a huge benefit to users of C.
Previously there were no standard, accepted, definitions of library
routines to provide support for the language. As a
result, portability suffered seriously.

The library routines do not
have to be present; they will only be present
in a hosted environment—typically the case for applications programmers.
Writers of embedded systems and the writers of the
hosted environment libraries will not have the libraries present.
They are using ‘raw’ C, in a freestanding environment,
and this chapter will not be of much interest
to them.

The descriptions (except for this introduction) are
not meant to be read as a whole chapter,
but as individual pieces. The material included here is
meant more for information and convenient reference than as
a full tutorial introduction. It would take a full
book by itself to do real justice to the libraries.

Headers and standard types
~~~~~~~~~~~~~~~~~~~~~~~~~~

A number of types and macros are used widely
by the library functions. Where necessary, they are defined
in the appropriate #include file for that function. The
header will also declare appropriate types and prototypes for
the library functions. Some important points should be noted here:

    All external identifiers and macro names declared in any
    of the library headers are reserved. They must not
    be used, or redefined, for any other purpose. In
    some cases they may be ‘magic’—their names may be
    known to the compiler and cause it to use special methods to implement them.

    All identifiers that begin with an underscore are reserved.

    Headers may be included in any order, and more
    than once, but must be included outside of any
    external declaration or definition and before any use of
    the functions or macros defined inside them.

    Giving a ‘bad value’ to a function—say a null
    pointer, or a value outside the range of values
    expected by the function—results in undefined behavior unless otherwise
    stated.

The C89 Standard isn't quite as restrictive about identifiers as
the list above is, but it's a brave move
to make use of the loopholes. Play safe instead.

The Standard headers are:

    <assert.h>   <locale.h>   <stddef.h>
    <ctype.h>    <math.h>     <stdio.h>
    <errno.h>    <setjmp.h>   <stdlib.h>
    <float.h>    <signal.h>   <string.h>
    <limits.h>   <stdarg.h>   <time.h>

A last general point is that many of the
library routines may be implemented as macros, provided that
there will be no problems to do with side-effects
(as :ref:`preprocessor` describes). The C89 Standard guarantees that, if
a function is normally implemented as a macro, there
will also be a true function provided to do
the same job. To use the real function, either
undefine the macro name with #undef, or enclose its
name in parentheses, which ensures that it won't be
treated as a macro:

.. code-block:: C

    some function("Might be a macro\n");
    (some function)("Can't be a macro\n");

Character set and cultural dependencies
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The Committee has introduced features that attempt to cater
for the use of C in environments which are
not based on the character set of US ASCII
and where there are cultural dependencies such as the
use of comma or full stop to indicate the
decimal point. Facilities have been provided (see Section 9.4)
for setting a program's idea of its locale, which
is used to control the behavior of the library
functions.

Providing full support for different native languages and customs
is a difficult and poorly understood task; the facilities
provided by the C library are only a first
step on the road to a full solution.

In several places the ‘C locale’ is referred to.
This is the only locale defined by the C89 Standard
and effectively provides support for the way that pre-C89
worked. Other locale settings may provide different behavior
in implementation-defined ways.

The <stddef.h> Header
~~~~~~~~~~~~~~~~~~~~~

There are a small number of types and macros,
found in <stddef.h>, which are widely used in other
headers. They are described in the following paragraphs.

Subtracting one pointer from another gives a result whose
type differs between different implementations. To allow safe use
of the difference, the type is defined in <stddef.h>
to be ptrdiff_t. Similarly, you can use size_t to
store the result of sizeof.

For reasons which still escape us, there is an
‘implementation defined null pointer constant’ defined in <stddef.h> called
NULL. Since the language explicitly defines the integer constant
0 to be the value which can be assigned
to, and compared with, a null pointer, this would
seem to be unnecessary. However, it is very common
practice among experienced C programmers to write this sort
of thing:

.. code-block:: C

    #include <stdio.h>
    #include <stddef.h>
    FILE *fp;

    if((fp = fopen("somefile", "r")) != NULL){
            /* and so on */

There is also a macro called offsetof which can be
used to find the offset, in bytes, of a structure
member. The offset is the distance between the member and
the start of the structure. It would be used like this:

.. literalinclude:: ../src/example9.1/src/example9.1.c
   :language: c
   :linenos:

Example 9.1

The expression s_tr.c must be capable of evaluation as an
address constant (see :ref:`structs`). If the member whose offset
you want is a bit-field, then you're out of luck;
offsetof has undefined behavior in that case.

Note carefully the
way that a size_t has to be cast to the
longest possible unsigned type to ensure that not only is
the argument to printf of the type that it expects
(%luis the format string for unsigned long), but also no
precision is lost. This is all because the type of
size_t is not known to the programmer.

The last item
declared in <stddef.h> is wchar_t, an integral type large enough
to hold a wide character from any supported extended character
sets.

The <errno.h> Header
~~~~~~~~~~~~~~~~~~~~

This header defines errno along with the macros EDOM and
ERANGE, which expand to nonzero integral constant expressions; their form
is additionally guaranteed to be acceptable to #if directives. The
latter two are used by the mathematical functions to report
which kind of errors they encountered and are more fully
described later.

errno is provided to tell you when library
functions have detected an error. It is not necessarily, as
it used to be, an external variable, but is now
a modifiable lvalue that has type int. It is set
to zero at program start-up, but from then on never
reset unless explicitly assigned to; in particular, the library routines
never reset it. If an error occurs in a library
routine, errno is set to a particular value to indicate
what went wrong, and the routine returns a value (often -1)
to indicate that it failed. The usual use is like this:

.. code-block:: C

    #include <stdio.h>
    #include <stddef.h>
    #include <errno.h>

    errno = 0;
    if(some_library_function(arguments) < 0){
            /* error processing code... */
            /* may use value of errno directly */

The implementation of errno is not known to the programmer,
so don't try to do anything other than reset it
or inspect its value. It isn't guaranteed to have an
address, for example.

What's more, you should only check errno if the particular
library function in use documents its effect on errno.

Other
library functions are free to set it to arbitrary values
after a call unless their description explicitly states what they
do with it.

Diagnostics
-----------

While you are debugging programs, it is often useful to
check that the value of an expression is the one
that you expected. The assert function provides such a diagnostic
aid.

In order to use assert you must first include
the header file <assert.h>. The function is defined as

.. code-block:: C

    #include <assert.h>

    void assert(int expression)

If the expression evaluates to zero (i.e. false) then assert
will write a message about the failing expression, including the
name of the source file, the line at which the
assertion was made and the expression itself. After this, the
abort function is called, which will halt the program.

.. code-block:: C

    assert(1 == 2);

    /* Might result in */

    Assertion failed: 1 == 2, file silly.c, line 15

Assert is actually defined as a macro, not as a
real function. In order to disable assertions when a program
is found to work satisfactorily, defining the name NDEBUG before
including <assert.h> will disable assertions totally. You should beware of
side effects that the expression may have: when assertions are
turned off with NDEBUG, the expression is not evaluated. Thus
the following example will behave unexpectedly when debugging is turned
off with the #define NDEBUG.

.. literalinclude:: ../src/example9.2/src/example9.2.c
   :language: c
   :linenos:

Example 9.2

Note that assert returns no value.

Character handling
------------------

There are a variety of functions provided for testing and
mapping characters. The testing functions, which are described first, allow
you to test if a character is of a particular
type, such as alphabetic, upper or lower case, numeric, a
control character, a punctuation mark, printable or not and so
on. The character testing functions return an integer, either zero
if the character supplied is not of the category specified,
or non-zero if it was. The functions all take an
integer argument, which should either be an int, the value
of which should be representable as unsigned char, or the
integer constant EOF, as returned from functions such as getchar().
The behavior is undefined if it is not.

These functions depend on the program's locale setting.

A printing character is a member of an implementation defined
character set. Each printing character occupies one printing position. A
control character is a member of an implementation defined character
set, each of which is not a printing character. If
the 7-bit ASCII character set is used, the printing characters
are those that lie between space (0x20) and tilde (0x7e),
the control characters are those between NUL (0x0) and US
(0x1f), and the character DEL (0x7f).

The following is a summary of all the character testing
functions. The header <ctype.h> must be included before any of
them is used.

    isalnum(int c)

        True if c is alphabetic or a digit; specifically (isalpha(c)||isdigit(c)).

    isalpha(int c)

        True if (isupper(c)||islower(c)).

Also true for an implementation-defined set of characters which do
not return true results from any of iscntrl, isdigit, ispunct
or isspace. In the C locale, this extra set of characters is empty.

    iscntrl(int c)

        True if c is a control character.

    isdigit(int c)

        True if c is a decimal digit.

    isgraph(int c)

        True if c is any printing character except space.

    islower(int c)

        True if c is a lower case alphabetic
        letter. Also true for an implementation defined set
        of characters which do not return true results
        from any of iscntrl, isdigit, ispunct or isspace.
        In the C locale, this extra set of characters is empty.

    isprint(int c)

        True if c is a printing character (including
        space).

    ispunct(int c)

        True if c is any printing character that
        is neither a space nor a character which
        would return true from isalnum.

    isspace(int c)

        True if c is either a white space
        character (one of ' ' '\f' '\n' '\r'
        '\t' '\v') or, in other than the C
        locale, characters which would not return true from
        isalnum

    isupper(int c)


        True if c is an upper case alphabetic character.

        Also true for an implementation-defined set of characters
        which do not return true results from any
        of iscntrl, isdigit, ispunct or isspace. In the
        C locale, this extra set of characters is empty.

    isxdigit(int c)

        True if c is a valid hexadecimal digit.



Two additional functions map characters from one set into
another. The function tolower will, if given a upper
case character as its argument, return the lower case
equivalent. For example,

.. code-block:: C

    tolower('A') == 'a'

If tolower is given any character other than an
upper case letter, it will return that character.

The converse function toupper maps lower case alphabetic letters
onto their upper case equivalent.

For each, the conversion is only performed if there
is a corresponding character in the alternate case. In
some locales, not all upper case characters have lower
case equivalents, and vice versa.

Localization
------------

This is where the program's idea of its current
locale can be controlled. The header file <locale.h> declares
the setlocale and localeconv functions and a number of macros:

    LC_ALL

    LC_COLLATE

    LC_CTYPE

    LC_MONETARY

    LC_NUMERIC

    LC_TIME


all of which expand to integral constant expressions and are
used as values of the category argument to setlocale (other
names may also be defined: they will all start with
LC_X where X is an upper case letter), and the type

.. code-block:: C

    struct lconv

which is used for storing information about the formatting of
numeric values. For members of type char, CHAR_MAX is used
to indicate that the value is not available in the
current locale.

lconv contains at least the following members:

    char \*decimal_point

        The character used for the decimal point in
        formatted non-monetary values. "." in the C locale.

    char \*thousands_sep

        The character used for separating groups of digits
        to the left of the decimal point in
        formatted non-monetary values. "" in the C locale.

    char \*grouping

        Defines the number of digits in each group
        when formatting non-monetary values. The elements are interpreted
        as follows: A value of CHAR_MAX indicates that
        no further grouping is to be performed; 0
        indicates that the previous element should be repeated
        for the remaining digits; if any other character
        is used, its integer value represents the number
        of digits that comprise the current group (the
        next character in the sequence is interpreted before
        grouping). "" in the C locale. As an
        example, "\3" specifies that digits should be grouped
        in threes; the terminating null in the string
        signifies that the \3 repeats.

    char \*int_curr_symbol

        The first three characters are used to hold
        the alphabetic international currency symbol for the current
        locale, the fourth character is used to separate
        the international currency symbol from the monetary quantity.
        "" in the C locale.

    char \*currency_symbol

        The currency symbol for the current locale. ""
        in the C locale.

    char \*mon_decimal_point

        The character used as the decimal point when
        formatting monetary values. "" in the C locale.

    char \*mon_thousands_sep

        The digit group separator for formatted monetary values.
        "" in the C locale.

    char \*mon_grouping

        Defines the number of digits in each group
        when formatting monetary values. Its elements are interpreted
        as those for grouping. "" in the C locale.

    char \*positive_sign

        The string used to signify a non-negative monetary
        value. "" in the C locale.

    char \*negative_sign

        The string used to signify a negative monetary
        value. "" in the C locale.

    char int_frac_digits

        The number of digits to be displayed after
        the decimal point in an internationally formatted monetary
        value. CHAR_MAX in the C locale.

    char frac_digits

        The number of digits to be displayed after
        the decimal point in a non-internationally formatted monetary
        value. CHAR_MAX in the C locale.

    char p_cs_precedes

        A value of 1 indicates that the currency_symbol
        should precede the value when formatting a non-negative
        monetary quantity; a value of 0 indicates that
        it should follow. CHAR_MAX in the C locale.

    char p_sep_by_space

        A value of 1 indicates that the currency
        symbol is separated by a space from the
        value when formatting a non-negative monetary quantity; 0
        indicates no space. CHAR_MAX in the C locale.

    char n_cs_precedes

        As p_cs_precedes for negative monetary values. CHAR_MAX in the C locale.

    char n_sep_by_space

        As p_sep_by_space for negative monetary values. CHAR_MAX in the C locale.

    char p_sign_posn


        Indicates the position of the positive_sign for a
        non-negative formatted monetary value according to the following:

            parentheses surround quantity and currency_symbol

            the string precedes the quantity and currency_symbol

            the string follows the quantity and currency_symbol

            the string precedes the currency_symbol

            the string follows the currency_symbol


        CHAR_MAX in the C locale.

    char n_sign_posn

        As p_sign_posn for negative monetary values. CHAR_MAX in the C locale.


The setlocale function
~~~~~~~~~~~~~~~~~~~~~~

#include <locale.h>

.. code-block:: C

    char *setlocale(int category, const char *locale);

This function allows the program's idea of its locale
to be set. All or parts of the locale
can be set by providing values for category as follows:

    LC_ALL

        Set entire locale.

    LC_COLLATE

        Modify behavior of strcoll and strxfrm.

    LC_CTYPE

        Modify behavior of character-handling functions.

    LC_MONETARY

        Modify monetary formatting information returned by localeconv.

    LC_NUMERIC

        Modify decimal-point character for formatted I/O and string conversion routines.

    LC_TIME

        Modify behavior of strftime.

    The values for locale can be:
    "C"         Select the minimal environment for C translation
    ""  Select the implementation-defined ‘native environment’
    implementation defined      Select other environments

When the program starts, it has an environment as if

.. code-block:: C

    setlocale(LC_ALL, "C");

has been executed.

The current string associated with a given category can be
queried by passing a null pointer as the value for
locale; if the selection can be performed, the string associated
with the specified category for the new locale is returned.
This string is such that if it is used in
a subsequent call to setlocale, along with its associated category,
that part of the program's locale will be restored. If
the selection cannot be performed, a null pointer is returned
and the locale is not changed.

The localeconv function
~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: C

    #include <locale.h>

    struct lconv *localeconv(void);

The function returns a pointer to a structure of type
struct lconv, set according to the current locale, which may
be overwritten by subsequent calls to localeconv or setlocale. The
structure must not be modified in any other way.

For
example, if in the current locale monetary values should be
represented as

IR£1,234.56     positive format
(IR£1,234.56)   negative format
IRP 1,234.56    international format

then the monetary members of lconv would have the values:
int_curr_symbol         "IRP "
currency_symbol         "IR£"
mon_decimal_point       "."
mon_thousands_sep       ","
mon_grouping    "\3"
positive_sign    ""
negative_sign   ""
int_frac_digits         2
frac_digits     2
p_cs_precedes   1
p_sep_by_space  0
n_cs_precedes   1
n_sep_by_space  0
p_sign_posn     CHAR_MAX
n_sign_posn     0

Limits
------

Two header files <float.h> and <limits.h> define several implementation specific
limits.

Limits.h
~~~~~~~~

Table 9.1 gives the names declared, the allowable values, and
a comment on what they mean. For example, the description
of SHRT_MIN shows that in a given implementation the value
must be less than or equal to -32767: this means
that for maximum portability a program cannot rely on short
variables being able to hold values more negative than -32767.
Implementations may choose to support values which are more negative
but must provide support for at least -32767.


+-------------------------+-------------------------+-----------------------------------------------+
| Name                    | Allowable value         | Comment                                       |
+=========================+=========================+===============================================+
| CHAR_BIT                |(>=8)                    |bits in a char                                 |
+-------------------------+-------------------------+-----------------------------------------------+
| CHAR_MAX                |see note                 |max value of a char                            |
+-------------------------+-------------------------+-----------------------------------------------+
| CHAR_MIN                |see note                 |min value of a char                            |
+-------------------------+-------------------------+-----------------------------------------------+
| INT_MAX                 |(>=+32767)               |max value of an int                            |
+-------------------------+-------------------------+-----------------------------------------------+
| INT_MIN                 |(<=-32767)               |min value of an int                            |
+-------------------------+-------------------------+-----------------------------------------------+
| LONG_MAX                |(>=+2147483647)          |max value of a long                            |
+-------------------------+-------------------------+-----------------------------------------------+
| LONG_MIN                |(<=-2147483647)          |min value of a long                            |
+-------------------------+-------------------------+-----------------------------------------------+
| MB_LEN_MAX              |(>=1)                    |max number of bytes in a multi-byte character  |
+-------------------------+-------------------------+-----------------------------------------------+
| SCHAR_MAX               |(>=+127)                 |max value of a signed char                     |
+-------------------------+-------------------------+-----------------------------------------------+
| SCHAR_MIN               |(<=-127)                 |min value of a signed char                     |
+-------------------------+-------------------------+-----------------------------------------------+
| SHRT_MAX                |(>=+32767)               |max value of a short                           |
+-------------------------+-------------------------+-----------------------------------------------+
| SHRT_MIN                |(<=-32767)               |min value of a short                           |
+-------------------------+-------------------------+-----------------------------------------------+
| UCHAR MAX               |(>=255U)                 |max value of an unsigned char                  |
+-------------------------+-------------------------+-----------------------------------------------+
| UINT_MAX                |(>=65535U)               |max value of an unsigned int                   |
+-------------------------+-------------------------+-----------------------------------------------+
| ULONG_MAX               |(>=4294967295U)          |max value of an unsigned long                  |
+-------------------------+-------------------------+-----------------------------------------------+
| USHRT_MAX               |(>=65535U)               |max value of an unsigned short                 |
+-------------------------+-------------------------+-----------------------------------------------+





Note: if the implementation treats chars as signed, then the values of CHAR_MAX and CHAR_MIN are the same as the equivalent SCHAR versions. If not, then the value of CHAR_MIN is zero and the value of CHAR_MAX is equal to the value of UCHAR_MAX.

Table 9.1. <limits.h>

Float.h
~~~~~~~

For floating point numbers, the file <float.h> contains a similar
set of minimum values. (It is assumed that where no
minimum value is specified, there is either no minimum, or
the value depends on another value.)

Name    Allowable value         Comment
FLT_RADIX       (>=2)    the radix of exponent representation
DBL_DIG         (>=10)   the number of digits of precision in a double
DBL_EPSILON     (<=1E-9)         minimum positive number such that 1.0 + x != 1.0
DBL_MANT_DIG    (—)     the number of base FLT_RADIX digits in the mantissa part of a double
DBL_MAX         (>=1E+37)        max value of a double
DBL_MAX_10_EXP  (>=+37)  max value of exponent (base 10) of a double
DBL_MAX_EXP     (—)     max value of exponent (base FLT_RADIX)) of a double
DBL_MIN         (<=1E-37)        min value of a double
DBL_MIN_10_EXP  (<=37)   minimum value of exponent (base 10) of a double
DBL_MIN_EXP     (—)     min value of exponent part of a double (base FLT_RADIX)
FLT_DIG         (>=6)    the number of digits of precision in a float
FLT_EPSILON     (<=1E-5)         minimum positive number such that 1.0 + x != 1.0
FLT_MANT_DIG    (—)     the number of base FLT_RADIX digits in the mantissa of a float
FLT_MAX         (>=1E+37)        max value of a float
FLT_MAX_10_EXP  (>=+37)  max value (base 10) of exponent part of a float
FLT_MAX_EXP     (—)     max value (base FLT_RADIX) of exponent part of a float
FLT_MIN         (<=1E-37)        min value of a float
FLT_MIN_10_EXP  (<=-37)  min value (base 10) of exponent part of a float
FLT_MIN_EXP     (—)     min value (base FLT_RADIX) of exponent part of a float
FLT_ROUNDS      (0)

affects rounding of floating point addition:

    -1

        indeterminate

    0

        towards zero

    1

        to nearest

    2

        towards +infinity

    3

        towards -infinity


any other value is implementation defined.




LDBL_DIG        (>=10)   the number of digits of precision in a long double
LDBL_EPSILON    (<=1E-9)         minimum positive number such that 1.0 + x != 1.0
LDBL_MANT_DIG   (—)     the number of base FLT_RADIX digits in the mantissa part of a long double
LDBL_MAX        (>=1E+37)        max value of a long double
LDBL_MAX_10_EXP         (>=+37)  max value of exponent (base 10) of a long double
LDBL_MAX_EXP    (—)     max value of exponent (base FLT_RADIX) of a long double
LDBL_MIN        (<=1E-37)        minimum value of a long double
LDBL_MIN_10_EXP         (<=-37)  min value of exponent part (base 10) of a long double
LDBL_MIN_EXP    (—)     min value of exponent part of a long double (base FLT_RADIX)

Table 9.2. <float.h>

Mathematical functions
----------------------

If you are writing mathematical programs, involving floating point
calculations and so on, then you will undoubtedly require
access to the mathematics library. This set of functions
all take double arguments, and return a double result.
The functions and associated macros are defined in the
include file <math.h>.

The macro HUGE_VAL is defined, which
expands to a positive double expression, which is not
necessarily representable as a float.

For all the functions,
a domain error occurs if an input argument is
outside the domain over which the function is defined.
An example might be attempting to take the square
root of a negative number. If this occurs, errno
is set to the constant EDOM, and the function
returns an implementation defined value.

If the result of
the function cannot be represented as a double value
then a range error occurs. If the magnitude of
the result is too large, the functions return ±HUGE_VAL
(the sign will be correct) and errno is set
to ERANGE. If the result is too small, 0.0
is returned and the value of errno is implementation
defined.

The following list briefly describes each of the
functions available:

    double acos(double x);

        Principal value of the arc
        cosine of x in the
        range 0–pi radians.

        Errors: EDOM if x is
        not in the range -1-1.

    double asin(double x);

        Principal value of the arc
        sine of x in the range -pi/2–+pi/2 radians.

        Errors: EDOM if x is not in the range -1-1.

    double atan(double x);

        Principal value of the arc
        tangent of x in the range -pi/2–+pi/2 radians.

    double atan2(double y, double x);

        Principal value of the arc
        tangent of y/x in the
        range -pi–+pi radians, using the
        signs of both arguments to
        determine the quadrant of the
        return value.

        Errors: EDOM may occur if both x and y are zero.

    double cos(double x);

        Cosine of x (x measured in radians).

    double sin(double x);

        Sine of x (x measured in radians).

    double tan(double x);

        Tangent of x (x measured
        in radians). When a range
        error occurs, the sign of
        the resulting HUGE_VAL is not
        guaranteed to be correct.

    double cosh(double x);

        Hyperbolic cosine of x.

        Errors: ERANGE occurs if the
        magnitude of x is too large.

    double sinh(double x);

        Hyperbolic sine of x.

        Errors: ERANGE occurs if the
        magnitude of x is too large.

    double tanh(double x);

        Hyperbolic tangent of x.

    double exp(double x);

        Exponential function of x. Errors:
        ERANGE occurs if the magnitude
        of x is too large.

    double frexp(double value, int \*exp);

        Break a floating point number
        into a normalized fraction and
        an integral power of two.
        This integer is stored in
        the object pointed to by exp.

    double ldexp(double x, int exp);

        Multiply x by 2 to the power exp

        Errors: ERANGE may occur.

    double log(double x);

        Natural logarithm of x.

        Errors: EDOM occurs if x
        is negative. ERANGE may occur if x is zero.

    double log10(double x);

        Base-ten logarithm of x.

        Errors: EDOM occurs if x is negative. ERANGE may occur if x is zero.

    double modf(double value, double \*iptr);

        Break the argument value into
        integral and fractional parts, each
        of which has the same
        sign as the argument. It
        stores the integral part as
        a double in the object
        pointed to by iptr, and
        returns the fractional part.

    double pow(double x, double y);

        Compute x to the power y.

        Errors: EDOM occurs if x
        < 0 and y not
        integral, or if the result
        cannot be represented if x
        is 0, and y <=
        0. ERANGE may also occur.

    double sqrt(double x);

        Compute the square root of x.

        Errors: EDOM occurs if x is negative.

    double ceil(double x);

        Smallest integer not less than x.

    double fabs(double x);

        Absolute value of x.

    double floor(double x);

        Largest integer not greater than x.

    double fmod(double x, double y);

        Floating point remainder of x/y.

        Errors: If y is zero,
        it is implementation defined whether
        fmod returns zero or a
        domain error occurs.



Non-local jumps
---------------

Provision is made for you to perform what is, in
effect, a goto from one function to another. It isn't
possible to do this by means of a goto and
a label, since labels have only function scope. However, the
macro setjmp and function longjmp provide an alternative, known as
a non-local goto, or a non-local jump.

The file <setjmp.h>
declares something called a jmp_buf, which is used by the
cooperating macro and function to store the information necessary to
make the jump. The declarations are as follows:

.. code-block:: C

    #include <setjmp.h>

    int setjmp(jmp_buf env);
    void longjmp(jmp_buf env, int val);

The setjmp macro is used to initialize the jmp_buf and
returns zero on its initial call. The bizarre thing is
that it returns again, later, with a non-zero value, when
the corresponding longjmp call is made! The non-zero value is
whatever value was supplied to the call of longjmp. This
is best explained by way of an example:

.. literalinclude:: ../src/example9.3/src/example9.3.c
   :language: c
   :linenos:



Example 9.3

The val argument to longjmp is the value seen in
the second and subsequent ‘returns’ from setjmp. It should normally
be something other than 0; if you attempt to return
0 via longjmp, it will be changed to 1. It
is therefore possible to tell whether the setjmp was called
directly, or whether it was reached by calling longjmp.

If
there has been no call to setjmp before calling longjmp,
the effect of longjmp is undefined, almost certainly causing the
program to crash. The longjmp function is never expected to
return, in the normal sense, to the instructions immediately following
the call. All accessible objects on ‘return’ from setjmp have
the values that they had when longjmp was called, except
for objects of automatic storage class that do not have
volatile type; if they have been changed between the setjmp
and longjmp calls, their values are indeterminate.

The longjmp function executes correctly in the contexts of interrupts,
signals and any of their associated functions. If longjmp is
invoked from a function called as a result of a
signal arriving while handling another signal, the behavior is undefined.


It's a serious error to longjmp to a function which
is no longer active (i.e. it has already returned or
another longjump call has transferred to a setjmp occurring earlier
in a set of nested calls).

The C89 Standard insists that,
apart from appearing as the only expression in an expression
statement, setjmp may only be used as the entire controlling
expression in an if, switch, do, while, or for statement.
A slight extension to that rule is that as long
as it is the whole controlling expression (as above) the
setjmp call may be the subject of the ! operator,
or may be directly compared with an integral constant expression
using one of the relational or equality operators. No more
complex expressions may be employed. Examples are:

.. code-block:: C

    setjmp(place);                    /* expression statement */
    if(setjmp(place)) ...             /* whole controlling expression */
    if(!setjmp(place)) ...            /* whole controlling expression */
    if(setjmp(place) < 4) ...         /* whole controlling expression */
    if(setjmp(place)<;4 && 1!=2) ...  /* forbidden */

Signal handling
---------------

Two functions allow for asynchronous event handling to be
provided. A signal is a condition that may be
reported during program execution, and can be ignored, handled
specially, or, as is the default, used to terminate
the program. One function sends signals, another is used
to determine how a signal will be processed. Many
of the signals may be generated by the underlying
hardware or operating system as well as by means
of the signal-sending function raise.

The signals are defined
in the include file <signal.h>.

    SIGABRT

        Abnormal termination, such as instigated
        by the abort function. (Abort.)

    SIGFPE

        Erroneous arithmetic operation, such as
        divide by 0 or overflow.
        (Floating point exception.)

    SIGILL

        An ‘invalid object program’ has
        been detected. This usually means
        that there is an illegal
        instruction in the program. (Illegal instruction.)

    SIGINT

        Interactive attention signal; on interactive
        systems this is usually generated
        by typing some ‘break-in’ key at the terminal. (Interrupt.)

    SIGSEGV

        Invalid storage access; most frequently
        caused by attempting to store
        some value in an object
        pointed to by a bad pointer. (Segment violation.)

    SIGTERM

        Termination request made to the program. (Terminate.)


Some implementations may have additional signals available, over and
above this standard set. They will be given names
that start SIG, and will have unique values, apart
from the set above.

The function signal allows you
to specify the action taken on receipt of a
signal. Associated with each signal condition above, there is
a pointer to a function provided to handle this
signal. The signal function changes this pointer, and returns
the original value. Thus the function is defined as

.. code-block:: C

    #include <signal.h>
    void (*signal (int sig, void (*func)(int)))(int);

That is to say, signal is a function that
returns a pointer to another function. This second function
takes a single int argument and returns void. The
second argument to signal is similarly a pointer to
a function returning void which takes an int argument.

Two special values may be used as the func
argument (the signal-handling function), SIG_DFL, the initial, default, signal
handler; and SIG_IGN, which is used to ignore a
signal. The implementation sets the state of all signals
to one or other of these values at the
start of the program.

If the call to signal
succeeds, the previous value of func for the specified
signal is returned. Otherwise, SIG_ERR is returned and errno
is set.

When a signal event happens which is
not being ignored, if the associated func is a
pointer to a function, first the equivalent of signal(sig,
SIG_DFL) is executed. This resets the signal handler to
the default action, which is to terminate the program.
If the signal was SIGILL then this resetting is
implementation defined. Implementations may choose to ‘block’ further instances
of the signal instead of doing the resetting.

Next,
a call is made to the signal-handling function. If
that function returns normally, then under most circumstances the
program will resume at the point where the event
occurred. However, if the value of sig was SIGFPE
(a floating point exception), or any implementation defined computational
exception, then the behavior is undefined. The most usual
thing to do in the handler for SIGFPE is
to call one of the functions abort, exit, or longjmp.

The following program fragment shows the use of signal
to perform a tidy exit to a program on
receipt of the interrupt or ‘interactive attention’ signal.


.. literalinclude:: ../src/example9.4/src/example9.4.c
   :language: c
   :linenos:


Example 9.4

It is possible for a program to send signals
to itself by means of the raise function. This is defined as follows

.. code-block:: C

    include <signal.h>
    int raise (int sig);

The signal sig is sent to the program.

Raise returns zero if successful, non-zero otherwise. The abort
library function is essentially implementable as follows:

.. code-block:: C

    #include <signal.h>

    void
    abort(void) {
      raise(SIGABRT);
    }

If a signal occurs for any reason other than
calling abort or raise, the signal-handling function may only
call signal or assign a value to a volatile
static object of type sig_atomic_t. The type sig_atomic_t is
declared in <signal.h>. It is the only type of
object that can safely be modified as an atomic
entity, even in the presence of asynchronous interrupts. This
is a very onerous restriction imposed by the C89 Standard,
which, for example, invalidates the leave function in the
example program above; although the function would work correctly
in some environments, it does not follow the strict
rules of the C89 Standard.

Variable numbers of arguments
-----------------------------

It is often desirable to implement a function where the
number of arguments is not known, or is not constant,
when the function is written. Such a function is printf,
described in Section 9.11. The following example shows the declaration
of such a function.

.. literalinclude:: ../src/example9.5/src/example9.5.c
   :language: c
   :linenos:

Example 9.5

In order to access the arguments within the called function,
the functions declared in the <stdarg.h> header file must be
included. This introduces a new type, called a va_list, and
three functions that operate on objects of this type, called
va_start, va_arg, and va_end.

Before any attempt can be made to access a variable
argument list, va_start must be called. It is defined as


.. code-block:: C

    #include <stdarg.h>
    void va_start(va_list ap, parmN);

The va_start macro initializes ap for subsequent use by the
functions va_arg and va_end. The second argument to va_start, parmN
is the identifier naming the rightmost parameter in the variable
parameter list in the function definition (the one just before
the , ... ). The identifier parmN must not be
declared with register storage class or as a function or array type.

Once initialized, the arguments supplied can be accessed sequentially by
means of the va_arg macro. This is peculiar because the
type returned is determined by an argument to the macro.
Note that this is impossible to implement as a true
function, only as a macro. It is defined as

.. code-block:: C

    #include <stdarg.h>
    type va_arg(va_list ap, type);

Each call to this macro will extract the next argument
from the argument list as a value of the specified
type. The va_list argument must be the one initialized by
va_start. If the next argument is not of the specified
type, the behavior is undefined. Take care here to avoid
problems which could be caused by arithmetic conversions. Use of
char or short as the second argument to va_arg is
invariably an error: these types always promote up to one
of signed int or unsigned int, and float converts to
double. Note that it is implementation defined whether objects declared
to have the types char, unsigned char, unsigned short and
unsigned bit-fields will promote to unsigned int, rather complicating the
use of va_arg. This may be an area where some
unexpected subtleties arise; only time will tell.

The behavior is also undefined if va_arg is called when
there were no further arguments.

The type argument must be a type name which can
be converted into a pointer to such an object simply
by appending a \* to it (this is so the
macro can work). Simple types such as char are fine
(because char \* is a pointer to a character) but
array of char won't work (char [] does not turn
into ‘pointer to array of char’ by appending a \*).
Fortunately, arrays can easily be processed by remembering that an
array name used as an actual argument to a function
call is converted into a pointer. The correct type for
an argument of type ‘array of char’ would be char \*.

When all the arguments have been processed, the va_end function
should be called. This will prevent the va_list supplied from
being used any further. If va_end is not used, the behavior is undefined.

The entire argument list can be re-traversed by calling va_start
again, after calling va_end. The va_end function is declared as

.. code-block:: C

    #include <stdarg.h>
    void va_end(va list ap);

The following example shows the use of va_start, va_arg, and
va_end to implement a function that returns the biggest of its integer arguments.

.. literalinclude:: ../src/example9.6/src/example9.6.c
   :language: c
   :linenos:

Example 9.6


Input and output
----------------


Introduction
~~~~~~~~~~~~

One of the reasons that has prevented many programming languages
from becoming widely used for ‘real programming’ is their poor
support for I/O, a subject which has never seemed to
excite language designers. C has avoided this problem, oddly enough,
by having no I/O at all! The C language approach
has always been to do I/O using library functions, which
ensures that system designers can provide tailored I/O instead of
being forced to change the language itself.

As C has evolved, a library package known as the
‘Standard I/O Library’ or stdio, has evolved with it and
has proved to be both flexible and portable. This package
has now become part of the C89 Standard.

The old stdio package relied heavily on the UNIX model
of file access, in particular the assumption that there is
no distinction between unstructured binary files and files containing readable
text. Many operating systems do maintain a distinction between the
two, and to ensure that C programs can be written
portably to run on both types of file model, the
stdio package has been modified. There are changes in this
area which affect many existing programs, although strenuous efforts were
taken to limit the amount of damage.

pre-C89 programs should still be able work unmodified in a UNIX environment.

The I/O model
~~~~~~~~~~~~~

The I/O model does not distinguish between the types of
physical devices supporting the I/O. Each source or sink of
data (file) is treated in the same way, and is
viewed as a stream of bytes. Since the smallest object
that can be represented in C is the character, access
to a file is permitted at any character boundary. Any
number of characters can be read or written from a
movable point, known as the file position indicator. The characters
will be read, or written, in sequence from this point,
and the position indicator moved accordingly. The position indicator is
initially set to the beginning of a file when it
is opened, but can also be moved by means of
positioning requests. (Where random access is not possible, the file
position indicator is ignored.) Opening a file in append mode
has an implementation defined effect on the stream's file position
indicator.

The overall effect is to provide sequential reads or writes
unless the stream was opened in append mode, or the
file position indicator is explicitly moved.

There are two types of file, text files and binary
files, which, within a program, are manipulated as text streams
and binary streams once they have been opened for I/O.
The stdio package does not permit operations on the contents
of files ‘directly’, but only by viewing them as streams.

Text streams
^^^^^^^^^^^^

The C89 Standard specifies what is meant by the term text
stream, which essentially considers a file to contain lines of
text. A line is a sequence of zero or more
characters terminated by a newline character. It is quite possible
that the actual representation of lines in the external environment
is different from this and there may be transformations of
the data stream on the way in and out of
the program; a common requirement is to translate the ‘\n’
line-terminator into the sequence ‘\r\n’ on output, and do the
reverse on input. Other translations may also be necessary.

Data read in from a text stream is guaranteed to
compare equal to the data that was earlier written out
to the file if the data consists only of complete
lines of printable characters and the control characters horizontal-tab and
newline, no newline character is immediately preceded by space characters
and the last character is a newline.

It is guaranteed that, if the last character written to
a text file is a newline, it will read back as the same.

It is implementation defined whether the last line written to
a text file must terminate with a newline character; this
is because on some implementations text files and binary files are the same.

Some implementations may strip the leading space from lines consisting
only of a space followed by a newline, or strip
trailing spaces at the end of a line!

An implementation must support text files with lines containing at
least 254 characters, including the terminating newline.

Opening a text
stream in update mode may result in a binary stream
in some implementations.

Writing on a text stream may cause some implementations to
truncate the file at that point—any data beyond the last
byte of the current write being discarded.

Binary streams
^^^^^^^^^^^^^^

A binary stream is a sequence of characters that can
be used to record a program's internal data, such as
the contents of structures or arrays in binary form. Data
read in from a binary stream will always compare equal
to data written out earlier to the same stream, under
the same implementation. In some circumstances, an implementation-defined number of
NUL characters may be appended to a binary stream.

The
contents of binary files are exceedingly machine specific, and not,
in general, portable.

Other streams
^^^^^^^^^^^^^

Other stream types may
exist, but are implementation defined.

The stdio.h header file
~~~~~~~~~~~~~~~~~~~~~~~

To provide support for streams of the various kinds, a
number of functions and macros exist. The <stdio.h> header file
contains the various declarations necessary for the functions, together with
the following macro and type declarations:

    FILE

        The type of an object used to contain
        stream control information. Users of stdio never need
        to know the contents of these objects, but
        simply manipulate pointers to them. It is not
        safe to copy these objects within the program;
        sometimes their addresses may be ‘magic’.

    fpos_t

        A type of object that can be used
        to record unique values of a stream's file
        position indicator.

    _IOFBF _IOLBF _IONBF

        Values used to control the buffering of a
        stream in conjunction with the setvbuf function.

    BUFSIZ

        The size of the buffer used by the
        setbuf function. An integral constant expression whose value
        is at least 256.

    EOF

        A negative integral constant expression, indicating the end-of-file
        condition on a stream i.e. that there is no more input.

    FILENAME_MAX

        The maximum length which a filename can have,
        if there is a limit, or otherwise the
        recommended size of an array intended to hold a file name.

    FOPEN_MAX

        The minimum number of files that the implementation
        guarantees may be held open concurrently; at least
        eight are guaranteed. Note that three predefined streams
        exist and may need to be closed if
        a program needs to open more than five files explicitly.

    L_tmpnam

        The maximum length of the string generated by
        tmpnam; an integral constant expression.

    SEEK_CUR SEEK_END SEEK_SET

        Integral constant expressions used to control the actions
        of fseek.

    TMP_MAX

        The minimum number of unique filenames generated by
        tmpnam; an integral constant expression with a value
        of at least 25.

    stdin stdout stderr

        Predefined objects of type (FILE \*) referring to
        the standard input, output and error streams respectively.
        These streams are automatically open when a program starts execution.

Opening, closing and buffering of streams
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Opening
^^^^^^^

A stream is connected to a file by means of the
fopen, freopen or tmpfile functions. These functions will, if successful, return
a pointer to a FILE object.

Three streams are available without any special action; they are normally
all connected to the physical device associated with the executing program:
usually your terminal. They are referred to by the names stdin,
the standard input, stdout, the standard output, and stderr, the standard
error streams. Normal keyboard input is from stdin, normal terminal output
is to stdout, and error messages are directed to stderr. The
separation of error messages from normal output messages allows the stdout
stream to be connected to something other than the terminal device,
and still to have error messages appear on the screen in
front of you, rather than to be redirected to this file.
These files are only fully buffered if they do not refer
to interactive devices.

As mentioned earlier, the file position indicator may or may not
be movable, depending on the underlying device. It is not possible,
for example, to move the file position indicator on stdin if
that is connected to a terminal, as it usually is.

All non-temporary files must have a filename, which is a string.
The rules for what constitutes valid filenames are implementation defined. Whether
a file can be simultaneously open multiple times is also implementation
defined. Opening a new file may involve creating the file. Creating
an existing file causes its previous contents to be discarded.

Closing
^^^^^^^

Files are closed by explicitly calling fclose, exit or by returning
from main. Any buffered data is flushed. If a program stops
for some other reason, the status of files which it had open is undefined.

Buffering
^^^^^^^^^

There are three types of buffering:

    Unbuffered

        Minimum internal storage is used by stdio in
        an attempt to send or receive data as soon as possible.

    Line buffered

        Characters are processed on a line-by-line basis. This
        is commonly used in interactive environments, and internal
        buffers are flushed only when full or when a newline is processed.

    Fully buffered

        Internal buffers are only flushed when full.


The buffering associated with a stream can always
be flushed by using fflush explicitly. Support for
the various types of buffering is implementation defined,
and can be controlled within these limits using
setbuf and setvbuf.

Direct file manipulation
~~~~~~~~~~~~~~~~~~~~~~~~

A number of functions exist to operate on files directly.

.. code-block:: C

    #include <stdio.h>

    int remove(const char *filename);
    int rename(const char *old, const char *new);
    char *tmpnam(char *s);
    FILE *tmpfile(void);

Description:

    remove

        Causes a file to be removed. Subsequent
        attempts to open the file will fail,
        unless it is first created again. If
        the file is already open, the operation
        of remove is implementation defined. The return
        value is zero for success, any other
        value for failure.

    rename

        Changes the name of the file identified
        by old to new. Subsequent attempts to
        open the original name will fail, unless
        another file is created with the old
        name. As with remove, rename returns zero
        for a successful operation, any other value
        indicating a failure.

        If a file with the new name
        exists prior to calling rename, the behavior
        is implementation defined.

        If rename fails for any reason, the
        original file is unaffected.

    tmpnam

        Generates a string that may be used as
        a filename and is guaranteed to be different
        from any existing filename. It may be called
        repeatedly, each time generating a new name. The
        constant TMP_MAX is used to specify how many
        times tmpnam may be called before it can
        no longer find a unique name. TMP_MAX will
        be at least 25. If tmpnam is called
        more than this number of times, its behavior
        is undefined by the C89 Standard, but many implementations
        offer no practical limit.

        If the argument s is set to NULL,
        then tmpnam uses an internal buffer to build
        the name, and returns a pointer to that.
        Subsequent calls may alter the same internal buffer.
        The argument may instead point to an array
        of at least L_tmpnam characters, in which case
        the name will be filled into the supplied
        buffer. Such a filename may then be created,
        and used as a temporary file. Since the
        name is generated by the function, it is
        unlikely to be very useful in any other
        context. Temporary files of this nature are not
        removed, except by direct calls to the remove
        function. They are most often used to pass
        temporary data between two separate programs.

   tmpfile
        Creates a temporary binary file, opened for update,
        and returns a pointer to the stream of
        that file. The file will be removed when
        the stream is closed. If no file could
        be opened, tmpfile returns a null pointer.

Opening named files
~~~~~~~~~~~~~~~~~~~

Named files are opened by a call to
the fopen function, whose declaration is this:

.. code-block:: C

    #include <stdio.h>
    FILE *fopen(const char *pathname, const char *mode);

The pathname argument is the name of the
file to open, such as that returned from
tmpnam, or some program-specific filename.

Files can be opened in a variety of
modes, such as read mode for reading data,
write mode for writing data, and so on.

Note that if you only want to write
data to a file, fopen will create the
file if it does not already exist, or
truncate it to zero length (losing its previous
contents) if it did exist.

The C89 Standard list of modes is shown in
Table 9.3, although implementations may permit extra modes
by appending extra characters at the end of
the modes.

+-------------+-------------+-----------------+-----------------+-----------------+-----------------+
| Mode        |Type Of File | Read            | Write           | Create          | Truncate        |
+=============+=============+=================+=================+=================+=================+
| "r"         | text        | yes             | no              | no              | no              |
+-------------+-------------+-----------------+-----------------+-----------------+-----------------+
| "rb"        | binary      | yes             | no              | no              | no              |
+-------------+-------------+-----------------+-----------------+-----------------+-----------------+
| "r+"        | text        | yes             | yes             | no              | no              |
+-------------+-------------+-----------------+-----------------+-----------------+-----------------+
| "r+b"       | binary      | yes             | yes             | no              | no              |
+-------------+-------------+-----------------+-----------------+-----------------+-----------------+
| "rb+"       | binary      | yes             | yes             | no              | no              |
+-------------+-------------+-----------------+-----------------+-----------------+-----------------+
| "w"         | text        | no              | yes             | yes             | yes             |
+-------------+-------------+-----------------+-----------------+-----------------+-----------------+
| "wb"        | binary      | no              | yes             | yes             | yes             |
+-------------+-------------+-----------------+-----------------+-----------------+-----------------+
| "w+"        | text        | yes             | yes             | yes             | yes             |
+-------------+-------------+-----------------+-----------------+-----------------+-----------------+
| "w+b"       | binary      | yes             | yes             | yes             | yes             |
+-------------+-------------+-----------------+-----------------+-----------------+-----------------+
| "wb+"       | binary      | yes             | yes             | yes             | yes             |
+-------------+-------------+-----------------+-----------------+-----------------+-----------------+
| "a"         | text        | no              | yes             | yes             | no              |
+-------------+-------------+-----------------+-----------------+-----------------+-----------------+
| "ab"        | binary      | no              | yes             | yes             | no              |
+-------------+-------------+-----------------+-----------------+-----------------+-----------------+
| "a+"        | text        | yes             | yes             | yes             | no              |
+-------------+-------------+-----------------+-----------------+-----------------+-----------------+
| "a+b"       | binary      | no              | yes             | yes             | no              |
+-------------+-------------+-----------------+-----------------+-----------------+-----------------+
| "ab+"       | binary      | no              | yes             | yes             | no              |
+-------------+-------------+-----------------+-----------------+-----------------+-----------------+



Table 9.3. File opening modes

Beware that some implementations of binary files may
pad the last record with NULL characters, so
opening them with modes ab, ab+ or a+b
could position the file pointer beyond the last
data written.

If a file is opened in
append mode, all writes will occur at the
end of the file, regardless of attempts to
move the file position indicator with fseek. The
initial position of the file position indicator will
be implementation defined.

Attempts to open a file in read mode,
indicated by an 'r' as the first character
in the mode string, will fail if the
file does not already exist or can't be
read.

Files opened for update (‘+’ as the second
or third character of mode) may be both
read and written, but a read may not
immediately follow a write, or a write follow
a read, without an intervening call to one
(or more) of fflush, fseek, fsetpos or rewind.
The only exception is that a write may
immediately follow a read if EOF was read.

It may also be possible in some implementations
to omit the b in the binary modes,
using the same modes for text and binary files.

Streams opened by fopen are fully buffered only
if they are not connected to an interactive
device; this ensures that prompts and responses are
handled properly.

If fopen fails to open a file, it
returns a null pointer; otherwise, it returns a
pointer to the object controlling the stream. The
stdin, stdout and stderr objects are not necessarily
modifiable and it may not be possible to
use the value returned from fopen for assignment
to one of them. For this reason, freopen
is provided.

Freopen
~~~~~~~

The freopen function is used to take an
existing stream pointer and associate it with another named file:

.. code-block:: C

    #include <stdio.h>
    FILE *freopen(const char *pathname,
                  const char *mode, FILE *stream);

The mode argument is the same as for
fopen. The stream is closed first, and any
errors from the close are ignored. On error,
NULL is returned, otherwise the new value for
stream is returned.

Closing files
~~~~~~~~~~~~~

An open file is closed using fclose.

.. code-block:: C

    #include <stdio.h>

    int fclose(FILE *stream);

Any unwritten data buffered for stream is flushed
out and any unread data is thrown away.
If a buffer had been automatically allocated for
the stream, it is freed. The file is then closed.

Zero is returned on success, EOF if any error occurs.

Setbuf, setvbuf
~~~~~~~~~~~~~~~

These two functions are used to change the
buffering strategy for an open stream:

.. code-block:: C

    #include <stdio.h>

    int setvbuf(FILE *stream, char *buf,
                  int type, size_t size);
    void setbuf(FILE *stream, char *buf);

They must be used before the file is
either read from or written to. The type
argument defines how the stream will be buffered
(see Table 9.4).

+--------------------+-------------------------------------------------------------------------------------------+
|  Value             | Effect                                                                                    |
+====================+===========================================================================================+
| _IONBF 	     | Do not buffer I/O                                                                         |
+--------------------+-------------------------------------------------------------------------------------------+
| _IOFBF             | Fully buffer I/O                                                                          |
+--------------------+-------------------------------------------------------------------------------------------+
| _IOLBF 	     | Line buffer: flush buffer when full, when newline is written or when a read is requested. |
+--------------------+-------------------------------------------------------------------------------------------+






Table 9.4. Type of buffering


The buf argument can be a null pointer,
in which case an array is automatically allocated
to hold the buffered data. Otherwise, the user
can provide a buffer, but should ensure that
its lifetime is at least as long as
that of the stream: a common mistake is
to use automatic storage allocated inside a compound
statement; in correct usage it is usual to
obtain the storage from malloc instead. The size
of the buffer is specified by the size
argument.

A call of setbuf is exactly the same
as a call of setvbuf with IOFBF for
the type argument, and BUFSIZ for the size
argument. If buf is a null pointer, the
value _IONBF is used for type instead.

No value is returned by setbuf, setvbuf returns
zero on success, non-zero if invalid values are
provided for type or size, or the request
cannot be complied with.

Fflush
~~~~~~

.. code-block:: C

    #include <stdio.h>

    int fflush(FILE *stream);

If stream refers to a file opened for
output or update, any unwritten data is ‘written’
out. Exactly what that means is a function
of the host environment, and C cannot guarantee,
for example, that data immediately reaches the surface
of a disk which might be supporting the
file. If the stream is associated with a
file opened for input or update, any preceding
ungetc operation is forgotten.

The most recent operation on the stream must
have been an output operation; if not, the
behavior is undefined.

A call of fflush with an argument of
zero flushes every output or update stream. Care
is taken to avoid those streams that have
not had an output as their last operation,
thus avoiding the undefined behavior mentioned above.

EOF is returned if an error occurs, otherwise zero.


Formatted I/O
-------------

Character I/O
-------------

Unformatted I/O
---------------

Random access functions
-----------------------

General Utilities
-----------------

String handling
---------------

Date and time
-------------

Summary
-------
