#include <stdio.h>
#include <math.h>
#include <float.h>

#include "my_plotter_lib.h"


void plot_edp(
              const char *plt_fname,
              const char *plt_title,
              int num_step,
              double *height_km,
              double *log10_ne_cc,
              double *pCoords,
              double *dCoords
) {


  printf("plot_edp: plt_fname = %s\n", plt_fname);

 /* Setup Plotter parameters */

  plPlotterParams *plotter_params;
  plotter_params = pl_newplparams ();
  char sizeStr[100];
  sprintf(sizeStr, "%ix%i", XPIX, YPIX);
  pl_setplparam (plotter_params, "BITMAPSIZE", sizeStr);

  /* create PNG plotter that writes to a file */
  plPlotter *plotter;
  // FILE* outfile = fopen("my_plotter.png", "w");
  FILE* outfile = fopen(plt_fname, "w");
  plotter = pl_newpl_r ("png", stdin, outfile, stderr, plotter_params);

  if (plotter == NULL)
    {
      fprintf (stderr, "Couldn't create Plotter\n");
      return 1;
    }

  if (pl_openpl_r (plotter) < 0)      /* open Plotter.. create page of graphics */
    {
      fprintf (stderr, "Couldn't open Plotter\n");
      return 1;
    }

  pl_fspace_r (plotter, 0.0, 0.0, XUSER, YUSER); /* set coord system */
  pl_erase_r (plotter);


  /* plot data with symbols */

  for (int i = 0; i < num_step; i++) {
    double x = log10_ne_cc[i];
    double y = height_km[i];
    drawCircle(plotter, pCoords, dCoords, x, y, 0.25, 3.0, "salmon");
  }



  int nxTicks = 11;
  int nyTicks = 15;

  drawAxes(plotter,
           pCoords,
           dCoords,
           nxTicks,
           nyTicks,
           "log10 Ne (#/cm^3)",
           "Altitude (km)",
           plt_title
);

  /* Cleanup */

  if (pl_closepl_r (plotter) < 0)
    {
      fprintf (stderr, "Couldn't close Plotter\n");
      return 1;
    }

  if (pl_deletepl_r (plotter) < 0)
    {
      fprintf (stderr, "Couldn't delete Plotter\n");
      return 1;
    }
  return 0;

};


int main(int argc, char** argv) {
  printf("C-language IRI driver\n");


  int iy; /* IRI model input: Year yyyy*/
  int imd; /* IRI model input: Date mmdd */
  double hour; /* IRI model input: Hour UTC */

  /* Input values to loop over */
  int imds[2] = {303, 304};
  double hours[2] = {11.0, 23.0};

  double height_km[1000]; /* ITI model output: ionosphere altitude */
  double ne_cc[1000]; /* IRI model output: electron density */
  int num_steps; /* IRI model output: number of altitude steps */

  for(int icase=0;icase < 2; icase++) {
    /* call IRI model and populate data arrays */

    iy = 2021;
    /* imd = 303;  */
    /* hour = 23.0; */
    imd = imds[icase];
    hour = hours[icase];

    iritest_sub_(&iy, &imd, &hour, &num_steps, height_km, ne_cc);

    /* calculate data limits */

    double xmin = DBL_MAX;
    double xmax = -DBL_MAX;
    // double ymin = height_km[0] - 50;
    // double ymax = height_km[num_steps-1] + 50;
    double ymin = 50;
    double ymax = 750;
    double log10_ne_cc[1000];

    for (int i = 0; i < num_steps; i++) {
      log10_ne_cc[i] = log10(ne_cc[i]);
      double floor_val = floor(log10_ne_cc[i]);
      double ceil_val = ceil(log10_ne_cc[i]);

      if (floor_val < xmin) xmin = floor_val;
      if (ceil_val > xmax) xmax = ceil_val;
    }


    /* setup plotting coordintes and plot data */

    double pCoords[4] = {20, 10, 90, 90};
    double dCoords[4] = {xmin, ymin, xmax, ymax};
    char plt_fname[100];
    char plt_title[100];

    sprintf(plt_fname, "edp_%04i%04i.png", imd, iy);
    sprintf(plt_title, "Electron Density Profile: %04i%04i at %4.2f UTC", imd, iy, hour);
    plot_edp(plt_fname, plt_title, num_steps, height_km, log10_ne_cc, pCoords, dCoords);

  }

};
