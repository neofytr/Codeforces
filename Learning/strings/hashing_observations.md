# Rolling Hashes -- Detailed Construction

---

## 22. Rolling Hashes (String Hashing)

**Setup.** Convert string s[0..n-1] to str[1..n] with str[i] = s[i-1]-'a'+1.
Choose base p and modulus MOD.

**Hash definition:**

    hash(l, r) = sum_{i=l}^{r} str[i] * p^{r-i}  (mod MOD)

**Prefix hash array:** h[0] = 0, h[i] = (h[i-1]*p + str[i]) % MOD.

**Range hash:**

    hash(l, r) = (h[r] - h[l-1] * pow_p[r-l+1] % MOD + MOD) % MOD

where pow_p[k] = p^k mod MOD is precomputed.

**Properties:**
- Equal strings -> guaranteed same hash.
- Different strings -> same hash with probability ~1/MOD (collision).
- Use double hashing (two different (p, MOD) pairs) to reduce collision
  probability to ~1/MOD^2.

**Common bases:** p = 31 (lowercase only), p = 131 (general ASCII).
**Common moduli:** Large primes like 1e9+7, 1e9+9. Or use __int128 with
MOD = 2^61 - 1 for speed.
