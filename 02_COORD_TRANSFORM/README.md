# Assessment: Coordinate Transformation

### Description (original problem statement)

>  Implement coordinate conversion utilities that
can convert radar coordinates (bearing, range) to GIS coordinates (lat, lon) and vice versa in C. The header declaration could be the following or your own design.


```
int GIS2Radar(double *range,
double *bearing,
double glonInit,
double glatInit,
double glonFinal,
double glatFinal);

int RtoG (double range,
double bearing,
double  glonInit,
double glatInit,
double *glonFinal,
double *glatFinal);
```


> You can use the following as the location of interest
> * Initial: Wallops Islands, lat: 37N, long: 75W)
> * Final: Puerto Rico, lat: long: 18N, 66W)


### Approach

Use the **Vincenty** algorithm to find geodesic distance based on oblate spheroid model of Earth, otherwise use spherical model with mean Earth radius based on WHS84 ellipsoid.


### Proposed Improvements

* Use ellipsoid formula in RadarToGis formula.
* Add error handling for indeterminate values (e.g., isnan, isinf) and check input and output parameter ranges.

### Usage

Build using c compiler:

```
cc coord_transform.c  -o coord_transform.x -lm
```

Exectute on command line:

```
> ./coord_transform.x
```


### Sample Output (Screenshots)

Example output from test program:
```
*** GisToRadar Example Ouput ****
starting location: lat, lon = 37.000000, -75.000000
ending location:   lat, lon = 18.000000, -66.000000
bearing [deg], range [km] = 154.963217, 2280.990152

*** RadarToGis Example Ouput ****
starting location: lat, lon = 37.000000, -75.000000
ending location:   lat, lon = 18.064530, -66.025807
bearing [deg], range [km] = 154.963217, 2280.990152
```
