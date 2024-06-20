#include "my_plotter_lib.h"

/* Helper Function Definitions */

void drawXAxis(plPlotter *plotter,
               double *pltCoords,
               double *datCoords,
               int nxTicks,
               const char *xtitle,
               char *labelFmtCode

) {
  double pltX0 = pltCoords[0];
  double pltY0 = pltCoords[1];
  double pltDx = pltCoords[2] - pltCoords[0];
  double pltDy = pltCoords[3] - pltCoords[1];
  double datX0 = datCoords[0];
  double datDx = datCoords[2] - datCoords[0];
  double dy = pltDy * 0.01;
  double dx = pltDx * 0.01;
  double y1 = pltY0;
  double y2 = pltY0 + dy;
  double ylabel = pltY0 - 1.5*dy;

  double fsizeLabel = dx*2;
  double fsizeTitle = dx*3;

  for(int i = 0; i < nxTicks; i++ ){

    /* Calculate Tick Location */

    double xDat = datCoords[0] + datDx*(double)i/(double)(nxTicks - 1);
    double x = (xDat - datX0)/datDx * pltDx + pltX0;

    /* Draw Tick Mark */

    pl_fline_r (plotter, x, y1, x, y2);
    pl_endsubpath_r (plotter);

    /* Draw Tick Label */

    if (labelFmtCode != NULL) {
      char my_label[12];
      sprintf(my_label, labelFmtCode, xDat);
      // printf("m_label = %s, fsize = %f\n", my_label, fsizeLabel);
      pl_ffontsize_r (plotter, fsizeLabel);
      pl_fmove_r (plotter, x, ylabel);
      pl_alabel_r (plotter, 'c', 't', my_label);
    }
  }

  /* Axis Title */

  double xtit = pltX0 + pltDx * 0.5;
  double ytit = pltY0 - 5 * dy;

  pl_ffontsize_r (plotter, fsizeTitle);
  pl_fmove_r(plotter, xtit, ytit);
  pl_alabel_r (plotter, 'c', 't', xtitle);

}

void drawYAxis(plPlotter *plotter,
               double *pltCoords,
               double *datCoords,
               int nyTicks,
               const char *ytitle,
               char *labelFmtCode

) {
  double pltX0 = pltCoords[0];
  double pltY0 = pltCoords[1];
  double pltDx = pltCoords[2] - pltCoords[0];
  double pltDy = pltCoords[3] - pltCoords[1];
  double datY0 = datCoords[1];
  double datDy = datCoords[3] - datCoords[1];
  double dx = pltDx * 0.01;
  double x1 = pltX0;
  double x2 = pltX0 + dx;
  double xlabel = pltX0 - dx*1.5;

  double fsizeLabel = dx*2;
  double fsizeTitle = dx*3;

  for (int i = 0; i < nyTicks; i++) {

    /* Calculate Tick Location */
    double yDat = datCoords[1] + datDy*(double)i/(double)(nyTicks - 1);
    double y = (yDat - datY0)/datDy * pltDy + pltY0;

    /* Draw Tick Mark */
    pl_fline_r (plotter, x1, y, x2, y);
    pl_endsubpath_r (plotter);

    /* Draw Tick Label */

    if (labelFmtCode != NULL) {
      char my_label[12];
      sprintf(my_label, labelFmtCode, yDat);
      pl_fmove_r (plotter, xlabel, y);
      pl_ffontsize_r (plotter, fsizeLabel);
      pl_alabel_r (plotter, 'r', 'c', my_label);
    }
  }

  /* Axis Title */

  double xtit = pltX0 - 2*7 * dx;
  double ytit = pltY0 + pltDy * 0.5;
  printf("xtit, ytit = %f,%f\n", xtit, ytit);



  pl_ffontsize_r (plotter, fsizeTitle);
  pl_fmove_r(plotter, xtit, ytit);
  pl_ftextangle_r(plotter, 90.0);
  pl_alabel_r (plotter, 'c', 't', ytitle);
  pl_ftextangle_r(plotter, 0.0);

}

double datToPltScaleX(double *pltCoords,
                      double *datCoords,
                      double xscalar
){
  double pltDx = pltCoords[2] - pltCoords[0];
  double datDx = datCoords[2] - datCoords[0];
  return xscalar * pltDx/datDx;
}

double datToPltScaleY(double *pltCoords,
                      double *datCoords,
                      double yscalar
){
  double pltDy = pltCoords[3] - pltCoords[1];
  double datDy = datCoords[3] - datCoords[1];
  return yscalar * pltDy/datDy;
}

double datToPltX(double *pltCoords,
                 double *datCoords,
                 double xDat
){
  double pltX0 = pltCoords[0];
  double pltDx = pltCoords[2] - pltCoords[0];
  double datX0 = datCoords[0];
  double datDx = datCoords[2] - datCoords[0];
  return pltX0 + (xDat - datX0)/datDx * pltDx;
}

double datToPltY(double *pltCoords,
                 double *datCoords,
                 double yDat
){
  double pltY0 = pltCoords[1];
  double pltDy = pltCoords[3] - pltCoords[1];
  double datY0 = datCoords[1];
  double datDy = datCoords[3] - datCoords[1];
  return pltY0 + (yDat - datY0)/datDy * pltDy;
}

void drawCircle(plPlotter *plotter,
                double *pltCoords,
                double *datCoords,
                double xpos,
                double ypos,
                double radius,
                double lineThick,
                const char *lineColor
){
  double xposPlt = datToPltX(pltCoords, datCoords, xpos);
  double yposPlt = datToPltY(pltCoords, datCoords, ypos);
  pl_flinewidth_r (plotter, XUSER/2e3 * lineThick);

  pl_pencolorname_r (plotter, lineColor);
  pl_fcircle_r(plotter, xposPlt, yposPlt, radius);
  pl_pencolorname_r (plotter, "black");
}


void drawAxes(plPlotter *plotter,
              double *pltCoords, // {x0, y0, x1, y1}
              double *datCoords, // same order as pltCoords
              int nxTicks,
              int nyTicks,
              const char *xtitle, // ignore if null
              const char *ytitle, //  "
              const char *title   //  "
) {

  pl_flinewidth_r (plotter, XUSER/2e3);
  pl_pencolorname_r (plotter, "black");


  /* Draw Plot Box and Axes */

  pl_orientation_r (plotter, 1);
  pl_fbox_r (plotter, pltCoords[0], pltCoords[1], pltCoords[2], pltCoords[3]);
  pl_endsubpath_r (plotter);
  drawXAxis(plotter, pltCoords, datCoords, nxTicks, xtitle,  "%.2f" );
  drawYAxis(plotter, pltCoords, datCoords, nyTicks, ytitle,  "%.2f" );


  /* Draw Plot Title */

  double pltX0 = pltCoords[0];
  double pltY1 = pltCoords[3];
  double pltDx = pltCoords[2] - pltCoords[0];
  double pltDy = pltCoords[3] - pltCoords[1];
  double dy = pltDy * 0.01;

  double xtit = pltX0 + pltDx * 0.5;
  double ytit = pltY1 + dy * 4;

  double fsizeTitle = dy * 2.5;

  pl_ffontsize_r (plotter, fsizeTitle);
  pl_fmove_r (plotter, xtit, ytit);
  pl_alabel_r (plotter, 'c', 't', title);

  /* End Path */

  pl_endpath_r (plotter);
}



