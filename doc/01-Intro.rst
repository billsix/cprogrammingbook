.. _intro:

Introduction
============

The form of a C program
-----------------------

If you're used to the block-structured form of, say, Pascal, then
at the outer level the layout of a C program may surprise you.
If your experience lies in the FORTRAN camp you will find it closer
to what you already know, but the inner level will look quite different.
C has borrowed shamelessly from both kinds of language, and from a lot
of other places too. The input from so many varied sources has spawned
a language a bit like a cross-bred terrier: inelegant in places, but
a tenacious brute that the family is fond of. Biologists refer to this
phenomenon as ‘hybrid vigour’. They might also draw your attention to the ‘chimera’,
an artificial crossbreed of creatures such as a sheep and a goat. If
it gives wool and milk, fine, but it might equally well just bleat and stink!

At the coarsest level, an obvious feature is the multi-file structure of
a program. The language permits separate compilation, where the parts of a complete
program can be kept in one or more source files and compiled independently
of each other. The idea is that the compilation process will produce files
which can then be linked together using whatever link editor or loader that
your system provides. The block structure of the Algol-like languages makes this
harder by insisting that the whole program comes in one chunk, although there
are usually ways of getting around it.

The reason for C's approach is historical and rather interesting. It is
supposed to speed things up: the idea is that compiling a program into
relocatable object code is slow and expensive in terms of resources; compiling is
hard work. Using the loader to bind together a number of object code
modules should simply be a matter of sorting out the absolute addresses of
each item in the modules when combined into a complete program. This should
be relatively inexpensive. The expansion of the idea to arrange for the loader
to scan libraries of object modules, and select the ones that are needed,
is an obvious one. The benefit is that if you change one small
part of a program then the expense of recompiling all of it may
be avoided; only the module that was affected has to be recompiled.

All, the same, it's true that the more work put on to
the loader, the slower it becomes, in fact sometimes it can be the
slowest and most resource consuming part of the whole procedure. It is possible
that, for some systems, it would be quicker to recompile everything in one
go than to have to use the loader: Ada has sometimes been quoted
as an example of this effect occurring. For C, the work that has
to be done by the loader is not large and the approach is a sensible one. Figure 1.1 shows the way that this works.

.. figure:: _static/1.1.png
    :align: center
    :alt: Seperate Compilation
    :figclass: align-center

    Seperate Compilation

This technique is important in C, where it is common to find all
but the smallest of programs constructed from a number of separate source files.
Furthermore, the extensive use that C makes of libraries means that even trivial
programs pass through the loader, although that might not be obvious at the first glance or to the newcomer.

Functions
---------


A C program is built up from a collection of items such as
functions and what we could loosely call global variables. All of these things
are given names at the point where they are defined in the program;
the way that the names are used to access those items from a
given place in the program is governed by rules. The rules are described
in the Standard using the term linkage. For the moment we only need
to concern ourselves with external linkage and no linkage. Items with external linkage
are those that are accessible throughout the program (library functions are a good
example); items with no linkage are also widely used but their accessibility is
much more restricted. Variables used inside functions are usually ‘local’ to the function;
they have no linkage. Although this book avoids the use of complicated terms
like those where it can, sometimes there isn't a plainer way of
saying things. Linkage is a term that you are going to become familiar
with later. The only external linkage that we will see for a while
will be when we are using functions.

Functions are C's equivalents of the functions and subroutines in FORTRAN, functions
and procedures in Pascal and ALGOL. Neither BASIC in most of its simple
mutations, nor COBOL has much like C's functions.

The idea of a function is, of course, to allow you to encapsulate
one idea or operation, give it a name, then to call that operation
from various parts of the rest of your program simply by using the
name. The detail of what is going on is not immediately visible at
the point of use, nor should it be. In well designed, properly structured
programs, it should be possible to change the way that a function does
its job (as long as the job itself doesn't change) with no
effect on the rest of the program.

In a hosted environment there is one function whose name is special; it's
the one called main. This function is the first one entered when
your program starts running. In a freestanding environment the way that a program
starts up is implementation defined; a term which means that although the Standard
doesn't specify what must happen, the actual behaviour must be consistent and
documented. When the program leaves the main function, the whole program comes to
an end. Here's a simple program containing two functions:


.. literalinclude:: ../src/example1.1/src/example1.1.c
   :language: c
   :linenos:

A description of Example 1.1
----------------------------


What was in it
~~~~~~~~~~~~~~
Even such a small example has introduced a lot of C. Among other
things, it contained two functions, a #include ‘statement’, and some comment. Since comment
is the easiest bit to handle, let's look at that first.

Layout and comment
~~~~~~~~~~~~~~~~~~

The layout of a C program is not very important to the compiler,
although for readability it is important to use this freedom to carry extra
information for the human reader. C allows you to put space, tab or
newline characters practically anywhere in the program without any special effect on the
meaning of the program. All of those three characters are the same as
far as the compiler is concerned and are called collectively white space, because
they just move the printing position without causing any ‘visible’ printing on an
output device. White space can occur practically anywhere in a program except in
the middle of identifiers, strings, or character constants. An identifier is simply the
name of a function or some other object; strings and character constants will
be discussed later—don't worry about them for the moment.

Apart from the special cases, the only place that white space must be
used is to separate things that would otherwise run together and become confused.
In the example above, the fragment void show_message needs space to separate
the two words, whereas show_message( could have space in front of the
( or not, it would be purely a matter of taste.

Comment is introduced
to a C program by the pair of characters /\*, which must not have
a space between them. From then on, everything found up to and including
the pair of characters \*/ is gobbled up and the whole lot is replaced
by a single space. In Old C, this was not the case. The
rule used to be that comment could occur anywhere that space could occur:
the rule is now that comment is space. The significance of the change
is minor and eventually becomes apparent in :ref:`preprocessor`
where we discuss the
preprocessor. A consequence of the rule for the end of comment is that
you can't put a piece of comment inside another piece, because the
first \*/ pair will finish all of it. This is a minor nuisance, but
you learn to live with it.

It is common practice to make a
comment stand out by making each line of multi-line comment always start
with a \*, as the example illustrates.

Preprocessor statements
~~~~~~~~~~~~~~~~~~~~~~~

The first statement in the example is a preprocessor directive. In days gone
by, the C compiler used to have two phases: the preprocessor, followed by
the real compiler. The preprocessor was a macro processor, whose job was to
perform simple textual manipulation of the program before passing the modified text on
to be compiled. The preprocessor rapidly became seen as an essential aspect of
the compiler and so has now been defined as part of the language
and cannot be bypassed.

The preprocessor only knows about lines of text; unlike
the rest of the language it is sensitive to the end of a
line and though it is possible to write multi-line preprocessor directives, they
are uncommon and a source of some wonder when they are found. Any
line whose first visible character is a # is a preprocessor directive.

In Example 1.1 the preprocessor directive #include causes the line containing it
to be replaced completely by the contents of another file. In this case
the filename is found between the < and > brackets. This is a widely used
technique to incorporate the text of standard header files into your program without
having to go through the effort of typing it all yourself. The <stdio.h>
file is an important one, containing the necessary information that allows you
to use the standard library for input and output. If you want to
use the I/O library you must include <stdio.h>. Old C was more relaxed on this point.

Define statements
"""""""""""""""""




Another of the preprocessor's talents which is widely exploited is the #define
statement. It is used like this:

.. code-block:: C

    #define IDENTIFIER      replacement

which says that the name represented by IDENTIFIER will be replaced by the
text of replacement whenever IDENTIFIER occurs in the program text. Invariably, the identifier
is a name in upper-case; this is a stylistic convention that helps
the reader to understand what is going on. The replacement part can be
any text at all—remember the preprocessor doesn't know C, it just
works on text. The most common use of the statement is to declare
names for constant numbers:

.. code-block:: C

   #define PI             3.141592
   #define SECS_PER_MIN   60
   #define MINS_PER_HOUR  60
   #define HOURS_PER_DAY  24

and to use them like this

.. code-block:: C

   circumf = 2*PI*radius;
   if(timer >= SECS_PER_MIN){
      mins = mins+1;
      timer = timer - SECS_PER_MIN;
   }

the output from the preprocessor will be as if you had written this:

.. code-block:: C

   circumf = 2*3.141592*radius;
   if(timer >= 60){
       mins = mins+1;
       timer = timer - 60;
   }

Summary
"""""""

#. Preprocessor statements work on a line-by-line basis, the rest of C does not.

#. #include statements are used to read the contents of a specified file, typically
   to facilitate the use of library functions.

#. #define statements are typically used to give names for constants. By convention, the
   names are in upper case (capitalized).

Function declaration and definition
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Declaration
"""""""""""

After the <stdio.h> file is included comes a function declaration; it tells
the compiler that show_message is a function which takes no arguments and
returns no values. This demonstrates one of the changes made by the Standard:
it is an example of a function prototype, a subject which :ref:`functions`
discusses in detail. It isn't always necessary to declare functions in advance — C
will use some (old) default rules in such cases—but it is
now strongly recommended that you do declare them in advance. The distinction between
a declaration and a definition is that the former simply describes the type
of the function and any arguments that it might take, the latter is
where the body of a function is provided. These terms become more important
later.

By declaring show_message before it is used, the compiler is able to
check that it is used correctly. The declaration describes three important things about
the function: its name, its type, and the number and type of its
arguments. The void show_message( part indicates that it is a function and
that it returns a value of type void, which is discussed in a
moment. The second use of void is in the declaration of the function's
argument list, (), which indicates that there are no arguments to this function.

Definition
""""""""""

Right at the end of the program is the function definition itself; although
it is only three lines long, it usefully illustrates a complete function.

In
C, functions perform the tasks that some other languages split into two parts.
Most languages use a function to return a value of some sort, typical
examples being perhaps trigonometric functions like sin, cos, or maybe a square root
function; C is the same in this respect. Other similar jobs are done
by what look very much like functions but which don't return a
value: FORTRAN uses subroutines, Pascal and Algol call them procedures. C simply uses
functions for all of those jobs, with the type of the function's
return value specified when the function is defined. In the example, the function
show_message doesn't return a value so we specify that its type
is void.

The use of void in that way is either crashingly obvious
or enormously subtle, depending on your viewpoint. We could easily get involved here
in an entertaining (though fruitless) philosophical side-track on whether void really is
a value or not, but we won't. Whichever side of the question
you favour, it's clear that you can't do anything with a
void and that's what it means here—“I don't want to
do anything with any value this function might or might not return”.

The type of the function is void, its name is show_message. The parentheses
() following the function name are needed to let the compiler know that at
this point we are talking about a function and not something else. If
the function did take any arguments, then their names would be put between
the parentheses. This one doesn't take any, which is made explicit by
putting void between the parentheses.

For something whose essence is emptiness, abnegation and
rejection, void turns out to be pretty useful.

The body of the function
is a compound statement, which is a sequence of other statements surrounded by
curly brackets {}. There is only one statement in there, but the brackets are
still needed. In general, C allows you to put a compound statement anywhere
that the language allows the use of a single simple statement; the job
of the brackets being to turn several statements in a row into what
is effectively a single statement.

It is reasonable to ask whether or not
the brackets are strictly needed, if their only job is to bind multiple
statements into one, yet all that we have in the example is a
single statement. Oddly, the answer is yes—they are strictly needed. The only
place in C where you can't put a single statement but must
have a compound statement is when you are defining a function. The simplest
function of all is therefore the empty function, which does nothing at all:

.. code-block:: C

   void do_nothing(){}

The statement inside show_message is a call of the library function printf.
printf is used to format and print things, this example being one of
the simplest of its uses. printf takes one or more arguments, whose values
are passed forward from the point of the call into the function itself.
In this case the argument is a string. The contents of the string
are interpreted by printf and used to control the way the values of
the other arguments are printed. It bears a little resemblance to the FORMAT
statement in FORTRAN; but not enough to predict how to use it.

Summary
"""""""


#. Declarations are used to introduce the name of a function, its return type
   and the type (if any) of its arguments.

#. A function definition is a declaration with the body of the function given
   too.

#. A function returning no value should have its type declared as void. For
   example, void func(/\* list of arguments \*/);

#. A function taking no arguments should be declared without an argument
   list. For example, void func();

Strings
~~~~~~~

In C, strings are a sequence of characters surrounded by quote marks:

.. code-block:: C

   "like this"

Because a string is a single element, a bit like an identifier, it
is not allowed to continue across a line—although space or tab characters
are permitted inside a string.

.. code-block:: C

   "This is a valid string"
   "This has a newline in it
   and is NOT a valid string"

To get a very long string there are two things that you can
do. You could take advantage of the fact that absolutely everywhere in a
C program, the sequence ‘backslash end-of-line’ disappears totally.

.. code-block:: C

   "This would not be valid but doesn't have \
   a newline in it as far as the compiler is concerned"

The other thing you could do is to to use the string joining
feature, which says that two adjacent strings are considered to be just one.

.. code-block:: C

   "All this " "comes out as "
   "just one string"

Back to the example. The sequence ‘\n’ in the string is an example
of an escape sequence which in this case represents ‘newline’. Printf simply prints
the contents of the string on the program's output file, so the
output will read ‘hello’, followed by a new line.

To support people working
in environments that use character sets which are ‘wider’ than U.S. ASCII,
such as the shift-JIS representation used in Japan, the Standard now allows
multibyte characters to be present in strings and comments. The Standard defines the
96 characters that are the alphabet of C (see :ref:`variables`). If your
system supports an extended character set, the only place that you may use
these extended characters is in strings, character constants, comment and the names of
header files. Support for extended character sets is an implementation defined feature, so
you will have to look it up in your system's documentation.

The main function
~~~~~~~~~~~~~~~~~

In Example 1.1 there are actually two functions, show_message and main.
Although main is a bit longer than show_message it is obviously built
in the same shape: it has a name, the parentheses () are there, followed
by the opening bracket { of the compound statement that must follow in a
function definition. True, there's a lot more stuff too, but right at
the end of the example you'll find the matching closing bracket } that
goes with the first one to balance the numbers.

This is a much more realistic function now, because there are several statements
inside the function body, not just one. You might also have noticed that
the function is not declared to be void. There is a good reason
for this: it returns a proper value. Don't worry about its arguments
yet; they are discussed in :ref:`complete`.

The most important thing about main is that it is the first function
to be called. In a hosted environment your C language system arranges, magically,
for a call on the main function (hence its name) when the program
is first started. When the function is over, so is the program. It's
obviously an important function. Equally important is the stuff inside main's
compound statement. As mentioned before, there can be several statements inside a compound
statement, so let's look at them in turn.

Declarations
~~~~~~~~~~~~

The first statement is this:

.. code-block:: C

   int count;

which is not an instruction to do anything, but simply introduces a variable
to the program. It declares something whose name is count, and whose type
is ‘integer’; in C the keyword that declares integers is unaccountably shortened to
int. C has an idiosyncratic approach to these keywords with some having their
names spelled in full and some being shortened like int. At least int
has a meaning that is more or less intuitive; just wait until we
get on to static.

As a result of that declaration the compiler now knows that there is
something that will be used to store integral quantities, and that its name
is count. In C, all variables must be declared before they are used;
there is none of FORTRAN's implicit declarations. In a compound statement, all
the declarations must come first; they must precede any ‘ordinary’ statements and are
therefore somewhat special.

(Note for pedants: unless you specifically ask, the declaration of a variable like
count is also a definition. The distinction will later be seen to matter.)

Assignment statement
~~~~~~~~~~~~~~~~~~~~

Moving down the example we find a familiar thing, an assignment statement. This
is where the first value is assigned to the variable count, in this
case the value assigned is a constant whose value is zero. Prior to
the assignment, the value of count was undefined and unsafe to use. You
might be a little surprised to find that the assignment symbol (strictly speaking
an assignment operator) is a single = sign. This is not fashionable in modern
languages, but hardly a major blemish.

So far then, we have declared a
variable and assigned the value of zero to it. What next?

The while statement
~~~~~~~~~~~~~~~~~~~

Next is one of C's loop control statements, the while statement. Look
carefully at its form. The formal description of the while statement is this:

.. code-block:: C

   while(expression)
       statement

Is that what we have got? Yes it is. The bit that reads

.. code-block:: C

   count < 10

is a relational expression, which is an example of a valid expression, and
the expression is followed by a compound statement, which is a form of
valid statement. As a result, it fits the rules for a properly constructed
while statement.

What it does must be obvious to anyone who has written programs before.
For as long as the relationship count < 10 holds true, the body of
the loop is executed and the comparison repeated. If the program is ever
to end, then the body of the loop must do something that will
eventually cause the comparison to be false: of course it does.

There are just two statements in the body of the loop. The first
one is a function call, where the function show_message is invoked. A
function call is indicated by the name of the function followed by the
parentheses () which contain its argument list—if it takes no arguments, then you
provide none. If there were any arguments, they would be put between the
parentheses like this:

.. code-block:: C

   /* call a function with several arguments */
   function_name(first_arg, second_arg, third_arg);

and so on. The call of printf is another example. More is explained
in :ref:`functions`.

The last statement in the loop is another assignment statement. It adds one
to the variable count, so that the requirement for program to stop will eventually be met.

The return statement
~~~~~~~~~~~~~~~~~~~~

The last statement that is left to discuss is the return statement. As
it is written, it looks like another function call, but in fact the
rule is that the statement is written

.. code-block:: C

   return expression;

where the expression is optional. The example uses a common stylistic convention and
puts the expression into parentheses, which has no effect whatsoever.

The return causes a value to be returned from the current function to
its caller. If the expression is missing, then an unknown value is passed
back to the caller—this is almost certainly a mistake unless the function
returns void. Main wasn't declared with any type at all, unlike show_message,
so what type of value does it return? The answer is int.
There are a number of places where the language allows you to declare
things by default: the default type of functions is int, so it is
common to see them used in this way. An equivalent declaration for main
would have been

.. code-block:: C

   int main(){

and exactly the same results would have occurred.

You can't use the same feature to get a default type for
variables because their types must be provided explicitly.

What does the value returned from main mean, and where does it go?
In Old C, the value was passed back to the operating system or
whatever else was used to start the program running. In a UNIX-like
environment, the value of 0 meant ‘success’ in some way, any other value
(often -1) meant ‘failure’. The Standard has enshrined this, stating that 0 stands
for correct termination of the program. This does not mean that 0 is
to be passed back to the host environment, but whatever is the appropriate
‘success’ value for that system. Because there is sometimes confusion around this, you
may prefer to use the defined values EXIT_SUCCESS and EXIT_FAILURE instead,
which are defined in the header file <stdlib.h>. Returning from the main
function is the same as calling the library function exit with the return
value as an argument. The difference is that exit may be called from
anywhere in the program, and terminates it at that point, after doing some
tidying up activities. If you intend to use exit, you must include the
header file <stdlib.h>. From now on, we shall use exit rather than
returning from main.

Summary
"""""""


#. The main function returns an int value.

#. Returning from main is the same as calling the exit function, but exit
   can be called from anywhere in a program.

#. Returning 0 or EXIT_SUCCESS is the way of indicating success, anything else
   indicates failure.

Progress so far
~~~~~~~~~~~~~~~

This example program, although short, has allowed us to introduce several important language
features, amongst them:

#. Program structure

#. Comment

#. File inclusion

#. Function definition

#. Compound statements

#. Function calling

#. Variable declaration

#. Arithmetic

#. Looping


although of course none of this has been covered rigorously.

Some more programs
------------------

While we're still in the informal phase, let's look at two
more examples. You will have to work out for yourself what some of
the code does, but as new or interesting features appear, they will be
explained.


.. literalinclude:: ../src/example1.2/src/example1.2.c
   :language: c
   :linenos:

1.4.1. A program to find prime numbers


What was interesting in there? A few new points, perhaps. The program works
in a really stupid way: to see if a number is prime, it
divides that number by all the numbers between half its value and two — if
any divide without remainder, then the number isn't prime. The two
operators that you haven't seen before are the remainder operator %, and the
equality operator, which is a double equal sign ==. That last one is without
doubt the cause of more bugs in C programs than any other single factor.

The problem with the equality test is that wherever it can appear it
is also legal to put the single = sign. The first, ==, compares two things
to see if they are equal, and is generally what you need in fragments like these:

.. code-block:: C

   if(a == b)
   while (c == d)

The assignment operator = is, perhaps surprisingly, also legal in places like those, but
of course it assigns the value of the right-hand expression to whatever
is on the left. The problem is particularly bad if you are used
to the languages where comparison for equality is done with what C uses
for assignment. There's nothing that you can do to help, so start
getting used to it now. (Modern compilers do tend to produce warnings when
they think they have detected ‘questionable’ uses of assignment operators, but that is
a mixed blessing when your choice was deliberate.)

There is also the introduction for the first time of the if statement.
Like the while statement, it tests an expression to see if the expression
is true. You might have noticed that also like the while statement, the
expression that controls the if statement is in parentheses. That is always the
case: all of the conditional control of flow statements require a parenthesized expression
after the keyword that introduces them. The formal description of the if statement
goes like this:

.. code-block:: C

   if(expression)
       statement

   if(expression)
       statement
   else
       statement

showing that it comes in two forms. Of course, the effect is that
if the expression part is evaluated to be true, then the following statement
is executed. If the evaluation is false, then the following statement is not
executed. When there is an else part, the statement associated with it is
executed only if the evaluation gives a false result.

If statements have a famous problem. In the following piece of code, is
the statement-2 executed or not?

.. code-block:: C

    if(1 > 0)
            if(1 < 0)
                    statement-1
    else
            statement-2

The answer is that it is. Ignore the indentation (which is misleading). The
else could belong to either the first or second if, according to the
description of the if statement that has just been given, so an extra
rule is needed to make it unambiguous. The rule is simply that an
else is associated with the nearest else-less if above it. To make
the example work the way that the indentation implied, we have to invoke
a compound statement:

.. code-block:: C

    if(1 > 0){
            if(1 < 0)
                    statement-1
    }
    else
            statement-2

Here, at least, C adheres to the practice used by most other languages.
In fact a lot of programmers who are used to languages where the
problem exists have never even realized that it is there—they just thought
that the disambiguating rule was ‘obvious’. Let's hope that everyone feels that way.

The division operators
~~~~~~~~~~~~~~~~~~~~~~

The division operators are the division operator /, and the remainder operator %. Division does
what you would expect, except that when it is applied to integer operands
it gives a result that is truncated towards zero. For example, 5/2
gives 2, 5/3 gives 1. The remainder operator is the way to
get the truncated remainder. 5%2 gives 1, 5%3 gives 2. The
signs of the remainder and quotient depend on the divisor and dividend in a way that is defined in the Standard and shown in :ref:`variables`.

An example performing input
~~~~~~~~~~~~~~~~~~~~~~~~~~~

It's useful to be able to perform input as well as to
write programs that print out more or less interesting lists and tables. The
simplest of the library routines (and the only one that we'll look
at just now) is called getchar. It reads single characters from the program's
input and returns an integer value. The value returned is a coded
representation for that character and can be used to print the same character
on the program output. It can also be compared against character constants or
other characters that have been read, although the only test that makes sense
is to see if both characters are the same. Comparing for greater or
less than each other is not portable in general; there is no guarantee
that 'a' is less than 'b', although on most common systems that would
be the case. The only guarantee that the Standard makes is that the
codes for '0' through to '9' will always be consecutive. Here is one example.


.. literalinclude:: ../src/example1.3/src/example1.3.c
   :language: c
   :linenos:

There are two interesting points in there. The first is to notice that
at the end of each line of input read, the character represented by

.. code-block:: C

    '\n'

(a character constant) will be seen. This just like the way that the
same symbol results in a new line when printf prints it. The model
of I/O used by C is not based on a line by
line view of the world, but character by character instead; if you choose
to think in a line-oriented way, then '\n' allows you to mark
the end of each ‘line’. Second is the way that %c is used
to output a character by printf, when it appears on the output as
a character. Printing it with %d prints the same variable, but displays the
integer value used by your program to represent the character.

If you try
that program out, you may find that some systems do not pass characters
one by one to a program, but make you type a whole line
of input first. Then the whole line is made available as input, one
character at a time. Beginners have been known to be confused: the program
is started, they type some input, and nothing comes back. This behaviour is
nothing to do with C; it depends on the computer and operating system in use.

Simple arrays
~~~~~~~~~~~~~

The use of arrays in C is often a problem for the beginner.
The declaration of arrays isn't too difficult, especially the one-dimensional ones,
but a constant source of confusion is the fact that their indices always
count from 0. To declare an array of 5 ints, the declaration would look like this:

.. code-block:: C

     int something[5];

In array declarations C uses square brackets, as you can see. There is
no support for arrays with indices whose ranges do not start at 0
and go up; in the example, the valid array elements are something[0]
to something[4]. Notice very carefully that something[5] is not a valid
array element.

This program reads some characters from its input, sorts them into the order
suggested by their representation, then writes them back out. Work out what it
does for yourself; the algorithm won't be given much attention in the
explanation which follows.

.. literalinclude:: ../src/example1.4/src/example1.4.c
   :language: c
   :linenos:


You might note that the defined constant ARSIZE is used everywhere instead of
the actual array size. Because of that, to change the maximum number of
characters that can be sorted by this program simply involves a change to
one line and then re-compiling. Not so obvious but critical to the
safety of the program is the detection of the array becoming full. Look
carefully; you'll find that the program stops when element ARSIZE-1 has
been filled. That is because in an N element array, only elements 0
through to N-1 are available (giving N in total).

Unlike some other languages it is unlikely that you will be told if
you ‘run off’ the end of an array in C. It results in
what is known as undefined behaviour on the part of your program, this
generally being to produce obscure errors in the future. Most skilled programmers avoid
this happening by rigorous testing to make sure either that it can't
happen given the particular algorithm in use, or by putting in an explicit
test before accessing a particular member of an array. This is a common
source of run-time errors in C; you have been warned.

Summary

#. Arrays always number from 0; you have no choice.

#. A n-element array has members which number from 0 to
   n-1 only. Element n does not exist and to access it
   is a big mistake.

Terminology
-----------

In C programs there are two distinct types of things: things used to
hold values and things that are functions. Instead of having to refer to
them jointly with a clumsy phrase that maintains the distinction, we think that
it's useful to call them both loosely ‘objects’. We do quite a
lot of that later, because it's often the case that they follow
more or less the same rules. Beware though, that this isn't quite
what the Standard uses the term to mean. In the Standard, an ‘object’
is explicitly a region of allocated storage that is used to represent a
value and a function is something different; this leads to the Standard often
having to say ‘… functions and objects …’. Because we don't think that it
leads to too much confusion and does improve the readability of the text
in most cases, we will continue to use our looser interpretation of object
to include functions and we will explicitly use the terms ‘data objects’ and
‘functions’ when the distinction is appropriate.

Be prepared to find this slight difference in meaning if you do read the Standard

Summary
-------

This chapter has introduced many of the basics of the language although informally.
Functions, in particular, form the basic building block for C. :ref:`functions` provides
a full description of these fundamental objects, but you should by now understand
enough about them to follow their informal use in the intervening material.

Although
the idea of library functions has been introduced, it has not been possible
to illustrate the extent of their importance to the C application programmer. The
Standard Library, described in :ref:`libraries`, is extremely important, both in the way
that it helps to improve the portability of programs intended for general use
and also in the aid to productivity that these useful functions can provide.

The use of variables, expressions and arithmetic are soon to be described in
great detail. As this chapter has shown, at a simple level, C differs
little from most other modern programming languages.

Only the use of structured data types still remains to be introduced, although
arrays have had a very brief airing.

Exercises
---------

Exercise 1.1. Type in and test Example 1.1 on your system.

Exercise 1.2. Using Example 1.2 as a pattern, write a program
that prints prime pairs — a pair of prime numbers that differ by 2,
for example 11 and 13, 29 and 31. (If you can detect a
pattern between such pairs, congratulations! You are either a genius or just wrong.)

Exercise 1.3. Write a function that returns an integer: the decimal value
of a string of digits that it reads using getchar. For example, if
it reads 1 followed by 4 followed by 6, it will return the
number 146. You may make the assumption that the digits 0–9 are
consecutive in the computer's representation (the Standard says so) and that the
function will only have to deal with valid digits and newline, so error
checking is not needed.

Exercise 1.4. Use the function that you just wrote to read a
sequence of numbers. Put them into an array declared in main, by repeatedly
calling the function. Sort them into ascending numerical order, then print the sorted
list.

Exercise 1.5. Again using the function from Exercise 1.3, write
a program that will read numbers from its input, then print them out
in binary, decimal and hexadecimal form. You should not use any features of
printf apart from those mentioned in this chapter (especially the hexadecimal output format!).
You are expected to work out what digits to print by calculating each
one in turn and making sure that they are printed in the right
order. This is not particularly difficult, but it is not trivial either.
