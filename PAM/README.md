# PAM modules

This section are a set of tests on PAM modules for Linux System PAM.

To compile one of this examples:

```bash
gcc -fPIC -fno-stack-protector -c brumpo_test.c
``` 
 
Now link it with the PAM library and add the executable on the PAM
modules folder.

```bash
ld -x --shared -o /lib/security/pam_brumpo.so brumpo_test.o
```
