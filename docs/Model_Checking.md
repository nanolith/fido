Model Checking
==============

Model checking is an entirely different process than unit testing. Unit testing
verifies behavior based on specific inputs. Unit tests ensure that software
performs specific scenarios as expected. It is expensive to build unit tests
that have 100% branch coverage. Model checks complement unit tests by providing,
through abstract interpretation, a way to simultaneously verify every function
input and output in order to find counter-examples where there is a safety issue
or where function contracts fail. It is expensive to build model checks that
cover every explicit scenario one would normally unit test, so instead, these
checks are generalized through non-determinism.

Non-determinism in satisfiability is not the same as fuzzing or randomness.
Instead, bits are left floating. In the case of a model checker, outcomes are
inverted.  The SAT solver is tasked with solving for any scenario in which a
safety issue occurs or a function contract fails. Ultimately, these input bits
are set with the specific sequence required to cause a failure.

Model checking is a decision problem. We set up scenarios that ensure, through
non-determinism of function parameters, that every possible branch is followed.
From here, we can ensure that, for any input, memory safety, UB safety, and
function contracts are upheld. State space for decision problems grow
combinatorially with lines of code. Further, loops and recursion must be
unwound. Model checking a complete program is thus far too computationally
expensive to be feasible. Instead, we break down and isolate functions. For
isolation, we build _shadow_ functions to replace any function that a given
function calls. These functions follow the same contract as the original
functions, but their behavior is non-deterministic over the range of expected
behavior.

Function Contracts and Hoare Triples
------------------------------------

This program is decomposed into functions, representing commands (C). For each
function, we specify function contracts representing preconditions (P) and
postconditions (Q).  All together, these form [Hoare Triples][hoare-triple] in
the form of:

    {P} C {Q}

[hoare-triple]: https://en.wikipedia.org/wiki/Hoare_logic 

For each function contract, we want to ensure that parameters follow data
structure invariants and specific input domains required by the function. We
also want to ensure that the function can read and write the memory for any
pointer over the range provided or assumed. Further, we want to describe
ownership changes. If a function is an object source or sink, this should be
specified in the contract. The model checker can trace memory leaks, UAF, and
other related issues, but the contract allows us to confirm that an output
variable for a source either contains the newly created instance on success or
`NULL` on failure.

Shadow Function Selection
-------------------------

As mentioned previously, to reduce state space explosions, functions are
isolated by replacing any function that they call with _shadow functions_. These
functions follow the same contracts as the original functions but have
non-deterministic behavior. Functions rarely exist in a vacuum. When functions
have side-effects, such as participating in the lifecycle of an object or a
descriptor, then this behavior needs to be simulated with an appropriate level
of fidelity to the original function. For instance, file I/O may need to track
the creation of a file descriptor via `open` so that it can be later reclaimed
by `close`. Likewise, `read` and `write` would need to ensure that this
descriptor is currently valid as part of their function contracts.

However, when testing a function that only performs I/O for a given descriptor,
it's enough for the function to specify, as part of its contract, that this is a
valid descriptor. If this is assumed for the sake of the model check, then a
simpler form of these standard Unix functions can be shadowed. Build shadow
functions with as much simulation as is needed, and no more.
