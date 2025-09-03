# Idea
I am by no means versed in internationalization or localization in any manner.  According to [gnu gettext] docs, there is `catgets`, and `gettext`, and I'm sure there are others.
These libraries use interfaces such as:
`init(...);`
`get(...);`
The problem is this is wide open to errors, missing values, and other inconsistencies.

My thought is to simplify this somewhat for the programmer.  The programmer primarily wants to deal in variables and functions and not managing excessive logic.  So optimally retrieving a particular string to display to the user would be as easy as `printf(working_directory_warning)` or (especially for internationalized plurals etc) `printf(file_count_notice(n))`.  Such an interface could be wrapped around these libraries manually, but I'd like to look into handling these somewhat automatically via dynamic linking where each each language essentially constructs a dynamic library that gets loaded, and such symbols are bound/loaded (much like opengl), and you're done.
Requiring to load an executable library does put a constraint on the system that is perhaps undesirable, but this is my starting point for now.

[gnu gettext]: [https://www.gnu.org/software/gettext/manual/gettext.html#Programmers]