## Telebook
For the ITT-310 course at [Grand Canyon University](https://gcu.edu), students must create a simple CLI application using the C programming language. The requirements for the CLI application are as follows: implements modular code, can enter and exit the CLI application, features a menu, has basic error handling, and utilizes user-defined functions. To complete this assignment, I created Telebook, a simple contact management application. 

### Features
- Persistent Data Storage: Telebook utilizes a .data file to binary dump the struct array from memory. This occurs every time a user is added or removed from the application and when a contact is added or removed from a user account.
- DJB2 Hashing Algorithm: No application should ever store plaintext passwords! Considering this application is for a class that focuses on cybersecurity principles, Telebook utilizes a simple hashing algorithm named [DJB2](http://www.cse.yorku.ca/~oz/hash.html) to illustrate the basic concept of password hashing. Telebook accomplishes this task by storing password hashes rather than plaintext passwords. It must be noted, DJB2 is a unsecure cryptographic function. No one should ever use this algorithm in a production environment, ever!
- ANSI Escape Codes: Telebook aims to provide users with a simplistic, user-friendly design.



