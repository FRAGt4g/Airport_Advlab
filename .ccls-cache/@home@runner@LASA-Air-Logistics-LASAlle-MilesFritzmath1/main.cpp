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

void simpleSortTotal(Data *s[], int c);
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

      if (*info->code == '\0')
        break;

      infile.getline(cNum, 3000, ',');
      info->longitude = atof(cNum);
      infile.getline(cNum, 3000, ',');
      info->latitude = atof(cNum);
      infile.getline(buffer, 3000);

      if (c % 1000 == 2) {
        Data *d = list.get(c - 1)->data;
        // cout << "index in linked list: " << c << "\n\t" << d->code << " long:
        // " << d->longitude << " lat: " << d->latitude << endl;
      }

      if (referenceId.compare(info->code) == 0) {
        cout << "\n------------------\nSETTING REFERENCE\n" << "data:\n\t"<<
        n->data->code << "\n\tLat: " << n->data->latitude << "\n\tLong: " <<
        n->data->longitude << "\n------------------\n\n";
        reference = *new Node(n->data, n->nextNode, n->previousNode);
      }

      list.add(n);

      i++;
      c++;
    }
    airportCount = c - 1;
    infile.close();

    cout << "\n\ntest get: " << list.get(2)->data->longitude << endl;

    float maxDistance = -1;
    float farthestIndex;
    LinkedList close = *new LinkedList();
    for (int c = 0; c < airportCount; c++) {
      // cout << "debug line 4" << endl;
      Node *current = list.get(c);
      double distance = distanceEarth(
        reference.data->latitude, reference.data->longitude,
        current->data->latitude, current->data->longitude
      );

      // cout << "debug line 5" << endl;
      if (distance < 100) {
        close.add(
            new Node(current->data, current->nextNode, current->previousNode));
      } else if (distance > maxDistance) {
        maxDistance = distance;
        farthestIndex = c;
      }
    }

    printf("Farthest airport is %s at %.2f miles\n", list.get(farthestIndex)->data->code, maxDistance);
    printf("List of close airports: \n");
    for (int i = 0; i < close.size(); i++) {
      printf("%s, ", close.get(i)->data->code);
    }
    cout << endl;

  } else {
    cout << "Error opening file";
  }
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
/*
void simpleSortTotal()
{
}
*/
