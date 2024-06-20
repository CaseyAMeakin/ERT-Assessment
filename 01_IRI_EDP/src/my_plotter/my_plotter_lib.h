#include <stdio.h>
#include <plot.h>

#define XPIX (1024*4)
#define YPIX (1024*4)
#define XUSER 100.0
#define YUSER 100.0
#define PIX_SIZE  XUSER/(double)XPIX
#define MAXORDER 12


/*
  Partial API documentation:
  https://vizier.cfa.harvard.edu/doc/viz/plotutils.html
*/


/* Function Prototypes */

void drawAxes(plPlotter *plotter,
              double *pltCoords, // {x0, y0, x1, y1}
              double *datCoords, // same order as pltCoords
              // double *xticks, // {number, 1st, 2nd, .., nth} - auto if NULL
              // double *yticks, // same as xticks - auto if NULL
              int nxTicks,
              int nyTicks,
              const char *xtitle, // ignore if null
              const char *ytitle, //  "
              const char *title   //  "
);

void drawXAxis(plPlotter *plotter,
               double *pltCoords,
               double *datCoords,
               int nxTicks,
               const char *xtitle,
               char *labelFmtCode);

void drawYAxis(plPlotter *plotter,
               double *pltCoords,
               double *datCoords,
               int nyTicks,
               const char *ytitle,
               char *labelFmtCode
);

void drawXtitle(plPlotter *plotter,
                double *pltCoords,
                double *datCoords,
                const char *xtitle
);

void drawCircle(plPlotter *plotter,
                double *pltCoords,
                double *datCoords,
                double xpos,
                double ypos,
                double radius,
                double lineThick,
                const char *lineColor
);

double datToPltX(double *pltCoords,
               double *datCoords,
               double datXin
);

double datToPltY(double *pltCoords,
               double *datCoords,
               double datYin
);

double datToPltScaleY(double *pltCoords,
                      double *datCoords,
                      double yscalar
);

double datToPltScaleX(double *pltCoords,
                      double *datCoords,
                      double xscalar
);

