# CS 300 — Data Structures & Algorithms (C++)

Portfolio submission for the ABCU course advising program. This folder showcases my work
analyzing and implementing data structures, and reflecting on what I learned.

## Portfolio Artifacts
- **`Project_One_Runtime_Analysis.docx`** — Project One: pseudocode plus the run-time and
  memory (Big-O) analysis comparing a vector, a hash table, and a binary search tree, with my
  recommendation.
- **`ProjectTwo_CourseSorter.cpp`** — Project Two: the working program that loads the course
  data, sorts it, and prints the Computer Science course list in alphanumeric order.
- Supporting lab implementations: `BinarySearchTree.cpp`, `LinkedList.cpp`, `VectorSorting.cpp`.

---

## Reflection

**What was the problem you were solving in the projects for this course?**
ABCU's academic advisors needed a program to manage the Computer Science course catalog. The
program had to read course data from a file, print a full list of all courses in alphanumeric
order, and look up any single course along with its prerequisites. The goal was to give advisors
a fast, reliable tool for helping students plan their schedules.

**How did you approach the problem? Consider why data structures are important to understand.**
I started with pseudocode and a shared `Course` object, then analyzed three data structures —
a vector, a hash table, and a binary search tree — for run-time and memory before writing any
real code. That step mattered because the data structure you choose decides whether a program is
fast and clean or slow and clunky. After weighing the trade-offs, I chose the binary search tree:
an in-order traversal prints the courses in sorted order automatically, and it still gives fast
average lookups, so it matched both advisor requirements at once.

**How did you overcome any roadblocks you encountered while going through the activities or project?**
My biggest roadblock was parsing the comma-separated file correctly and validating that every
prerequisite listed actually existed as a real course. I also got stuck on index and pointer
logic in the sorting and traversal work. I got past these by breaking the problem into small,
testable functions, running my code against the sample data file, and tracing the logic by hand
or printing intermediate values until the behavior matched what I expected.

**How has your work on this project expanded your approach to designing software and developing programs?**
I now think about trade-offs before I code instead of jumping straight to a solution. Analyzing
Big-O and memory up front, and matching the data structure to the actual requirements, has made my
design decisions intentional rather than accidental.

**How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?**
I write in small, modular functions with clear names, comments, and consistent style, and I build
in input validation and error handling. Because the load, print, and search logic are separated,
the program is easy to read and adapt — for example, swapping one data structure for another
without rewriting the whole program.
