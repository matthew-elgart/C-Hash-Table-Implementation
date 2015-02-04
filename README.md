# C-Hash-Table-Implementation
C: Implementation of a Hash Table data structure using an array of linked lists, for storing data of students' grades.

The code takes in arguments from the command line in the style of:
command (char), ID (int), Grade 1 (int), Grade 2 (int), Student Name (string)

The code performs various functions with the data depending on the character input for the command:
i (insert): inserts the entry with given data into the database (unless an entry with the same ID already exists)

d (delete): deletes the entry with the given ID from the database (unless no entry with that ID exists)

l (lookup): prints out all of the member variables for the record with the specified ID (or that the ID was not found)

p (print): prints the member variables for each entry in the hash table

s (stats): when passed in ID is zero and student name is "all", this command prints out hte minimum, maximum, and average
  class grade for each exam. When an nonzero ID is passed in, it prints out the student's ID, name, and grade average.
