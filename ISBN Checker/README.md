# ISBN Checker

## Abstract
This software is the solution for a the first assignment in my System Analysis Class. It is a program written in C to get students familiar with solving problems in code, making documentation, the process of design and testing. 
It also gets studentes familiar with using the VS debugger, command line arguments and writing fully commented, properly indented, "magic numberless" code. and getting them to think about more abstract and general purpose solutions rather than "Hard Coded solutions".

## Purpose 
This program is designed for the sole purpose of checking whether an ISBN (A number used to
identify international books) is a valid ISBN or not. There are certain steps used to identify
whether the ISBN is valid or not. An ISBN is a mostly numeric string of characters consisting of
10 digits, it always consists of numbers unless there is a ‘10’ in the code which is denoted as
capital x (“X”).
To figure out whether the number is valid is by finding the partial sum of the digits and then
finding the partial sums of the digit’s first partial sums. The last partial sum in the second set
should be divisible by 11(ie. Can be divided by 11 without resulting in any remainders or
fractions).
The program works by dragging the .txt file containing the ISBNs (which are placed
independently on their own lines) to the executable (.exe) file. This will then display a new
window showing all the ISBNs and which ones are valid and invalid.

## Design and Implementaiton
### Pseudo Code:
#### Header
#### Implementation
#### Main


## Testing
### Test 1: File with no name
#### Purpose/Objective: 
#### Test Configuration: 
#### Expected Results:
#### Actual Results: 
#### Pass/Fail:

### Test 2: Extra Hyphen Check
#### Purpose/Objective: 
#### Test Configuration: 
#### Expected Results:
#### Actual Results: 
#### Pass/Fail:

### Test 3: Not Enough Characters Check
#### Purpose/Objective: 
#### Test Configuration: 
#### Expected Results:
#### Actual Results: 
#### Pass/Fail:

### Test 4: Space After Code Check
#### Purpose/Objective: 
#### Test Configuration: 
#### Expected Results:
#### Actual Results: 
#### Pass/Fail:


