# Spell_Check
## Overview
This program is designed to be a sample spell check application to be ran from the console. It is only a prototype demonstration of what a TRIE data structure can do ([more can be read about TRIEs here](https://en.wikipedia.org/wiki/Trie)). Due to the time/space efficient nature of a TRIE, this un-optimized version can store and reference an extremely large collection of words with little comparison and minimal caching. This structure is also easily implemented into more useful applications such as autocorrect, page searching (ctrl/cmd - F) and many other string and character based applications.

## Implementation
To use this prototype, download the source files and run from terminal or command line. It is compatible with UTF - 8 and ASCII but will only work for characters in the english alphabet (however, some easy-ish manipulation would solve that). It is currently rigged to read dictionary text files of the form: 

Word1

Word2

So I recommend using the provided "randic.txt" to test with. 

To run from console use $./SpellCheck (*name of dictionary file*). 
