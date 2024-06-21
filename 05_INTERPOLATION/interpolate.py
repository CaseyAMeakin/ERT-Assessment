import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import griddata

# Provided data samples

SAMPLE_DATA = [
    (121.39, 13.51, 1.494),
    (126.19, 12.02, 1.934),
    (130.27, 13.11, 2.148),
    (127.42, 10.09, 9.155),
    (126.14, 15.33, 2.221),
    (125.96, 14, 8.1),
    (123.15, 10.88, 2.039),
    (130.5, 11.18, 1.916),
    (129.08, 15.78, 3.729),
    (122.74, 15.82, 7.137),
]

SAMPLE_LON = np.array([dat[0] for dat in SAMPLE_DATA])
SAMPLE_LAT = np.array([dat[1] for dat in SAMPLE_DATA])
SAMPLE_POS = np.array([(dat[0], dat[1]) for dat in SAMPLE_DATA])
SAMPLE_VAL = np.array([dat[2] for dat in SAMPLE_DATA])


# Interpolation Function


def get_nearest_point_index(points, xpos, ypos) -> int:
    nodes = np.asarray(points)
    node = tuple((xpos, ypos))
    distSquared = np.sum((nodes - node) ** 2, axis=1)
    return np.argmin(distSquared)


def my_interpolate_nearest(data_pos, data_val, xygrid) -> np.ndarray:
    xx = xygrid[0]
    yy = xygrid[1]
    nx, ny = xx.shape
    z = np.zeros((nx, ny), "float64")

    for i in range(nx):
        for j in range(ny):
            x = xx[i][j]
            y = yy[i][j]
            i_closest_data = get_nearest_point_index(data_pos, x, y)
            z[i][j] = data_val[i_closest_data]

    return z


# Test Plotting Program


def main():

    # Create Grid

    # Grid description: "construct grid
    # 50 rows and 70 columns with a
    # longitude range [121.0, 131.0]
    # and latitude range [10.0, 16.0]"

    xgrid = np.linspace(121, 131, 50)
    ygrid = np.linspace(10, 16, 70)
    xx, yy = np.meshgrid(xgrid, ygrid)

    # Interpolate Data

    zz_nearest = griddata(SAMPLE_POS, SAMPLE_VAL, (xx, yy), method="nearest")
    zz_cubic = griddata(SAMPLE_POS, SAMPLE_VAL, (xx, yy), method="cubic")
    zz_nearest_mine = my_interpolate_nearest(SAMPLE_POS, SAMPLE_VAL, (xx, yy))

    # Plot Data

    # Setup

    fig, axs = plt.subplots(2, 2, figsize=(12, 8))

    # Panel 1 - axs[0][0]
    # Sample Points and Structured Grid

    ax = axs[0][0]

    ax.plot(
        xx,
        yy,
        marker="o",
        ms=1.0,
        color="grey",
        linestyle="none",
    )

    for i in range(len(SAMPLE_DATA)):
        x = SAMPLE_DATA[i][0]
        y = SAMPLE_DATA[i][1]
        ax.plot(
            [x],
            [y],
            marker="o",
            ms=10.0,
            color="b",
            markeredgewidth=2,
            markerfacecolor="none",
        )

    ax.set_xlabel("Longitude")
    ax.set_ylabel("Latitude")
    ax.set_title("Structured Grid and Data Sample Positions")
    ax.set_aspect("equal")

    # Panel 2 - axs[1][0]
    # Nearest point interpolation (scipy)

    ax = axs[1][0]

    ax.imshow(
        zz_nearest,
        extent=(min(xgrid), max(xgrid), min(ygrid), max(ygrid)),
        origin="lower",
        # aspect="auto",
    )

    ax.plot(
        SAMPLE_LON,
        SAMPLE_LAT,
        linestyle="none",
        marker="o",
        ms=10.0,
        color="b",
        markeredgewidth=2,
        markerfacecolor="none",
    )

    ax.set_xlabel("Longitude")
    ax.set_ylabel("Latitude")
    ax.set_title("Nearest Point Interpolation (scipy)")
    ax.set_aspect("equal")

    # Panel 3 - axs[0][1]
    # Cubic interpolation

    ax = axs[0][1]

    ax.imshow(
        zz_cubic,
        extent=(min(xgrid), max(xgrid), min(ygrid), max(ygrid)),
        origin="lower",
        # aspect="auto",
    )

    ax.plot(
        SAMPLE_LON,
        SAMPLE_LAT,
        linestyle="none",
        marker="o",
        ms=10.0,
        color="b",
        markeredgewidth=2,
        markerfacecolor="none",
    )

    ax.set_xlabel("Longitude")
    ax.set_ylabel("Latitude")
    ax.set_title("Cubic Interpolation (scipy)")
    ax.set_aspect("equal")

    # Panel 4 - axs[1][1]
    # Nearest point interpolation (mine)

    ax = axs[1][1]

    ax.imshow(
        zz_nearest_mine,
        extent=(min(xgrid), max(xgrid), min(ygrid), max(ygrid)),
        origin="lower",
        # aspect="auto",
    )

    ax.plot(
        SAMPLE_LON,
        SAMPLE_LAT,
        linestyle="none",
        marker="o",
        ms=10.0,
        color="b",
        markeredgewidth=2,
        markerfacecolor="none",
    )

    ax.set_xlabel("Longitude")
    ax.set_ylabel("Latitude")
    ax.set_title("Nearest Point Interpolation (mine)")
    ax.set_aspect("equal")

    figname = "interpolate_samples.png"
    plt.savefig(figname, dpi=300)
    # plt.show()
    plt.close()


# Run script

if __name__ == "__main__":
    print("Interpolation example program")
    main()
