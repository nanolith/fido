Config Scanner
=============

Lexical analysis for the config file is performed using a hand-written scanner.
This scanner was written by hand so that it could be built up via model
checking. The scanner is decomposed into functions to simplify model checking.

Each function is model checked independently. To make these model checks easier
to understand, functions are split between _read_ and _complete_ functions. The
_read_ functions exist as a convenience for model checking; they replicate the
steps performed in the token read function that are specific for scanning a
specific token type. The _complete_ functions are called by the token read
function.

When model checking the token read function, each of the _complete_ functions
can be shadowed. When model checking the token peek function, the token read
function can be shadowed.

Downstream, the scanner itself can be shadowed when model checking the parser.
