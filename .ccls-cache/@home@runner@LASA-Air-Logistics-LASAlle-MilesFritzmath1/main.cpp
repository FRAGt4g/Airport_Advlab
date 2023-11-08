/*
 *
 *	Linked List lab.
 *	- Build a library for singly linked list.
 *	- Replace the airport array in main with a Linked List.
 *  - sort the array.
 *
 */

#include "slist.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void simpleSortTotal(LinkedList *list);
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);

int main() {
  ifstream infile;
  int i = 0;
  char cNum[20];
  char buffer[256];
  LinkedList list = *(new LinkedList()); // Replace array with Linked List
  int airportCount;
  const string referenceId = "AUS";
  Node reference;

  infile.open("USAirportCodes.csv", ifstream::in);
  Data ref;
  if (infile.is_open()) {
    int c = 0;
    infile.getline(buffer, 3000, '\n');
    while (infile.good()) {
      Node *n = new Node(new Data((char *)malloc(1), NAN, NAN));
      Data *info = n->data;
      infile.getline(info->code, 256, ',');
      cout << c << ") " << info->code << endl;

      infile.getline(cNum, 3000, ',');
      info->longitude = atof(cNum);
      infile.getline(cNum, 3000, '\n');
      info->latitude = atof(cNum);
      
      if (referenceId.compare(info->code) == 0) {
        reference = *new Node(n->data, n->nextNode, n->previousNode);
      }

      else {
        list.add(n);
      }

      i++;
      c++;
    }
    cout << "out of while" << endl;

    Node* n = list.get(0);
    c = 1;
    while(n->nextNode != nullptr) {
      n->data->distance = distanceEarth(n->data->latitude, n->data->longitude, reference.data->latitude, reference.data->longitude); 
      n = n->nextNode;
      c++;
    }
    
    simpleSortTotal(&list);
    
    n = list.get(0);
    c = 1;
    while(n->nextNode != nullptr) {
      printf("%s) %f\n", n->data->code, n->data->distance);
      n = n->nextNode;
      c++;
    }
    
    airportCount = c - 1;
    infile.close();
  } 

  else {
    cout << "Error opening file";
  }

  cout << "end of program" << endl;
}

#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

// This function converts decimal degrees to radians
double deg2rad(double deg) { return (deg * pi / 180); }

//  This function converts radians to decimal degrees
double rad2deg(double rad) { return (rad * 180 / pi); }

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r) / 2);
  v = sin((lon2r - lon1r) / 2);
  return 2.0 * earthRadiusKm *
         asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

/*
        Provide sort routine on linked list
*/
void simpleSortTotal(LinkedList *list) {
  Node* next = list->get(0);
  int c = 0;
  
  while (next->nextNode != nullptr) {
    Node* sub = next;
    int subC = 0;
    
    while(sub->nextNode != nullptr) {
      if (next->data->distance < sub->data->distance) {
        //printf("-------------------\nbefore switch\n\tnext: %s\n\tsub: %s\n", next->data->code, sub->data->code);
        Data* t = next->data;
        next->data = sub->data;
        sub->data = t;
        //printf("after switch\n\tnext: %s\n\tsub: %s\n", next->data->code, sub->data->code);
      }

      subC++;
      sub = sub->nextNode;
    }
    
    next = next->nextNode;
    c++;
  }
  
  /*
  for (int i = 0; i < s; i++) {
    d = list->get(i)->data;
    for (int j = i; j < s; j++) {
      d2 = list->get(j)->data;
      double dis = distanceEarth(d->latitude, d->longitude, ref.latitude, ref.latitude);
      double dis2 = distanceEarth(d2->latitude, d2->longitude, ref.latitude, ref.longitude);
      if (dis < dis2) {
        list->swap(i, j);
      }
    }
  }
  */
}