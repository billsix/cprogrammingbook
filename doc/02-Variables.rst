.. _variables:

Variables & arithmetic
======================


Some fundamentals
-----------------

Here is where we start to look in detail at the
bits that the last chapter chose to sweep under the carpet
while it did its ‘Instant C’ introduction. The problem is, of
course, the usual one of trying to introduce enough of the
language to let you get a feel for what it's
all about, without drowning beginners in a froth of detail that
isn't essential at the time.

Because this is a lengthy
chapter, and because it deliberately chooses to cover some subtle problems
that are often missed out in introductory texts, you should make
sure that you are in the right mood and proper frame
of mind to read it.

The weary brain may find that
the breaks for exercises are useful. We strongly recommend that you
do actually attempt the exercises on the way through. They help
to balance the weight of information, which otherwise turns into an
indigestible lump.

It's time to introduce some of the fundamentals.

The alphabet of C
-----------------

This is an interesting area; alphabets are important. All the same
, this is the one part of this chapter that you can
read superficially first time round without missing too much. Read it
to make sure that you've seen the contents once, and
make a mental note to come back to it later on.


Basic Alphabet
~~~~~~~~~~~~~~

Few computer languages bother to define their alphabet rigorously. There's
usually an assumption that the English alphabet augmented by a sprinkling
of more or less arbitrary punctuation symbols will be available in
every environment that is trying to support the language. The assumption
is not always borne out by experience. Older languages suffer less
from this sort of problem, but try sending C programs by
Telex or restrictive e-mail links and you'll understand the
difficulty.

The C89 Standard talks about two different character sets: the one
that programs are written in and the one that programs execute
with. This is basically to allow for different systems for compiling
and execution, which might use different ways of encoding their characters.
It doesn't actually matter a lot except when you are
using character constants in the preprocessor, where they may not have
the same value as they do at execution time. This behavior
is implementation-defined, so it must be documented. Don't worry about it yet.

The C89 Standard requires that an alphabet of 96 symbols is available for C as follows:::

     a b c d e f g h i j k l m n o p q r s t u v w x y z

     A B C D E F G H I J K L M N O P Q R S T U V W X Y Z

     0 1 2 3 4 5 6 7 8 9

     ! " # % & ' ( ) * + , - . /

     : ; < = > ? [ \ ] ^ _ { | } ~

     space, horizontal and vertical tab

     form feed, newline

Table 2.1. The Alphabet of C

It turns out that most of the commonly used computer alphabets
contain all the symbols that are needed for C with a
few notorious exceptions. The C alphabetic characters shown below are missing
from the International Standards Organization ISO 646 standard 7-bit character
set, which is as a subset of all the widely used computer alphabets.

    # [ \ ] ^ { | } ~

To cater for systems that can't provide the full 96
characters needed by C, the C89 Standard specifies a method of using
the ISO 646 characters to represent the missing few; the technique
is the use of trigraphs.

Trigraphs
~~~~~~~~~~~~~~
Trigraphs are a sequence of three ISO 646 characters that get
treated as if they were one character in the C alphabet;
all of the trigraphs start with two question marks ?? which helps
to indicate that ‘something funny’ is going on. Table 2.1
below shows the trigraphs defined in the C89 Standard.::

    C character 	Trigraph
    # 	??=
    [ 	??(
    ] 	??)
    { 	??<
    } 	??>
    \ 	??/
    | 	??!
    ~ 	??-
    ^ 	??'

Table 2.2. Trigraphs

As an example, let's assume that your terminal doesn't
have the # symbol. To write the preprocessor line

.. code-block:: C

   #define MAX     32767

isn't possible; you must use trigraph notation instead:

.. code-block:: C

   ??=define MAX   32767

Of course trigraphs will work even if you do have a
# symbol; they are there to help in difficult circumstances more than
to be used for routine programming.

The ? ‘binds to the right’, so in any sequence of repeated
?s, only the two at the right could possibly be part
of a trigraph, depending on what comes next—this disposes of
any ambiguity.

It would be a mistake to assume that programs written to
be highly portable would use trigraphs ‘in case they had to
be moved to systems that only support ISO 646’. If your
system can handle all 96 characters in the C alphabet, then
that is what you should be using. Trigraphs will only be
seen in restricted environments, and it is extremely simple to write
a character-by-character translator between the two representations. However, all
compilers that conform to the C89 Standard will recognize trigraphs when they
are seen.

Trigraph substitution is the very first operation that a compiler performs
on its input text.


Multi-byte Characters
~~~~~~~~~~~~~~~~~~~~~

Support for multi-byte characters is new in the C89 Standard. Why?

A very large proportion of day-to-day computing involves data
that represents text of one form or another. Until recently, the
rather chauvinist computing industry has assumed that it is adequate to
provide support for about a hundred or so printable characters (hence
the 96 character alphabet of C), based on the requirements of
the English language—not surprising, since the bulk of the development
of commercial computing has been in the US market. This alphabet
(technically called the repertoire) fits conveniently into 7 or 8 bits
of storage, which is why the US-ASCII character set standard
and the architecture of mini and microcomputers both give very heavy
emphasis to the use of 8-bit bytes as the basic
unit of storage.

C also has a byte-oriented approach to
data storage. The smallest individual item of storage that can be
directly used in C is the byte, which is defined to
be at least 8 bits in size. Older systems or architectures
that are not designed explicitly to support this may incur a
performance penalty when running C as a result, although there are
not many that find this a big problem.

Perhaps there was
a time when the English alphabet was acceptable for data processing
applications worldwide—when computers were used in environments where the users
could be expected to adapt—but those days are gone. Nowadays
it is absolutely essential to provide for the storage and processing
of textual material in the native alphabet of whoever wants to
use the system. Most of the US and Western European language
requirements can be squeezed together into a character set that still
fits in 8 bits per character, but Asian and other languages simply cannot.

There are two general ways of extending character sets. One is
to use a fixed number of bytes (often two) for every
character. This is what the wide character support in C is
designed to do. The other method is to use a shift-in
shift-out coding scheme; this is popular over 8-bit
communication links. Imagine a stream of characters that looks like:::

    a b c <SI> a b g <SO> x y

where <SI> and <SO> mean ‘switch to Greek’ and ‘switch back
to English’ respectively. A display device that agreed to use that
method might well then display a, b, c, alpha, beta, gamma,
x and y. This is roughly the scheme used by the
shift-JIS Japanese standard, except that once the shift-in has
been seen, pairs of characters together are used as the code
for a single Japanese character. Alternative schemes exist which use more
than one shift-in character, but they are less common.

The C89 Standard now allows explicitly for the use of extended character
sets. Only the 96 characters defined earlier are used for the
C part of a program, but in comments, strings, character constants
and header names (these are really data, not part of the
program as such) extended characters are permitted if your environment supports
them. The C89 Standard lays down a number of pretty obvious rules
about how you are allowed to use them which we will
not repeat here. The most significant one is that a byte
whose value is zero is interpreted as a null character irrespective
of any shift state. That is important, because C uses a
null character to indicate the end of strings and many library
functions rely on it. An additional requirement is that multi-byte sequences
must start and end in the initial shift state.

The char
type is specified by the C89 Standard as suitable to hold the
value of all of the characters in the ‘execution character set’,
which will be defined in your system's documentation. This means
that (in the example above) it could hold the value of
‘a’ or ‘b’ or even the "switch to Greek" character itself.
Because of the shift-in shift-out mechanism, there would be
no difference between the value stored in a char that was
intended to represent ‘a’ or the Greek ‘alpha’ character. To do
that would mean using a different representation - probably needing more than
8 bits, which on many systems would be too big for
a char. That is why the C89 Standard introduces the wchar_ttype.
To use this, you must include the <stddef.h> header, because
wchar_t is simply defined as an alternative name for one
of C's other types. We discuss it further in Section 2.8.

Summary
~~~~~~~

#. C requires at least 96 characters in the source program
   character set.

#. Not all character sets in common use can stretch
   to 96 characters, trigraphs allow the basic
   ISO 646 character set to be used (at a pinch).

#. Multi-byte character support has been added by the
   C89 Standard, with support for

   #. Shift-encoded multi-byte characters, which can be squeezed
      into ‘ordinary’ character arrays, so still have char type.

   #. Wide characters, each of which may use more storage than
      a regular character. These usually have a different type from char.



The Textual Structure of Programs
---------------------------------

Program Layout
~~~~~~~~~~~~~~

The examples so far have used the sort of indentation and
line layout that is common in languages belonging to the same
family as C. They are ‘free format’ languages and you are
expected to use that freedom to lay the program out in
a way that enhances its readability and highlights its logical structure.
Space (including horizontal tab) characters can be used for indentation anywhere
except in identifiers or keywords without any effect on the meaning
of the program. New lines work in the same way as
space and tab except on preprocessor command lines, which have a
line-by-line structure.

If a line is getting too long for comfort there are
two things you can do. Generally it will be possible to
replace one of the spaces by a newline and use simply
two lines instead, as this example shows.

.. code-block:: C

    /* a long line */
    a = fred + bill * ((this / that) * sqrt(3.14159));
    /* the same line */
    a = fred + bill *
            ((this / that) *
            sqrt(3.14159));

If you're unlucky it may not be possible to break
the lines like that. The preprocessor suffers most from the problem,
because of its reliance on single-line ‘statements’. To help, it's
useful to know that the sequence ‘backslash newline’ becomes invisible
to the C translation system. As a result, the sequence is
valid even in unusual places such as the middle of identifiers,
keywords, strings and so on. Only trigraphs are processed before this step.

.. code-block:: C

    /*
     * Example of the use of line joining
     */
    #define IMPORTANT_BUT_LONG_PREPROCESSOR_TEXT \
    printf("this is effectively all ");\
    printf("on a single line ");\
    printf("because of line-joining\n");

The only time that you might want to use this way
of breaking lines (outside of preprocessor control lines) is to prevent
long strings from disappearing off the right-hand side of a
program listing. New lines are not permitted inside strings and character
constants, so you might think that the following is a good idea.

.. code-block:: C

    /* not a good way of folding a string */
    printf("This is a very very very\
    long string\n");

That will certainly work, but for strings it is preferable to
make use of the string-joining feature introduced by the C89 Standard:

.. code-block:: C

    /* This string joining will not work in pre-C89 */
    printf("This is a very very very"
           "long string\n");

The second example allows you to indent the continuation portion of
the string without changing its meaning; adding indentation in the first
example would have put the indentation into the string.

Incidentally, both examples contain what is probably a mistake. There is
no space in front of the ‘long’ in the continuation string,
which will contain the sequence ‘verylong’ as a result. Did you notice?

Comment
~~~~~~~

Comment, as has been said already, is introduced by the character
pair /\* and terminated by \*/. It is translated into a single space
wherever it occurs and so it follows exactly the same rules
that spaces do. It's important to realize that it doesn't
simply disappear, which it used to do in pre-C89,
and that it is not possible to put comment into strings
or character constants. Comment in such a place becomes part of
the string or constant:

.. code-block:: C

    /*"This is comment"*/
    "/*The quotes mean that this is a string*/"

pre-C89 was a bit hazy about what the deletion of
comment implied. You could argue that

.. code-block:: C

    int/**/egral();

should have the comment deleted and so be taken by the
compiler to be a call of a function named integral. The
C89 Standard C rule is that comment is to be read as
if were a space, so the example must be equivalent to

.. code-block:: C

    int egral();

which declares a function egral that returns type int.

Translation phases
~~~~~~~~~~~~~~~~~~

The various character translation, line joining, comment recognition and other early
phases of translation must be specified to occur in a certain
order. The C89 Standard says that the translation is to proceed as
if the phases occurred in this order (there are more phases,
but these are the important ones):

    Trigraph translation.
    Line joining.
    Translate comment to space (but not in strings or character constants). At this stage, multiple white spaces may optionally be condensed into one.
    Translate the program.

Each stage is completed before the next is started.

Keywords and identifiers
------------------------

After covering the underlying alphabet, we can look at more interesting
elements of C. The most obvious of the language elements are
keywords and identifiers; their forms are identical (although their meanings are
different).

Keywords
~~~~~~~~

C keeps a small set of keywords for its own use.
These keywords cannot be used as identifiers in the program — a
common restriction with modern languages. Where users of pre-C89 may
be surprised is in the introduction of some new keywords; if
those names were used as identifiers in previous programs, then the
programs will have to be changed. It will be easy to
spot, because it will provoke your compiler into telling you about
invalid names for things. Here is the list of keywords used
in C89 Standard C; you will notice that none of them use upper-case letters.


+--------------+-----------+--------------+--------------+
| auto         | double    | int          | struct       |
+--------------+-----------+--------------+--------------+
| break        | else      | long         | switch       |
+--------------+-----------+--------------+--------------+
| case         | enum      | register     | typedef      |
+--------------+-----------+--------------+--------------+
| char         | extern    | return       | union        |
+--------------+-----------+--------------+--------------+
| const        | float     | short        | unsigned     |
+--------------+-----------+--------------+--------------+
| continue     | for       | signed       | void         |
+--------------+-----------+--------------+--------------+
| default      | goto      | sizeof       | volatile     |
+--------------+-----------+--------------+--------------+
| do           | if        | static       | while        |
+--------------+-----------+--------------+--------------+


Table 2.3. Keywords

The new keywords that are likely to surprise old programmers are:
const, signed, void and volatile (although void has been around for
a while). Eagle eyed readers may have noticed that some implementations
of C used to use the keywords entry, asm, and fortran.
These are not part of the C89 Standard, and few will mourn them.

Identifiers
~~~~~~~~~~~

Identifier is the fancy term used to mean ‘name’. In C,
identifiers are used to refer to a number of things: we've
already seen them used to name variables and functions. They
are also used to give names to some things we haven't
seen yet, amongst which are labels and the ‘tags’ of
structures, unions, and enums.

The rules for the construction of identifiers
are simple: you may use the 52 upper and lower case
alphabetic characters, the 10 digits and finally the underscore ‘_’, which is
considered to be an alphabetic character for this purpose. The only
restriction is the usual one; identifiers must start with an alphabetic
character.

Although there is no restriction on the length of identifiers
in the C89 Standard, this is a point that needs a bit
of explanation. In pre-C89, as in C89, there has
never been any restriction on the length of identifiers. The problem
is that there was never any guarantee that more than a
certain number of characters would be checked when names were compared
for equality—in pre-C89 this was eight characters, in C89 Standard
C this has changed to 31.

So, practically speaking, the new
limit is 31 characters—although identifiers may be longer, they must
differ in the first 31 characters if you want to be
sure that your programs are portable. The C89 Standard allows for implementations
to support longer names if they wish to, so if you
do use longer names, make sure that you don't rely
on the checking stopping at 31.

One of the most controversial
parts of the C89 Standard is the length of external identifiers. External
identifiers are the ones that have to be visible outside the
current source code file. Typical examples of these would be library
routines or functions which have to be called from several different
source files.

The C89 Standard chose to stay with the old restrictions
on these external names: they are not guaranteed to be different
unless they differ from each other in the first six characters.
Worse than that, upper and lower case letters may be treated
the same!

The reason for this is a pragmatic one: the
way that most C compilation systems work is to use operating
system specific tools to bind library functions into a C program.
These tools are outside the control of the C compiler writer,
so the C89 Standard has to impose realistic limits that are likely
to be possible to meet. There is nothing to prevent any
specific implementation from giving better limits than these, but for maximum
portability the six monocase characters must be all that you expect.
The C89 Standard warns that it views both the use of only
one case and any restriction on the length of external names
to less than 31 characters as obsolescent features. A later standard
may insist that the restrictions are lifted; let's hope that it is soon.

Declaration of variables
------------------------

You may remember that in :ref:`intro` we said that you
have to declare the names of things before you can use
them (the only exceptions to this rule are the names of
functions returning int, because they are declared by default, and the
names of labels). You can do it either by using a
declaration, which introduces just the name and type of something but
allocates no storage, or go further by using a definition, which
also allocates the space used by the thing being declared.

The
distinction between declaration and definition is an important one, and it
is a shame that the two words sound alike enough to
cause confusion. From now on they will have to be used
for their formal meaning, so if you are in doubt about
the differences between them, refer back to this point.

The rules
about what makes a declaration into a definition are rather complicated,
so they will be deferred for a while. In the meantime,
here are some examples and rule-of-thumb guidelines which will
work for the examples that we have seen so far, and
will do for a while to come.

.. code-block:: C

    /*
    * A function is only defined if its body is given
    * so this is a declaration but not a definition
    */

    int func_dec();

    /*
    * Because this function has a body, it is also
    * a definition.
    * Any variables declared inside will be definitions,
    * unless the keyword 'extern' is used.
    * Don't use 'extern' until you understand it!
    */

    int def_func(){
         float f_var;            /* a definition */
         int counter;            /* another definition */
         int rand_num();     /* declare (but not define) another function */

         return(0);
    }

Exercise 2.1. Why are trigraphs used?

Exercise 2.2. When would you expect to find them in use, and when not?

Exercise 2.3. When is a newline not equivalent to a space or tab?

Exercise 2.4. When would you see the sequence of ‘backslash newline’ in use?

Exercise 2.5. What happens when two strings are put side by side?

Exercise 2.6. Why can't you put one piece of comment inside another one? (This prevents the technique of ‘commenting out’ unused bits of program, unless you are careful.)

Exercise 2.7. What are the longest names that may safely be used for variables?

Exercise 2.8. What is a declaration?

Exercise 2.9. What is a definition?

Now we go on to look at the type of variables and expressions.

Real types
----------

It's easier to deal with the real types first because
there's less to say about them and they don't
get as complicated as the integer types. The C89 Standard breaks new
ground by laying down some basic guarantees on the precision and
range of the real numbers; these are found in the header
file float.h which is discussed in detail in :ref:`libraries`.
For some users this is extremely important information, but it is
of a highly technical nature and is likely only to be
fully understood by numerical analysts.

The varieties of real numbers are these:

- float

- double

- long double

Each of the types gives access to a particular way of
representing real numbers in the target computer. If it only has
one way of doing things, they might all turn out to
be the same; if it has more than three, then C
has no way of specifying the extra ones. The type float
is intended to be the small, fast representation corresponding to what
FORTRAN would call REAL. You would use double for extra precision,
and long double for even more.

The main points of interest
are that in the increasing ‘lengths’ of float, double and long
double, each type must give at least the same range and
precision as the previous type. For example, taking the value in
a double and putting it into a long double must result
in the same value.

There is no requirement for the three
types of ‘real’ variables to differ in their properties, so if
a machine only has one type of real arithmetic, all of
C's three types could be implemented in the same way.
None the less, the three types would be considered to be
different from the point of view of type checking; it would
be ‘as if’ they really were different. That helps when you
move the program to a system where the three types really
are different—there won't suddenly be a set of warnings
coming out of your compiler about type mismatches that you didn't
get on the first system.

In contrast to more ‘strongly
typed’ languages, C permits expressions to mix all of the scalar
types: the various flavors of integers, the real numbers and also
the pointer types. When an expression contains a mixture of arithmetic
(integer and real) types there are implicit conversions invoked which can
be used to work out what the overall type of the
result will be. These rules are quite important and are known
as the usual arithmetic conversions; it will be worth committing them
to memory later. The full set of rules is described in
Section 2.8; for the moment, we will investigate only the
ones that involve mixing float, double and long double to see
if they make sense.

The only time that the conversions are needed is when two
different types are mixed in an expression, as in the example below:

.. literalinclude:: ../src/example2.1/src/example2.1.c
   :language: c
   :linenos:

Example 2.1

There are a lot of forced conversions in that example. Getting
the easiest of them out of the way first, let's
look at the assignments of the constant value 1 to each
of the variables. As the section on constants will point out,
that 1 has type int, i.e. it is an integer,
not a real constant. The assignment converts the integer value to
the appropriate real type, which is easy to cope with.

The interesting conversions come next. The first of them is on the line

.. code-block:: C

    d_var = d_var + f_var;

What is the type of the expression involving the + operator? The
answer is easy when you know the rules. Whenever two different
real types are involved in an expression, the lower precision type
is first implicitly converted to the higher precision type and then
the arithmetic is performed at that precision. The example involves both
a double and a float, so the value of f_var
is converted to type double and is then added to the
value of the double d_var. The result of the expression
is naturally of type double too, so it is clearly of
the correct type to assign to d_var.

The second of
the additions is a little bit more complicated, but still perfectly
O.K. Again, the value of f_var is converted and
the arithmetic performed with the precision of double, forming the sum
of the two variables. Now there's a problem. The result
(the sum) is double, but the assignment is to a long
double. Once again the obvious procedure is to convert the lower
precision value to the higher one, which is done, and then
make the assignment.

So we've taken the easy ones. The
difficult thing to see is what to do when forced to
assign a higher precision result to a lower precision destination. In
those cases it may be necessary to lose precision, in a
way specified by the implementation. Basically, the implementation must specify whether
and in what way it rounds or truncates. Even worse, the
destination may be unable to hold the value at all. The
C89 Standard says that in these cases loss of precision may occur;
if the destination is unable to hold the necessary value—say
by attempting to add the largest representable number to itself—then
the behavior is undefined, your program is faulty and you can
make no predictions whatsoever about any subsequent behavior.

It is no
mistake to re-emphasize that last statement. What the C89 Standard means
by undefined behavior is exactly what it says. Once a program's
behavior has entered the undefined region, absolutely anything can happen.
The program might be stopped by the operating system with an
appropriate message, or just as likely nothing observable would happen and
the program be allowed to continue with an erroneous value stored
in the variable in question. It is your responsibility to prevent
your program from exhibiting undefined behavior. Beware!

Summary of real arithmetic


#. Arithmetic with any two real types is done at the
   highest precision of the members involved.

#. Assignment involves loss of precision if the receiving type has
   a lower precision than the value being assigned to it.

#. Further conversions are often implied when expressions mix other types,
   but they have not been described yet.

Printing real numbers
~~~~~~~~~~~~~~~~~~~~~

The usual output function, printf, can be used to format real
numbers and print them. There are a number of ways to
format these numbers, but we'll stick to just one for
now. Table 2.4 below shows the appropriate format description for
each of the real types.

+------------------------+------------+
| Type                   | Format     |
+========================+============+
| float                  | %f         |
+------------------------+------------+
| double                 | %f         |
+------------------------+------------+
| long double            | %Lf        |
+------------------------+------------+


Table 2.4. Format codes for real numbers

Here's an example to try:

.. literalinclude:: ../src/example2.2/src/example2.2.c
   :language: c
   :linenos:

Example 2.2

Try that example on your own computer to see what results you get.

Exercise 2.10. Which type of variable can hold the largest range of values?

Exercise 2.11. Which type of variable can store values to the greatest precision?

Exercise 2.12. Are there any problems possible when assigning a float or double to a double or long double?

Exercise 2.13. What could go wrong when assigning, say, a long double to a double?

Exercise 2.14. What predictions can you make about a program showing ‘undefined behavior’?


Integral types
--------------

The real types were the easy ones. The rules for the
integral types are more complicated, but still tolerable, and these rules
really should be learned. Fortunately, the only types used in C
for routine data storage are the real and integer types, or
structures and arrays built up from them. C doesn't have
special types for character manipulation or the handling of logical (boolean)
quantities, but uses the integral types instead. Once you know the
rules for the reals and the integers you know them all.

We will start by looking at the various types and then the conversion rules.

Plain integers
~~~~~~~~~~~~~~

There are two types (often called ‘flavors’) of integer variables. Other
types can be built from these, as we'll see, but
the plain undecorated ints are the base. The most obvious of
the pair is the ‘signed’ int, the less obvious is its
close relative, the unsigned int. These variables are supposed to be
stored in whatever is the most convenient unit for the machine
running your program. The int is the natural choice for undemanding
requirements when you just need a simple integral variable, say as
a counter in a short loop. There isn't any guarantee
about the number of bits that an int can hold, except
that it will always be 16 or more. The standard header
file <limits.h> details the actual number of bits available in
a given implementation.

Curiously, pre-C89 had no guarantee whatsoever about
the length of an int, but consensus and common practice has
always assumed at least 16 bits.

Actually, <limits.h> doesn't
quite specify a number of bits, but gives maximum and minimum
values for an int instead. The values it gives are 32767
and -32767 which implies 16 bits or more, whether ones or
twos complement arithmetic is used. Of course there is nothing to
stop a given implementation from providing a greater range in either
direction.

The range specified in the C89 Standard for an unsigned int
is 0 to at least 65535, meaning that it cannot be
negative. More about these shortly.

If you aren't used to
thinking about the number of bits in a given variable, and
are beginning to get worried about the portability implications of this
apparently machine-dependent concern for the number of bits, then you're
doing the right thing. C takes portability seriously and actually
bothers to tell you what values and ranges are guaranteed to
be safe. The bit-wise operators encourage you to think about the
number of bits in a variable too, because they give direct
access to the bits, which you manipulate one by one or
in groups. Almost paradoxically, the overall result is that C programmers
have a healthy awareness of portability issues which leads to more
portable programs. This is not to say that you can't
write C programs that are horribly non-portable!

Character variables
~~~~~~~~~~~~~~~~~~~

A bit less obvious than int is the other of the
plain integral types, the char. It's basically just another sort
of int, but has a different application. Because so many C
programs do a lot of character handling, it's a good
idea to provide a special type to help, especially if the
range provided by an int uses up much more storage than
is needed by characters. The limits file tells us that three
things are guaranteed about char variables: they have at least 8
bits, they can store a value of at least +127, and
the minimum value of a char is zero or lower. This
means that the only guaranteed range is 0–127. Whether or
not char variables behave as signed or unsigned types is implementation
defined.

In short, a character variable will probably take less storage than
an int and will most likely be used for character manipulation.
It's still an integer type though, and can be used
for arithmetic, as this example shows.

.. literalinclude:: ../src/example2.3/src/example2.3.c
   :language: c
   :linenos:

Example 2.3

Running that program is left as an exercise for the easily
amused. If you are bothered about where CHAR_MIN and CHAR_MAX
come from, find limits.h and read it.

Here's a more enlightening example. It uses character constants, which
are formed by placing a character in single quotes:

.. code-block:: C

    'x'

Because of the rules of arithmetic, the type of this sort
of constant turns out to be int, but that doesn't
matter since their value is always small enough to assign them
to char variables without any loss of precision. (Unfortunately, there is
a related version where that guarantee does not hold. Ignore it
for the moment.) When a character variable is printed using the
%c format with printf, the appropriate character is output. You can
use %d, if you like, to see what integer value is
used to represent the character. Why %d? Because a char is
just another integral type.

It's also useful to be able to read characters into
a program. The library function getchar is used for the job.
It reads characters from the program's standard input and returns
an int value suitable for storing into a char. The int
value is for one reason only: not only does getchar return
all possible character values, but it also returns an extra value
to indicate that end-of-input has been seen. The range
of a char might not be enough to hold this extra
value, so the int has to be used.

The following program reads its input and counts the number of
commas and full stops that it sees. On end-of-input,
it prints the totals.

.. literalinclude:: ../src/example2.4/src/example2.4.c
   :language: c
   :linenos:

Example 2.4

The two features of note in that example were the multiple
assignment to the two counters and the use of the defined
constant EOF. EOF is the value returned by getchar on end
of input (it stands for End Of File), and is defined
in <stdio.h>. The multiple assignment is a fairly common feature
of C programs.

Another example, perhaps. This will either print out the whole lower
case alphabet, if your implementation has its characters stored consecutively, or
something even more interesting if they aren't. C doesn't
make many guarantees about the ordering of characters in internal form,
so this program produces non-portable results!


.. literalinclude:: ../src/example2.5/src/example2.5.c
   :language: c
   :linenos:

Example 2.5

Yet again this example emphasizes that a char is only another
form of integer variable and can be used just like any
other form of variable. It is not a ‘special’ type with
its own rules.

The space saving that a char offers when
compared to an int only becomes worthwhile if a lot of
them are being used. Most character-processing operations involve the use
of not just one or two character variables, but large arrays
of them. That's when the saving can become noticeable: imagine
an array of 1024 ints. On a lot of common machines
that would eat up 4096 8-bit bytes of storage, assuming
the common length of 4 bytes per int. If the computer
architecture allows it to be done in a reasonably efficient way,
the C implementer will probably have arranged for char variables to
be packed one per byte, so the array would only use
1024 bytes and the space saving would be 3072 bytes.

Sometimes it doesn't matter whether or not a program tries
to save space; sometimes it does. At least C gives you
the option of choosing an appropriate type.

More complicated types
~~~~~~~~~~~~~~~~~~~~~~

The last two types were simple, in both their declaration and
subsequent use. For serious systems programming they just aren't adequate
in the precision of control over storage that they provide and
the behavior that they follow. To correct this problem, C provides
extra forms of integral types, split into the categories of signed
and unsigned. (Although both these terms are reserved words, they will
also be used as adjectives.) The difference between the two types
is obvious. Signed types are those that are capable of being
negative, the unsigned types cannot be negative at any time. Unsigned
types are usually used for one of two reasons: to get
an extra bit of precision, or when the concept of being
negative is simply not present in the data that is being
represented. The latter is by far the better reason for choosing
them.

Unsigned types also have the special property of never overflowing in
arithmetic. Adding 1 to a signed variable that already contains the
maximum possible positive number for its type will result in overflow,
and the program's behavior becomes undefined. That can never happen
with unsigned types, because they are defined to work ‘modulo one
greater than the maximum number that they can hold’. What this
means is best illustrated by example:


.. literalinclude:: ../src/example2.6/src/example2.6.c
   :language: c
   :linenos:

Example 2.6

Assuming that the variable x is stored in 16 bits, then
its range of values will be 0–65535 and that sequence
will be printed endlessly. The program can't terminate: the test

.. code-block:: C

    x >= 0

must always be true for an unsigned variable.

For both the signed and unsigned integral types there are three
subtypes: short, ordinary and long. Taking those into account, here is
a list of all of the possible integral types in C,
except for the character types:

- unsigned short int

- unsigned int

- unsigned long int

- signed short int

- signed int

- signed long int

In the last three, the signed keyword is unnecessary because the
int types are signed types anyway: you have to say unsigned
to get anything different. It's also permissible, but not recommended,
to drop the int keyword from any of those declarations provided
that there is at least one other keyword present—the int
will be ‘understood’ to be present. For example long is equivalent
to signed long int. The long and short kinds give you
more control over the amount of space used to store variables.
Each has its own minimum range specified in <limits.h> which
in practice means at least 16 bits in a short and
an int, and at least 32 bits in a long, whether
signed or unsigned. As always, an implementation can choose to give
you more bits than the minimum if it wants to. The
only restriction is that the limits must be equaled or bettered,
and that you don't get more bits in a shorter
type than a longer one (not an unreasonable rule).

The only character types are the signed char and the unsigned
char. The difference between char and int variables is that, unless
otherwise stated, all ints are signed. The same is not true
for chars, which are signed or unsigned depending on the implementer's
choice; the choice is presumably taken on efficiency grounds. You
can of course explicitly force signed or unsignedness with the right
keyword. The only time that it is likely to matter is
if you are using character variables as extra short shorts to
save more space.

Summary of integral types

#. The integral types are the short, long, signed, unsigned and plain ints.

#. The commonest is the ordinary int, which is signed unless declared not to be.

#. The char variables can be made signed or unsigned, as you prefer, but
   in the absence of indications to the
   contrary, they will be allocated the most efficient type.

Printing the integral types
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Once again you can use printf to print these various types.
Character variables work exactly the same way that the other integral
variables do, so you can use the standard format letters to
print their contents—although the actual numbers stored in them are
not likely to be very interesting. To see their contents interpreted
as characters, use %c as was done earlier. All of the
integral types can be printed as if they were signed decimal
numbers by using the %d format, or %ld for long types.
Other useful formats are shown in Table 2.5; notice that
in every case a letter ‘l’ is put in front of
the normal format letter if a long is to be printed.
That's not just there to get the right result printed:
the behavior of printf is undefined if the wrong format is given.


+------------------------+-----------------------------------------------------+
| Format                 | Use with                                            |
+========================+=====================================================+
| %c                     | char (in character form)                            |
+------------------------+-----------------------------------------------------+
| %d                     | decimal signed int, short, char                     |
+------------------------+-----------------------------------------------------+
| %u                     | decimal unsigned int, unsigned short, unsigned char |
+------------------------+-----------------------------------------------------+
| %x                     | hexadecimal int, short, char                        |
+------------------------+-----------------------------------------------------+
| %o                     | octal int, short, char                              |
+------------------------+-----------------------------------------------------+
| %ld                    | decimal signed long                                 |
+------------------------+-----------------------------------------------------+
| %lu %lx %lo            | as above, but for longs                             |
+------------------------+-----------------------------------------------------+



Table 2.5. More format codes

A full description of the format codes that you can use
with printf is given in :ref:`libraries`.

Expressions and arithmetic
--------------------------

Expressions in C can get rather complicated because of the number
of different types and operators that can be mixed together. This
section explains what happens, but can get deep at times. You
may need to re-read it once or twice to make
sure that you have understood all of the points.

First, a
bit of terminology. Expressions in C are built from combinations of
operators and operands, so for example in this expression

.. code-block:: C

    x = a+b*(-c)

we have the operators =, + \* and -. The operands are the variables x,
a, b and c. You will also have noticed that parentheses
can be used for grouping sub-expressions such as the -c.
Most of C's unusually rich set of operators are either
binary operators, which take two operands, or unary operators, which take
only one. In the example, the - was being used as a
unary operator, and is performing a different task from the binary
subtraction operator which uses the same - symbol. It may seem like
hair-splitting to argue that they are different operators when the
job that they do seems conceptually the same, or at least
similar. It's worth doing though, because, as you will find
later, some of the operators have both a binary and a
unary form where the two meanings bear no relation to each
other; a good example would be the binary multiplication operator \*, which
in its unary form means indirection via a pointer variable!

A
peculiarity of C is that operators may appear consecutively in expressions
without the need for parentheses to separate them. The previous example
could have been written as

.. code-block:: C

    x = a+b*-c;

and still have been a valid expression. Because of the number
of operators that C has, and because of the strange way
that assignment works, the precedence of the operators (and their associativity)
is of much greater importance to the C programmer than in
most other languages. It will be discussed fully after the introduction
of the important arithmetic operators.

Before that, we must investigate the type conversions that may occur.

Conversions
~~~~~~~~~~~

C allows types to be mixed in expressions, and permits operations
that result in type conversions happening implicitly. This section describes the
way that the conversions must occur. pre-C89 programmers should read
this carefully, because the rules have changed — in particular, the promotion
of float to double, the promotions of short integral types and
the introduction of value preserving rules are genuinely different in C89 Standard
C.

Although it isn't directly relevant at the moment, we
must note that the integral and the floating types are jointly
known as arithmetic types and that C also supports other types
(notably pointer types). The rules that we discuss here are appropriate
only in expressions that have arithmetic types throughout - additional rules come
into play when expressions mix pointer types with arithmetic types and
these are discussed much later.

There are various types of conversion
in arithmetic expressions:

- The integral promotions

- Conversions between integral types

- Conversions between floating types

- Conversions between floating and integral types

Conversions between floating (real) types were discussed in Section 2.8;
what we do next is to specify how the other conversions
are to be performed, then look at when they are required.
You will need to learn them by heart if you ever
intend to program seriously in C.

The C89 Standard has, among some
controversy, introduced what are known as value preserving rules, where a
knowledge of the target computer is required to work out what
the type of an expression will be. Previously, whenever an unsigned
type occurred in an expression, you knew that the result had
to be unsigned too. Now, the result will only be unsigned
if the conversions demand it; in many cases the result will
be an ordinary signed type.

The reason for the change was
to reduce some of the surprises possible when you mix signed
and unsigned quantities together; it isn't always obvious when this
has happened and the intention is to produce the ‘more commonly
required’ result.

Integral promotions
^^^^^^^^^^^^^^^^^^^

No arithmetic is done by C at a precision shorter than
int, so these conversions are implied almost whenever you use one
of the objects listed below in an expression. The conversion is
defined as follows:

    Whenever a short or a char (or a bitfield or
    enumeration type which we haven't met yet) has the integral
    promotions applied
    if an int can hold all of the
    values of the original type then the value is converted
    to int
    otherwise, the conversion will be to unsigned int

This preserves both the value and the sign of the original
type. Note that whether a plain char is treated as signed
or unsigned is implementation dependent.

These promotions are applied very often—they are applied as part
of the usual arithmetic conversions, and to the operands of the
shift, unary +, -, and ~ operators. They are also applied when the expression
in question is an argument to a function but no type
information has been provided as part of a function prototype, as
explained in :ref:`functions`.

Signed and unsigned integers
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

A lot of conversions between different types of integers are caused
by mixing the various flavors of integers in expressions. Whenever these
happen, the integral promotions will already have been done. For all
of them, if the new type can hold all of the
values of the old type, then the value remains unchanged.

When converting from a signed integer to an unsigned integer whose length
is equal to or longer than the original type, then if
the signed value was non-negative, its value is unchanged. If the
value was negative, then it is converted to the signed form
of the longer type and then made unsigned by conceptually adding
it to one greater than the maximum that can be held
in the unsigned type. In a twos complement system, this preserves
the original bit-pattern for positive numbers and guarantees ‘sign-extension’
of negative numbers.

Whenever an integer is converted into a shorter
unsigned type, there can be no ‘overflow’, so the result is
defined to be ‘the non-negative remainder on division by the
number one greater than the largest unsigned number that can be
represented in the shorter type’. That simply means that in a
two's complement environment the low-order bits are copied into
the destination and the high-order ones discarded.

Converting an integer
to a shorter signed type runs into trouble if there is
not enough room to hold the value. In that case, the
result is implementation defined (although most old-timers would expect that
simply the low-order bit pattern is copied).

That last item
could be a bit worrying if you remember the integral promotions,
because you might interpret it as follows—if I assign a
char to another char, then the one on the right is
first promoted to one of the kinds of int; could doing
the assignment result in converting (say) an int to a char
and provoking the ‘implementation defined’ clause? The answer is no, because
assignment is specified not to involve the integral promotions, so you
are safe.

Floating and integral
^^^^^^^^^^^^^^^^^^^^^

Converting a floating to an integral type simply throws away any
fractional part. If the integral type can't hold the value
that is left, then the behavior is undefined—this is a
sort of overflow.

As has already been said, going up the scale from float
to double to long double, there is no problem with conversions — each
higher one in the list can hold all the values
of the lower ones, so the conversion occurs with no loss
of information.

Converting in the opposite direction, if the value is outside the
range that can be held, the behavior is undefined. If the
value is in range, but can't be held exactly, then
the result is one of the two nearest values that can
be held, chosen in a way that the implementation defines. This
means that there will be a loss of precision.

The usual arithmetic conversions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

A lot of expressions involve the use of sub-expressions of mixed
types together with operators such as +, \* and so on. If the
operands in an expression have different types, then there will have
to be a conversion applied so that a common resulting type
can be established; these are the conversions:

#.  If either operand is a long double, then the other
    one is converted to long double and that is the
    type of the result.

#.  Otherwise, if either operand is a double, then the other
    one is converted to double, and that is the type
    of the result.

#.  Otherwise, if either operand is a float, then the other
    one is converted to float, and that is the type
    of the result.

#.  Otherwise the integral promotions are applied to both operands and
    the following conversions are applied:

    #. If either operand is an unsigned long int, then the
    other one is converted to unsigned long int, and that
    is the type of the result.

    #. Otherwise, if either operand is a long int, then the
    other one is converted to long int, and that is
    the type of the result.

    #. Otherwise, if either operand is an unsigned int, then the
    other one is converted to unsigned int, and that is
    the type of the result.

    #. Otherwise, both operands must be of type int, so that
    is the type of the result.

The C89 Standard contains a strange sentence: ‘The values of floating operands
and of the results of floating expressions may be represented in
greater precision and range than that required by the type; the
types are not changed thereby’. This is in fact to allow
the pre-C89 treatment of floats. In Old C, float variables
were automatically promoted to double, the way that the integral promotions
promote char to int. So, an expression involving purely float variables
may be done as if they were double, but the type
of the result must appear to be float. The only effect
is likely to be on performance and is not particularly important
to most users.

Whether or not conversions need to be applied,
and if so which ones, is discussed at the point where
each operator is introduced.

In general, the type conversions and type
mixing rules don't cause a lot of trouble, but there
is one pitfall to watch out for. Mixing signed and unsigned
quantities is fine until the signed number is negative; then its
value can't be represented in an unsigned variable and something
has to happen. The standard says that to convert a negative
number to unsigned, the largest possible number that can be held
in the unsigned plus one is added to the negative number;
that is the result. Because there can be no overflow in
an unsigned type, the result always has a defined value. Taking
a 16-bit int for an example, the unsigned version has
a range of 0–65535. Converting a signed value of -7
to this type involves adding 65536, resulting in 65529. What is
happening is that the C89 Standard is enshrining previous practice, where the
bit pattern in the signed number is simply assigned to the
unsigned number; the description in the standard is exactly what would
happen if you did perform the bit pattern assignment on a
two's complement computer. The one's complement implementations are going
to have to do some real work to get the same
result.

Putting it plainly, a small magnitude negative number will result
in a large positive number when converted to unsigned. If you
don't like it, suggest a better solution—it is plainly
a mistake to try to assign a negative number to an
unsigned variable, so it's your own fault.

Well, it's easy to say ‘don't do it’, but
it can happen by accident and the results can be very
surprising. Look at this example.

.. literalinclude:: ../src/example2.7/src/example2.7.c
   :language: c
   :linenos:



Example 2.7

You might expect that to print out the list of values
from -10 to 0, but it won't. The problem is
in the comparison. The variable i, with a value of -10,
is being compared against an unsigned 0. By the rules of
arithmetic (check them) we must convert both types to unsigned int
first, then make the comparison. The -10 becomes at least 65526
(see <limits.h>) when it's converted, and is plainly somewhat
larger than 0, so the loop is never executed. The moral
is to steer clear of unsigned numbers unless you really have
to use them, and to be perpetually on guard when they
are mixed with signed numbers.

Wide characters
^^^^^^^^^^^^^^^

The C89 Standard, as we've already said, now makes allowances for
extended character sets. You can either use the shift-in shift-out
encoding method which allows the multi-byte characters to be stored
in ordinary C strings (which are really arrays of chars, as
we explore later), or you can use a representation that uses
more than one byte of storage per character for every character.
The use of shift sequences only works if you process the
characters in strict order; it is next to useless if you
want to create an array of characters and access them in
non-sequential order, since the actual index of each char in
the array and the logical index of each of the encoded
characters are not easily determined. Here's the illustration we used
before, annotated with the actual and the logical array indexes:

    0 1 2  3   4 5 6  7   8 9 (actual array index)

    a b c <SI> a b g <SO> x y

    0 1 2      3 4 5      6 7 (logical index)

We're still in trouble even if we do manage to
use the index of 5 to access the ‘correct’ array entry,
since the value retrieved is indistinguishable from the value that encodes
the letter ‘g’ anyhow. Clearly, a better approach for this sort
of thing is to come up with a distinct value for
all of the characters in the character set we are using,
which may involve more bits than will fit into a char,
and to be able to store each one as a separate
item without the use of shifts or other position-dependent techniques.
That is what the wchar_t type is for.

Although it
is always a synonym for one of the other integral types,
wchar_t (whose definition is found in <stddef.h>) is defined
to be the implementation-dependent type that should be used to
hold extended characters when you need an array of them. The
C89 Standard makes the following guarantees about the values in a wide
character:

- A wchar_t can hold distinct values for each member
  of the largest character set supported by the implementation.

- The null character has the value of zero.

- Each member of the basic character set (see Section 2.2.1)
  is encoded in a wchar_t with the same value as it has in a char.

There is further support for this method of encoding characters. Strings,
which we have already seen, are implemented as arrays of char,
even though they look like this:

.. code-block:: C

    "a string"

To get strings whose type is wchar_t, simply prefix a
string with the letter L. For example:

.. code-block:: C

    L"a string"

In the two examples, it is very important to understand the
differences. Strings are implemented as arrays and although it might look
odd, it is entirely permissible to use array indexing on them:

.. code-block:: C

    "a string"[4]
    L"a string"[4]

are both valid expressions. The first results in an expression whose
type is char and whose value is the internal representation of
the letter ‘r’ (remember arrays index from zero, not one). The
second has the type wchar_t and also has the value
of the internal representation of the letter ‘r’.

It gets more interesting if we are using extended characters. If
we use the notation <a>, <b>, and so on to indicate
‘additional’ characters beyond the normal character set which are encoded using
some form of shift technique, then these examples show the problems.

.. code-block:: C

    "abc<a><b>"[3]
    L"abc<a><b>"[3]

The second one is easiest: it has a type of wchar_t
and the appropriate internal encoding for whatever <a> is supposed
to be—say the Greek letter alpha. The first one is
unpredictable. Its type is unquestionably char, but its value is probably
the value of the ‘shift-in’ marker.

As with strings, there are also wide character constants.

.. code-block:: C

    'a'

has type char and the value of the encoding for the letter ‘a’.

.. code-block:: C

    L'a'

is a constant of type wchar_t. If you use a
multi-byte character in the first one, then you have the same
sort of thing as if you had written

.. code-block:: C

    'xy'

—multiple characters in a character constant (actually, this is valid but
means something funny). A single multi-byte character in the second example
will simply be converted into the appropriate wchar_t value.

If
you don't understand all the wide character stuff, then all
we can say is that we've done our best to
explain it. Come back and read it again later, when it
might suddenly click. In practice it does manage to address the
support of extended character sets in C and once you're
used to it, it makes a lot of sense.

Exercise 2.15.

Assuming that chars, ints and longs are respectively 8, 16 and
32 bits long, and that char defaults to unsigned char on
a given system, what is the resulting type of expressions involving
the following combinations of variables, after the usual arithmetic conversions have
been applied?

- Simply signed char.

- Simply unsigned char.

- int, unsigned int.

- unsigned int, long.

- int, unsigned long.

- char, long.

- char, float.

- float, float.

- float, long double.

Casts
^^^^^

From time to time you will find that an expression turns
out not to have the type that you wanted it to
have and you would like to force it to have a
different type. That is what casts are for. By putting a
type name in parentheses, for example

.. code-block:: C

    (int)

you create a unary operator known as a cast. A cast
turns the value of the expression on its right into the
indicated type. If, for example, you were dividing two integers a/b
then the expression would use integer division and discard any
remainder. To force the fractional part to be retained, you could
either use some intermediate float variables, or a cast. This example
does it both ways.

.. literalinclude:: ../src/example2.8/src/example2.8.c
   :language: c
   :linenos:



Example 2.8

The easiest way to remember how to write a cast is
to write down exactly what you would use to declare a
variable of the type that you want. Put parentheses around the
entire declaration, then delete the variable name; that gives you the
cast. Table 2.6 shows a few simple examples—some of
the types shown will be new to you, but it's
the complicated ones that illustrate best how casts are written. Ignore
the ones that you don't understand yet, because you will
be able to use the table as a reference later.

+------------------------+-------------+-----------------------------------+
| Declaration            | Cast        | Type                              |
+========================+=============+===================================+
| int x;                 | (int)       | int                               |
+------------------------+-------------+-----------------------------------+
| float f;               | (float)     | float                             |
+------------------------+-------------+-----------------------------------+
| char x[30];            | (char [30]) | array of char                     |
+------------------------+-------------+-----------------------------------+
| int \*ip;              | (int \*)     | pointer to int                   |
+------------------------+-------------+-----------------------------------+
| int (\*f)();           | (int (\*)())| pointer to function returning int |
+------------------------+-------------+-----------------------------------+



Table 2.6. Casts

Operators
~~~~~~~~~

The multiplicative operators
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Or, put another way, multiplication \*, division / and the remainder operator %. Multiplication
and division do what is expected of them for both real
and integral types, with integral division producing a truncated result. The
truncation is towards zero. The remainder operator is only defined to
work with integral types, because the division of real numbers supposedly
doesn't produce a remainder.

If the division is not exact
and neither operand is negative, the result of / is positive and
rounded toward zero—to get the remainder, use %. For example,

.. code-block:: C

    9/2 == 4
    9%2 == 1

If either operand is negative, the result of / may be the
nearest integer to the true result on either side, and the
sign of the result of % may be positive or negative. Both
of these features are implementation defined.

It is always true that the following expression is equal to zero:

.. code-block:: C

    (a/b)*b + a%b - a

unless b is zero.

The usual arithmetic conversions are applied to both of the operands.

Additive operators
^^^^^^^^^^^^^^^^^^

Addition + and subtraction - also follow the rules that you expect. The
binary operators and the unary operators both have the same symbols,
but rather different meanings. For example, the expressions a+b and
a-b both use a binary operator (the + or - operators), and
result in addition or subtraction. The unary operators with the same
symbols would be written +b or -b.

The unary minus has
an obvious function—it takes the negative value of its operand;
what does the unary plus do? In fact the answer is
almost nothing. The unary plus is a new addition to the
language, which balances the presence of the unary minus, but doesn't
have any effect on the value of the expression. Very
few pre-C89 users even noticed that it was missing.

The
usual arithmetic conversions are applied to both of the operands of
the binary forms of the operators. Only the integral promotions are
performed on the operands of the unary forms of the operators.

The bit-wise operators
^^^^^^^^^^^^^^^^^^^^^^

One of the great strengths of C is the way that
it allows systems programmers to do what had, before the advent
of C, always been regarded as the province of the assembly
code programmer. That sort of code was by definition highly non
-portable. As C demonstrates, there isn't any magic about that
sort of thing, and into the bargain it turns out to
be surprisingly portable. What is it? It's what is often
referred to as ‘bit-twiddling’—the manipulation of individual bits in
integer variables. None of the bit-wise operators may be used on
real operands because they aren't considered to have individual or
accessible bits.

There are six bit-wise operators, listed in Table 2.7, which
also shows the arithmetic conversions that are applied.

+------------------------+-------------------+-----------------------------------+
| Operator               | Effect            | Conversions                       |
+========================+===================+===================================+
|   &                    | bit-wise AND      | usual arithmetic conversions      |
+------------------------+-------------------+-----------------------------------+
|   |                    | bit-wise OR       | usual arithmetic conversions      |
+------------------------+-------------------+-----------------------------------+
|   ^                    | bit-wise XOR      | usual arithmetic conversions      |
+------------------------+-------------------+-----------------------------------+
|   <<                   | left shift        | integral promotions               |
+------------------------+-------------------+-----------------------------------+
|   >>                   | right shift       | integral promotions               |
+------------------------+-------------------+-----------------------------------+
|   ~                    | one's complement  | integral promotions               |
+------------------------+-------------------+-----------------------------------+

Table 2.7. Bit-wise operators

Only the last, the one's complement, is a unary operator.
It inverts the state of every bit in its operand and
has the same effect as the unary minus on a one's
complement computer. Most modern computers work with two's complement,
so it isn't a waste of time having it there.

Illustrating the use of these operators is easier if we can
use hexadecimal notation rather than decimal, so now is the time
to see hexadecimal constants. Any number written with 0x at its
beginning is interpreted as hexadecimal; both 15 and 0xf (or 0XF)
mean the same thing. Try running this or, better still, try
to predict what it does first and then try running it.

.. literalinclude:: ../src/example2.9/src/example2.9.c
   :language: c
   :linenos:


Example 2.9

The way that the loop works in that example is the
first thing to study. The controlling variable is x, which is
initialized to zero. Every time round the loop it is compared
against y, which has been set to a word-length independent
pattern of all 1s by taking the one's complement of
zero. At the bottom of the loop, x is shifted left
once and has 1 ORed into it, giving rise to a
sequence that starts 0, 1, 11, 111, … in binary.

For each
of the AND, OR, and XOR (exclusive OR) operators, x is
operated on by the operator and some other interesting operand, then
the result printed.

The left and right shift operators are in
there too, giving a result which has the type and value
of their left-hand operand shifted in the required direction a
number of places specified by their right-hand operand; the type
of both of the operands must be integral. Bits shifted off
either end of the left operand simply disappear. Shifting by more
bits than there are in a word gives an implementation dependent
result.

Shifting left guarantees to shift zeros into the low-order
bits.

Right shift is fussier. Your implementation is allowed to choose
whether, when shifting signed operands, it performs a logical or arithmetic
right shift. This means that a logical shift shifts zeros into
the most significant bit positions; an arithmetic shift copies the current
contents of the most significant bit back into itself. The position
is clearer if an unsigned operand is right shifted, because there
is no choice: it must be a logical shift. For that
reason, whenever right shift is being used, you would expect to
find that the thing being shifted had been declared to be
unsigned, or cast to unsigned for the shift, as in the example:

.. code-block:: C

    int i,j;
    i = (unsigned)j >> 4;

The second (right-hand) operand of a shift operator does not
have to be a constant; any integral expression is legal. Importantly,
the rules involving mixed types of operands do not apply to
the shift operators. The result of the shift has the same
type as the thing that got shifted (after the integral promotions),
and depends on nothing else.

Now something different; one of those
little tricks that C programmers find helps to write better programs.
If for any reason you want to form a value that
has 1s in all but its least significant so-many bits,
which are to have some other pattern in them, you don't
have to know the word length of the machine. For
example, to set the low order bits of an int to
0x0f0 and all the other bits to 1, this is the way to do it:

.. code-block:: C

    int some_variable;
    some_variable = ~0xf0f;

The one's complement of the desired low-order bit pattern
has been one's complemented. That gives exactly the required result
and is completely independent of word length; it is a very
common sight in C code.

There isn't a lot more to say about the bit-twiddling
operators, and our experience of teaching C has been that
most people find them easy to learn. Let's move on.

The assignment operators
^^^^^^^^^^^^^^^^^^^^^^^^

No, that isn't a mistake, ‘operators’ was meant to be
plural. C has several assignment operators, even though we have only
seen the plain = so far. An interesting thing about them is
that they are all like the other binary operators; they take
two operands and produce a result, the result being usable as
part of an expression. In this statement

.. code-block:: C

    x = 4;

the value 4 is assigned to x. The result has the
type of x and the value that was assigned. It can
be used like this

.. code-block:: C

    a = (x = 4);

where a will now have the value 4 assigned to it,
after x has been assigned to. All of the simpler assignments
that we have seen until now (except for one example) have
simply discarded the resulting value of the assignment, even though it
is produced.

It's because assignment has a result that an
expression like

.. code-block:: C

    a = b = c = d;

works. The value of d is assigned to c, the result
of that is assigned to b and so on. It makes
use of the fact that expressions involving only assignment operators are
evaluated from right to left, but is otherwise like any other
expression. (The rules explaining what groups right to left and vice
versa are given in Table 2.9.)

If you look back
to the section describing ‘conversions’, there is a description of what
happens if you convert longer types to shorter types: that is
what happens when the left-hand operand of an assignment is
shorter than the right-hand one. No conversions are applied to
the right-hand operand of the simple assignment operator.

The remaining
assignment operators are the compound assignment operators. They allow a useful
shorthand, where an assignment containing the same left- and right-hand
sides can be compressed; for example

.. code-block:: C

    x = x + 1;

can be written as

.. code-block:: C

    x += 1;

using one of the compound assignment operators. The result is the
same in each case. It is a useful thing to do
when the left-hand side of the operator is a complicated
expression, not just a variable; such things occur when you start
to use arrays and pointers. Most experienced C programmers tend to
use the form given in the second example because somehow it
‘feels better’, a sentiment that no beginner has ever been known
to agree with. Table 2.8 lists the compound assignment operators;
you will see them used a lot from now on.

+------------------------+-------------+-----------------------------------+
|   \*=                  | /=          |  %=                               |
+------------------------+-------------+-----------------------------------+
|   +=                   | -=          |                                   |
+------------------------+-------------+-----------------------------------+
|   &=                   | \|=         | ^=                                |
+------------------------+-------------+-----------------------------------+
|   >>=                  | <<=         |                                   |
+------------------------+-------------+-----------------------------------+


Table 2.8. Compound assignment operators

In each case, arithmetic conversions are applied as if the expression
had been written out in full, for example as if a+=b
had been written a=a+b.

Reiterating: the result of an assignment operator has both the value
and the type of the object that was assigned to.

Increment and decrement operators
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

It is so common to simply add or subtract 1 in
an expression that C has two special unary operators to do
the job. The increment operator ++ adds 1, the decrement -- subtracts 1
. They are used like this:

.. code-block:: C

    x++;
    ++x;
    x--;
    --x;

where the operator can come either before or after its operand.
In the cases shown it doesn't matter where the operator
comes, but in more complicated cases the difference has a definite
meaning and must be used properly.

Here is the difference being used.

.. literalinclude:: ../src/example2.10/src/example2.10.c
   :language: c
   :linenos:


Example 2.10

The results printed were

11
6
10
6

The difference is caused by the different positions of the operators.
If the inc/decrement operator appears in front of the variable,
then its value is changed by one and the new value
is used in the expression. If the operator comes after the
variable, then the old value is used in the expression and
the variable's value is changed afterwards.

C programmers never add or subtract one with statements like this

.. code-block:: C

    x += 1;

they invariably use one of

.. code-block:: C

    x++; /* or */ ++x;

as a matter of course. A warning is in order though:
it is not safe to use a variable more than once
in an expression if it has one of these operators attached
to it. There is no guarantee of when, within an expression,
the affected variable will actually change value. The compiler might choose
to ‘save up’ all of the changes and apply them at
once, so an expression like this

.. code-block:: C

    y = x++ + --x;

does not guarantee to assign twice the original value of x
to y. It might be evaluated as if it expanded to
this instead:

.. code-block:: C

    y = x + (x-1);

because the compiler notices that the overall effect on the value
of x is zero.

The arithmetic is done exactly as if
the full addition expression had been used, for example x=x+1,
and the usual arithmetic conversions apply.

Exercise 2.16. Given the following variable definitions

.. code-block:: C

    int i1, i2;
    float f1, f2;

How would you find the remainder when i1 is divided by i2?
How would you find the remainder when i1 is divided by the value of f1, treating f1 as an integer?
What can you predict about the sign of the remainders calculated in the previous two questions?
What meanings can the - operator have?
How would you turn off all but the low-order four bits in i1?
How would you turn on all the low-order four bits in i1?
How would you turn off only the low-order four bits in i1?
How would you put into i1 the low-order 8 bits in i2, but swapping the significance of the lowest four with the next
What is wrong with the following expression?

.. code-block:: C

    f2 = ++f1 + ++f1;

Precedence and grouping
~~~~~~~~~~~~~~~~~~~~~~~

After looking at the operators we have to consider the way
that they work together. For things like addition it may not
seem important; it hardly matters whether

.. code-block:: C

    a + b + c

is done as

.. code-block:: C

    (a + b) + c

or

.. code-block:: C

    a + (b + c)

does it? Well, yes in fact it does. If a+b
would overflow and c held a value very close to -b,
then the second grouping might give the correct answer where the
first would cause undefined behavior. The problem is much more obvious
with integer division:

.. code-block:: C

    a/b/c

gives very different results when grouped as

.. code-block:: C

    a/(b/c)

or

.. code-block:: C

    (a/b)/c

If you don't believe that, try it with a=10,
b=2, c=3. The first gives 10/(2/3); 2/3
in integer division gives 0, so we get 10/0
which immediately overflows. The second grouping gives (10/2), obviously 5,
which divided by 3 gives 1.

The grouping of operators like that is known as associativity. The
other question is one of precedence, where some operators have a
higher priority than others and force evaluation of sub-expressions involving
them to be performed before those with lower precedence operators. This
is almost universal practice in high-level languages, so we ‘know’ that

.. code-block:: C

    a + b * c + d

groups as

.. code-block:: C

    a + (b * c) + d

indicating that multiplication has higher precedence than addition.

The large set
of operators in C gives rise to 15 levels of precedence!
Only very boring people bother to remember them all. The complete
list is given in Table 2.9, which indicates both precedence
and associativity. Not all of the operators have been mentioned yet.
Beware of the use of the same symbol for both unary
and binary operators: the table indicates which are which.

+---------------------------------+---------------+-----------------------------------+
| Operator                        | Direction     | Notes                             |
+=================================+===============+===================================+
| () [] -> .                      | left to right | 1                                 |
+---------------------------------+---------------+-----------------------------------+
| ! ~ ++ -- - + (cast) \* & sizeof| right to left | all unary                         |
+---------------------------------+---------------+-----------------------------------+
| \* / %                          | left to right | binary                            |
+---------------------------------+---------------+-----------------------------------+
| \+ -                            | left to right | binary                            |
+---------------------------------+---------------+-----------------------------------+
| << >>                           | left to right | binary                            |
+---------------------------------+---------------+-----------------------------------+
| < <= > >=                       | left to right | binary                            |
+---------------------------------+---------------+-----------------------------------+
| == !=                           | left to right | binary                            |
+---------------------------------+---------------+-----------------------------------+
| &                               | left to right | binary                            |
+---------------------------------+---------------+-----------------------------------+
| ^                               | left to right | binary                            |
+---------------------------------+---------------+-----------------------------------+
| \|                              | left to right | binary                            |
+---------------------------------+---------------+-----------------------------------+
| &&                              | left to right | binary                            |
+---------------------------------+---------------+-----------------------------------+
| ||                              | left to right | binary                            |
+---------------------------------+---------------+-----------------------------------+
| ?:                              | right to left | 2                                 |
+---------------------------------+---------------+-----------------------------------+
| = += and all combined assignment| right to left | binary                            |
+---------------------------------+---------------+-----------------------------------+
| ,                               | left to right | binary                            |
+---------------------------------+---------------+-----------------------------------+

    1. Parentheses are for expression grouping, not function call.
    2. This is unusual. See Section 3.4.1.

Table 2.9. Operator precedence and associativity

The question is, what can you do with that information, now
that it's there? Obviously it's important to be able
to work out both how to write expressions that evaluate in
the proper order, and also how to read other people's.
The technique is this: first, identify the unary operators and the
operands that they refer to. This isn't such a difficult
task but it takes some practice, especially when you discover that
operators such as unary \* can be applied an arbitrary number of
times to their operands; this expression

.. code-block:: C

    a*****b

means a multiplied by something, where the something is an expression
involving b and several unary * operators.

It's not too difficult to work out which are the
unary operators; here are the rules.

- ++ and - are always unary operators.

- The operator immediately to the right of an operand is
  a binary operator unless (1) applies, when the operator to
  its right is binary.

- All operators to the left of an operand are unary unless (2) applies.

Because the unary operators have very high precedence, you can work
out what they do before worrying about the other operators. One
thing to watch out for is the way that ++ and -- can
be before or after their operands; the expression

.. code-block:: C

    a + -b++ + c

has two unary operators applied to b. The unary operators all
associate right to left, so although the - comes first when you
read the expression, it really parenthesizes (for clarity) like this:

.. code-block:: C

    a + -(b++) + c

The case is a little clearer if the prefix, rather than
the postfix, form of the increment/decrement operators is being used.
Again the order is right to left, but at least the
operators come all in a row.

After sorting out what to
do with the unary operators, it's easy to read the
expression from left to right. Every time you see a binary
operator, remember it. Look to the right: if the next binary
operator is of a lower precedence, then the operator you just
remembered is part of a sub-expression to evaluate before anything else
is seen. If the next operator is of the same precedence,
keep repeating the procedure as long as equal precedence operators are
seen. When you eventually find a lower precedence operator, evaluate the
sub-expression on the left according to the associativity rules. If a
higher precedence operator is found on the right, forget the previous
stuff: the operand to the left of the higher precedence operator
is part of a sub-expression separate from anything on the left
so far. It belongs to the new operator instead.

If that
lot isn't clear don't worry. A lot of C
programmers have trouble with this area and eventually learn to parenthesize
these expressions ‘by eye’, without ever using formal rules.

What does
matter is what happens when you have fully parenthesized these expressions.
Remember the ‘usual arithmetic conversions’? They explained how you could predict
the type of an expression from the operands involved. Now, even
if you mix all sorts of types in a complicated expression,
the types of the sub-expressions are determined only from the the
types of the operands in the sub-expression. Look at this.

.. literalinclude:: ../src/example2.11/src/example2.11.c
   :language: c
   :linenos:


Example 2.11

The value printed is 3.0000, not 5.0000—which might
surprise some, who thought that because a float was involved the
whole statement involving the division would be done in that real
type.

Of course, the division operator had only int types on
either side, so the arithmetic was done as integer division and
resulted in zero. The addition had a float and an int
on either side, so the conversions meant that the int was
converted to float for the arithmetic, and that was the correct
type for the assignment, so there were no further conversions.

The
previous section on casts showed one way of changing the type
of an expression from its natural one to the one that
you want. Be careful though:

.. code-block:: C

    (float)(j/i)

would still use integer division, then convert the result to float
. To keep the remainder, you should use

.. code-block:: C

    (float)j/i

which would force real division to be used.

Parentheses
~~~~~~~~~~~

C allows you to override the normal effects of precedence and
associativity by the use of parentheses as the examples have illustrated.
In pre-C89, the parentheses had no further meaning, and in
particular did not guarantee anything about the order of evaluation in
expressions like these:

.. code-block:: C

    int a, b, c;
    a+b+c;
    (a+b)+c;
    a+(b+c);

You used to need to use explicit temporary variables to get
a particular order of evaluation—something that matters if you know
that there are risks of overflow in a particular expression, but
by forcing the evaluation to be in a certain order you
can avoid it.

C89 Standard C says that evaluation must be done
in the order indicated by the precedence and grouping of the
expression, unless the compiler can tell that the result will not
be affected by any regrouping it might do for optimization reasons.

So, the expression a = 10+a+b+5; cannot be rewritten
by the compiler as a = 15+a+b; unless it can
be guaranteed that the resulting value of a will be the
same for all combinations of initial values of a and b.
That would be true if the variables were both unsigned integral
types, or if they were signed integral types but in that
particular implementation overflow did not cause a run-time exception and
overflow was reversible.

Side Effects
~~~~~~~~~~~~

To repeat and expand the warning given for the increment operators:
it is unsafe to use the same variable more than once
in an expression if evaluating the expression changes the variable and
the new value could affect the result of the expression. This
is because the change(s) may be ‘saved up’ and only
applied at the end of the statement. So f = f+1;
is safe even though f appears twice in a value-changing
expression, f++; is also safe, but f = f++; is unsafe.

The
problem can be caused by using an assignment, use of the
increment or decrement operators, or by calling a function that changes
the value of an external variable that is also used in
the expression. These are generally known as ‘side effects’. C makes
almost no promise that side effects will occur in a predictable
order within a single expression. (The discussion of ‘sequence points’ in
:ref:`specialized` will be of interest if you care about this.)

Constants
---------

2.9.1. Integer constants
~~~~~~~~~~~~~~~~~~~~~~~~

The normal integral constants are obvious: things like 1, 1034
and so on. You can put l or L at
the end of an integer constant to force it to
be long. To make the constant unsigned, one of u
or U can be used to do the job.

Integer
constants can be written in hexadecimal by preceding the constant
with 0x or 0X and using the upper or lower
case letters a, b, c, d, e, f in the
usual way.

Be careful about octal constants. They are indicated
by starting the number with 0 and only using the
digits 0, 1, 2, 3, 4, 5, 6, 7. It
is easy to write 015 by accident, or out of
habit, and not to realize that it is not in
decimal. The mistake is most common with beginners, because experienced
C programmers already carry the scars.

The C89 Standard has now
invented a new way of working out what type an
integer constant is. In the old days, if the constant
was too big for an int, it got promoted to
a long (without warning). Now, the rule is that a
plain decimal constant will be fitted into the first in this list

    int   long   unsigned long

that can hold the value.

Plain octal or hexadecimal constants will use this list

    int   unsigned int   long   unsigned long

If the constant is suffixed by u or U:

    unsigned int   unsigned long

If it is suffixed by l or L:

    long   unsigned long

and finally, if it suffixed by both u or U
and l or L, it can only be an unsigned long.

All that was done to try to give you ‘what
you meant’; what it does mean is that it is
hard to work out exactly what the type of a
constant expression is if you don't know something about
the hardware. Hopefully, good compilers will warn when a constant
is promoted up to another length and the U or
L etc. is not specified.

A nasty bug hides here:

.. code-block:: C

    printf("value of 32768 is %d\n", 32768);

On a 16-bit two's complement machine, 32768 will
be a long by the rules given above. But printf
is only expecting an int as an argument (the %d
indicates that). The type of the argument is just wrong.
For the ultimate in safety-conscious programming, you should cast
such cases to the right type:

.. code-block:: C

    printf("value of 32768 is %d\n", (int)32768);

It might interest you to note that there are no
negative constants; writing -23 is an expression involving a positive
constant and an operator.

Character constants actually have type int (for historical reasons) and
are written by placing a sequence of characters between single
quote marks:

.. code-block:: C

    'a'
    'b'
    'like this'

Wide character constants are written just as above, but prefixed with L:

.. code-block:: C

    L'a'
    L'b'
    L'like this'

Regrettably it is valid to have more than one character
in the sequence, giving a machine-dependent result. Single characters
are the best from the portability point of view, resulting
in an ordinary integer constant whose value is the machine
representation of the single character. The introduction of extended characters
may cause you to stumble over this by accident; if
'<a>' is a multi-byte character (encoded with a shift-in
shift-out around it) then '<a>' will be a plain
character constant, but containing several characters, just like the more
obvious 'abcde'. This is bound to lead to trouble in
the future; let's hope that compilers will warn about it.

To ease the way of representing some special characters that
would otherwise be hard to get into a character constant
(or hard to read; does ' ' contain a space or a
tab?), there is what is called an escape sequence which
can be used instead. Table 2.10 shows the escape
sequences defined in the C89 Standard.

+--------------------+-------------------+
| Sequence           | Represents        |
+====================+===================+
| \\a                | audible alarm     |
+--------------------+-------------------+
| \\b                | backspace         |
+--------------------+-------------------+
| \\f                | form feed         |
+--------------------+-------------------+
| \\n                | newline           |
+--------------------+-------------------+
| \\r                | carriage return   |
+--------------------+-------------------+
| \\t                | tab               |
+--------------------+-------------------+
| \\v                | vertical tab      |
+--------------------+-------------------+
| ``\\``             | backslash         |
+--------------------+-------------------+
| \\'                | quote             |
+--------------------+-------------------+
| \\"                | double quote      |
+--------------------+-------------------+
| \\?                | question mark     |
+--------------------+-------------------+



Table 2.10. C escape sequences

It is also possible to use numeric escape sequences to
specify a character in terms of the internal value used
to represent it. A sequence of either \ooo or \xhhhh,
where the ooo is up to three octal digits and
hhhh is any number of hexadecimal digits respectively. A common
version of it is '\033', which is used by those
who know that on an ASCII based machine, octal 33
is the ESC (escape) code. Beware that the hexadecimal version
will absorb any number of valid following hexadecimal digits; if
you want a string containing the character whose value is
hexadecimal ff followed by a letter f, then the safe
way to do it is to use the string joining feature:

.. code-block:: C

    "\xff" "f"

The string

.. code-block:: C

    "\xfff"

only contains one character, with all three of the fs
eaten up in the hexadecimal sequence.

Some of the escape sequences aren't too obvious, so
a brief explanation is needed. To get a single quote
as a character constant you type '\'', to get a question
mark you may have to use '\?'; not that it matters
in that example, but to get two of them in
there you can't use '??', because the sequence ??' is a
trigraph! You would have to use '\?\?'. The escape \" is only
necessary in strings, which will come later.

There are two distinct purposes behind the escape sequences. It's
obviously necessary to be able to represent characters such
as single quote and backslash unambiguously: that is one purpose.
The second purpose applies to the following sequences which control
the motions of a printing device when they are sent to it, as follows: ::

    \a
        Ring the bell if there is one. Do not move.
    \b
        Backspace.
    \f
        Go to the first position on the ‘next page’, whatever that may mean for the output device.
    \n
        Go to the start of the next line.
    \r
        Go back to the start of the current line.
    \t
        Go to the next horizontal tab position.
    \v
        Go to the start of the line at the next vertical tab position.

For \b, \t, \v, if there is no such position,
the behavior is unspecified. The C89 Standard carefully avoids mentioning the
physical directions of movement of the output device which are
not necessarily the top to bottom, left to right movements
common in Western cultural environments.

It is guaranteed that each escape sequence has a unique
integral value which can be stored in a char.

2.9.2. Real constants
~~~~~~~~~~~~~~~~~~~~~

These follow the usual format:

    1.0

    2.

    .1

    2.634

    .125

    2.e5

    2.e+5

    .125e-3

    2.5e5

    3.1E-6


and so on. For readability, even if part of the
number is zero, it is a good idea to show it:

    1.0

    0.1

The exponent part shows the number of powers of ten
that the rest of the number should be raised to, so

    3.0e3

is equivalent in value to the integer constant

    3000

As you can see, the e can also be E.
These constants all have type double unless they are suffixed
with f or F to mean float or l or
L to mean long double.

For completeness, here is the
formal description of a real constant:

A real constant is one of:

    A fractional constant followed by an optional exponent.

    A digit sequence followed by an exponent.

In either case followed by an optional one of f, l, F, L, where:

    A fractional constant is one of:

        An optional digit sequence followed by a decimal
        point followed by a digit sequence.

        A digit sequence followed by a decimal point.

    An exponent is one of

        e or E followed by an optional + or - followed
        by a digit sequence.

    A digit sequence is an arbitrary combination of one or more digits.


Summary
-------

This has been a lengthy, and perhaps disconcerting chapter.

The
alphabet of C, although of relevance, is not normally a
day-to-day consideration of practicing programmers, so it has
been discussed but can now be largely ignored.

Much the
same can be said regarding keywords and identifiers, since the
topic is not complicated and simply becomes committed to memory.

The declaration of variables is rarely a problem, although it
is worth re-emphasizing the distinction between a declaration and
a definition. If that still remains unclear, you might find
it of benefit to go back and re-read the
description.

Beyond any question, the real complexity lies in what
happens when the integral promotions and the arithmetic conversions occur.
For beginners, it is often worthwhile to remember that here
is a difficult and arduous piece of terrain. Nothing else
in the language requires so much attention or is so
important to the production of correct, reliable programs. Beginners should
not try to remember it all, but to go on
now and to gain confidence with the rest of the
language. After two or three months' practice at using the
easier parts of the language, the time really does come
when you can no longer afford to ignore Section 2.8.

Many highly experienced C programmers never bother to learn
the different precedence of operators, except for a few important
cases. A precedence table pinned above your desk, for easy
reference, is a valuable tool.

The C89 Standard has substantially affected parts of the language described
in this chapter. In particular, the changes to the conversions
and the change from ‘unsignedness preserving’ to ‘value preserving’ rules
of arithmetic may cause some surprises to experienced C programmers.
Even they have some real re-learning to do.

Exercises
---------

Exercise 2.17. First, fully parenthesize the following expressions according
to the precedence and associativity rules. Then, replacing the variables
and constants with the appropriate type names, show how the
type of the expression is derived by replacing the highest
precedence expressions with its resulting type.

The variables are:

    char c;

    int i;

    unsigned u;

    float f;

For example: i = u+1; parenthesizes as (i = (u + 1));

The types are ::

    (int = (unsigned + int));

then ::

    (int = (unsigned)); /* usual arithmetic conversions */

then ::

    (int); /* assignment */

        c = u * f + 2.6L;
        u += --f / u % 3;
        i <<= u * - ++f;
        u = i + 3 + 4 + 3.1;
        u = 3.1 + i + 3 + 4;
        c = (i << - --f) & 0xf;

..  LocalWords:  sqrt
