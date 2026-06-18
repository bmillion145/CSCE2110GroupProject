// test_main.cpp
// Standalone test driver for StudentNode.h / StudentNode.cpp.
//
// It runs a series of checks against every public method of StudentList,
// keeps going even when a check fails, and prints a report of exactly what
// failed at the end. Returns 0 if everything passed, 1 if anything failed.
//
// Build (in place of your usual main):
//     g++ -std=c++17 StudentNode.cpp test_main.cpp -o test
//     ./test
//
// NOTE: this file does NOT modify StudentNode.h or StudentNode.cpp.

#include "StudentNode.h"
#include <iostream>
#include <string>
#include <cmath>
#include <cstdio>   // std::remove for temp-file cleanup

using namespace std;

// ---------------------------------------------------------------------------
// Tiny test harness
// ---------------------------------------------------------------------------
static int g_pass = 0;
static int g_fail = 0;

// Generic boolean check.
static void check(bool condition, const string& testName) {
    if (condition) {
        ++g_pass;
        cout << "  [PASS] " << testName << "\n";
    } else {
        ++g_fail;
        cout << "  [FAIL] " << testName << "\n";
    }
}

// Check two ints are equal, printing expected vs actual on failure.
static void checkEqualInt(int actual, int expected, const string& testName) {
    if (actual == expected) {
        ++g_pass;
        cout << "  [PASS] " << testName << "\n";
    } else {
        ++g_fail;
        cout << "  [FAIL] " << testName
             << "  (expected " << expected << ", got " << actual << ")\n";
    }
}

// Check two doubles are equal within a small tolerance (GPAs).
static void checkClose(double actual, double expected, const string& testName) {
    if (fabs(actual - expected) < 1e-9) {
        ++g_pass;
        cout << "  [PASS] " << testName << "\n";
    } else {
        ++g_fail;
        cout << "  [FAIL] " << testName
             << "  (expected " << expected << ", got " << actual << ")\n";
    }
}

// Convenience: does a student with these exact fields exist (looked up by id)?
static bool hasStudent(StudentList& list, int id, const string& name,
                       const string& major, double grade) {
    StudentNode* n = list.search(id);
    return n != nullptr
        && n->name == name
        && n->major == major
        && fabs(n->grade - grade) < 1e-9;
}

// ---------------------------------------------------------------------------
// Test sections
// ---------------------------------------------------------------------------
static void testEmptyList() {
    cout << "\n== Empty list ==\n";
    StudentList list;
    check(list.isEmpty(), "new list is empty");
    checkEqualInt(list.size(), 0, "new list size is 0");
    check(list.search(123) == nullptr, "search on empty list returns nullptr (id)");
    check(list.search("nobody") == nullptr, "search on empty list returns nullptr (name)");
    // These must simply not crash on an empty list:
    list.remove(123);
    list.remove("nobody");
    list.updateGrade(123, 4.0);
    check(list.isEmpty(), "list still empty after no-op operations");
}

static void testInsertAndSearch() {
    cout << "\n== Insert / size / search ==\n";
    StudentList list;
    list.insert(1, "Alice", "CS", 3.50);
    list.insert(2, "Bob", "Math", 2.75);
    list.insert(3, "Carol", "Physics", 3.90);

    check(!list.isEmpty(), "list not empty after inserts");
    checkEqualInt(list.size(), 3, "size is 3 after 3 inserts");

    check(list.search(2) != nullptr, "search by id finds existing student");
    if (list.search(2)) {
        check(list.search(2)->name == "Bob", "search by id returns correct name");
        checkClose(list.search(2)->grade, 2.75, "grade stored as double (not truncated)");
    }
    check(list.search(99) == nullptr, "search by id returns nullptr when absent");

    check(list.search("Carol") != nullptr, "search by name finds existing student");
    if (list.search("Carol")) {
        checkEqualInt(list.search("Carol")->id, 3, "search by name returns correct id");
    }
    check(list.search("Zelda") == nullptr, "search by name returns nullptr when absent");
}

static void testUpdateGrade() {
    cout << "\n== updateGrade ==\n";
    StudentList list;
    list.insert(1, "Alice", "CS", 3.50);
    list.updateGrade(1, 3.95);
    if (list.search(1)) {
        checkClose(list.search(1)->grade, 3.95, "updateGrade changes the grade");
    } else {
        check(false, "student present after updateGrade");
    }
    // Updating a non-existent id should do nothing and not crash:
    list.updateGrade(999, 1.00);
    checkEqualInt(list.size(), 1, "updateGrade on missing id leaves list unchanged");
}

static void testRemove() {
    cout << "\n== remove (by id and by name) ==\n";

    // Remove the HEAD by id
    {
        StudentList list;
        list.insert(1, "A", "CS", 3.0);
        list.insert(2, "B", "CS", 3.0);
        list.insert(3, "C", "CS", 3.0);
        list.remove(1);
        checkEqualInt(list.size(), 2, "remove head by id -> size 2");
        check(list.search(1) == nullptr, "removed head no longer found");
        check(list.search(2) != nullptr && list.search(3) != nullptr,
              "remaining students intact after head removal");
    }
    // Remove a MIDDLE node by id
    {
        StudentList list;
        list.insert(1, "A", "CS", 3.0);
        list.insert(2, "B", "CS", 3.0);
        list.insert(3, "C", "CS", 3.0);
        list.remove(2);
        checkEqualInt(list.size(), 2, "remove middle by id -> size 2");
        check(list.search(2) == nullptr, "removed middle no longer found");
        check(list.search(1) != nullptr && list.search(3) != nullptr,
              "head and tail intact after middle removal");
    }
    // Remove the TAIL by id
    {
        StudentList list;
        list.insert(1, "A", "CS", 3.0);
        list.insert(2, "B", "CS", 3.0);
        list.insert(3, "C", "CS", 3.0);
        list.remove(3);
        checkEqualInt(list.size(), 2, "remove tail by id -> size 2");
        check(list.search(3) == nullptr, "removed tail no longer found");
    }
    // Remove a non-existent id
    {
        StudentList list;
        list.insert(1, "A", "CS", 3.0);
        list.remove(42);
        checkEqualInt(list.size(), 1, "remove non-existent id leaves size unchanged");
    }
    // Remove by name
    {
        StudentList list;
        list.insert(1, "Alice", "CS", 3.0);
        list.insert(2, "Bob", "CS", 3.0);
        list.remove("Alice");
        checkEqualInt(list.size(), 1, "remove by name -> size 1");
        check(list.search("Alice") == nullptr, "removed-by-name no longer found");
        check(list.search("Bob") != nullptr, "other student intact after name removal");
    }
}

static void testCopySemantics() {
    cout << "\n== Copy constructor / copy assignment (deep copy) ==\n";

    // Copy constructor: original and copy must be independent.
    {
        StudentList original;
        original.insert(1, "Alice", "CS", 3.5);
        original.insert(2, "Bob", "Math", 2.9);

        StudentList copy = original;          // copy constructor
        checkEqualInt(copy.size(), 2, "copy has same size as original");

        copy.insert(3, "Carol", "Bio", 3.1);  // mutate the copy
        checkEqualInt(original.size(), 2, "mutating copy does NOT affect original (deep copy)");

        original.updateGrade(1, 1.0);         // mutate the original
        if (copy.search(1))
            checkClose(copy.search(1)->grade, 3.5, "mutating original does NOT affect copy");
        else
            check(false, "copy still has student 1 after original mutated");
    }

    // Copy assignment + self-assignment.
    {
        StudentList a;
        a.insert(1, "Alice", "CS", 3.5);
        StudentList b;
        b.insert(99, "Old", "X", 1.0);
        b = a;                                 // copy assignment (b's old data must be replaced)
        checkEqualInt(b.size(), 1, "copy-assigned list takes source's size");
        check(b.search(99) == nullptr, "copy assignment replaces previous contents");
        check(b.search(1) != nullptr, "copy assignment brings in source contents");

        b = b;                                 // self-assignment must not corrupt
        checkEqualInt(b.size(), 1, "self-assignment leaves list intact");
        check(b.search(1) != nullptr, "self-assignment preserves data");
    }
}

static void testMoveSemantics() {
    cout << "\n== Move constructor / move assignment ==\n";

    // Move constructor
    {
        StudentList src;
        src.insert(1, "Alice", "CS", 3.5);
        src.insert(2, "Bob", "Math", 2.9);

        StudentList moved = std::move(src);    // move constructor
        checkEqualInt(moved.size(), 2, "move-constructed list has the data");
        check(src.isEmpty(), "moved-from list is empty but valid (move ctor)");
    }

    // Move assignment
    {
        StudentList src;
        src.insert(1, "Alice", "CS", 3.5);
        StudentList dst;
        dst.insert(50, "Temp", "X", 1.0);
        dst = std::move(src);                  // move assignment
        checkEqualInt(dst.size(), 1, "move-assigned list has the data");
        check(dst.search(1) != nullptr, "move assignment brings in source data");
        check(src.isEmpty(), "moved-from list is empty but valid (move assign)");
    }
}

static void testClear() {
    cout << "\n== clear ==\n";
    StudentList list;
    list.insert(1, "Alice", "CS", 3.5);
    list.insert(2, "Bob", "Math", 2.9);
    list.clear();
    check(list.isEmpty(), "list empty after clear");
    checkEqualInt(list.size(), 0, "size 0 after clear");
    // Re-use after clear must work:
    list.insert(7, "New", "CS", 4.0);
    checkEqualInt(list.size(), 1, "list usable again after clear");
}

static void testConstSearch() {
    cout << "\n== const-correct search overload ==\n";
    StudentList list;
    list.insert(1, "Alice", "CS", 3.5);
    const StudentList& cref = list;            // force the const overloads
    const StudentNode* byId = cref.search(1);
    const StudentNode* byName = cref.search("Alice");
    check(byId != nullptr && byId->name == "Alice", "const search by id works");
    check(byName != nullptr && byName->id == 1, "const search by name works");
}

static void testFileIO() {
    cout << "\n== File I/O (save / load round-trip) ==\n";
    const string tmp = "test_students_tmp.txt";   // temp file, cleaned up below

    StudentList original;
    original.insert(5001, "Daniel", "CS", 3.44);
    original.insert(5002, "Scarlett", "IT", 3.71);
    original.insert(5003, "Matthew", "CE", 2.88);

    check(original.saveToFile(tmp), "saveToFile returns true on success");

    // Load into a list that already has junk: load should replace, not append.
    StudentList loaded;
    loaded.insert(9999, "ShouldBeGone", "X", 0.0);
    check(loaded.loadFromFile(tmp), "loadFromFile returns true on success");
    checkEqualInt(loaded.size(), 3, "loadFromFile replaces existing contents (size 3)");
    check(loaded.search(9999) == nullptr, "old contents cleared on load");

    check(hasStudent(loaded, 5001, "Daniel", "CS", 3.44),
          "round-trip preserves student 5001 (incl. GPA 3.44)");
    check(hasStudent(loaded, 5002, "Scarlett", "IT", 3.71),
          "round-trip preserves student 5002");
    check(hasStudent(loaded, 5003, "Matthew", "CE", 2.88),
          "round-trip preserves student 5003");

    // Loading a file that does not exist should fail gracefully (return false).
    StudentList missing;
    check(!missing.loadFromFile("this_file_does_not_exist_12345.txt"),
          "loadFromFile returns false for a missing file");

    std::remove(tmp.c_str());   // clean up temp file
}

// ---------------------------------------------------------------------------
// main
// ---------------------------------------------------------------------------
int main() {
    cout << "Running StudentList tests...\n";

    testEmptyList();
    testInsertAndSearch();
    testUpdateGrade();
    testRemove();
    testCopySemantics();
    testMoveSemantics();
    testClear();
    testConstSearch();
    testFileIO();

    cout << "\n=====================================\n";
    cout << "Results: " << g_pass << " passed, " << g_fail << " failed.\n";
    if (g_fail == 0) {
        cout << "ALL TESTS PASSED.\n";
    } else {
        cout << g_fail << " TEST(S) FAILED -- see the [FAIL] lines above.\n";
    }
    cout << "=====================================\n";

    return (g_fail == 0) ? 0 : 1;   // non-zero exit code signals failure
}
