#include "Vector2D.h"
#include <iostream>
#include <assert.h>
#include <math.h>

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

const Vector2D Vector2D::operator+(const Vector2D& vec) {
    Vector2D vec2;
    vec2.x = x + vec.x;
    vec2.y = y + vec.y;
    return vec2;
}

const Vector2D Vector2D::operator+(float b) {
    Vector2D r;
    r.x = x + b;
    r.y = y + b;
    return r;
}

Vector2D Vector2D::operator-(const Vector2D& vec){
    Vector2D vec2;
    vec2.x = x - vec.x;
    vec2.y = y - vec.y;
    return vec2;
}

const Vector2D Vector2D::operator*(const Vector2D &vec){
    Vector2D vec2;
    vec2.x = (x * vec.x) - (y * vec.y);
    vec2.y = (x * vec.y) + (vec.x * y);
    return vec2;
}

Vector2D Vector2D::operator*(float b){
    Vector2D vec;
    vec.x = x * b;
    vec.y = y * b;
    return vec;
}

Vector2D Vector2D::operator/(float b){
    Vector2D r;
    if(b == 0){
        cout << "Erreur, division par 0" << endl;
        r = {0, 0};
    }
    else {
        r.x = x / b;
        r.y = y / b;
    }

    return r;
}

const float Vector2D::module(){
    return sqrt(pow(x, 2) + pow(y, 2));
}

void Vector2D::regressionTest()
{
    cout << endl << "- TESTS Vector2D -" << endl;
    cout << "**************************" << endl;

    Vector2D vec1(15, 15);
    Vector2D vec2(10, 10);

    Vector2D vec3 = vec1 + vec2;
    assert(vec3.x == 25 && vec3.y == 25);
    cout << "--> Operator+ OK" << endl;

    vec3 = vec1 - vec2;
    assert(vec3.x == 5 && vec3.y == 5);
    cout << "--> Operator- OK" << endl;

    vec3 = vec1 * vec2;
    assert(vec3.x == 0 && vec3.y == 300);
    cout << "--> Operator* OK" << endl;

    vec3 = vec1 / 2;
    assert(vec3.x == 7.5 && vec3.y == 7.5);
    cout << "--> Operator/ OK" << endl;
}