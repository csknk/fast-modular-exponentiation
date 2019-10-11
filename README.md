Fast Modular Exponentiation
===========================
Modular exponentiation is used in public key cryprography. It involves exponentiation over a modulus.

```
_c_ ← _b_<sup>e</sup> (mod _m_) 
```

It is important to have __fast__ (efficient) algorithms for this process - in cryptography, the numbers involved are usually very large. Without an efficient algorithm, the process would take too long.

This article is educational - it is a summary of what I have learned about the process of modular exponentiation, rather than a presentation of the most efficient methods.

Naive Exponentiation
--------------------


