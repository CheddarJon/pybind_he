import emb

def multiply(a,b):
    print("Will compute", a, "times", b)
    c = 0
    for i in range(0, a):
        c = c + b
    return c

def multMod(arg):
    a, b, c = emb.getarg(arg)
    print("Will compute", a, "time", b, "mod", c)
    return (a * b) % c
