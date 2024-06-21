# Assessment: ERT Software Developer Position

### Instructions (original problem statement)

> Please submit all work products, including documentation, through your open public github
account and discuss these during the technical interview process. **Please complete as many
assessment challenges as you would like.** No hard timeline, so submit when you feel ready and
have a good high-level understanding of what we do.  These exercises are extracted from our
working code and are intended to provide realistic examples of what we do to support AFRL
R&D ionospheric impact application development. Evaluation criteria are based on
thoroughness, attention to detail, problem-solving, and communication in writing and verbal.

### Summary of Work

This github repository contains the work done and documentation produced for this assessment. I have organized my work into the following 6 sub folders and provide a README file along side any supporting code in each.


|Folder | Status |
|-------|--------|
|01_IRI_EDP| completed|
|02_COORD_TRANSFORM| completed|
|03_DATA_COLLECTION| did not attempt|
|04_JAVASCRIPT_CANVAS| completed|
|05_INTERPOLATION| completed|
|06_CONVOLUTION| completed|

Given the time I had available I completed 5 of the 6 assessment challenges.

The work was completed during two evenings the week of Monday, the 17th of June 2024.


#### A Note on the Data Collection Assessment

For the uncompleted task ("Data Collection"), I would have implemented this as a standard CRUD (create, read, update, delete) web app using a lightweight framework such as Flask or FastAPI. For persistence, the json based table data from SWPC is well suited to be stored within an SQL database: sqlite, mysql, or postgresql are good candidates, depending on the expected app load. My container system of choice is Docker: creating the image would require a Dockerfile, which could be placed in the git repos for ease of image creation upon app updates. For the dashboard, I would have used React.js because of my experience with it although vanilla JS or another framework would be fine. For predicting a solar storm, I would have reviewed current approaches in the literature (e.g., see reference [1] below) and implemented using one of the powerful and freely available ML python packages (e.g., pytorch or tensorflow for deep learning approaches; or scikit-learn if a simpler classical approach like *random forest* were adopted).


# References

[1] Wang, X., Chen, Y., Toth, G., Manchester, W.B., Gombosi, T.I., Hero, A.O., Jiao, Z., Sun, H.,
Jin, M., & Liu, Y. (2020). Predicting solar flares with machine learning: investigating solar cycle
dependence. The Astrophysical Journal, 895(1). [https://iopscience.iop.org/article/10.3847/1538-4357/ab89ac/meta](https://iopscience.iop.org/article/10.3847/1538-4357/ab89ac/meta)


