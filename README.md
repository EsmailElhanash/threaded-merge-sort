# threaded-merge-sort
Merge sort is an O (n log n) comparison-based sorting algorithm.
It is a divide and conquer algorithm. Conceptually, a merge sort works as follows:
a) If the list is of length 0 or 1, then it is already sorted. Otherwise:
b) Divide the unsorted list into two sub-lists of about half the size.
c) Sort each sub-list recursively by re-applying the merge sort.
d) Merge the two sub-lists back into one sorted list.
So you are required to implement it using Pthreads. Each time the list is divided;
two threads are created to do merge-sort on each half separately. This step is
repeated recursively until each sub-list has only one element.
The program should read two input matrices in a certain format as mentioned in
the “merge-sort-readme.txt” file associated with project. When the program
finishes, it should print out the sorted array.
