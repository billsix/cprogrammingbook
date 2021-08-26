.. _control-flow:


Control flow
============


The Task ahead
--------------

In this chapter we look at the various ways that
the control of flow statements can be used in a
C program, including some statements that haven't been introduced
so far. They are almost always used in conjunction with
logical expressions to select the next action. Examples of logical
expressions that have been seen already are some simple ones
used in if or while statements. As you might have
expected, you can use expressions more complicated than simple comparison
(>, <=, == etc.); what may surprise you is the type of the
result.

Logical expressions and Relational Operators
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

All of the examples we have used so far have
deliberately avoided using complicated logical expressions in the control of
flow statements. We have seen expressions like this

.. code-block:: C

    if(a != 100){...

and presumably you have formed the idea that C supports
the concept of ‘true’ and ‘false’ for these relationships. In
a way, it does, but in a way that differs
from what is often expected.

All of the relational operators shown in Table 3.1
are used to compare two operands in the way indicated.
When the operands are arithmetic types, the usual arithmetic conversions
are applied to them.

+------------------------+-------------------------------+
| Operator               | Operation                     |
+========================+===============================+
| <                      | less than                     |
+------------------------+-------------------------------+
| <=                     | less than or equal to         |
+------------------------+-------------------------------+
| >                      | greater than                  |
+------------------------+-------------------------------+
| >=                     | greater than or equal to      |
+------------------------+-------------------------------+
| ==                     | equal to                      |
+------------------------+-------------------------------+
| !=                     | not equal to                  |
+------------------------+-------------------------------+

Table 3.1. Relational operators

Be extra careful of the test for equality, ==. As we
have already pointed out, it is often valid to use
assignment = where you might have meant == and C can't
tell you about your mistake. The results are normally different
and it takes a long time for beginners to get
used to using == and =.

Now, that usefully introduces the question ‘why?’. Why are both
valid? The answer is simple. C's concept of ‘true’
and ‘false’ boils down to simply ‘non-zero’ and ‘zero’,
respectively. Where we have seen expressions involving relational operators used
to control do and if statements, we have just been
using expressions with numeric results. If the expression evaluates to
non-zero, then the result is effectively true. If the
reverse is the case, then of course the result is
false. Anywhere that the relational operators appear, so may any
other expression.

The relational operators work by comparing their operands and giving
zero for false and (remember this) one for true. The
result is of type int. This example shows how they work.


.. literalinclude:: ../src/example3.1/src/example3.1.c
   :language: c
   :linenos:

Example 3.1

Which produces this on its standard output:

    value of i is -10, i == 0 = 0, i > -5 = 0

    value of i is -9, i == 0 = 0, i > -5 = 0

    value of i is -8, i == 0 = 0, i > -5 = 0

    value of i is -7, i == 0 = 0, i > -5 = 0

    value of i is -6, i == 0 = 0, i > -5 = 0

    value of i is -5, i == 0 = 0, i > -5 = 0

    value of i is -4, i == 0 = 0, i > -5 = 1

    value of i is -3, i == 0 = 0, i > -5 = 1

    value of i is -2, i == 0 = 0, i > -5 = 1

    value of i is -1, i == 0 = 0, i > -5 = 1

    value of i is 0, i == 0 = 1, i > -5 = 1

    value of i is 1, i == 0 = 0, i > -5 = 1

    value of i is 2, i == 0 = 0, i > -5 = 1

    value of i is 3, i == 0 = 0, i > -5 = 1

    value of i is 4, i == 0 = 0, i > -5 = 1

    value of i is 5, i == 0 = 0, i > -5 = 1


In this probably mistaken piece of code, what do you
think happens?

.. code-block:: C

    if(a = b)...

The value of b is assigned to a. As you
know, the result has the type of a and whatever
value was assigned to a. The if will execute the
next statement if the value assigned is not zero. If
zero is assigned, the next statement is ignored. So now
you understand what happens if you confuse the assignment with
the equality operator!

In all of the statements that test
the value of an expression, the if, while, do, and
for statements, the expression is simply tested to see if
its value is zero or not.

We will look at
each one in turn.

Control of flow
---------------

The if statement
~~~~~~~~~~~~~~~~

The if statement has two forms:

.. code-block:: C

    if(expression) statement

    if(expression) statement1
    else statement2

In the first form, if (and only if) the expression
is non-zero, the statement is executed. If the expression
is zero, the statement is ignored. Remember that the statement
can be compound; that is the way to put several
statements under the control of a single if.

The second form is like the first except that if
the statement shown as statement1 is selected then statement2 will
not be, and vice versa.

Either form is considered to be a single statement in
the syntax of C, so the following is completely legal.

.. code-block:: C

    if(expression)
        if(expression) statement

The first if (expression) is followed by a properly formed
, complete if statement. Since that is legally a statement, the
first if can be considered to read

.. code-block:: C

    if(expression) statement

and is therefore itself properly formed. The argument can be
extended as far as you like, but it's a
bad habit to get into. It is better style to
make the statement compound even if it isn't necessary.
That makes it a lot easier to add extra statements
if they are needed and generally improves readability.

The form involving else works the same way, so we
can also write this.

.. code-block:: C

    if(expression)
      if(expression)
        statement
      else
        statement

As :ref:`intro` has said already, this is now ambiguous.
It is not clear, except as indicated by the indentation,
which of the ifs is responsible for the else. If
we follow the rules that the previous example suggests, then
the second if is followed by a statement, and is
therefore itself a statement, so the else belongs to the
first if.

That is not the way that C views it. The
rule is that an else belongs to the first if
above that hasn't already got an else. In the
example we're discussing, the else goes with the second
if.

To prevent any unwanted association between an else and an
if just above it, the if can be hidden away
by using a compound statement. To repeat the example in
:ref:`intro`, here it is.

.. code-block:: C

    if(expression){
        if(expression)
                statement
    }else
        statement

Putting in all the compound statement brackets, it becomes this:

.. code-block:: C

    if(expression){
        if(expression){
            statement
        }
    }else{
        statement
    }

If you happen not to like the placing of the
brackets, it is up to you to put them where
you think they look better; just be consistent about it.
You probably need to know that this a subject on
which feelings run deep.

The while and do statements
~~~~~~~~~~~~~~~~~~~~~~~~~~~

The while is simple:

.. code-block:: C

    while(expression)
        statement

The statement is only executed if the expression is non-zero.
After every execution of the statement, the expression is
evaluated again and the process repeats if it is non-zero.
What could be plainer than that? The only point
to watch out for is that the statement may never
be executed, and that if nothing in the statement affects
the value of the expression then the while will either
do nothing or loop for ever, depending on the initial
value of the expression.

It is occasionally desirable to guarantee at least one execution
of the statement following the while, so an alternative form
exists known as the do statement. It looks like this:

.. code-block:: C

    do
        statement
    while(expression);

and you should pay close attention to that semicolon—it
is not optional! The effect is that the statement part
is executed before the controlling expression is evaluated, so this
guarantees at least one trip around the loop. It was
an unfortunate decision to use the keyword while for both
purposes, but it doesn't seem to cause too many
problems in practice.

If you feel the urge to use a do, think
carefully. It is undoubtedly essential in certain cases, but experience
has shown that the use of do statements is often
associated with poorly constructed code. Not every time, obviously, but
as a general rule you should stop and ask yourself
if you have made the right choice. Their use often
indicates a hangover of thinking methods learned with other languages,
or just sloppy design. When you do convince yourself that
nothing else will give you just what is wanted, then
go ahead - be daring—use it.

Handy hints
~~~~~~~~~~~

A very common trick in C programs is to use
the result of an assignment to control while and do
loops. It is so commonplace that, even if you look
at it the first time and blench, you've got
no alternative but to learn it. It falls into the
category of ‘idiomatic’ C and eventually becomes second nature to
anybody who really uses the language. Here is the most
common example of all:

.. literalinclude:: ../src/example3.2/src/example3.2.c
   :language: c
   :linenos:

Example 3.2

The clever bit is the expression assigning to input_c.
It is assigned to, compared with EOF (End Of File),
and used to control the loop all in one go.
Embedding the assignment like that is a handy embellishment. Admittedly
it only saves one line of code, but the benefit
in terms of readability (once you have got used to
seeing it) is quite large. Learn where the parentheses are,
too. They're necessary for precedence reasons—work out why!

Note that input_c is an int. This is because
getchar has to be able to return not only every
possible value of a char, but also an extra value,
EOF. To do that, a type longer than a char is necessary.

Both the while and the do statements are themselves syntactically
a single statement, just like an if statement. They occur
anywhere that any other single statement is permitted. If you
want them to control several statements, then you will have
to use a compound statement, as the examples of if illustrated.

The for statement
~~~~~~~~~~~~~~~~~

A very common feature in programs is loops that are
controlled by variables used as a counter. The counter doesn't
always have to count consecutive values, but the usual
arrangement is for it to be initialized outside the loop,
checked every time around the loop to see when to
finish and updated each time around the loop. There are
three important places, then, where the loop control is concentrated:
initialize, check and update. This example shows them.

.. literalinclude:: ../src/example3.3/src/example3.3.c
   :language: c
   :linenos:

Example 3.3

As you will have noticed, the initialization and check parts
of the loop are close together and their location is
obvious because of the presence of the while keyword. What
is harder to spot is the place where the update
occurs, especially if the value of the controlling variable is
used within the loop. In that case, which is by
far the most common, the update has to be at
the very end of the loop: far away from the
initialize and check. Readability suffers because it is hard to
work out how the loop is going to perform unless
you read the whole body of the loop carefully. What
is needed is some way of bringing the initialize, check
and update parts into one place so that they can
be read quickly and conveniently. That is exactly what the
for statement is designed to do. Here it is.

.. code-block:: C

    for (initialize; check; update) statement

The initialize part is an expression; nearly always an assignment
expression which is used to initialize the control variable. After
the initialization, the check expression is evaluated: if it is
non-zero, the statement is executed, followed by evaluation of
the update expression which generally increments the control variable, then
the sequence restarts at the check. The loop terminates as
soon as the check evaluates to zero.

There are two important things to realize about that last
description: one, that each of the three parts of the
for statement between the parentheses are just expressions; two, that
the description has carefully explained what they are intended to
be used for without proscribing alternative uses—that was done
deliberately. You can use the expressions to do whatever you
like, but at the expense of readability if they aren't
used for their intended purpose.

Here is a program that does the same thing twice,
the first time using a while loop, the second time
with a for. The use of the increment operator is
exactly the sort of use that you will see in everyday practice.

.. literalinclude:: ../src/example3.4/src/example3.4.c
   :language: c
   :linenos:

Example 3.4

There isn't any difference between the two, except that
in this case the for loop is more convenient and
maintainable than the while statement. You should always use the
for when it's appropriate; when a loop is being
controlled by some sort of counter. The while is more
at home when an indeterminate number of cycles of the
loop are part of the problem. As always, it needs
a degree of judgment on behalf of the author of
the program; an understanding of form, style, elegance and the
poetry of a well written program. There is no evidence
that the software business suffers from a surfeit of those
qualities, so feel free to exercise them if you are
able.

Any of the initialize, check and update expressions in
the for statement can be omitted, although the semicolons must
stay. This can happen if the counter is already initialized,
or gets updated in the body of the loop. If
the check expression is omitted, it is assumed to result
in a ‘true’ value and the loop never terminates. A
common way of writing never-ending loops is either

.. code-block:: C

    for(;;)

or

.. code-block:: C

    while(1)

and both can be seen in existing programs.

A brief pause
~~~~~~~~~~~~~

The control of flow statements that we've just seen
are quite adequate to write programs of any degree of
complexity. They lie at the core of C and even
a quick reading of everyday C programs will illustrate their
importance, both in the provision of essential functionality and in
the structure that they emphasize. The remaining statements are used
to give programmers finer control or to make it easier
to deal with exceptional conditions. Only the switch statement is
enough of a heavyweight to need no justification for its
use; yes, it can be replaced with lots of ifs,
but it adds a lot of readability. The others, break,
continue and goto, should be treated like the spices in
a delicate sauce. Used carefully they can turn something commonplace
into a treat, but a heavy hand will drown the
flavor of everything else.

The switch statement
~~~~~~~~~~~~~~~~~~~~

This is not an essential part of C. You could
do without it, but the language would have become significantly
less expressive and pleasant to use.

It is used to select one of a number of
alternative actions depending on the value of an expression, and
nearly always makes use of another of the lesser statements:
the break. It looks like this.

.. code-block:: C

    switch (expression){
    case const1:    statements
    case const2:    statements
    default:        statements
    }

The expression is evaluated and its value is compared with
all of the const1 etc. expressions, which must all evaluate
to different constant values (strictly they are integral constant expressions,
see :ref:`structs` and below). If any of them has
the same value as the expression then the statement following
the case label is selected for execution. If the default
is present, it will be selected when there is no
matching value found. If there is no default and no
matching value, the entire switch statement will do nothing and
execution will continue at the following statement.

One curious feature is that the cases are not exclusive, as this example shows.

.. literalinclude:: ../src/example3.5/src/example3.5.c
   :language: c
   :linenos:

Example 3.5

The loop cycles with i having values 0–10. A
value of 1 or 2 will cause the printing of
the message 1 or 2 by selecting the first of
the printf statements. What you might not expect is the
way that the remaining messages would also appear! It's
because the switch only selects one entry point to the
body of the statement; after starting at a given point
all of the following statements are also executed. The case
and default labels simply allow you to indicate which of
the statements is to be selected. When i has the
value of 7, only the last two messages will be
printed. Any value other than 1, 2, or 7 will
find only the last message.

The labels can occur in any order, but no two
values may be the same and you are allowed either
one or no default (which doesn't have to be
the last label). Several labels can be put in front
of one statement and several statements can be put after
one label.

The expression controlling the switch can be of any of
the integral types. Old C used to insist on only
int here, and some compilers would forcibly truncate longer types,
giving rise on rare occasions to some very obscure bugs.

The major restriction
^^^^^^^^^^^^^^^^^^^^^

The biggest problem with the switch statement is that it
doesn't allow you to select mutually exclusive courses of
action; once the body of the statement has been entered
any subsequent statements within the body will all be executed.
What is needed is the break statement. Here is the
previous example, but amended to make sure that the messages
printed come out in a more sensible order. The break
statements cause execution to leave the switch statement immediately and
prevent any further statements in the body of the switch
from being executed.

.. literalinclude:: ../src/example3.6/src/example3.6.c
   :language: c
   :linenos:

Example 3.6

The break has further uses. Its own section follows soon.

Integral Constant Expression
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Although :ref:`structs` deals with constant expressions, it is worth
looking briefly at what an integral constant expression is, since
that is what must follow the case labels in a
switch statement. Loosely speaking, it is any expression that does
not involve any value-changing operation (like increment or assignment),
function calls or comma operators. The operands in the expression
must all be integer constants, character constants, enumeration constants, sizeof
expressions and floating-point constants that are the immediate operands
of casts. Any cast operators must result in integral types.

Much what you would expect, really.

The break statement
~~~~~~~~~~~~~~~~~~~

This is a simple statement. It only makes sense if
it occurs in the body of a switch, do, while
or for statement. When it is executed the control of
flow jumps to the statement immediately following the body of
the statement containing the break. Its use is widespread in
switch statements, where it is more or less essential to
get the control that most people want.

The use of the break within loops is of dubious
legitimacy. It has its moments, but is really only justifiable
when exceptional circumstances have happened and the loop has to
be abandoned. It would be nice if more than one
loop could be abandoned with a single break but that
isn't how it works. Here is an example.

.. literalinclude:: ../src/example3.7/src/example3.7.c
   :language: c
   :linenos:

Example 3.7

It reads a single character from the program's input
before printing the next in a sequence of numbers. If
an ‘s’ is typed, the break causes an exit from the loop.

If you want to exit from more than one level
of loop, the break is the wrong thing to use.
The goto is the only easy way, but since it
can't be mentioned in polite company, we'll leave
it till last.

The continue statement
~~~~~~~~~~~~~~~~~~~~~~

This statement has only a limited number of uses. The
rules for its use are the same as for break,
with the exception that it doesn't apply to switch
statements. Executing a continue starts the next iteration of the
smallest enclosing do, while or for statement immediately. The use
of continue is largely restricted to the top of loops,
where a decision has to be made whether or not
to execute the rest of the body of the loop.
In this example it ensures that division by zero (which
gives undefined behavior) doesn't happen.

.. literalinclude:: ../src/example3.8/src/example3.8.c
   :language: c
   :linenos:

Example 3.8

You could take a puritanical stance and argue that, instead
of a conditional continue,, the body of the loop should
be made conditional instead—but you wouldn't have many
supporters. Most C programmers would rather have the continue than
the extra level of indentation, particularly if the body of
the loop is large.

Of course the continue can be used in other parts
of a loop, too, where it may occasionally help to
simplify the logic of the code and improve readability. It
deserves to be used sparingly.

Do remember that continue has no special meaning to a
switch statement, where break does have. Inside a switch, continue
is only valid if there is a loop that encloses
the switch, in which case the next iteration of the
loop will be started.

There is an important difference between loops written with while
and for. In a while, a continue will go immediately
to the test of the controlling expression. The same thing
in a for will do two things: first the update
expression is evaluated, then the controlling expression is evaluated.

goto and labels
~~~~~~~~~~~~~~~

Everybody knows that the goto statement is a ‘bad thing’.
Used without care it is a great way of making
programs hard to follow and of obscuring any structure in
their flow. Dijkstra wrote a famous paper in 1968 called
‘Goto Statement Considered Harmful’, which everybody refers to and almost
nobody has read.

What's especially annoying is that there
are times when it is the most appropriate thing to
use in the circumstances! In C, it is used to
escape from multiple nested loops, or to go to an
error handling exit at the end of a function. You
will need a label when you use a goto; this example shows both.

.. code-block:: C

    goto L1;
    /* whatever you like here */
    L1: /* anything else */

A label is an identifier followed by a colon. Labels
have their own ‘name space’ so they can't clash
with the names of variables or functions. The name space
only exists for the function containing the label, so label
names can be re-used in different functions. The label
can be used before it is declared, too, simply by
mentioning it in a goto statement.

Labels must be part of a full statement, even if
it's an empty one. This usually only matters when
you're trying to put a label at the end
of a compound statement—like this.

.. code-block:: C

    label_at_end: ; /* empty statement */
    }

The goto works in an obvious way, jumping to the
labeled statements. Because the name of the label is only
visible inside its own function, you can't jump from
one function to another one.

It's hard to give rigid rules about the use
of gotos but, as with the do, continue and the
break (except in switch statements), over-use should be avoided.
Think carefully every time you feel like using one, and
convince yourself that the structure of the program demands it.
More than one goto every 3–5 functions is a
symptom that should be viewed with deep suspicion.

Summary
~~~~~~~

Now we've seen all of the control of flow
statements and examples of their use. Some should be used
whenever possible, some are not for use line by line
but for special purposes where their particular job is called
for. It is possible to write elegant and beautiful programs
in C if you are prepared to take the extra
bit of care necessary; the specialized control of flow statements
give you the chance to add the extra polish that
some other languages lack.

All that remains to be done
to complete the picture of flow of control in C
is to finish off the logical operators.

More logical expressions
------------------------

This chapter has already shown how C makes no distinction
between ‘logical’ and other values. The relational operators all give
a result of 0 or 1 for false and true,
respectively. Whenever the control of flow statements demand it, an
expression is evaluated to determine what to do next. A
0 means ‘don't do it’; anything else means ‘do’.
It means that the fragments below are all quite reasonable.

.. code-block:: C

    while (a<b)...
    while (a)....
    if ( (c=getchar()) != EOF )...

No experienced C programmer would be surprised by any of
them. The second of them, while (a), is a common
abbreviation for while (a != 0), as you should be able
to work out.

What we need now is a way of writing more
complicated expressions involving these logical true and false values. So
far, it has to be done like this, when we
wanted to say if(a<b AND c<d)

.. code-block:: C

    if (a < b){
          if (c < d)...
    }

It will not be a source of great amazement to
find that there is a way of expressing such a
statement.

There are three operators involved in this sort of operation:
the logical AND &&, the logical OR || and the NOT !. The
last is unary, the other two are binary. All of
them take expressions as their operands and give as results
either 1 or 0. The && gives 1 only when both
of its operands are non-zero. The || gives 0 only
when both operands are zero. The ! gives 0 if its
operand is non-zero and vice versa. Easy really. The
results are of type int for all three.

Do not confuse & and | (the bit-wise operators) with their logical
counterparts. They are not the same.

One special feature of
the logical operators, found in very few of the other
operators, is their effect on the sequence of evaluation of
an expression. They evaluate left to right (after precedence is
taken into account) and every logical expression ceases evaluation as
soon as the overall result can be determined. For example,
a sequence of ||s can stop as soon as one
operand is found to be non-zero. This next fragment
guarantees never to divide by zero.

.. code-block:: C

    if (a!=0 && b/a > 5)...
    /* alternative */
    if (a && b/a > 5)

In either version b/a will only be evaluated if
a is non-zero. If a were zero, the overall
result would already have been decided, so the evaluation must
stop to conform with C's rules for the logical
operators.

The unary NOT is simple. It isn't all
that common to see it in use largely because most
expressions can be rearranged to do without it. The examples
show how.

.. code-block:: C

    if (!a)...
    /* alternative */
    if (a==0)...

.. code-block:: C

    if(!(a>b))
    /* alternative */
    if(a <= b)

.. code-block:: C

    if (!(a>b && c<d))...
    /* alternative */
    if (a<=b || c>=d)...

Each of the examples and the alternatives serve to show
ways of avoiding (or at least doing without) the ! operator.
In fact, it's most useful as an aid to
readability. If the problem that you are solving has a
natural logical relationship inherent in it—say the (b*b-4*a*c) > 0
found in quadratic equation solving—then
it probably reads better if you write if( !((b*b-4*a*c) > 0))
than if( (b*b-4*a*c) <= 0) —
but it's up to you. Pick the
one that feels right.

Most expressions using these logical operators work out just about
right in terms of the precedence rules, but you can
get a few nasty surprises. If you look back to
the precedence tables, you will find that there are some
operators with lower precedence than the logical ones. In particular,
this is a very common mistake:

.. code-block:: C

    if(a&b == c){...

What happens is that b is compared for equality with
c, then the 1 or 0 result is anded with
a! Some distinctly unexpected behavior has been caused by that
sort of error.

Strange operators
-----------------

There are two operators left to mention which look
decidedly odd. They aren't ‘essential’, but from time
to time do have their uses. Don't ignore
them completely. This is the only place where we
describe them, so our description includes what happens when
they are mixed with pointer types, which makes them
look more complicated than they really are.

The ?: operator
~~~~~~~~~~~~~~~

Like playing the accordion, this is easier to demonstrate than to describe.

.. code-block:: C

    expression1?expression2:expression3

If expression1 is true, then the result of the whole
expression is expression2, otherwise it is expression3; depending on the
value of expression1, only one of them will be evaluated
when the result is calculated.

The various combinations of types
that are permitted for expression2 and expression3 and, based on
those, the resulting type of the whole expression, are complicated.
A lot of the complexity is due to types and
notions that we haven't seen so far. For completeness
they are described in detail below, but you'll have
to put up with a number of forward references.

The easiest case is when both expressions have arithmetic type
(i.e. integral or real). The usual arithmetic conversions are
applied to find a common type for both expressions and
then that is the type of the result. For example

.. code-block:: C

    a>b?1:3.5

contains a constant (1) of type int and another (3.5)
of type double. Applying the arithmetic conversions gives a
result of type double.

Other combinations are also permitted.

    If both operands are of compatible structure or union types,
    then that is the type of the result.

    If both operands have void type, then that is the
    type of the result.

Various pointer types can be mixed.

    Both operands may be pointers to (possibly qualified) compatible types.

    One operand may be a pointer and the other a null pointer constant.

    One operand may be a pointer to an object or
    incomplete type and the other a pointer to (possibly qualified) void.

The type of the result when pointers are involved is
derived in two separate steps.

    If either of the operands is a pointer to a
    qualified type, the result is a pointer to a type
    that is qualified by all the qualifiers of both operands.

    If one operand is a null pointer constant, then the
    result has the type of the other operand. If one
    operand is a pointer to void, the other operand is
    converted to pointer to void and that is the type
    of the result. If both operands are pointers to compatible
    types (ignoring any qualifiers) the the result has the composite
    type.

Qualifiers, composite types and compatible types are all subjects discussed
later.

The shortest useful example that we can think of is
this one, where the string to be printed by printf
is selected using this magical operator.

.. literalinclude:: ../src/example3.9/src/example3.9.c
   :language: c
   :linenos:

Example 3.9

It's cute when you need it, but the first
time that they see it most people look very uncomfortable
for a while, then recollect an urgent appointment somewhere else.

After evaluating the first operand there is one of the
sequence points described in :ref:`specialized`.

The comma operator
~~~~~~~~~~~~~~~~~~

This wins the prize for ‘most obscure operator’. It allows
a list of expressions to be separated by commas:

.. code-block:: C

    expression-1,expression-2,expression-3,...,expression-n

and it goes on as long as you like. The
expressions are evaluated strictly left to right and their values
discarded, except for the last one, whose type and value
determine the result of the overall expression. Don't confuse
this version of the comma with any of the other
uses C finds for it, especially the one that separates
function arguments. Here are a couple of examples of it in use.

.. literalinclude:: ../src/example3.10/src/example3.10.c
   :language: c
   :linenos:

Example 3.10

Unless you are feeling very adventurous, the comma operator is
just as well ignored. Be prepared to see it only
on special occasions.

After evaluating each operand there is one of the sequence
points described in :ref:`specialized`.


Summary
-------

This chapter has described the entire range of control of
flow available in C. The only areas that cause even
moderate surprise are the way in which cases in a
switch statement are not mutually exclusive, and the fact that
goto cannot transfer control to any function except the one
that is currently active. None of this is intellectually deep
and it has never been known to cause problems either
to beginners or programmers experienced in other languages.

The logical
expressions all give integral results. This is perhaps slightly unusual,
but once again takes very little time to learn.

Probably the most surprising part about the whole chapter will have
been to learn of the conditional and comma operators. A
strong case could be made for the abolition of the
conditional operator, were it not for compatibility with existing code,
but the comma operator does have important uses, especially for
automatic generators of C programs.

The Standard has not had
much effect on the contents of this chapter. Prospective users
of C should ensure that they are completely familiar with
all of the topics discussed here (except the conditional and
comma operators). They are essential to the practical use of
the language, and none of the material is hard.

Exercises
---------

Exercise 3.1. What is the type and value of the result of
the relational operators?

Exercise 3.2. What is the type and value of the result of
the logical operators ( &&, ||, and ! )?

Exercise 3.3. What is unusual about the logical
operators?

Exercise 3.4. Why is break useful in switch
statements?

Exercise 3.5. Why is continue not very useful in
switch statements?

Exercise 3.6. What is a possible problem using continue
in while statements?

Exercise 3.7. How can you jump from one function
to another?
