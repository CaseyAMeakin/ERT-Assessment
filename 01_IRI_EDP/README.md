# Asessment IRI EDP


### Assessment Description

> Create a C-based modeling and simulation program that drive IRI model Fortran code. The code should capture and generate vertical EDP (Electron Density Profile) for a given time and location of interest.
> time of interest: Mar 3 2021 UT 11:00:00 and Mar 4, 2021 UT 23:00:00 location o interest: Lat 37.8N and Lon 75.4W
> Assessment Criteria:
> 1) Create a simple Makefile that can compile iri2016 (http://irimodel.org) and generate a shared object/library
> 2) Write a C-program that links with the shared object created and create all data needed for step (3)
> 3) Use gnuplot (www.gnuplot.info) or other similar C-based plotting tools to generate plots of EDP parameters using the shared objective created in step 1.
> 4) alternatively, use F2PY (https://www.numfys.net/howto/F2PY/) and Python to create EDP plots using the shared object created in step 1. (Although C-based plotting is the preferred solution)
> 5) Furnish instructions/documentation, etc. on how to run the code and lesson/insights learned by doing this exercise.

