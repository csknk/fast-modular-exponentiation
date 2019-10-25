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
2. If _b_ and _e_ are large, a lot of multiplications are required. The universe might not last long enough for us to carry out the computation…

Slightly Less Naive Approach
----------------------------
For multiplication (mod _m_) congruence is maintained. In other words:

if a ≡ x (mod m) then a ∙ k ≡ x (mod m) 

It follows that if we're just concerned with congruences (i.e. the residue mod m), multiplying the congruences provides the same result as multiplying the factors and then taking the result modulo m:

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

From rules of indices:

(b<sup>e</sup>)<sup>f</sup> = b<sup>ef</sup>

For example, this allows a⁸, can be represented as ((a²)²)².

If you calculate a⁸ naively:

`a⁸ = a ∙ a ∙ a ∙ a ∙ a ∙ a ∙ a ∙ a`

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

Exponent is Not Necessarily a Power of Two
------------------------------------------
The previous algorithm gets us on the right track, but it has a major limitation - it only works if the exponent is a power of two.

We can however take the principle and generalise it so that it works for any number.

The idea is to take any number represented as the summation of powers of two - which as luck would have it, is exactly the way that modern computers represent numbers - and to create a running total of the required squares.

Example:

a<sup>11</sup> = a<sup>8</sup> ∙ a<sup>2</sup> ∙ a<sup>1<sup>

...Notice that 8, 2 and one are powers of 2 (3, 1 and 0 respectively).

We can get the answer by working through each power of two up to the maximum possible given the size of e, squaring the base at each stage and only adding the squares to the result if the given power of two is a factor in the exponent. 

### Algorithm
Given a base `b`, an exponent `e` and modulo `m`, compute b<sup>e</sup> (mod m):

1. Create an integer (or long) variable called `result` and set this result equal to 1.
2. Check the least significant bit (2⁰) of the exponent e. If it is 1, set `result` equal to `base`.
2. Check each bit in the exponent by iteratively bitshifting and masking against 1 - this checks each position in order, starting from the second-least-significant bit (we have already considered the least significant bit in stage 2.
3. Start a loop
4. At each iteration, set `base` equal to the value of the previous `base` squared, modulo `m`
5. At each stage, if the LSB of `e` is set, set `result` equal to the product of the previous `result` and the current `base` (which is the previous base squared, as described in stage 3), all modulo `m`
6. When the value of `e` is NULL, end the loop
7. The value of result is the product of all b to the power of two for all powers of two that constitute the exponent. 

In summary, set the result to be 1. Starting from the least significant bit of the exponent, iteratively check each bit - which denotes that the particular power of two is a component of the exponent. Square the base modulo m at each stage. If the exponent bit is set, multiply the base with the current result, modulo m. The final result is the base raised to the exponent mod m - the product of a set of base raised to exponents that constitute the original exponent broken into powers of two.  

### Example: C
```c

int fastExp(int b, int e, int m)
{
	int result = 1;
	if (1 & e)
		result = b;
	while (1) {
		if (!e) break;
		e >>= 1;
		b = (b * b) % m;
		if (e & 1)
			result = (result * b) % m;
	}
	return result;
}
```

References
----------
* [Modular Arithmetic, Khan Academy][1], with practice quizzes
* [Intro to modular exponentiation][2], You Tube, Mark's Education Tutorials
* [Modular Exponentiation Made Easy][3], Randall Heyman YouTube

[1]: https://www.khanacademy.org/computing/computer-science/cryptography#modarithmetic
[2]: https://www.youtube.com/watch?v=DtV4Fwvn0e8
[3]: https://www.youtube.com/watch?v=tTuWmcikE0Q
