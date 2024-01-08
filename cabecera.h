#include <cstdlib>
#include <ctime>
#include <iostream>
#include <math.h>
#include <stdio.h>

const int MaxReflections = 5; //Max buncings
const double LostEnergy = 0.20; //Init Energy
using namespace std;

//----------VECTOR----------
class vector {
//Constructor
public:
  double x, y, z;
  vector() {
    x = 0.0;
    y = 0.0;
    z = 0.0;
  }
// Operators overload

// init a Vector with d value in each component
  void operator=(double d) {
    x = y = z = d;
  }
// Sums two vectos
  vector operator+(vector p) {
    vector r;
    r.x = x + p.x;
    r.y = y + p.y;
    r.z = z + p.z;
    return r;
  }
//thisVector - pVector
  vector operator-(vector p) {
    vector r;
    r.x = x - p.x;
    r.y = y - p.y;
    r.z = z - p.z;
    return r;
  }
// d factor like d*V
  vector operator*(double d) {
    vector v;
    v.x = x * d;
    v.y = y * d;
    v.z = z * d;
    return v;
  }
// 1/d factor like (1/d)*V
  vector operator/(double d) {
    vector v;
    v.x = x / d;
    v.y = y / d;
    v.z = z / d;
    return v;
  }
//Scalar Vectorial product
  double operator*(vector v) {
    return x * v.x + y * v.y + z * v.z;
  }
// Vectorial Product
  vector operator/(vector v) {
    vector r;
    r.x = y * v.z - z * v.y;
    r.y = z * v.x - x * v.z;
    r.z = x * v.y - y * v.x;
    return r;
  }
//Vector magnitude
  double modulo() { // Módulo
    return sqrt(x * x + y * y + z * z);
  }
};
//----------POINT----------
class point {
//Constructor
public:
  double x, y, z;
  point() {
    x = 0.0;
    y = 0.0;
    z = 0.0;
  }
// Init Point with same components
  void operator=(double d) {
    x = y = z = d;
  }
// Asign components
  void assign(double d1, double d2, double d3) {
    x = d1;
    y = d2;
    z = d3;
  }
// thisPoint + pPoint
  point operator+(point p) {
    point r;
    r.x = x + p.x;
    r.y = y + p.y;
    r.z = z + p.z;
    return r;
  }
// thisPoint + pVector = Point
  point operator+(vector v) { // Translación (Mover un punto)
    point r;
    r.x = x + v.x;
    r.y = y + v.y;
    r.z = z + v.z;
    return r;
  }
// thisPoint - pPoint = Vector
  vector operator-(point p) { // Resta de puntos = Vector
    vector v;
    v.x = x - p.x;
    v.y = y - p.y;
    v.z = z - p.z;
    return v;
  }
// d factor
  point operator*(double d) { // Multiplicación por Escalar
    point p;
    p.x = x * d;
    p.y = y * d;
    p.z = z * d;
    return p;
  }
// 1/d factor
  point operator/(double d) { // División por Escalar
    point p;
    p.x = x / d;
    p.y = y / d;
    p.z = z / d;
    return p;
  }
//Gap between two points
  double distancia(point p) { // Distancia entre dos puntos
    return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2) + pow(z - p.z, 2));
  }
//reset Point
  void clear() { // Limpieza del punto (setear todos los valores en 0)
    x = y = z = 0;
  }
};

//----------TRIANGLE----------
class triangle {
// Constructor
public:
  point p1, p2, p3, bc;
  vector n;
  triangle() {
    p1 = 0.0;
    p2 = 0.0;
    p3 = 0.0;
    bc = 0.0;
    n = 0.0;
  }
// Calculate baricentro
  void baricentro() {
    bc = (p1 + p2 + p3) / 3;
  }
// Calculate Normal Vector from triangle
  vector normalTriangle() {
    n = (p2 - p1) / (p3 - p1);
    if (n.modulo() == 0)
      n = 0;
    else
      n = n / n.modulo();
    return n;
  }
// Reset triangle
  void clear() { // Setea los atributos
    p1 = 0.0;
    p2 = 0.0;
    p3 = 0.0;
    bc = 0.0;
    n = 0.0;
  }
};
//----------PLANE----------
class plane {
//Constructor
public:
  point *p;    // Elementos tipo plano
  int NP;      // Número de planos
  triangle *t; // Elemento tipo triángulo
  int NT;      // Número de triangulos
  vector n;    // Vector normal del plano
  float minX, minY, minZ;
  float maxX, maxY, maxZ;

  plane() {
    p = NULL;
    NP = 0;
    t = NULL;
    NT = 0;
    n = 0;
    minX = 0;
    minY = 0;
    minZ = 0;
    maxX = 0;
    maxY = 0;
    maxZ = 0;
  }
//Reset plane
  void clear() {
    delete[] p;
    NP = 0;
    delete[] t;
    NT = 0;
    n = 0;
    minX = 0;
    minY = 0;
    minZ = 0;
    maxX = 0;
    maxY = 0;
    maxZ = 0;
  }
// Calculate normal vector from plane/triangle
  void normalPlane() { // Normal del plano = Normal del triangulo
    n = t[0].normalTriangle();
  }
//Add Points to plane
  void newPoints(int N) { // Agrega más puntos
    int P;
    point *tp;
    tp = new point[NP + N];
    for (P = 0; P < NP; P++) {
      tp[P] = p[P];
    }
    for (P = NP; P < NP + N; P++) {
      tp[P].clear();
    }
    if (NP > 0) {
      delete[] p;
      p = NULL;
    }
    p = tp;
    NP += N;
  }
//Add triangles to plane
  void newTriangle(int N) {
    int T;
    triangle *aux;
    aux = new triangle[NT + N];
    for (T = 0; T < NT; T++) {
      aux[T] = t[T];
    }
    for (T = NT; T < NT + N; T++) {
      aux[T].clear();
    }
    if (NP > 0) {
      delete[] t;
      t = NULL;
    }
    t = aux;
    NT += N;
  }
//transform a plane in two triangles
  void pointGenTriangle() {
    newTriangle(NP - 2);
    int i = 1;
    for (int T = 0; T < NT; T++) {
      i--;
      t[T].p1.x = p[i].x;
      t[T].p1.y = p[i].y;
      t[T].p1.z = p[i].z;
      i++;
      if (i == NP)
        i = 0;
      t[T].p2.x = p[i].x;
      t[T].p2.y = p[i].y;
      t[T].p2.z = p[i].z;
      i++;
      if (i == NP)
        i = 0;
      t[T].p3.x = p[i].x;
      t[T].p3.y = p[i].y;
      t[T].p3.z = p[i].z;
      i++;
    }
  }
// Init edge values
  void valuesDefault() {
    minX = p[0].x;
    minY = p[0].y;
    minZ = p[0].z;
    maxX = p[0].x;
    maxY = p[0].y;
    maxZ = p[0].z;
  }
//Calculate ranges for the plane
  void obtenerRangos() {
    for (int i = 0; i < NP; i++) {
      if (p[i].x < minX) {
        minX = p[i].x;
      }
      if (p[i].x > maxX) {
        maxX = p[i].x;
      }

      if (p[i].y < minY) {
        minY = p[i].y;
      }
      if (p[i].y > maxY) {
        maxY = p[i].y;
      }

      if (p[i].z < minZ) {
        minZ = p[i].z;
      }
      if (p[i].z > maxZ) {
        maxZ = p[i].z;
      }
    }
  }

 // Is this Point in that plane?
  bool pointInPlane(point punto) {
    int accept = 0;
    if (punto.x >= minX && punto.x <= maxX) {
      accept++;
    }
    if (punto.y >= minY && punto.y <= maxY) {
      accept++;
    }
    if (punto.z >= minZ && punto.z <= maxZ) {
      accept++;
    }

    if (accept == 3) {
      return true;
    } else {
      return false;
    }
  }
};
//----------SOURCE----------
class source {
//Constructor
public:
  point p; // Posición
  double eF;    // Energía de la fuente
  int NRAYS;    // Número de  rayos que parten de la fuente
  vector *Rays; // Dirección de partida de la fuente

  source() {
    p = 0.0;
    eF = 0.0;
    NRAYS = 0;
    Rays = NULL;
  }
//Init ray
  void createRay(double x, double y, double z) {
    if (NRAYS > 0)
      delete[] Rays;
    NRAYS = 1;
    Rays = new vector[NRAYS];
    Rays[0].x = x;
    Rays[0].y = y;
    Rays[0].z = z;
    Rays[0] = Rays[0] / Rays[0].modulo();
  }
//Change ray energy
  void changeEnergy(double energy) {
    eF = energy;
  }
};
