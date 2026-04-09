# Useful `scanf` Tricks in C

`scanf` is a powerful function in C for reading formatted input. While it does not support full regular expressions, it offers useful pattern-matching capabilities using format specifiers and scansets.

---

## **1. Basic Input**
```c
int x;
scanf("%d", &x);  // Reads an integer
```
- `%d` - Integer
- `%f` - Floating-point number
- `%c` - Single character
- `%s` - String (stops at whitespace)

---

## **2. Reading Strings with Spaces**
By default, `%s` stops at spaces. To read a full line:
```c
char str[100];
fgets(str, sizeof(str), stdin);  // Reads the entire line
```

Alternatively, use `scanf` with a scanset:
```c
scanf("%[^"]", str);  // Reads until a newline
```

---

## **3. Using Scanset `[ ]` to Match Specific Characters**

### **Read Only Lowercase Letters**
```c
char str[100];
scanf("%[a-z]", str);  // Reads only lowercase letters
```
**Input:** `hello123`

**Output:** `"hello"` (stops at `1`)

### **Read Only Alphanumeric Characters**
```c
scanf("%[a-zA-Z0-9]", str);  
```
**Input:** `abc123!@#`

**Output:** `"abc123"` (stops at `!`)

---

## **4. Using Negated Scanset `[^ ]` to Exclude Certain Characters**

### **Read Until a Space**
```c
scanf("%[^ ]", str);  // Reads everything until a space
```
**Input:** `hello world`

**Output:** `"hello"`

### **Read Until a Comma**
```c
scanf("%[^,]", str);
```
**Input:** `hello,world`

**Output:** `"hello"` (stops at `,`)

---

## **5. Reading Fixed-Length Input**
### **Read Exactly 3 Digits**
```c
int num;
scanf("%3d", &num);
```
**Input:** `123456`

**Output:** `123`

---

## **6. Skipping Characters Using `%*`**

### **Skip an Integer and Read a String**
```c
int num;
char str[100];
scanf("%*d %s", str);  // Skips the first integer and reads a string
```
**Input:** `42 hello`

**Output:** `str = "hello"`

### **Skip Certain Characters**
```c
scanf("%*[^0-9]%d", &num);  // Skips all non-numeric characters and reads an integer
```
**Input:** `abc123xyz`

**Output:** `num = 123`

---

## **7. Handling Newlines and Whitespace**

- `scanf("%d", &x);` leaves a newline in the buffer.
- Use `scanf("%d\n", &x);` to consume the newline.
- Better alternative: `getchar()` after `scanf()` to consume unwanted characters.

---

## **8. Reading a Full Line with `scanf`**
```c
scanf("%[^"]", str);  // Reads until a newline
```
Alternatively, use:
```c
fgets(str, sizeof(str), stdin);
```

---

## **Limitations of `scanf`**
🚫 Cannot handle complex patterns like full regex.
🚫 Stops reading at first non-matching character.
🚫 `%s` doesn’t check buffer overflow (use `%99s` for safety).

For **full regex support**, use `regex.h` in C.

---


