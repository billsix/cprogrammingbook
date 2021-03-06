.. _functions:

Functions
=========

Changes
-------
The single worst feature of pre-C89 was that there
was no way to declare the number and types of
a function's arguments and to have the compiler check
that the use of the function was consistent with its
declaration. Although it didn't do a lot of damage
to the success of C, it did result in portability
and maintainability problems that we all could have done without.

The C89 Standard has changed that state of affairs. You can
now declare functions in a way that allows their use
to be checked, and which is also largely compatible with
the old style (so old programs still work, provided they
had no errors before). Another useful feature is a portable
way of using functions with a variable number of arguments,
like printf, which used to be non-portable; the only
way to implement it relied upon intimate knowledge of the
hardware involved.

The C89 Standard's way of fixing this problem
was in large measure to plagiarize from C++, which had
already tried out the new ideas in practice. This model
has been so successful that lots of ‘Old’ C compilers
adopted it on their way to conforming to the C89 Standard.

The C89 Standard still retains compatibility with pre-C89 function declarations,
but that is purely for the benefit of existing programs.
Any new programs should make full use of the much
tighter checking that the C89 Standard permits and strenuously avoid the
old syntax (which may disappear one day).
Footnotes

1. Stroustrup B. (1991). The C++ Programming Language 2nd edn. Reading, MA: Addison-Wesley

The type of functions
---------------------

All functions have a type: they return a value of
that type whenever they are used. The reason that C
doesn't have ‘procedures’, which in most other languages are
simply functions without a value, is that in C it
is permissible (in fact well-nigh mandatory) to discard the
eventual value of most expressions. If that surprises you, think
of an assignment

.. code-block:: C

      a = 1;

That's a perfectly valid assignment, but don't forget
that it has a value too. The value is discarded.
If you want a bigger surprise, try this one:

.. code-block:: C

      1;

That is an expression followed by a semicolon. It is
a well formed statement according to the rules of the
language; nothing wrong with it, it is just useless. A
function used as a procedure is used in the same
way—a value is always returned, but you don't use it:

.. code-block:: C

      f(argument);

is also an expression with a discarded value.

It's all very well saying that the value returned
by a function can be ignored, but the fact remains
that if the function really does return a value then
it's probably a programming error not to do something
with it. Conversely, if no useful value is returned then
it's a good idea to be able to spot
anywhere that it is used by mistake. For both of
those reasons, functions that don't return a useful value
should be declared to be void.

Functions can return any type supported by C (except for
arrays and functions), including the pointers, structures and unions which
are described in later chapters. For the types that can't
be returned from functions, the restrictions can often be
sidestepped by using pointers instead.

All functions can be called recursively.

Declaring functions
~~~~~~~~~~~~~~~~~~~

Unfortunately, we are going to have to use some jargon
now. This is one of the times that the use
of an appropriate technical term really does reduce the amount
of repetitive descriptive text that would be needed. With a
bit of luck, the result is a shorter, more accurate
and less confusing explanation. Here are the terms.

     declaration

         The point at which a name has a type associated with it.

     definition

         Also a declaration, but at this point some
	 storage is reserved for the named object. The
	 rules for what makes a declaration into a
	 definition can be complicated, but are easy for
	 functions: You turn a function declaration into a
	 definition by providing a body for the function
	 in the form of a compound statement.

     formal parameters

     parameters

         These are the names used inside a function
	 to refer to its arguments.

     actual arguments

     arguments

         These are the values used as arguments when
	 the function is actually called. In other words,
	 the values that the formal parameters will have
	 on entry to the function.

The terms ‘parameter’ and ‘argument’ do tend to get used
as if they were interchangeable, so don't read too
much into it if you see one or the other
in the text below.

If you use a function before
you declare it, it is implicitly declared to be ‘function
returning int’. Although this will work, and was widely used
in pre-C89, in C89 Standard C it is bad practice —
the use of undeclared functions leads to nasty problems to
do with the number and type of arguments that are
expected for them. All functions should be fully declared before
they are used. For example, you might be intending to
use a function in a private library called, say, aax1.
You know that it takes no arguments and returns a
double. Here is how it should be declared:

.. literalinclude:: ../src/example4.1/src/example4.1.c
   :language: c
   :linenos:

and here is how it might be used:

.. literalinclude:: ../src/example4.1/src/example4.1.c
   :language: c
   :linenos:


Example 4.1

The declaration was an interesting one. It defined return_v,
actually causing a variable to come into existence. It also
declared aax1 without defining it; as we know, functions only
become defined when a body is provided for them. Without
a declaration in force, the default rules mean that aax1
would have been assumed to be int, even though it
really does return a double—which means that your program
will have undefined behavior. Undefined behavior is disastrous!

The presence
of void in the argument list in the declaration shows
that the function really takes no arguments. If it had
been missing, the declaration would have been taken to give
no information about the function's arguments. That way, compatibility
with pre-C89 is maintained at the price of the
ability of the compiler to check.

To define a function
you also have to provide a body for it, in
the form of a compound statement. Since no function can
itself contain the definition of a function, functions are all
separate from each other and are only found at the
outermost level of the program's structure. Here is a
possible definition for the function aax1.

.. literalinclude:: ../src/example4.1/src/example4.1.c
   :language: c
   :linenos:

It is unusual for a block-structured language to prohibit
you from defining functions inside other functions, but this is
one of the characteristics of C. Although it isn't
obvious, this helps to improve the run-time performance of
C by reducing the housekeeping associated with function calls.

The return statement
~~~~~~~~~~~~~~~~~~~~

The return statement is very important. Every function except those
returning void should have at least one, each return showing
what value is supposed to be returned at that point.
Although it is possible to return from a function by
falling through the last }, unless the function returns void an
unknown value will be returned, resulting in undefined behavior.

Here
is another example function. It uses getchar to read characters
from the program input and returns whatever it sees except
for space, tab or newline, which it throws away.

.. code-block:: C

    #include <stdio.h>

    int
    non_space(){
          int c;
          while ( (c=getchar ())=='\t' || c== '\n' || c==' ')
                  ; /* empty statement */
          return c;
    }

Look at the way that all of the work is
done by the test in the while statement, whose body
was an empty statement. It is not an uncommon sight
to see the semicolon of the empty statement sitting there
alone and forlorn, with only a piece of comment for
company and readability. Please, please, never write it like this:

.. code-block:: C

       while (something);

with the semicolon hidden away at the end like that.
It's too easy to miss it when you read
the code, and to assume that the following statement is
under the control of the while.

The type of expression
returned must match the type of the function, or be
capable of being converted to it as if an assignment
statement were in use. For example, a function declared to
return double could contain

.. code-block:: C

       return 1;

and the integral value will be converted to double. It
is also possible to have just return without any expression —
but this is probably a programming error unless the function
returns void. Following the return with an expression is not
permitted if the function returns void.

Arguments to functions
~~~~~~~~~~~~~~~~~~~~~~

Before the C89 Standard, it was not possible to give any
information about a function's arguments except in the definition
of the function itself. The information was only used in
the body of the function and was forgotten at the
end. In those bad old days, it was quite possible
to define a function that had three double arguments and
only to pass it one int, when it was called.
The program would compile normally, but simply not work properly.
It was considered to be the programmer's job to
check that the number and the type of arguments to
a function matched correctly. As you would expect, this turned
out to be a first-rate source of bugs and
portability problems. Here is an example of the definition and
use of a function with arguments, but omitting for the
moment to declare the function fully.

.. literalinclude:: ../src/example4.2/src/example4.2.c
   :language: c
   :linenos:

Example 4.2

What can we learn from this? To start with, notice
the careful declaration that pmax returns void. In the function
definition, the matching void occurs on the line before the
function name. The reason for writing it like that is
purely one of style; it makes it easier to find
function definitions if their names are always at the beginning
of a line.

The function declaration (in main) gave no
indication of any arguments to the function, yet the use
of the function a couple of lines later involved two
arguments. That is permitted by both the old and C89 Standard
versions of C, but must nowadays be considered to be
bad practice. It is much better to include information about
the arguments in the declaration too, as we will see.
The old style is now an ‘obsolescent feature’ and may
disappear in a later version of the C89 Standard.

Now on
to the function definition, where the body is supplied. The
definition shows that the function takes two arguments, which will
be known as a1 and a2 throughout the body of
the function. The types of the arguments are specified too,
as can be seen.

In the function definition you don't
have to specify the type of each argument because
they will default to int, but this is bad style.
If you adopt the practice of always declaring arguments, even
if they do happen to be int, it adds to
a reader's confidence. It indicates that you meant to
use that type, instead of getting it by accident: it
wasn't simply forgotten. The definition of pmax could have
been this:

.. code-block:: C

       /* BAD STYLE OF FUNCTION DEFINITION */

       void
       pmax(a1, a2){
             /* and so on */

The proper way to declare and define functions is through
the use of prototypes.

Function prototypes
~~~~~~~~~~~~~~~~~~~

The introduction of function prototypes is the biggest change of
all in the C89 Standard.

A function prototype is a function
declaration or definition which includes information about the number and
types of the arguments that the function takes.

Although you
are allowed not to specify any information about a function's
arguments in a declaration, it is purely because of
backwards compatibility with pre-C89 and should be avoided.

A
declaration without any information about the arguments is not a
prototype.

Here's the previous example ‘done right’.

.. literalinclude:: ../src/example4.3/src/example4.3.c
   :language: c
   :linenos:

Example 4.3

This time, the declaration provides information about the function arguments,
so it's a prototype. The names first and second
are not an essential part of the declaration, but they
are allowed to be there because it makes it easier
to refer to named arguments when you're documenting the
use of the function. Using them, we can describe the
function simply by giving its declaration

.. code-block:: C

       void pmax (int xx, int yy );

and then say that pmax prints whichever of the arguments
xx or yy is the larger. Referring to arguments by
their position, which is the alternative (e.g. the fifth
argument), is tedious and prone to miscounting.

All the same, you can miss out the names if
you want to. This declaration is entirely equivalent to the
one above.

.. code-block:: C

       void pmax (int,int);

All that is needed is the type names.

For a function that has no arguments the declaration is

.. code-block:: C

       void f_name ();

and a function that has one int, one double and
an unspecified number of other arguments is declared this way:

.. code-block:: C

       void f_name (int,double,...);

The ellipsis (...) shows that other arguments follow. That's useful
because it allows functions like printf to be written. Its declaration is this:

.. code-block:: C

       int printf (const char *format_string,...)

where the type of the first argument is ‘pointer to
const char’; we'll discuss what that means later.

Once
the compiler knows the types of a function's arguments,
having seen them in a prototype, it's able to
check that the use of the function conforms to the
declaration.

If a function is called with arguments of the wrong
type, the presence of a prototype means that the actual
argument is converted to the type of the formal argument
‘as if by assignment’. Here's an example: a function
is used to evaluate a square root using Newton's
method of successive approximations.

.. literalinclude:: ../src/example4.4/src/example4.4.c
   :language: c
   :linenos:

Example 4.4

The prototype tells everyone that sq_root takes a single
argument of type double. The argument actually passed in the
main function is an int, so it has to be
converted to double first. The critical point is that if
no prototype had been seen, C would assume that the
programmer had meant to pass an int and an int
is what would be passed. The C89 Standard simply notes that
this results in undefined behavior, which is as understated as
saying that catching rabies is unfortunate. This is a very
serious error and has led to many, many problems in pre-C89 programs.

The conversion of int to double could be done because
the compiler had seen a prototype for the function and
knew what to do about it. As you would expect,
there are various rules used to decide which conversions are
appropriate, so we need to look at them next.

Argument Conversions
~~~~~~~~~~~~~~~~~~~~

When a function is called, there are a number of
possible conversions that will be applied to the values supplied
as arguments depending on the presence or absence of a
prototype. Let's get one thing clear: although you can
use these rules to work out what to do if
you haven't used prototypes, it is a recipe for
pain and misery in the long run. It's so
easy to use prototypes that there really is no excuse
for not having them, so the only time you will
need to use these rules is if you are being
adventurous and using functions with a variable number of arguments,
using the ellipsis notation in the prototype that is explained
in :ref:`libraries`.

The rules mention the default argument promotions and compatible type.
Where they are used, the default argument promotions are:

    Apply the integral promotions (see :ref:`variables`) to the value of each argument

    If the type of the argument is float it is converted to double

The introduction of prototypes (amongst other things) has increased the
need for precision about ‘compatible types’, which was not much
of an issue in pre-C89. The full list of
rules for type compatibility is deferred until :ref:`specialized`, because
we suspect that most C programmers will never need to
learn them. For the moment, we will simply work on
the basis that if two types are the same, they
are indisputably compatible.

The conversions are applied according to these
rules (which are intended to be guidance on how to
apply the C89 Standard, not a direct quote):

    At the point of calling a function, if no prototype
    is in scope, the arguments all undergo the default argument
    promotions. Furthermore:

        If the number of arguments does not agree with the
	number of formal parameters to the function, the behavior is
	undefined.

        If the function definition was not a definition containing a
	prototype, then the type of the actual arguments after promotion
	must be compatible with the types of the formal parameters
	in the definition after they too have had the promotions
	applied. Otherwise the behavior is undefined.

        If the function definition was a definition containing a prototype,
	and the types of the actual arguments after promotion are
	not compatible with the formal parameters in the prototype, then
	the behavior is undefined. The behavior is also undefined it
	the prototype included ellipsis (, ...).


    At the point of calling a function, if a prototype
    is in scope, the arguments are converted, as if by
    assignment, to the types specified in the prototype. Any arguments
    which fall under the variable argument list category (specified by
    the ... in the prototype) still undergo the default argument
    conversions.

    It is possible to write a program so badly that
    you have a prototype in scope when you call the
    function, but for the function definition itself not to have
    a prototype. Why anyone should do this is a mystery,
    but in this case, the function that is called must
    have a type that is compatible with the apparent type
    at the point of the call.

The order of evaluation of the arguments in the function
call is explicitly not defined by the C89 Standard.

Function definitions
~~~~~~~~~~~~~~~~~~~~

Function prototypes allow the same text to be used for
both the declaration and definition of a function. To turn a declaration:

.. code-block:: C

     double
     some_func(int a1, float a2, long double a3);

into a definition, we provide a body for the function:

.. code-block:: C

     double
     some_func(int a1, float a2, long double a3){
           /* body of function */
           return(1.0);
     }

by replacing the semicolon at the end of the declaration
with a compound statement.

In either a definition or a declaration of a function,
it serves as a prototype if the parameter types are specified; both of the examples above are prototypes.

The pre-C89 syntax for the declaration of a function's
formal arguments is still supported by the C89 Standard, although
it should not be used by new programs. It looks
like this, for the example above:

.. code-block:: C

     double
     some_func(a1, a2, a3)
           int a1;
           float a2;
           long double a3;
     {

           /* body of function */
           return(1.0);
     }

Because no type information is provided for the parameters at
the point where they are named, this form of definition
does not act as a prototype. It declares only the
return type of the function; nothing is remembered by the
compiler about the types of the arguments at the end
of the definition.

The C89 Standard warns that support for this syntax may disappear
in a later version. It will not be discussed further.

Summary

    Functions can be called recursively.

    Functions can return any type that you can declare, except
    for arrays and functions (you can get around that restriction
    to some extent by using pointers). Functions returning no value
    should return void.

    Always use function prototypes.

    Undefined behavior results if you call or define a function
    anywhere in a program unless either

        a prototype is always in scope for every call or
	definition, or
        you are very, very careful.

    Assuming that you are using prototypes, the values of the
    arguments to a function call are converted to the types
    of the formal parameters exactly as if they had been
    assigned using the = operator.

    Functions taking no arguments should have a prototype with ()
    as the argument specification.

    Functions taking a variable number of
    arguments must take at least one named argument; the variable
    arguments are indicated by ... as shown:

    int
    vfunc(int x, float y, ...);

    :ref:`libraries` describes how to write this sort of function.

Compound statements and declarations
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

As we have seen, functions always have a compound statement
as their body. It is possible to declare new variables
inside any compound statement; if any variables of the same
name already exist, then the old ones are hidden by
the new ones within the new compound statement. This is
the same as in every other block-structured language. C
restricts the declarations to the head of the compound statement
(or ‘block’); once any other kind of statement has been
seen in the block, declarations are no longer permitted within that block.

How can it be possible for names to be hidden? The following example shows it happening:

.. literalinclude:: ../src/example4.5/src/example4.5.c
   :language: c
   :linenos:

Example 4.5

A name declared inside a block hides any outer versions of
the same name until the end of the block where it
is declared. Inner blocks can also re-declare that name—you
can do this for ever.

The scope of a name is the range in which it
has meaning. Scope starts from the point at which the name
is mentioned and continues from there onward to the end of
the block in which it is declared. If it is external
(outside of any function) then it continues to the end of
the file. If it is internal (inside a function), then it
disappears at the end of the block containing it. The scope
of any name can be suspended by re-declaring the name inside
a block.

Using knowledge of the scope rules, you can play silly tricks
like this one:

.. code-block:: C

     main () {}
     int i;
     f () {}
     f2 () {}

Now f and f2 can use i, but main can't,
because the declaration of the variable comes later than that of
main. This is not an aspect that is used very much,
but it is implicit in the way that C processes declarations.
It is a source of confusion for anyone reading the file
(external declarations are generally expected to precede any function definitions in
a file) and should be avoided.

The C89 Standard has changed things slightly with respect to a function's
formal parameters. They are now considered to have been declared
inside the first compound statement, even though textually they aren't:
this goes for both the new and old ways of function
definition. So, if a function has a formal parameter with the
same name as something declared in the outermost compound statement, this
causes an error which will be detected by the compiler.

In pre-C89, accidental redefinition of a function's formal parameter
was a horrible and particularly difficult mistake to track down. Here
is what it would look like:

.. code-block:: C

     /* erroneous re-declaration of arguments */

     func(a, b, c){
           int a;  /* AAAAgh! */
     }

The pernicious bit is the new declaration of a in the
body of the function, which hides the parameter called a. Since
the problem has now been eliminated we won't investigate it
any further.

Footnotes

1. Stroustrup B. (1991). The C++ Programming Language 2nd edn. Reading, MA: Addison-Wesley

Recursion and argument passing
------------------------------

So far, we've seen how to give functions a type
(how to declare the return value and the type of any
arguments the function takes), and how the definition is used to
give the body of the function. Next we need to see
what the arguments can be used for.

Call by value
~~~~~~~~~~~~~

The way that C treats arguments to functions is both simple
and consistent, with no exceptions to the single rule.

When a function is called, any arguments that are provided by
the caller are simply treated as expressions. The value of each
expression has the appropriate conversions applied and is then used to
initialize the corresponding formal parameter in the called function, which behaves
in exactly the same way as any other local variables in
the function. It's illustrated here:

.. literalinclude:: ../src/example4.6/src/example4.6.c
   :language: c
   :linenos:

Example 4.6

The arguments to called_func in main are two expressions, which
are evaluated. The value of each expression is used to initialize
the parameters iarg and farg in called_func, and the parameters
are indistinguishable from the other local variable declared in called_func,
which is tmp.

The initialization of the formal parameters is the last time that
any communication occurs between the caller and the called function, except
for the return value.

For those who are used to FORTRAN and var arguments in
Pascal, where a function can change the values of its arguments:
forget it. You cannot affect the values of a function's
actual arguments by anything that you try. Here is an example
to show what we mean.

.. literalinclude:: ../src/example4.7/src/example4.7.c
   :language: c
   :linenos:

Example 4.7

The result of running that is:

before i=5
changer: x=5
changer: x=4
changer: x=3
changer: x=2
changer: x=1
after i=5

The function changer uses its formal parameter x as an ordinary
variable—which is exactly what it is. Although the value of
x is changed, the variable i (in main) is unaffected. That
is the whole point—the arguments in C are passed into
a function by their value only, no changes made by the
function are passed back.

Call by reference
~~~~~~~~~~~~~~~~~

It is possible to write functions that take pointers as their
arguments, giving a form of call by reference. This is described
in :ref:`arrays` and does allow functions to change values in
their callers.

Recursion
~~~~~~~~~

With argument passing safely out of the way we can look
at recursion. Recursion is a topic that often provokes lengthy and
unenlightening arguments from opposing camps. Some think it is wonderful, and
use it at every opportunity; some others take exactly the opposite
view. Let's just say that when you need it, you
really do need it, and since it doesn't cost much
to put into a language, as you would expect, C supports recursion.

Every function in C may be called from any other or
itself. Each invocation of a function causes a new allocation of
the variables declared inside it. In fact, the declarations that we
have been using until now have had something missing: the keyword
auto, meaning ‘automatically allocated’.

.. code-block:: C

     /* Example of auto */
     main(){
           auto int var_name;
           .
           .
           .
     }

The storage for auto variables is automatically allocated and freed on
function entry and return. If two functions both declare large automatic
arrays, the program will only have to find room for both
arrays if both functions are active at the same time. Although
auto is a keyword, it is never used in practice because
it's the default for internal declarations and is invalid for
external ones. If an explicit initial value (see ‘ initialization’) isn't
given for an automatic variable, then its value will be unknown
when it is declared. In that state, any use of its
value will cause undefined behavior.

The real problem with illustrating recursion is in the selection of
examples. Too often, simple examples are used which don't really
get much out of recursion. The problems where it really helps
are almost always well out of the grasp of a beginner
who is having enough trouble trying to sort out the difference
between, say, definition and declaration without wanting the extra burden of
having to wrap his or her mind around a new concept
as well. The chapter on data structures will show examples of
recursion where it is a genuinely useful technique.


The following example uses recursive functions to evaluate expressions involving single
digit numbers, the operators \*, %, /, +, - and parentheses in the same way that
C does. (Stroustrup1, in his book about C++, uses almost an
identical example to illustrate recursion. This happened purely by chance.) The
whole expression is evaluated and its value printed when a character
not in the ‘language’ is read. For simplicity no error checking
is performed. Extensive use is made of the ungetc library function,
which allows the last character read by getchar to be ‘unread’
and become once again the next character to be read. Its
second argument is one of the things declared in stdio.h.

Those of you who understand BNF notation might like to know
that the expressions it will understand are described as follows:

.. code-block:: BNF

     <primary> ::= digit | (<exp>)
     <unary>   ::= <primary> | -<unary> | +<unary>
     <mult>    ::= <unary> | <mult> * <unary> |
                   <mult> / <unary> | <mult> % <unary>
     <exp>     ::= <exp> + <mult> | <exp> - <mult> | <mult>

The main places where recursion occurs are in the function unary_exp,
which calls itself, and at the bottom level where primary
calls the top level all over again to evaluate parenthesized expressions.

If you don't understand what it does, try running it.
Trace its actions by hand on inputs such as

.. code-block:: C

     1
     1+2
     1+2 * 3+4
     1+--4
     1+(2*3)+4

That should keep you busy for a while!

.. literalinclude:: ../src/example4.8/src/example4.8.c
   :language: c
   :linenos:

Example 4.8

Footnotes

1. Stroustrup B. (1991). The C++ Programming Language 2nd edn. Reading, MA: Addison-Wesley

Linkage
-------

Although the simple examples have carefully avoided the topic, we now
have to look into the effects of scope and linkage, terms
used to describe the accessibility of various objects in a C
program. Why bother? It's because realistic programs are built up
out of multiple files and of course libraries. It is clearly
crucial that functions in one file should be able to refer
to functions (or other objects) in other files and libraries; naturally
there are a number of concepts and rules that apply to
this mechanism.

If you are relatively new to C, there are
more important subjects to cover first. Come back to this stuff
later instead.

There are essentially two types of object in C:
the internal and external objects. The distinction between external and internal
is to do with functions: anything declared outside a function is
external, anything inside one, including its formal parameters, is internal. Since
no function can be defined inside another, functions themselves are always
external. At the outermost level, a C program is a collection
of external objects.

Only external objects participate in this cross-file
and library communication.

The term used by the C89 Standard to describe
the accessibility of objects from one file to another, or even
within the same file, is linkage. There are three types of
linkage: external linkage, internal linkage and no linkage. Anything internal to
a function—its arguments, variables and so on—always has no
linkage and so can only be accessed from inside the function
itself. (The way around this is to declare something inside a
function but prefix it with the keyword extern which says ‘it
isn't really internal’, but we needn't worry about that
just yet.)

Objects that have external linkage are all considered to
be located at the outermost level of the program; this is
the default linkage for functions and anything declared outside of a
function. All instances of a particular name with external linkage refer
to the same object in the program. If two or more
declarations of the same name have external linkage but incompatible types,
then you've done something very silly and have undefined behavior.
The most obvious example of external linkage is the printf function,
whose declaration in <stdio.h> is

.. code-block:: C

     int printf(const char *, ...);

From that we can tell that it's a function returning
int and with a particular prototype—so we know everything about
its type. We also know that it has external linkage, because
that is the default for every external object. As a result,
everywhere that the name printf is used with external linkage, we
are referring to this function.

Quite often, you want to be
able to declare functions and other objects within a single file
in a way that allows them to reference each other but
not to be accessible from outside that file. This is often
necessary in the modules that support library functions, where the additional
framework that makes those functions work is not interesting to the
user and would be a positive nuisance if the names of
those things became visible outside the module. You do it through
the use of internal linkage.

Names with internal linkage only refer
to the same object within a single source file. You do
this by prefixing their declarations with the keyword static, which changes
the linkage of external objects from external linkage to internal linkage.
It is also possible to declare internal objects to be static,
but that has an entirely different meaning which we can defer
for the moment.

It's confusing that the types of linkage
and the types of object are both described by the terms
‘internal’ and ‘external’; this is to some extent historical. C archaeologists
may know that at one time the two were equivalent and
one implied the other—for us it's unfortunate that the
terms remain but the meanings have diverged. To summarize:



+--------------------+-----------------+------------------------------+
|    Type of linkage +  Type of object + Accessibility                |
+====================+=================+==============================+
|    external 	     |  external       | throughout the program       |
+--------------------+-----------------+------------------------------+
|    internal 	     |  external       | a single file                |
+--------------------+-----------------+------------------------------+
|    none 	     |  internal       | local to a single function   |
+--------------------+-----------------+------------------------------+

Table 4.1. Linkage and accessibility

Finally, before we see an example, it is important to know
that all objects with external linkage must have one and only
one definition, although there can be as many compatible declarations as
you like. Here's the example.

.. literalinclude:: ../src/example4.9/src/example4.9.c
   :language: c
   :linenos:


.. literalinclude:: ../src/example4.9/src/secondfile.c
   :language: c
   :linenos:



Example 4.9

Although the full set of rules is a bit more complex,
the basic way of working out what constitutes a definition and
a declaration is not hard:

    A function declaration without a body for the function is
    just a declaration.

    A function declaration with a body for the function is
    a definition.

    At the external level, a declaration of an object (like
    the variables) is a definition unless it has the keyword
    extern in front of it, when it is a declaration only.


:ref:`specialized` revisits the definition and declaration criteria to a depth
that will cause decompression sickness when you surface.

In the example it's easy to see that each file
is able to access the objects defined in the other by
using their names. Just from that example alone you should be
able to work out how to construct programs with multiple files
and functions and variables declared or defined as appropriate in each
of them.

Here's another example, using static to restrict the accessibility of
functions and other things.

.. literalinclude:: ../src/example4.10/src/example4.10.c
   :language: c
   :linenos:

Example 4.10

A user of this module can safely re-use the names
declared here, length, buf, and fillup, without any danger of surprising
effects. Only the name callable is accessible outside this module.

A very useful thing to know is that any external object
that has no other initializer (and except for functions we haven't
seen any initializers yet) is always set to the value
of zero before the program starts. This is widely used and
relied on—the previous example relies on it for the initial
value of length.

Effect of scope
~~~~~~~~~~~~~~~

There's one additional complicating factor beyond simply linkage. Linkage allows
you to couple names together on a per-program or a
per-file basis, but scope determines the visibility of the names.
Fortunately, the rules of scope are completely independent of anything to
do with linkage, so you don't have to remember funny
combinations of both.

What introduces the complexity is the dreaded extern keyword. The nice
regular block structure gets blown to pieces with this, which although
at a first glance is simple and obvious, does some very
nasty things to the fabric of the language. We'll leave
its nasty problems to :ref:`specialized`, since they only rear up
if you deliberately start to do perverse things with it and
then say ‘what does this mean’? We've already seen it
used to ensure that the declaration of something at the outer
block level (the external level) of the program is a declaration
and not a definition (but beware: you can still override the
extern by, for example, providing an initializer for the object).

Unless you prefix it with extern, the declaration of any data
object (not a function) at the outer level is also a
definition. Look back to Example 4.9 to see this in use.

All function declarations implicitly have the extern stuck in front of
them, whether or not you put it there too. These two
ways of declaring some_function are equivalent and are always declarations:

.. code-block:: C

     void some_function();

     extern void some_function();

The thing that mysteriously turns those declarations into definitions is that
when you also provide the body of the function, that is
effectively the initializer for the function, so the comment about initializers
comes into effect and the declaration becomes a definition. So far,
no problem.

Now, what is going on here?

.. code-block:: C

     void some_function(){
           int i_var;
           extern float e_f_var;
     }

     void another_func(){
           int i;
           i = e_f_var;    /* scope problem */
     }

What happened was that although the declaration of e_f_var
declares that something called e_f_var is of type float
and is accessible throughout the entire program, the scope of the
name disappears at the end of the function that contains it.
That's why it is meaningless inside another_func—the name
of e_f_var is out of scope, just as much
as i_var is.

So what use is that? It's
sometimes handy if you only want to make use of an
external object from within a single function. If you followed the
usual practice and declared it at the head of the particular
source file, then there is no easy way for the reader
of that file to see which functions actually use it. By
restricting the access and the scope of the name to the
place where is needed, you do communicate to a later reader
of the program that this is a very restricted use of
the name and that there is no intention to make widespread
use of it throughout the file. Of course, any half-way
decent cross-reference listing would communicate that anyway, so the argument
is a bit hard to maintain.

:ref:`specialized` is the place to find out more. There's
a set of guidelines for how to get the results that
are most often wanted from multi-file construction, and a good
deal more detail on what happens when you mix extern, static
and internal and external declarations. It isn't the sort of
reading that you're likely to do for pleasure, but it
does answer the ‘what if’ questions.

Internal static
~~~~~~~~~~~~~~~

You are also allowed to declare internal objects as static. Internal
variables with this attribute have some interesting properties: they are initialized
to zero when the program starts, they retain their value between
entry to and exit from the statement containing their declaration and
there is only one copy of each one, which is shared
between all recursive calls of the function containing it.

Internal statics can be used for a number of things. One
is to count the number of times that a function has
been called; unlike ordinary internal variables whose value is lost after
leaving their function, statics are convenient for this. Here's a
function that always returns a number between 0 and 15, but
remembers how often it was called.

.. literalinclude:: ../src/example4.11/src/example4.11.c
   :language: c
   :linenos:

Example 4.11

They can help detect excessive recursion:

.. literalinclude:: ../src/example4.12/src/example4.12.c
   :language: c
   :linenos:


Example 4.12

Footnotes

1. Stroustrup B. (1991). The C++ Programming Language 2nd edn. Reading, MA: Addison-Wesley

Summary
-------

With the appropriate declarations, you can have names that are visible
throughout the program or limited to a single file or limited
to a single function, as appropriate.

Here are the combinations of the use of the keywords, the
types of declarations and the resulting linkage:

+--------------------+-----------------+------------------------------+--------------------------+-------------------+
| Declaration        + Keyword         +  Resulting Linkage           | Accessibility            | Note              |
+====================+=================+==============================+==========================+===================+
| external           | none            | external                     | entire program           | 2                 |
+--------------------+-----------------+------------------------------+--------------------------+-------------------+
| external           | extern          | external                     | entire program 	         | 2                 |
+--------------------+-----------------+------------------------------+--------------------------+-------------------+
| external           | static          | internal                     | a single file 	         | 2                 |
+--------------------+-----------------+------------------------------+--------------------------+-------------------+
| internal           | none            | none 	                      | a single function        | n                 |
+--------------------+-----------------+------------------------------+--------------------------+-------------------+
| internal           | extern          | external                     | entire function          | 1                 |
+--------------------+-----------------+------------------------------+--------------------------+-------------------+
| internal           | static          | none                         | a single function        | 2                 |
+--------------------+-----------------+------------------------------+--------------------------+-------------------+


Although the accessibility of internal declarations prefixed with extern is program-wide,
watch out for the scope of the name.
External (or
internal static) objects are initialized once only, at program start-up.
The absence of explicit initialization is taken to be a default
initialization of zero.

Table 4.2. Summary of Linkage

There are a few golden rules for the use of functions
that are worth re-stating too.

    To use a function returning other than int, a declaration
    or definition must be in scope.

    Do not return from a function by falling out of
    its body unless its type is void.

A declaration of the types of arguments that a function takes
is not mandatory, but it is extremely strongly recommended.

Functions taking
a variable number of arguments can be written portably if you
use the methods described in Section 9.9.

Functions are the
cornerstone of C. Of all the changes to the language, the
C89 Standard has had by far its most obvious effect by introducing
function prototypes. This change has won widespread approval throughout the user
community and should help to produce a substantial improvement in reliability
of C programs, as well as opening the possibility of optimization
by compilers in areas previously closed to them.

The use of
call-by-value is sometimes surprising to people who have used
languages that prefer a different mechanism, but at least the C
approach is the ‘safest’ most of the time.

The attempts by
the C89 Standard to remove ambiguity in the scope and meaning of
declarations are interesting, but frankly have explored an obscure region which
rarely caused any difficulties in practice.

From the beginner's point
of view, it is important to learn thoroughly everything discussed in
this chapter, perhaps with the exception of the linkage rules. They
can be deferred for a more leisurely inspection at some later
time.

Footnotes

1. Stroustrup B. (1991). The C++ Programming Language 2nd edn. Reading, MA: Addison-Wesley

Exercises
---------

If you skipped the section on Linkage, then Exercise 4.2,
Exercise 4.3, and Exercise 4.4 will cause you problems;
it's up to you whether or not you want to
read it and then try them.

Write a function and the
appropriate declaration for the following tasks:

Exercise 4.1. A function
called abs_val that returns int and takes an int argument.
It returns the absolute value of its argument, by negating it
if it is negative.

Exercise 4.2. A function called output that takes a single
character argument and sends it to the program output with putchar.
It will remember the current line number and column number reached
on the output device—the only values passed to the function
are guaranteed to be alphanumeric, punctuation, space and newline characters.

Exercise 4.3. Construct a program to test output, where that
function is in a separate file from the functions that are
used to test it. In the same file as output will
be two functions called current_line and current_column which return
the values of the line and column counters. Ensure that those
counters are made accessible only from the file that contains them.

Exercise 4.4. Write and test a recursive function that performs
the admittedly dull task of printing a list of numbers from
100 down to 1. On entry to the function it increments
a static variable. If the variable has a value below 100,
it calls itself again. Then it prints the value of the
variable, decrements it and returns. Check that it works.

Exercise 4.5. Write functions to calculate the sine and cosine
of their input. Choose appropriate types for both argument and return
value. The series (given below) can be used to approximate the
answer. The function should return when the value of the final
term is less than 0.000001 of the current value of the function.

.. code-block:: C

     sin x = x - pow(x,3)/fact(3) + pow(x,5)/fact(5)...
     cos x = 1 - pow(x,2)/fact(2) + pow(x,4)/fact(4)...

Note the fact that the sign in front of each term
alternates (--+--+--+...). pow(x,n) returns x to the nth power, fact(n)
factorial of n (1 × 2 × 3 × ... × n). You will have to
write such functions. Check the results against published tables.

Footnotes

1. Stroustrup B. (1991). The C++ Programming Language 2nd edn. Reading, MA: Addison-Wesley
