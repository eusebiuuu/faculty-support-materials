
1. Incorporate helper classes
```cpp
// abstract class suitable to inherit from it the base classes from the problem
// in this way one needs to override only the read and the write functions once
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

    virtual void read(std::istream &in){}
    virtual void write(std::ostream &out) const {}
};

// --------------------------------------------------------

// good for handling input and out-of-bound errors
template <class T>
class Checker{
public:
    Checker() = default;
    virtual ~Checker() = default;

    static void throwIfNotPositive(T);
    static void throwIfNotStrictPositive(T);
    static void throwIfNotInRange(T, T, T, std::string = "Numarul");
    static void throwIfGreaterThan(T, T, std::string = "Numarul");
};

template <class T>
void Checker<T>::throwIfNotPositive(T value) {
    if (value < 0) {
        throw std::runtime_error("Numarul trebuie sa fie pozitiv!");
    }
}

template <class T>
void Checker<T>::throwIfNotStrictPositive(T value) {
    if (value <= 0) {
        throw std::runtime_error("Numarul trebuie sa fie strict pozitiv!");
    }
}

template <class T>
void Checker<T>::throwIfNotInRange(T value, T a, T b, std::string ob_name) {
    if (value<a || value>b) {
        throw std::runtime_error(ob_name+" trebuie sa fie in intervaulul ["+std::to_string(a)+", "+std::to_string(b)+"]");
    }
}

template <class T>
void Checker<T>::throwIfGreaterThan(T value, T a, std::string ob_name) {
    if (value>a) {
        throw std::runtime_error(ob_name+" trebuie sa fie < "+std::to_string(a));
    }
}

```

2. Model code snippets
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
class DezinfectantFactory{
    DezinfectantFactory() = default;
public:
	static Dezinfectant *copyInstance(Dezinfectant *contract) {
        if (auto var = dynamic_cast<DezinfectantBacterii *>(contract))
            return new DezinfectantBacterii(*var);
        else if (auto var = dynamic_cast<DezinfectantFungi *>(contract))
            return new DezinfectantFungi(*var);
        else if (auto var = dynamic_cast<DezinfectantVirusuri *>(contract))
            return new DezinfectantVirusuri(*var);
        else if (auto var = dynamic_cast<DezinfectantGeneral *>(contract))
            return new DezinfectantGeneral(*var);
        else if (contract == nullptr)
            return nullptr;
        throw std::runtime_error("Tipul dezinfectantului este invalid!");
    }
    
    static Dezinfectant *newInstance(const std::string &tip) {
        if (tip == "bacterii")
            return new DezinfectantBacterii();
        else if (tip == "fungi")
            return new DezinfectantFungi();
        else if (tip == "virusuri")
            return new DezinfectantVirusuri();
        else if (tip == "general")
            return new DezinfectantGeneral();
        throw std::runtime_error("Tipul dezinfectantului este invalid!");
    }
};
```

#### Menu function example
```cpp
void menu() {  
    int command;  
    do {  
        printMenu();  
        std::cin >> command;  
        Checker<int>::throwIfNotInRange(command, 1, 8, "Comanda");  
        switch(command) {  
            case 1:  
                try {  
                    Lume::getInstance()->citireNCopii();  
                } catch (const std::exception &ex) {  
                    std::cout << ex.what() << '\n';  
                }  
                break;  
            case 2:  
                try {  
                    Lume::getInstance()->afisareNCopii();  
                } catch (const std::exception &ex) {  
                    std::cout << ex.what() << '\n';  
                }  
                break;  
            case 3:  
                try {  
                    Lume::getInstance()->gasesteCopil();  
                } catch (const std::exception &ex) {  
                    std::cout << ex.what() << '\n';  
                }  
                break;  
            case 4:  
                try {  
                    Lume::getInstance()->ordonareCopiiVarsta();  
                } catch (const std::exception &ex) {  
                    std::cout << ex.what() << '\n';  
                }  
                break;  
            case 5:  
                try {  
                    Lume::getInstance()->ordonareCopiiFapteBune();  
                } catch (const std::exception &ex) {  
                    std::cout << ex.what() << '\n';  
                }  
                break;  
            case 6:  
                try {  
                    Lume::getInstance()->adaugareInCopil();  
                } catch (const std::exception &ex) {  
                    std::cout << ex.what() << '\n';  
                }  
                break;  
            case 7:  
                try {  
                    Lume::getInstance()->afisareRaport();  
                } catch (const std::exception &ex) {  
                    std::cout << ex.what() << '\n';  
                }  
                break;  
            default:  
                return;  
        }  
    } while (true);  
}
```

4. Read all the statement
5. Create the app structure
6. Class creation checklist
	- [ ] Default constructors
	- [ ] Normal constructor
		- Initialisation list
		- Const and & / use std::move()
	- [ ] Override the read and write functions
		 - Use the checker class on input
		 - Print information before reading or writing data
	- [ ] Add id or counter (if needed) - static use case
	- [ ] Virtual destructor overriding
	- [ ] Classes with pointers as data members must have the copy constructor and the `=` operator rewritten, and its destructor must delete the respective allocated memory (rule of three, kind of)
	- [ ] Encapsulation (getters and setters) (CLion generated)
	- [ ] Computations in functions, not on data members
	- [ ] Statement specific functionalities
7. Additional advice
	- [ ] Singleton on control panel class (or Menu class)
	- [ ]  Try - catch in menu (on menu commands execution)
	- [ ] Use `sort`  (with lambda and predefined comparison operator) and `count` functions (if possible)
	- [ ] Add factory class for base classes for ease in reading specific types and copying
	- [ ] **Read and print n objects functionality in menu**
8. Testing
	- [ ] Test the app with the demo (if any)
	- [ ] Create input file and run the app with it
9. If any time left
	- [ ] Add more STL containers and features (pair, map, array, list, iterators etc.)
	- [ ] Other operators overloading (member and non-member functions)
	- [ ] Struct
	- [ ] Exception classes from `std::exception`
	- [ ] Create builder classes
	- [ ] Comments on used OOP concepts
10. Examples
	- Example 1
    	- [Cerinta](https://github.com/FMI-Materials/FMI-Materials/blob/main/Year%20I/Semester%20II/Programare%20Orientata%20Pe%20Obiecte/Modele%20Colocviu/2019%20-%202020/Model%2001.pdf)
    	- [Cod furat](https://github.com/FMI-Materials/FMI-Materials/blob/main/Year%20I/Semester%20II/Programare%20Orientata%20Pe%20Obiecte/Modele%20Colocviu/2019%20-%202020/Rezolvari/Model%2001%20Rezolvare%201.cpp)
	- Example 2
    	- [Cerinta](https://github.com/FMI-Materials/FMI-Materials/blob/main/Year%20I/Semester%20II/Programare%20Orientata%20Pe%20Obiecte/Modele%20Colocviu/2020%20-%202021/Model%2004.pdf)
    	- [Codul meu](./main.cpp)