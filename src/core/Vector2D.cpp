#include "Vector2D.h"
#include <iostream>
#include <assert.h>

using namespace std;

Vector2D::Vector2D(){
    x = 0;
    y = 0;
}

Vector2D::Vector2D(float a, float b){
    x = a;
    y = b;
}

Vector2D::~Vector2D(){

}

void Vector2D::show(){
    if(x == 0 && y != 0)
        cout << "Vecteur: " << y << "i" << endl << endl;
    else if(x != 0 && y == 0)
        cout << "Vecteur: " << x << endl << endl;
    else if(x != 0 && y > 0)
        cout << "Vecteur: " << x << " + " << y << "i" << endl << endl;
    else if(x != 0 && y < 0)
        cout << "Vecteur: " << x << " " << y << "i" << endl << endl;
    else if(x == 0 && y == 0)
        cout << "Vecteur nul" << endl << endl;
}

void operator+(Vector2D &a, Vector2D b) {
    a.x = a.x + b.x;
    a.y = a.y + b.y;
}

void operator-(Vector2D &a, Vector2D b){
    a.x = a.x - b.x;
    a.y = a.y - b.y;
}

void operator*(Vector2D &a, float b){
    a.x = a.x * b;
    a.y = a.y * b;
}

void operator/(Vector2D &a, float b){
    if(b == 0){
        cout << "Erreur, division par 0" << endl;
    }
    else {
        a.x = a.x / b;
        a.y = a.y / b;
    }
}

void Vector2D::regressionTest(){
    int zeroCoeff = 0;
    int coeff = 2;

    Vector2D vecAfterTest(30, 40);
    Vector2D vecDefault(25, 30);
    Vector2D vec(25, 30);
    Vector2D vec2(5, 10);
    Vector2D vecY0(25, 0);
    Vector2D vecX0(0, 30);
    Vector2D vecBig(30, 50);
    Vector2D vecZero;

    assert(vec.x == 25 && vec.y == 30);

    operator+(vec, vecZero);
    assert(vec.x == 25 && vec.y == 30);
    cout << "Add 0 ok" << endl;

    operator+(vec, vec2);
    assert(vec.x == 30 && vec.y == 40);
    cout << "Vec + Vec ok" << endl;

    operator-(vec, vecZero);
    assert(vec.x == 30 && vec.y == 40);
    cout << "Vec - 0 ok" << endl;

    operator-(vec, vec);
    assert(vec.x == 0 && vec.y == 0);
    cout << "Vec nul" << endl;
    operator+(vec, vecAfterTest);

    operator-(vec, vec2);
    assert(vec.x == 25 && vec.y == 30);
    cout << "Vec - vec ok" << endl;

    operator-(vec, vecBig);
    assert(vec.x == -5 && vec.y == -20);
    cout << "Vec négatif ok" << endl;
    operator+(vec, vecBig);

    operator-(vec, vecY0);
    assert(vec.x == 0 && vec.y == 30);
    cout << "x nul ok" << endl;
    operator+(vec, vecY0);

    operator-(vec, vecX0);
    assert(vec.x == 25 && vec.y == 0);
    cout << "y nul ok" << endl;
    vec.show();
    operator+(vec, vecX0);
    vec.show();

    operator*(vec, zeroCoeff);
    assert(vec.x == 0 && vec.y == 0);
    cout << "Vec * 0 ok" << endl;
    vec.show();
    operator+(vec, vecDefault);

    operator*(vec, coeff);
    assert(vec.x == 50 && vec.y == 60);
    cout << "Vec * vec ok" << endl;
    vec.show();

    operator/(vec, coeff);
    assert(vec.x == 25 && vec.y == 30);
    cout<<"Vec / vec ok"<<endl;
    vec.show();

    operator/(vec, 0);
    cout << "Div 0 ok" << endl;
    vec.show();
}