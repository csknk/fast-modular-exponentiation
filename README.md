Fast Modular Exponentiation
===========================
Modular exponentiation is used in public key cryptography.

It involves computing _b_ to the power _e_ (mod _m_):

_c_ ← _b_<sup>e</sup> (mod _m_) 

You could brute-force this problem by multiplying _b_ by itself _e_ - 1 times, but it is important to have __fast__ (efficient) algorithms for this process.

In cryptography, the numbers involved are usually very large. Without an efficient algorithm, the process would take too long.

This article is educational - it is a summary of what I have learned about the process of modular exponentiation, with a few code implementations of a possible algorithm rather than a presentation of the most efficient methods.

Naive Exponentiation
--------------------
THe most basic approach would be to multiply _b_ by itself _e_ - 1 times, and performing floor division on the result to obtain the result modulo _m_ (which will be the remainder or residue of floor division of the result by the modulus). There are a few problems with this approach:

1. If _b_ and _e_ are large numbers, _b_<sup>e</sup> will be enormous - which causes problems representing the resultant data as a native type in many languages/systems.
2. If _b_ and _e_ are large, a lot of multiplications are required

Slightly Less Naive Approach
----------------------------
For multiplication (mod _m_) congruence is maintained. In other words:

if a ≡ x (mod m) then a ∙ k ≡ x (mod m) 

It follows that if we're just concerned with congruences (i.e. the residue mod m), multiplying the congruencesprovides the same result as multiplying the factors and then taking the result modulo m:

If a ∙ b ≡ x (mod m), then a (mod m) ∙ a (mod m) ≡ x (mod m)

In terms of an exponentiation algorithm, multiplying the result modulo _m_ at each step leads to much smaller numbers which spares computational resources.

### Slightly Better Algorithm
For _c_ ← _b_<sup>e</sup> (mod _m_)

Start with 1, multiply by _b_, take the result mod(_m_), repeat _e_ times.

In other words:
1. Start with _c_ ← 1
2. Repeat _e_ times: _c_ ← _c_ ∙ _b_ mod _m_


Exponent is a Power of Two
--------------------------
If _c_ ← _b_<sup>e</sup> (mod _m_) and 

_e_ = 2<sup>k</sup>

We can compute _c_ using the "squares" method - this allows for fast computation of large positive integer powers of a number.

For example, a⁸, can be represented as ((a²)²)².

If you calculate a⁸ naively:

a⁸ = _a_ ∙ _a_ ∙ _a_ ∙ _a_ ∙ _a_ ∙ _a_ ∙ _a_ ∙ _a_

...7 multiplications are required (the exponent - 1).

Alternatively, computing `a⁸` as `((a²)²)²` requires three multiplications:

a ∙ a = s₁
s₁ ∙ s₁ = s₂, where s₂ is equivalent to (a²)²
s₂ ∙ s₂ = s₃, where s₃ is equivalent to ((a²)²)²

In this way, `aⁿ` requires no more than 2 log₂(_e_) multiplications, where _e_ is the exponent.

So long as our exponent is a power of 2, and we multiply congruences at each stage, we have an efficient algorithm that can be converted to code:

### Example Code: Exponent is a Power of 2
```python
#!/usr/bin/env python3

def exponent_power_of_2(a, e_power2, mod):
    for i in range (0, e_power2):
        a = (a * a) % mod
    return a
```
