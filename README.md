# contend
## contingency tables on the command line

----
### What is contend?

Contend helps you understand contingencies in your data.  When given a two-column, tabular input it prints a [contingency table](http://en.wikipedia.org/wiki/Contingency_table) describing the relationship between the two variables.

----
### How do I work this thing?

Provide contend suitable input, and you'll be rewarded with counts describing the relationship between column 1 and column 2.

    % ( echo A B; echo B A; echo B B; echo B B ) | tr ' ' '\t' | ./contend
    .       A       B
    A       0       1
    B       1       2

Be careful that your input is really categorical.

Following Wikipedia:

    % ( for i in $(seq 43); do echo Male Right-handed; done; \
        for i in $(seq 9); do echo Male Left-handed; done; \
        for i in $(seq 44); do echo Female Right-handed; done; \
        for i in $(seq 4); do echo Female Left-handed; done ) \
      | tr ' ' '\t' | ./contend | column -t
    .       Left-handed  Right-handed
    Female  4            44
    Male    9            43

The use of the '.' in as a placeholder in the upper-left ensures that column -t can be used to make the results legible.
