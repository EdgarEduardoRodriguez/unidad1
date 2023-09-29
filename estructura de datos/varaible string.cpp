#include<iostream>
#include<string>
using namespace std;

int main(){
    string nom, am, ap, serie, mes, dia, año; //variables de cadena  

    cout<<"Cual es su nombre?"; cin>>nom;
    cout<<"cual es su apellido paterno?"; cin>>ap;
    cout<<"Cual es su apellido materno?"; cin>>am;
    cout<<"cual es el dia en que nacio?"; cin>>dia;
    cout<<"Cual es el mes en el que nacio?"; cin>>mes;
    cout<<"Cual es el año en el que nacio?"; cin>>año;
    //limpiar el bufer despues de usar cin para poder usar el getline 
    cin.ignore();
    cout<<"Cual es su serie o peliula favorita?"; getline(cin, serie);// getline sirve para guardar cadenas con espacio
    string longitud = ap + " " + am + " " + nom + " " + dia + " " + mes + " " + año + " " + serie; 
    cout<<longitud.length();// para leer los caracteres de la cadena
    cout<<" "<<longitud<<endl;
    cout<<"la primera letra y segunda del apellido paterno es :"<<ap[0] <<ap[1] <<endl;
    cout<<"la primera letra y segunda del apellido materno es :"<<am[0] <<am[1] <<endl;
    cout<<"la primera letra y segunda del nombre es: "<<nom[0] <<nom[1] <<endl;
    
    

    return 0;
    
}