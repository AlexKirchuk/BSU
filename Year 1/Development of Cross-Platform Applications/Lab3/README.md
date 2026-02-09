# Lab 3 — Regular Expressions

## Description

This laboratory work is dedicated to working with **regular expressions** in C++.

The lab includes several tasks implemented using both:

* **STL (`std::regex`)**
* **Qt (`QRegularExpression`)**

The goal is to compare the capabilities, syntax, and convenience of standard C++ regular expressions and their Qt counterparts.

---

## Task 1 — Text File Processing (STL)

### Tools

* C++ Standard Library
* `std::regex`

### Problem Statement

Given a text file `Input.txt` consisting of words separated by a set of punctuation characters:

* Read the first line of the file
* For each subsequent line, remove all words that occur in the first line
* Write the processed text into a new file `Output.txt`

Word separation is performed using regular expressions.

---

## Task 2 — String Processing (Qt)

### Tools

* Qt framework
* `QString`
* `QRegularExpression`

### Problem Statement

Given a string with words separated by an arbitrary set of delimiters:

* In a single pass over the string characters, find all words containing the **maximum number of distinct characters**
* Store these words in a new string
* Separate words in the resulting string by **exactly one space**

The task demonstrates string analysis using Qt regular expressions.

---

## Task 3 — URL Validation (STL and Qt)

### Tools

* `std::regex`
* `QRegularExpression`

### Problem Statement

It is required to write a regular expression that determines whether a given string is a **valid URL**.

Valid URLs must satisfy the following conditions:

* Supported protocols: `http`, `https` (protocol may be omitted)
* Only symbolic domain names are allowed (IP addresses are not permitted)
* Subdomains are allowed
* Optional port specification using a colon is allowed
* Access to subdirectories is allowed
* GET parameters are allowed
* Anchor fragments using `#` are allowed
* Single-letter domain names are forbidden
* Special symbols are forbidden at the beginning and end of domain names
* The `_` character and spaces are forbidden in domain names

The regular expression should correctly classify valid and invalid URLs based on the provided test set.

### Test Data

```
std::vector<std::string> URLs =
{
    "http://www.zcontest.ru",
    "http://zcontest.ru",
    "http://zcontest.com",
    "https://zcontest.ru",
    "https://sub.zcontest-ru.com:8080",
    "http://zcontest.ru/dir%201/dir_2/program.ext?var1=x&var2=my%20value",
    "zcon.com/index.html#bookmark",
    "Just Text.",
    "http://a.com",
    "http://www.domain-.com",
};
```

---

## Purpose of the Lab

* Learn to use regular expressions in C++
* Compare `std::regex` and `QRegularExpression`
* Practice text and string processing using regex
* Develop complex validation patterns

---

## Conclusion

This laboratory work demonstrates practical usage of regular expressions for text processing and validation tasks and highlights the differences between STL and Qt approaches.
