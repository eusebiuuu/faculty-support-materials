
1. Helpers

#### Abstract Stream class
```cpp
class Stream {
public:
    Stream() = default;
    virtual ~Stream() = default;

    friend std::istream &operator>>(std::istream &in, Stream &ob) {
        ob.read(in);
        return in;
    }

    friend std::ostream &operator<<(std::ostream &out, const Stream &ob) {
        ob.write(out);
        return out;
    }

    virtual void read(std::istream &in) = 0;
    virtual void write(std::ostream &out) const = 0;
};
```

#### Checker class
```cpp
// good for handling input and out-of-bound errors
template<class T>
class Checker {
public:
    Checker() = default;
    virtual ~Checker() = default;

    static void throwIfNotInRange(T value, T a, T b, const std::string &err) {
        if (value < a || value > b) {
            throw std::range_error(err);
        }
    }

    static void throwIfGreaterThan(T value, T x, const std::string &err) {
        if (value > x) {
            throw std::runtime_error(err);
        }
    }

    static void throwIfNotInList(T value, const std::vector<T> &arr, const std::string &err) {
        if (std::count(arr.begin(), arr.end(), value) == 0) {
            throw std::runtime_error(err);
        }
    }
};
```

#### Singleton

```cpp
// example of Singleton class with no functionality
class Menu {
private:
    Menu() = default;
public:
    Menu(const Menu&) = delete;

    Menu& operator=(const Menu&) = delete;

    static Menu& getMenu() {
        static Menu menu;
        return menu;
    }
};
```
#### Factory
```cpp
// Factory class for easier read of the children classes and copying
class ModelFactory {
    ModelFactory() = default;
public:
    static std::string getType(std::istream &in) {
        std::cout << "Introduceti tipul de model (electric / hibrid / fosil): \n";
        std::string tip;
        in >> tip;
        return tip;
    }

    static Model *copyInstance(Model *model) {
        if (auto var1 = dynamic_cast<ModelHibrid *>(model))
            return new ModelHibrid(*var1);
        else if (auto var2 = dynamic_cast<ModelElectric *>(model))
            return new ModelElectric(*var2);
        else if (auto var3 = dynamic_cast<ModelFosil *>(model))
            return new ModelFosil(*var3);
        else if (model == nullptr)
            return nullptr;
        throw std::runtime_error("Tip de model invalid");
    }

    static Model *newInstance(const std::string &tip) {
        if (tip == "hibrid") {
            return new ModelHibrid();
        } else if (tip == "electric") {
            return new ModelElectric();
        } else if (tip == "fosil") {
            return new ModelFosil();
        }
        throw std::runtime_error("Tip de model invalid");
    }
};
```

2. App structure
   - Read **ALL** the statement
   - Figure out the overall app functionality
   - Divide it into required and extra
3. Implement `Stream` and `Checker` classes
4. Classes creation
	- [ ] Default constructor
	- [ ] Normal constructor
		- Initialisation list
		- Const and `&`
	- [ ] Override the read and write functions
        - Print information before reading or writing data
	- [ ] Encapsulation (getters and setters)
	- [ ] Add ID with static counter
	- [ ] Classes with pointers (rule of three, kind of)
    	- Copy constructor must be overriden
    	- Assignment operator must be overriden (check for self-assignment, delete the existing memory)
    	- The destructor must delete the respective allocated memory
    - [ ] Clone function (on small hierarchy)
	- [ ] Specific required functionalities
5. Menu functionalities
	- [ ] Singleton class
	- [ ] Read and print n objects functionality
	- [ ] Try - catch
	- [ ] Pay attention to pointers (instead of objects) printing (on all `cout` occurences)
6. Testing
7.  Extra
	- [ ] Add the rest of functionalities
	- [ ] Use the checker class on some input
	- [ ] Use `sort` (with lambda and predefined comparison operator)
	- [ ] Comments on used OOP concepts
	- [ ] Stronger testing
	- [ ] Add more STL containers and features (pair, map, array, list, iterators etc.)
	- [ ] Other operators overloading (member and non-member functions)
	- [ ] Create builder classes
8.  Examples
	- Example 1
    	- [Cerinta](https://github.com/FMI-Materials/FMI-Materials/blob/main/Year%20I/Semester%20II/Programare%20Orientata%20Pe%20Obiecte/Modele%20Colocviu/2019%20-%202020/Model%2001.pdf)
    	- [Cod furat](https://github.com/FMI-Materials/FMI-Materials/blob/main/Year%20I/Semester%20II/Programare%20Orientata%20Pe%20Obiecte/Modele%20Colocviu/2019%20-%202020/Rezolvari/Model%2001%20Rezolvare%201.cpp)
	- Example 2
    	- [Cerinta](https://github.com/FMI-Materials/FMI-Materials/blob/main/Year%20I/Semester%20II/Programare%20Orientata%20Pe%20Obiecte/Modele%20Colocviu/2020%20-%202021/Model%2004.pdf)
    	- [Codul meu](./main.cpp)