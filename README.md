# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

An invented long word said to mean a lung disease caused by inhaling very fine ash and sand dust.

## According to its man page, what does `getrusage` do?

returns resource usage measures for who, which can be oneof the following;
RUSAGE_SELF
RUSAGE_CHILDREN
RUSAGE_THREAD

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

To stop duplication of data, ultimately it can cause a stack overflow.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

The program is provided by the user the file to be checked and an optional dictionary via arguments,
should no dictionary be provided a default dictionary will be used. The dictionary is checked for successful load, The program then opens the provided txt file in read-only mode (checking that it was successfully opened). Three integer variables are defined 'index', 'misspellings', 'words' and one char variable 'word' with it's liength being defined as 'LENGTH + 1' (this will define the variables length based on the word + 1 allowing for the null terminating character '\0'). 

The program then defines a for loop that iterates over each character
until the end of file, within this for loop an if condiiton checks to confirm the character is an alphabetical character or an apostrophe and that the size is more than 0, if it resolves to true the character is added to the word array and the index variable is incremented, next another if statement that checks for words that are too long and if so sets the index variable to 0. It then checks for digits and agin if found sets index to 0. if that resolves to false a final if statement checks that index is more than zero (hasn't been set to 0 by the previous checks, terminates the word with \n, increments the words variable and defines a bool that equals the opposite of what check will return.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

fscanf will read whitespace

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

Because we wnat them to be immutable.
