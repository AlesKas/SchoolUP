def FibIdeal(n):

    a = 0
    b = 1
    if n == 0:
        return a
    elif n == 1:
        return b
    for _ in range(2, n+1):
        c = a + b
        a = b
        b = c
    return b

print(FibIdeal(9))