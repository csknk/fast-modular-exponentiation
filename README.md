Fast Modular Exponentiation
===========================
Modular exponentiation is used in public key cryptography. It involves exponentiation of a base integer over a modulus.

```
_c_ ← _b_<sup>e</sup> (mod _m_) 
```
You could brute-force this problem by multiplying _b_ by itself _e_ - 1 times, but it is important to have __fast__ (efficient) algorithms for this process.

In cryptography, the numbers involved are usually very large. Without an efficient algorithm, the process would take too long.

This article is educational - it is a summary of what I have learned about the process of modular exponentiation, with a few code implementations of a possible algorithm rather than a presentation of the most efficient methods.

Naive Exponentiation
--------------------



