### OOP summary notes

1.  Definitions of objects, classes and OOP

2.  References, pointers and functions

  - A reference is an implicit pointer that acts like another
        name for the referenced object / variable

  - References must be always initialised because it points
        always to the same memory address (exceptions: function
        params, member data in classes, returned value)

  - One cannot get the address of a reference, create an array
        of references or cannot reference bytes

  - The formal params are those created in the function
        initiation and destroyed in the function termination

  - Reference call - copy of the param address

  - Value call - copy of the value in a formal param

  - Function identification in overloading: number of params,
        returned type

  - Default parameters must be specified only once (either in
          definition, either in implementation)

  - Arrays of pointers (\*\*p)

  - Modifications of the reference represent modifications of
        the referred value.

  - One cannot get the address of a reference

  - When a function returns an object, a temporary object is created to store the value; after the value was returned the object is then destroyed

  - Functions in structs are allowed in C++

  - Default return type is int

3.  Constants and data types
	1. One cannot implicitly change the data types of pointers of different occupied space (see double* to int* example)
	2. (Const T* = T const*) vs (const) T* const

    iii. T x; Const T\* x = &x is allowed, but the reverse is not!
        (const T x; T\* x = (T\*)&x is allowed but considered a
        bad practice)

    iv. Constants default data types: 10 - int, 10.1 - double, 'c' -
        char

    v.  Data types ambiguity appears when multiple conversions are
        possible

    vi. T x = const T a is valid syntax

    vii. A non-const reference cannot reference a const object

    viii. Returning consts by value in functions has no special
          meaning, thus one can convert it to the non-constant
          type without any problem

4.  Relation between objects

    i.  Aggregation / composition: composition of an object of more
        simpler (and independent / dependent) objects

    ii. Union type (to be completed)

    iii. Non-static members cannot have initialisation

    iv. An object cannot have members of class data type, but can
        have pointers to it

    v.  No auto, extern, register etc.

    vi. Encapsulation represents the separation of internal (and
        private) functionalities of an object to the external (and
        public) ones

    vii. Friend functions and classes

    viii. Inline functions in classes: explicit and implicit
          inlining

5.  Class related types

    i.  Struct has default as public and can have functions (in c++)

    ii. Union are similar to structs, except for the fact that any
        data type references the same memory location (wholly or
        divided - in arrays)

    iii. The inheritance, copying, references or statics are not
        defined on union types

    iv. No objects with constructors or destructors can be union
        members

    v.  Anonymous unions

        1.  If global, must be static

        2.  Cannot have functions (thus, they don't accept private
            and protected)

    vi. Local classes cannot have static members and cannot access
        local data from the context where is declared in (except
        if the data is static)

6.  Operators

    i.  Cannot be overloaded: ., ?:, ::, .\*, sizeof, typeid

    ii. Can be overloaded only with friend functions: =

    iii. Cannot be overloaded with friend functions (), \[\], -\
    iv. New and delete operators overloading

    v.  Overloading ',' operator use cases

7.  Constructors and destructors

    i.  Calling order (in inheritance too)

    ii. Self made copy constructor hides the default one

    iii. Initialisation list of constructors makes optional the
        local class data initialisation

    iv. On dynamic memory allocation the constructors must be
        redefined

    v.  Pseudo-constructors allow predefined data types to be
        treated as objects in the context of initialisation

    vi. Objects with one parameter constructors of type T are
        declared same as the data type T

    vii. Virtual destructors in polymorphic hierarchies

8.  Statics

    i.  Static data are variables unique for the class they are
        instantiated in, but same for all objects of that class;
        they are stored in memory independent of the objects

    ii. Static functions can access only static data (non-static can
        access all types of data)

    iii. Static functions cannot access the alias this

9.  Nested classes

    i.  The implementations of defined functions of nested classes
        are written outside the most external class

    ii. Nested classes cannot access non-static members of outside
        classes

    iii. Classes inside functions cannot have static members, but
        can have static functions

    iv. Local classes (inside functions) can access local static
        variables and global variables

    v.  Classes inside functions must have the implementation of
        their functions inline implicit

10. Initialisation list for constructors are faster than usual ways
    (+ memory allocation)

11. Non-const static variables must be initialised after the class
    declaration

12. Classes in functions

    i.  Cannot separate the declaration from the definition (cannot
        use resolution operator) (eg.: function definition and
        implementation)

    ii. Cannot have static data, but can have static functions

    iii. Can access local static variables and global variables

    iv. Can access data and functions from other local classes from
        the same function (siblings)

13. Nested classes

    i.  Declaration and definition can be separated (but resolution
        operator must be used) (implementation is outside external
        class)

    ii. Cannot access data from the external class (except for
        statics)

14. Constants and references as data members need manual
    implementation of the copy constructor

15. Constructors lists use cases: constants, references, members
    data, inheritance

16. Constructors call order in nested inheritance: parent, local,
    children

17. A class without members has size of 1

18. Padding and filling of bytes (the greatest datatype represent
    the step)

19. Virtual creates a pointer (\*vptr) to the address of the first
    function of size 8 bytes (?)

20. Public, protected and private inheritance (private is the
    default) & external access (protected cannot be accessed from
    outer scopes)

21. Using::ClassName attributeName;

22. The access is checked at the compilation time

23. New, delete and memory leaks

24. Rule of 3: copy constructor, = operator, destructor

25. Polymorphism la executie (moștenire, funcții virtuale,
    upcasting) vs polymorphism la compilare (functions overloading
    (constructors), operators overloading, templates)

26. Virtual destructors need abstract base class

27. A derived class from an abstract class must implement the
    virtual function in order to not be abstract too

28. Dynamic cast iff polymorphic hierarchy