# NFA2DFA (Coffeescript Edition)
This was primarily for humourous purposes.
Implementing NFA2DFA in Coffeescript, in under 100 lines of code.
I decided to try this after taking an interest in Coffeescript.

Converts an E-NFA parsed fro ma text file (examples are somewhere in this repo I guess) to a DFA.

The `nfa2dfa.true.coffee` is the same as `nfa2dfa.coffee` without comments and excess spacing. This is to simply show how many lines the program would take if it was compact.

## Synopsis
```
coffee nfa2dfa.coffee < nfa_file > dfa_file
coffee nfa2dfa.true.coffee < nfa_file > dfa_file
```
