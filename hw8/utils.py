import numpy as np
import gmpy2
from numpy.random import randint


# Modular Exponentiation
# m is base, d is power, n is module
def mod_exp(m, d, n):
    x = 1
    while d:
        if d&1:
            x = x*m % n
        m = m * m % n
        d = d >> 1
    return x


# generate random number until a prime
def gen_rand_prime(bit):
    while 1:
        num = gmpy2.mpz(1)
        a = randint(0, 2, bit)
        for i in a:
            num = num * 2 + i
        if gmpy2.is_prime(num):
            break
    return num


# extended Euclidean Algorithm
def eea(a, b):
    if a==b:
        return a, 0, 1
    agb = True
    if a<b:
        a, b = b, a
        agb = False
    r0 = b
    r1 = a
    s0 = 0
    s1 = 1
    t0 = 1
    t1 = 0
    while r0:
        q = int(r1/r0)
        r1, r0 = r0, r1-q*r0
        s1, s0 = s0, s1-q*s0
        t1, t0 = t0, t1-q*t0
    if agb is False:
        s1, t1 = t1, s1
    return r1, s1, t1
