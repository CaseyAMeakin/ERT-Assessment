#include <math.h>
#include <stdio.h>

/* Function Prototypes */

int GisToRadar(double *range,
               double *bearing,
               double glonInit,
               double glatInit,
               double glonFinal,
               double glatFinal
);

int RadarToGis(double range,
               double bearing,
               double  glonInit,
               double glatInit,
               double *glonFinal,
               double *glatFinal
);


/* Test Program */

int main(){

  double lat1 = 37.0;
  double lon1 = -75.0;
  double lat2 = 18.0;
  double lon2 = -66.0;

  int ierr;
  double range, bearing;

  if( (ierr = GisToRadar(&range, &bearing, lon1, lat1, lon2, lat2)) != 0) {
    fprintf(stderr, "GisToRadar failed with error code %i\n", ierr);
    return 1;
  }


  printf("*** GisToRadar Example Ouput ****\n");
  printf("starting location: lat, lon = %f, %f\n", lat1, lon1);
  printf("ending location:   lat, lon = %f, %f\n", lat2, lon2);
  printf("bearing [deg], range [km] = %f, %f\n", bearing, range);


 if( (ierr = RadarToGis(range, bearing, lon1, lat1, &lon2, &lat2)) != 0) {
    fprintf(stderr, "RadarToGis failed with error code %i\n", ierr);
    return 1;
  }

  printf("\n");
  printf("*** RadarToGis Example Ouput ****\n");
  printf("starting location: lat, lon = %f, %f\n", lat1, lon1);
  printf("ending location:   lat, lon = %f, %f\n", lat2, lon2);
  printf("bearing [deg], range [km] = %f, %f\n", bearing, range);

}

/* Function Definitions */

int GisToRadar(double *range,
               double *bearing,
               double glonInit,
               double glatInit,
               double glonFinal,
               double glatFinal
){
  double lat1 = glatInit / 180.0 * M_PI;
  double lat2 = glatFinal / 180.0 * M_PI;
  double lon1 = glonInit / 180.0 * M_PI;
  double lon2 = glonFinal / 180.0 * M_PI;
  double dlon = lon2 - lon1;
  double dlat = lat2 - lat1;

  double theta_rad = atan2(sin(dlon) * cos(lat2), cos(lat1)*sin(lat2) - sin(lat1)*cos(lat2)*cos(dlon));
  double theta_deg = fmod(theta_rad *180/M_PI, 360);

  *bearing = theta_deg;

  /* Oblate Earth: Vincenty Formula for Geodesic Length */

  double a = pow(sin(dlat/2.0), 2.0) + cos(lat1)*cos(lat2)*pow(sin(dlon/2.0), 2.0);
  double c = 2.0 *atan2(sqrt(a), sqrt(1.0 - a));
  double f = 1.0/298.257223563; // Earth ellipsoid flatterning parameter
  double b = (1.0 - f) * 6371.0; // Earth semi-minor axis in km
  *range = c * b;

  return 0; // Error code
}

int RadarToGis(double range,
               double bearing,
               double  glonInit,
               double glatInit,
               double *glonFinal,
               double *glatFinal
) {
  double rearth = 6371.009; /* mean earth radius for WHS84 ellipsoid */
  double lat1 = glatInit / 180.0 * M_PI;
  double lon1 = glonInit / 180.0 * M_PI;
  double theta = bearing / 180.0 * M_PI;

  double delta = range / rearth;

  double lat2 = asin(sin(lat1) * cos(delta) + cos(lat1)*sin(delta)*cos(theta));
  double lon2 = lon1 + atan2(sin(theta)*sin(delta)*cos(lat1), cos(delta) - sin(lat1)*sin(lat2));

  *glatFinal = lat2 * 180.0 / M_PI;
  *glonFinal = lon2 * 180.0 / M_PI;

  return 0; // Error code
}
