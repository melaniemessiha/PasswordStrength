# Password Strength Meter

# Overview
This C program validates passwords based on a set of configurable rules read from text files. It checks various criteria, including length, character variety, and optional requirements, ensuring that passwords meet specified security standards. This tool can be particularly useful for applications requiring robust password security, such as user registration and account management systems.

# Features
Configurable Rules: The program supports reading configuration settings from text files, allowing easy adjustments to password requirements.<br />
Passphrase Support: Users can configure the program to accept passphrases with specified minimum lengths.<br />
Comprehensive Checks:<br />
Length Validation: Ensures passwords fall within defined minimum and maximum lengths.<br />
Repetition Prevention: Checks for sequences of three or more identical characters.<br />
Character Diversity: Validates that passwords contain at least one letter, one digit, and one special character.<br />
Optional Tests: Configurable checks for additional character types, such as lowercase, uppercase, minimum digits, and minimum special characters.<br />

# Files
The program reads from three text files, each containing configuration settings and proposed passwords. The files should be named:

Proposed Passwords #1.txt<br />
Proposed Passwords #2.txt<br />
Proposed Passwords #3.txt<br />

# Example Configuration Format
Each file should contain the following information:

<max_length> <min_length> <allow_passphrases>
<min_phrase_length> (if passphrases are allowed)
<require_optional> <min_optional_passes>

Example:<br />

16 8 1<br />
10<br />
1 3<br />

This configuration indicates:

Maximum password length: 16 characters<br />
Minimum password length: 8 characters<br />
Passphrases are allowed, with a minimum phrase length of 10<br />
Optional tests are required, with at least 3 tests needing to be passed.<br />

# Functions
isPassphrase: Checks if the password contains spaces, indicating it's a passphrase.<br />
cnum_Length: Validates whether the password meets specified length requirements.<br />
cnum_Repeats: Checks for sequences of three or more consecutive identical characters and returns false if found.<br />
cnum_Characters: Ensures the password includes at least one letter, one digit, and one special character.<br />
cnum_Lowercase: Validates the presence of at least one lowercase letter.<br />
cnum_Uppercase: Validates the presence of at least one uppercase letter.<br />
cmin_Digits: Checks if the password contains a specified minimum number of digits.<br />
cmin_Special: Checks if the password contains a specified minimum number of special characters.<br />

# Compilation and Execution

Example Usage
Prepare Configuration Files: Create text files following the specified format with your desired password rules and a list of proposed passwords.
Run the Program: Execute the program to process each file and output validation results.
Output

The program outputs:

Configuration settings read from each file.
Results for each proposed password, indicating whether it is valid or detailing the specific reasons for any failures.

# Example Output:

Processing password file #1<br />

Maximum password length: 16<br />
Minimum password length: 8<br />
Pass phrases are allowed<br />
Minimum phrase length: 10<br />
Optional Tests are required<br />
Number of optional tests that must be passed: 3<br />

Potential password: P@ssw0rd<br />
Password failed - it cannot be used.<br />
The password must contain at least two special characters.<br />

Potential password: My Safe Passphrase<br />
Password is valid.<br />



