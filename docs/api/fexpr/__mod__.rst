
.. xmethod:: datatable.FExpr.__mod__
    :src: src/core/expr/fbinary/fexpr__mod__.cc evaluate1
    :tests: tests/expr/fbinary/test-mod.py

    __mod__(x, y)
    --

    Compute the remainder of division of two FExprs, i.e. ``x % y``.

    The modulus and integer division together satisfy the identity
    that ``x == (x // y) * y + (x % y)`` for all non-zero values of `y`.
    In addition, the result of ``x % y`` is always in the range
    ``[0; y)`` for positive ``y``, and in the range ``(y; 0]`` for
    negative ``y``.

    If `x` or `y` are multi-column expressions, then they must have the
    same number of columns, and the `%` operator will be applied to each
    corresponding pair of columns. If either `x` or `y` are single-column
    while the other is multi-column, then the single-column expression
    will be repeated to the same number of columns as its opponent.

    The integer division operation can only be applied to integer columns.
    The resulting column will have stype equal to the largest of the stypes
    of both columns, but at least ``int32``.


    Parameters
    ----------
    x, y: FExpr
        The arguments must be either `FExpr`s, or expressions that can be
        converted into `FExpr`s.

    return: FExpr
        An expression that evaluates `x % y`.


    See also
    --------
    - :meth:`x // y <FExpr.__floordiv__>` -- integer division operator.
