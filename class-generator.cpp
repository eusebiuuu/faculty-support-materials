#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;

class Class_Generator
{
public:
  string nume_clasa;
  vector<string> tipuri;
  vector<string> denumiri;
  vector<string> stl_denumiri;
  Class_Generator *clasa_baza;
  Class_Generator *clasa_baza2;
  vector<string> obiecte;

public:
  friend istream &operator>>(istream &, Class_Generator &);
  friend ostream &operator<<(ostream &, Class_Generator &);
  void generare();
  void set_clasa_baza(Class_Generator *aux)
  {
    clasa_baza = aux;
  };
  void set_clasa_baza2(Class_Generator *aux)
  {
    clasa_baza2 = aux;
  };
  void generare_derivata();
  void generare_template_vector();
  void generare_supraincarcare_string();
  void generare_citire_afisare();
  void add(string tip, string denumire, string stl_denumire = "")
  {
    tipuri.push_back(tip);
    denumiri.push_back(denumire);
    stl_denumiri.push_back(stl_denumire);
  }
};

istream &operator>>(istream &in, Class_Generator &aux)
{
  cout << "Introduceti numele clasei: ";
  in >> aux.nume_clasa;
  int n;
  cout << "Introduceti numarul de date membre: ";
  in >> n;
  for (int i = 0; i < n; i++)
  {
    string auxx;
    while (true)
    {
      cout << "Introduceti tipul datei: ";
      in >> auxx;
      if (auxx == "int" || auxx == "string" || auxx == "float" || auxx == "double" || auxx == "bool" || auxx == "vector")
        break;
      cout << "Poate fi doar int, string,float sau double, bool, vector\n";
    }
    aux.tipuri.push_back(auxx);
    int accesat = 1;
    if (auxx == "vector")
    {
      cout << "Introduceti tipul din vector: ";
      in >> auxx;
      accesat = 0;
      aux.stl_denumiri.push_back(auxx);
    }
    cout << "Introduceti numele variabilei:";
    in >> auxx;
    aux.denumiri.push_back(auxx);
    if (accesat)
      aux.stl_denumiri.push_back("");
  }
  return in;
}
ostream &operator<<(ostream &out, Class_Generator &aux)
{
  out << aux.nume_clasa << endl;
  for (int i = 0; i < aux.denumiri.size(); i++)
  {
    out << aux.tipuri[i] << " " << aux.denumiri[i];
    if (aux.tipuri[i] == "vector")
      out << aux.stl_denumiri[i];
    out << endl;
  }
  return out;
}

void Class_Generator::generare_supraincarcare_string()
{
  cout << "istream& operator >> (istream& in, string& a)\n{\nin.ignore();\ngetline(in,a);\nreturn in;\n}\n\n";
}
void Class_Generator::generare_template_vector()
{
  cout << "template<typename T>\nostream& operator<<(ostream& out, vector<T> t) {\nfor (size_t i = 0; i < t.size(); i++) {\nout << t[i] << \" \";\n}\nout<<endl;\nreturn out;\n}\n\ntemplate<typename T>\nistream& operator>>(istream& in, vector<T> *t) {\nint counter;\ncout<<\"\\nNumar elemente:\";\nin>>counter;\nT aux;\nfor (int i = 0; i < counter; i++) {\ncin>>aux;\ntry{\nt->push_back(aux);\n}\ncatch(bad_alloc){\ncout<<\"ALLOCATION ERROR\";\nexit(EXIT_FAILURE);\n}\n}\nreturn in;\n}\n\n\n\n";
}

void Class_Generator::generare()
{
  cout << "class " << nume_clasa << "{\n";
  cout << "private:\n";
  for (int i = 0; i < denumiri.size(); i++)
  {
    if (tipuri[i] == "vector")
    {
      cout << tipuri[i] << "<" << stl_denumiri[i] << "> " << denumiri[i] << ";" << endl;
    }
    else
    {
      cout << tipuri[i] << " " << denumiri[i] << ";" << endl;
    }
  }
  cout << "public:\n";
  cout << nume_clasa << "(";
  for (int i = 0; i < tipuri.size() - 1; i++)
  {
    if (tipuri[i] == "vector")
    {
      cout << "const " << tipuri[i] << "<" << stl_denumiri[i] << ">*,";
    }
    else
    {
      cout << "const " << tipuri[i];
      if (tipuri[i] == "string")
      {
        cout << "&";
      }
      cout << ",";
    }
  }
  if (tipuri[tipuri.size() - 1] == "vector")
  {
    cout << "const " << tipuri[tipuri.size() - 1] << "<" << stl_denumiri[tipuri.size() - 1] << ">*";
  }
  else
  {
    cout << "const " << tipuri[tipuri.size() - 1];
    if (tipuri[tipuri.size() - 1] == "string")
    {
      cout << "&";
    }
  }
  cout << ");\n";

  cout << nume_clasa << "(const " << nume_clasa << "&);\n";
  cout << "virtual ~" << nume_clasa << "();\n";

  cout << "virtual void citire(istream&);\n";
  cout << "virtual void afisare(ostream&) const;\n";

  cout << nume_clasa << "& " << "operator=(const " << nume_clasa << "&);\n";
  cout << "friend istream& operator>>(istream&," << nume_clasa << "&);\n";
  cout << "friend ostream& operator<<(ostream&,const " << nume_clasa << "&);\n";
  cout << "};\n";

  cout << "\n\n";
  cout << nume_clasa << "::" << nume_clasa << "(";
  for (int i = 0; i < tipuri.size() - 1; i++)
  {
    if (tipuri[i] == "vector")
    {
      cout << "const " << tipuri[i] << "<" << stl_denumiri[i] << ">*";
      cout << " " << denumiri[i] << "= new " << tipuri[i] << "<" << stl_denumiri[i] << ">(),";
    }
    else
    {
      cout << "const " << tipuri[i];
      if (tipuri[i] == "string")
      {
        cout << "&";
      }
      cout << " " << denumiri[i];
      cout << "=";
      if (tipuri[i] == "float" || tipuri[i] == "bool" || tipuri[i] == "int" || tipuri[i] == "double")
        cout << "0";
      if (tipuri[i] == "string")
        cout << "\"\"";
      cout << ",";
    }
  }
  if (tipuri[tipuri.size() - 1] == "vector")
  {
    cout << "const " << tipuri[tipuri.size() - 1] << "<" << stl_denumiri[tipuri.size() - 1] << ">*";
    cout << " " << denumiri[tipuri.size() - 1] << "= new " << tipuri[tipuri.size() - 1] << "<" << stl_denumiri[tipuri.size() - 1] << ">()";
  }
  else
  {
    cout << "const " << tipuri[tipuri.size() - 1];
    if (tipuri[tipuri.size() - 1] == "string")
    {
      cout << "&";
    }
    cout << " " << denumiri[tipuri.size() - 1];
    if (tipuri[tipuri.size() - 1] == "float" || tipuri[tipuri.size() - 1] == "bool" || tipuri[tipuri.size() - 1] == "int" || tipuri[tipuri.size() - 1] == "double")
      cout << "=0";
    if (tipuri[tipuri.size() - 1] == "string")
      cout << "=\"\"";
  }
  cout << "){\n";

  for (int i = 0; i < tipuri.size(); i++)
    if (tipuri[i] == "vector")
    {
      cout << "this->" << denumiri[i] << "=*(" << denumiri[i] << ");\n";
    }
    else
    {
      cout << "this->" << denumiri[i] << "=" << denumiri[i] << ";\n";
    }
  cout << "}\n";

  cout << "\n\n";

  /// Constructor copiere
  cout << nume_clasa << "::" << nume_clasa << "(const " << nume_clasa << "& aux){\n";
  for (int i = 0; i < tipuri.size(); i++)
    cout << denumiri[i] << "=aux." << denumiri[i] << ";\n";
  cout << "}\n\n";

  /// Destructor
  cout << nume_clasa << "::~" << nume_clasa << "(){\n";
  for (int i = 0; i < tipuri.size(); i++)
  {
    if (tipuri[i] == "vector")
    {
      cout << denumiri[i] << ".clear();\n";
    }
    else
    {
      cout << denumiri[i] << "=";
      if (tipuri[i] == "float" || tipuri[i] == "bool" || tipuri[i] == "int" || tipuri[i] == "double")
        cout << "0";
      if (tipuri[i] == "string")
        cout << "\"\"";
      cout << ";\n";
    }
  }
  cout << "}\n\n\n";

  /// Citire
  cout << "void " << nume_clasa << "::" << "citire(istream& in){\n";
  for (int i = 0; i < tipuri.size(); i++)
  {
    cout << "cout<<\"Introduceti " << denumiri[i] << ":\";\n";
    if (tipuri[i] == "vector")
    {
      cout << "in>>(&" << denumiri[i] << ");\n";
    }
    else
    {
      cout << "in>>" << denumiri[i] << ";\n";
    }
  }
  cout << "}\n\n\n";

  /// Afisare
  cout << "void " << nume_clasa << "::" << "afisare(ostream& out) const {\n";
  for (int i = 0; i < tipuri.size(); i++)
  {
    cout << "out<<\"" << denumiri[i] << "=\""
                                        "<<"
         << denumiri[i] << "<<endl;\n";
  }
  cout << "}\n\n\n";

  /// Supraincarcare >>
  cout << "istream& " << "operator>>(istream& in," << nume_clasa << " &aux){\n";
  cout << "aux.citire(in);\n";
  cout << "return in;\n";
  cout << "}\n\n\n";

  /// Supraincarcare <<
  cout << "ostream& " << " operator<<(ostream& out,const " << nume_clasa << " &aux){\n";
  cout << "aux.afisare(out);\n";
  cout << "return out;\n";
  cout << "}\n\n\n";

  /// Supraincarcare =

  cout << nume_clasa << "& " << nume_clasa << "::operator=(const " << nume_clasa << "& aux){\n";
  cout << "if (this!=&aux){\n";
  for (int i = 0; i < tipuri.size(); i++)
    cout << denumiri[i] << "=aux." << denumiri[i] << ";\n";

  cout << "}\nreturn *this;\n";

  cout << "}\n\n\n";
}
void Class_Generator::generare_derivata()
{
  if (clasa_baza != NULL)
  {
    cout << "\n\n";
    cout << "class " << nume_clasa << ": public " << clasa_baza->nume_clasa << "{\n";
    cout << "private:\n";

    /// Declarari
    for (int i = 0; i < tipuri.size(); i++)
    {
      if (tipuri[i] == "vector")
      {
        cout << tipuri[i] << "<" << stl_denumiri[i] << "> " << denumiri[i] << ";" << endl;
      }
      else
      {
        cout << tipuri[i] << " " << denumiri[i] << ";" << endl;
      }
    }

    cout << "public:\n";
    /// Constructor
    cout << nume_clasa << "(";
    int counter = 0;
    for (int i = 0; i < clasa_baza->tipuri.size(); i++)
    {
      counter = 1;
      if (i >= 1)
      {
        cout << ", ";
      }
      if (clasa_baza->tipuri[i] == "vector")
      {
        cout << "const " << clasa_baza->tipuri[i] << "<" << clasa_baza->stl_denumiri[i] << ">*";
      }
      else
      {
        cout << "const " << clasa_baza->tipuri[i];
        if (clasa_baza->tipuri[i] == "string")
        {
          cout << "&";
        }
      }
    }

    for (int i = 0; i < tipuri.size(); i++)
    {
      if (counter == 1)
      {
        cout << ", ";
      }
      if (tipuri[i] == "vector")
      {
        cout << "const " << tipuri[i] << "<" << stl_denumiri[i] << ">*";
      }
      else
      {
        cout << "const " << tipuri[i];
        if (tipuri[i] == "string")
        {
          cout << "&";
        }
      }
    }
    cout << ");\n";

    /// Constructor Copiere
    cout << nume_clasa << "(const " << nume_clasa << "& aux);\n";

    /// Destructor
    cout << "~" << nume_clasa << "();\n";

    /// Citire si Afisare
    cout << "virtual void citire(istream&);\n";
    cout << "virtual void afisare(ostream&) const;\n";
    cout << nume_clasa << "& " << "operator=(const " << nume_clasa << "&);\n";
    cout << "friend istream& operator>>(istream&," << nume_clasa << "&);\n";
    cout << "friend ostream& operator<<(ostream&,const " << nume_clasa << "&);\n";
    cout << "};\n\n";

    /// Constructor

    cout << nume_clasa << "::" << nume_clasa << "(";
    for (int i = 0; i < clasa_baza->tipuri.size(); i++)
    {
      counter = 1;
      if (i >= 1)
      {
        cout << ", ";
      }
      if (clasa_baza->tipuri[i] == "vector")
      {
        cout << "const " << clasa_baza->tipuri[i] << "<" << clasa_baza->stl_denumiri[i] << ">*";
        cout << " " << clasa_baza->denumiri[i] << "= new " << clasa_baza->tipuri[i] << "<" << clasa_baza->stl_denumiri[i] << ">()";
      }
      else
      {
        cout << "const " << clasa_baza->tipuri[i];
        if (clasa_baza->tipuri[i] == "string")
          cout << "&";
        cout << " " << clasa_baza->denumiri[i];
        cout << "=";
        if (clasa_baza->tipuri[i] == "string")
          cout << "\"\"";
        if (clasa_baza->tipuri[i] == "int" || clasa_baza->tipuri[i] == "double" || clasa_baza->tipuri[i] == "float" || clasa_baza->tipuri[i] == "bool")
          cout << "0";
      }
    }
    for (int i = 0; i < tipuri.size(); i++)
    {
      if (counter == 1)
      {
        cout << ", ";
      }
      if (tipuri[i] == "vector")
      {
        cout << "const " << tipuri[i] << "<" << stl_denumiri[i] << ">*";
        cout << " " << denumiri[i] << "= new " << tipuri[i] << "<" << stl_denumiri[i] << ">()";
      }
      else
      {
        cout << "const " << tipuri[i];
        if (tipuri[i] == "string")
          cout << "&";
        cout << " " << denumiri[i];
        cout << "=";
        if (tipuri[i] == "string")
          cout << "\"\"";
        if (tipuri[i] == "int" || tipuri[i] == "double" || tipuri[i] == "float" || tipuri[i] == "bool")
          cout << "0";
      }
    }
    cout << "):" << clasa_baza->nume_clasa << "(";
    for (int i = 0; i < clasa_baza->tipuri.size(); i++)
    {
      counter = 1;
      if (i >= 1)
      {
        cout << ", ";
      }
      cout << clasa_baza->denumiri[i];
    }
    cout << "){\n";

    for (int i = 0; i < denumiri.size(); i++)
    {
      if (tipuri[i] == "vector")
      {
        cout << "this->" << denumiri[i] << "=*(" << denumiri[i] << ");\n";
      }
      else
      {
        cout << "this->" << denumiri[i] << "=" << denumiri[i] << ";\n";
      }
    }
    cout << "}\n";

    /// Constructor Copiere
    cout << nume_clasa << "::" << nume_clasa << "(const " << nume_clasa << "& aux):" << clasa_baza->nume_clasa << "(aux){\n";
    for (int i = 0; i < denumiri.size(); i++)
    {
      cout << denumiri[i] << "= aux." << denumiri[i] << ";\n";
    }
    cout << "}\n\n";

    /// Destructor
    cout << nume_clasa << "::~" << nume_clasa << "(){\n";
    for (int i = 0; i < denumiri.size(); i++)
    {
      if (tipuri[i] == "vector")
      {
        cout << denumiri[i] << ".clear();\n";
      }
      else
      {
        cout << denumiri[i] << "=";
        if (tipuri[i] == "float" || tipuri[i] == "bool" || tipuri[i] == "int" || tipuri[i] == "double")
          cout << "0";
        if (tipuri[i] == "string")
          cout << "\"\"";
        cout << ";\n";
      }
    }
    cout << "}\n\n";

    /// Citire
    cout << "void " << nume_clasa << "::" << "citire(istream& in){\n";
    cout << clasa_baza->nume_clasa << "::citire(in);\n";
    for (int i = 0; i < tipuri.size(); i++)
    {
      cout << "cout<<\"Introduceti " << denumiri[i] << ":\";\n";
      if (tipuri[i] == "vector")
      {
        cout << "in>>(&" << denumiri[i] << ");\n";
      }
      else
      {
        cout << "in>>" << denumiri[i] << ";\n";
      }
    }
    cout << "}\n\n\n";

    /// Afisare
    cout << "void " << nume_clasa << "::" << "afisare(ostream& out) const {\n";
    cout << clasa_baza->nume_clasa << "::afisare(out);\n";
    for (int i = 0; i < tipuri.size(); i++)
    {
      cout << "out<<\"" << denumiri[i] << "=\""
                                          "<<"
           << denumiri[i] << "<<endl;\n";
    }
    cout << "}\n\n\n";

    /// Supraincarcare >>
    cout << "istream& " << "operator>>(istream& in," << nume_clasa << " &aux){\n";
    cout << "aux.citire(in);\n";
    cout << "return in;\n";
    cout << "}\n\n\n";

    /// Supraincarcare <<
    cout << "ostream& " << " operator<<(ostream& out,const " << nume_clasa << " &aux){\n";
    cout << "aux.afisare(out);\n";
    cout << "return out;\n";
    cout << "}\n\n\n";

    /// Supraincarcare =

    cout << nume_clasa << "& " << nume_clasa << "::operator=(const " << nume_clasa << "& aux){\n";
    cout << "if (this!=&aux){\n";
    cout << nume_clasa << "::operator=(aux);\n";
    for (int i = 0; i < tipuri.size(); i++)
      cout << denumiri[i] << "=aux." << denumiri[i] << ";\n";

    cout << "}\nreturn *this;\n";

    cout << "}\n\n\n";
  }
}
void Class_Generator::generare_citire_afisare()
{
  cout << "vector<" << obiecte[0] << "*> obiecte;\n";
  cout << "cout<<\"Numar obiecte:\";\n";
  cout << "int n;\n";
  cout << "cin>>n;\n";
  cout << "string tip;\n";
  cout << "for(int i=0;i<n;){\n";
  cout << "cout<<\"Introduceti tipul obiectului:\";\n";
  cout << "cin>>tip;\n";
  cout << "try{\n";
  for (int i = 0; i < obiecte.size(); i++)
  {
    if (i >= 1)
      cout << "\nelse ";
    cout << "if(tip==\"" << obiecte[i] << "\"){\n";
    cout << obiecte[i] << " *p= new " << obiecte[i] << ";\n";
    cout << "cin>>*p;\n";
    cout << "obiecte.push_back(p);\n";
    cout << "i++;\n}\n";
  }
  cout << "else{\n";
  cout << "cout<<\"Sunt valabile doar: ";
  for (int i = 0; i < obiecte.size(); i++)
    cout << obiecte[i] << " ";
  cout << "\\n\";";
  cout << "}\n";
  cout << "}\n";
  cout << "catch (bad_alloc bdal){\ncout << \"Eroare alocare...\";\nexit(EXIT_FAILURE);\n}\n";
  cout << "\n\n}\n\n";

  cout << "//// afisare\n";
  cout << "cout<<\"Afisare obiecte:\\n\";\n";
  for (int i = 0; i < obiecte.size(); i++)
  {
    cout << "cout<<\"Afisez " << obiecte[i] << ":\\n\"; \n";
    cout << "for(int i=0;i<obiecte.size();i++){\n";
    cout << obiecte[i] << "* p=dynamic_cast<" << obiecte[i] << "*>(obiecte[i]);\n";
    cout << "if(p){\n";
    cout << "cout<<*obiecte[i];";
    cout << "\n}\n";
    cout << "cout<<\"\\n\\n\";\n";
    cout << "}\n";
  }
}

int main()
{

  Class_Generator cg;
  cg.nume_clasa = "Zbor";
  cg.add("string", "id");
  cg.add("string", "oras");
  cg.add("string", "destinatie");
  cg.add("string", "zi_plecare");
  cg.add("float", "durata");
  cg.generare_template_vector();
  cg.generare();

  Class_Generator cg2;
  cg2.nume_clasa = "ZborTemporar";
  cg2.add("int", "disponibilitate");
  cg2.clasa_baza = &cg;
  cg2.generare_derivata();

  Class_Generator cg3;
  cg3.nume_clasa = "ZborOferta";
  cg3.add("float", "discount");
  cg3.clasa_baza = &cg;
  cg3.generare_derivata();
}