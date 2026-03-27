## Program 2 - Comparing Lookup Type Data Structures

### Provided to Me

The original location of the files included in this project can be found here:
[RugbyProf's 5243 Algorithms P02](https://github.com/rugbyprof/5243-Algorithms/blob/main/Assignments/05-P02/README.md)

C++ implementations for:

- Binary Search Tree
- Hash Table
- Linked List
- Ordered Dynamic Array

With all necessary basic functionality and small tests to show how to use each of them.
There is no additional code added to count any of the stats we want to collect for comparing different data structures and how they handle certain types of behaviors (insert, find, delete). Below is the folder structure:

### Folder Structure

Here is the organization for 'Program 02''s

```txt
📁 05-P02
├── ✳️ README.md        // This file
├── 📁 builds
|   ├── 📕 test_ds
│   └── 📕 workload_generator
├── 📁 src              // Code files
|   ├── 📁 include      // Include hpps can't run directly
|   │   ├── 📕 bst.hpp
|   │   ├── 📕 counters.hpp
|   |   ├── 📕 dataStructure.hpp
|   │   ├── 📕 hashTable.hpp
|   │   ├── 📕 json.hpp
|   │   ├── 📕 linkedList.hpp
|   │   ├── 📕 sortedArraySet.hpp
|   │   ├── 📕 termcolor.hpp
|   │   └── 📕 usagePrinter.hpp
|   ├── 📁 tests        // Tests for each of the hpp data structures
|   │   └── 📕 test_ds.cpp
|   ├── 📁 workloads
|   |   └── 📕 workload_cat_qty.json
|   ├── 📕 batch.sh
|   └── 📕workload_generator.cpp
├── 📁 work_files
|   └── 📕 ds_cat_qty.json
├── 📁 z_reference_removed
└── 📕README.md
```

Where the 'src' folder holds all the 'hpp's' in the 'include' folder and the 'tests' folder containing the 'test_ds.cpp' file that compiles and runs each file contained in the 'workloads' folder. These files were generated from the 'batch.sh' file that contains a script to execute the contents of the 'workload_generator.cpp' file. The resulting 'test_ds.cpp' files are contained in the 'work_files' folder. Finally, the 'z_reference_removed' folder contains files that were provided for this project by rugbyprof, but are not needed for the final test or output.

### Executing

Executable code is uploaded in the 'builds' folder. The workload_generator object file was compiled from the workload_generator.cpp file, and the test_ds object file was compiled from the test_ds.cpp file. The test_ds executable will look for workload files in the ../src/workloads folder and output to the ../work_files folder.

## Programs Goal and How Performance is Measured

The goal is to track stats for each of the data structures that have been discussed in class as they process the same data sets. The "big picture" is to learn and understand certain choices we make when determining what structures would work best in specific conditions. However, before we compare structures, we need to determine what data points are important enough to track. The following is a list (with descriptions) of the stats (data points) we will analyze.

### Comparisons

The number of times an input value is compared to a node within a data structure to make a determination for an insert, contains, or delete operation.

### Structural Operations

The number of times an internal rearrangement of data is performed within a data structure.

### Inserts

The number of times a value is added to a data structure.

### Deletes

The number of times a value is removed from a data structure.

### Lookups

The number of times a data structure is checked to determine if a value exists within that data structure.

### Resize Events

The number of times a data structure runs out of space and must grow.

### Shifts/Relinks

The number of times a node is moved after an insert or delete within a linked list-based data structure.

## Workload Types

Above, we discuss the data structures we compare, how to execute the code, and a bit about counting events for each structure, Now we discuss the different workload types, which very much impact which data structure we would normally choose. For this experiment, we will expose each structure to all workload types. Just for a simple overview, the major workload types are:

- Build once, tons of searches with few inserts and deletes (stable structure)
- Highly fluctuating: lots of inserts and deletes with few searches
- Mix: a little bit of everything

Based on some pretty common workload experiences, here are 4 that we will use to test our structures:

### Workload A

- Random inserts followed by random lookups (not a ton of fluctuation)

- Pattern:

```
     insert
     insert
     insert
     ...
     contains
     contains
```

---

### Workload B

- Same as workload A except **inserts are sorted first**
- This often stresses ordered data structures differently
- Example: BSTs without balancing

---

### Workload C

- Mixed workload with random ordering of operations.

- Operation mix:
  - 50% contains
  - 25% insert
  - 25% delete

- Deletes only occur if something exists in the population.

---

### Workload D

- Insert n items then perform heavy lookup activity (stable structure).

- Pattern:
  - n inserts
  - 5n lookups
- Useful for read-heavy workloads.

---

## Results

### 1000 Operations

| Workload A  | Inserts | Lookups | Comparisons | Resize Events | Structural Operations |
| ----------- | ------- | ------- | ----------- | ------------- | --------------------- |
| Array       | 958     | 1,000   | 38,992      | 7             | 224,526               |
| BST         | 958     | 1,000   | 59,425      | 0             | 958                   |
| Hash Table  | 958     | 1,000   | 28,829      | 0             | 958                   |
| Linked List | 958     | 2,000   | 955,472     | 0             | 958                   |

---

| Workload B  | Inserts | Lookups | Comparisons | Resize Events | Structural Operations |
| ----------- | ------- | ------- | ----------- | ------------- | --------------------- |
| Array       | 958     | 1,000   | 37,812      | 7             | 0                     |
| BST         | 958     | 1,000   | 2,888,316   | 0             | 958                   |
| Hash Table  | 958     | 1,000   | 29,258      | 0             | 958                   |
| Linked List | 958     | 2,000   | 935,573     | 0             | 958                   |

---

| Workload C  | Inserts | Lookups | Deletes | Comparisons | Resize Events | Structural Operations |
| ----------- | ------- | ------- | ------- | ----------- | ------------- | --------------------- |
| Array       | 499     | 971     | 487     | 15,871      | 3             | 5,831                 |
| BST         | 499     | 1,014   | 485     | 26,851      | 0             | 986                   |
| Hash Table  | 499     | 1,012   | 487     | 1,591       | 0             | 986                   |
| Linked List | 499     | 1,512   | 487     | 19,562      | 0             | 986                   |

---

| Workload D  | Inserts | Lookups | Comparisons | Resize Events | Structural Operations |
| ----------- | ------- | ------- | ----------- | ------------- | --------------------- |
| Array       | 958     | 5,000   | 122,416     | 7             | 224,526               |
| BST         | 958     | 5,000   | 207,981     | 0             | 958                   |
| Hash Table  | 958     | 5,000   | 243,384     | 0             | 958                   |
| Linked List | 958     | 6,000   | 4,605,800   | 0             | 958                   |

### 5000 Operations

| Workload A  | Inserts | Lookups | Comparisons | Resize Events | Structural Operations |
| ----------- | ------- | ------- | ----------- | ------------- | --------------------- |
| Array       | 4,754   | 5,000   | 241,502     | 10            | 5,653,747             |
| BST         | 4,754   | 5,000   | 386,653     | 0             | 4,754                 |
| Hash Table  | 4,754   | 5,000   | 691,423     | 0             | 4,754                 |
| Linked List | 4,754   | 10,000  | 955,472     | 0             | 4,754                 |

---

| Workload B  | Inserts | Lookups | Comparisons | Resize Events | Structural Operations |
| ----------- | ------- | ------- | ----------- | ------------- | --------------------- |
| Array       | 4,754   | 5,000   | 235,844     | 10            | 0                     |
| BST         | 4,754   | 5,000   | 71,419,392  | 0             | 4,754                 |
| Hash Table  | 4,754   | 5,000   | 704,087     | 0             | 4,754                 |
| Linked List | 4,754   | 10,000  | 23,167,477  | 0             | 4,754                 |

---

| Workload C  | Inserts | Lookups | Deletes | Comparisons | Resize Events | Structural Operations |
| ----------- | ------- | ------- | ------- | ----------- | ------------- | --------------------- |
| Array       | 2,498   | 4,835   | 2,436   | 103,345     | 4             | 81,703                |
| BST         | 2,498   | 5,064   | 2,434   | 152,449     | 0             | 4,934                 |
| Hash Table  | 2,498   | 5,064   | 2,436   | 16,415      | 0             | 4,934                 |
| Linked List | 2,498   | 7,564   | 2,436   | 241,233     | 0             | 4,934                   |

---

| Workload D  | Inserts | Lookups | Comparisons | Resize Events | Structural Operations |
| ----------- | ------- | ------- | ----------- | ------------- | --------------------- |
| Array       | 4,754   | 25,000  | 752,960     | 10            | 224,526               |
| BST         | 4,754   | 25,000  | 1,335,708   | 0             | 4,754                 |
| Hash Table  | 4,754   | 25,000  | 6,039,197   | 0             | 4,754                 |
| Linked List | 4,754   | 30,000  | 114,538,571 | 0             | 4,754                 |

### 10000 Operations

| Workload A  | Inserts | Lookups | Comparisons | Resize Events | Structural Operations |
| ----------- | ------- | ------- | ----------- | ------------- | --------------------- |
| Array       | 9,533   | 10,000  | 523,066     | 11            | 22,777,885            |
| BST         | 9,533   | 10,000  | 848,392     | 0             | 9,533                 |
| Hash Table  | 9,533   | 10,000  | 2,771,250   | 0             | 9,533                 |
| Linked List | 9,533   | 20,000  | 95,357,059  | 0             | 9,533                 |

---

| Workload B  | Inserts | Lookups | Comparisons | Resize Events | Structural Operations |
| ----------- | ------- | ------- | ----------- | ------------- | --------------------- |
| Array       | 9,533   | 10,000  | 511,646     | 11            | 0                     |
| BST         | 9,533   | 10,000  | 285,810,808 | 0             | 9,533                 |
| Hash Table  | 9,533   | 10,000  | 2,811,714   | 0             | 9,533                 |
| Linked List | 9,533   | 20,000  | 93,134,766  | 0             | 9,533                 |

---

| Workload C  | Inserts | Lookups | Deletes | Comparisons | Resize Events | Structural Operations |
| ----------- | ------- | ------- | ------- | ----------- | ------------- | --------------------- |
| Array       | 4,997   | 9,823   | 4,918   | 235,051     | 4             | 5,831                 |
| BST         | 4,997   | 10,083  | 4,918   | 345,584     | 0             | 9,915                 |
| Hash Table  | 4,997   | 10,080  | 4,918   | 47,979      | 0             | 9,915                 |
| Linked List | 4,997   | 15,080  | 4,918   | 751,309     | 0             | 9,915                 |

---

| Workload D  | Inserts | Lookups | Comparisons | Resize Events | Structural Operations |
| ----------- | ------- | ------- | ----------- | ------------- | --------------------- |
| Array       | 9,533   | 50,000  | 1,625,720   | 11            | 22,777,885            |
| BST         | 9,533   | 50,000  | 2,903,583   | 0             | 9,533                 |
| Hash Table  | 9,533   | 50,000  | 24,127,298  | 0             | 9,533                 |
| Linked List | 9,533   | 60,000  | 458,208,545 | 0             | 9,533                 |

### 20000 Operations

| Workload A  | Inserts | Lookups | Comparisons | Resize Events | Structural Operations |
| ----------- | ------- | ------- | ----------- | ------------- | --------------------- |
| Array       | 19,084  | 20,000  | 1,125,962   | 12            | 91,385,785            |
| BST         | 19,084  | 20,000  | 1,849,880   | 0             | 19,084                |
| Hash Table  | 19,084  | 20,000  | 11,077,948  | 0             | 19,084                |
| Linked List | 19,084  | 40,000  | 381,615,459 | 0             | 19,084                |

---

| Workload B  | Inserts | Lookups | Comparisons   | Resize Events | Structural Operations |
| ----------- | ------- | ------- | ------------- | ------------- | --------------------- |
| Array       | 19,084  | 20,000  | 1,103,470     | 12            | 0                     |
| BST         | 19,084  | 20,000  | 1,144,278,728 | 0             | 19,084                |
| Hash Table  | 19,084  | 20,000  | 11,236,511    | 0             | 19,084                |
| Linked List | 19,084  | 40,000  | 373,068,086   | 0             | 19,084                |

---

| Workload C  | Inserts | Lookups | Deletes | Comparisons | Resize Events | Structural Operations |
| ----------- | ------- | ------- | ------- | ----------- | ------------- | --------------------- |
| Array       | 9,996   | 19,807  | 9,920   | 459,640     | 4             | 430,050               |
| BST         | 9,996   | 20,080  | 9,918   | 754,942     | 0             | 19,916                |
| Hash Table  | 9,996   | 20,079  | 9,920   | 88,421      | 0             | 19,916                |
| Linked List | 9,996   | 30,079  | 9,920   | 1,344,803   | 0             | 19,916                |

---

| Workload D  | Inserts | Lookups | Comparisons   | Resize Events | Structural Operations |
| ----------- | ------- | ------- | ------------- | ------------- | --------------------- |
| Array       | 19,084  | 100,000 | 3,490,888     | 12            | 91,385,785            |
| BST         | 19,084  | 100,000 | 6,289,739     | 0             | 19,084                |
| Hash Table  | 19,084  | 100,000 | 96,563,716    | 0             | 19,084                |
| Linked List | 19,084  | 120,000 | 1,834,724,093 | 0             | 19,084                |

## Discussion

For the purposes of the tables, structural operations and shifts/relinks were combined into the Structural Operations column, being as they are similar operations. 

For workload A, where the operations were limited to 1,000 random inserts and 1,000 random lookups and considering the smaller quantities of comparisons and structural operations as defining a more efficient data structure, the hash table shows the best promise. The only structural operations that occur are during insertion operations, and there are approximately 30,000 fewer comparisons made as opposed to the next most effiencient structure, which was the BST. However, as the quantities of operations rise, the efficiency of the hash table falls. Even at 5,000 inserts and lookups, you can see the BST showing that it's nearly twice as efficient. Of course, the limited size of the hash table in this experiment makes a big difference, as it is never resized as each bucket is filled, which drastically increases the number of comparisons made during insert and search operations. The array performs somewhat well when only comparisons are taken into account, but the number of shifts required gets into the 10's of millions by the time 10,000 values are input. Therefore, for workload A, where operations are limited to random inserts and random lookups, and failing any resizing of a hash table, the most efficient data structure is the binary search tree.

For workload B, we see the same 1,000, 5,000, 10,000, and 20,000 operation spread, but this time the values that are input are pre-sorted. For this workload, as the number of inserts increases, the binary search tree becomes increasingly inefficient, as the balance becomes highly skewed. Again, at 1,000 inserts, the hash table is the winner, requiring two-thirds of the comparisons of the next best structure. However, as the number of inserts increases without any resizing of the table, the array becomes far more efficient. This being because, with the values pre-sorted, the shift operations that slowed the structure's operation with workload A are no longer necessary. All that is needed are up to 12 resize events at 20,000 inserts. It is here that I realize a mistake was made in counting structural operations, as resize events should've counted towards that statistic, but it was missed. Even still, with binary search tree comparisons getting into the trillions and hash table comparisons getting into the 10's of millions, a few hundred thousand structural operations from copying array elements is minor. 

Workload C is where the hash table finally shines at all quantities. The balanced mix of inserts and deletes keeps the table size at bay, which results in a structure that requires nearly one-tenth of the comparisons and structural operations as either the binary search tree or the sorted array. Couple that with the limited number of searches perfomed, and the hash table becomes a highly-efficient data structure for this type of workload.

In workload D, we again see the binary search tree show why it is one of the most studied data structures across Computer Science classrooms. While we can't outright see a search efficiency of O(log n) due to the comparisons made during each insert operation and search operation being combined over the course of up to 20,000 inserts, you can see how, as the number of inserts and searches increase, the number of comparisons increases at approximately the same rate from 207K to 1.3M to 2.9M to 6.2M. Again, the size of the hash table holds it back, as the chaining method of collision resolution leads to a reduced efficiency as the increased number of inserts cause the length of the chains grow.