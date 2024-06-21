import sys
import numpy as np
from scipy.signal import convolve2d
from scipy.sparse import coo_matrix
import matplotlib.pyplot as plt


# Helper function to read file data into numpy array


def read_data_file(fname: str) -> np.ndarray:
    with open(fname, "r") as f:
        lines = f.readlines()
        num_lines = len(lines)
        data = np.ones((num_lines, 3), "float64")
        for i, line in enumerate(lines):
            lstrip = line.strip()
            lsplit = lstrip.split()
            data[i, :] = [float(x) for x in lsplit]

    return data


# Test program


def main():
    print("hi world!")

    # Read in data files

    dat0 = read_data_file("convolve_raw_0.dat")
    dat1 = read_data_file("convolve_raw_1.dat")

    extents0 = [
        np.min(dat0[:, 0]),
        np.max(dat0[:, 0]),
        np.min(dat0[:, 1]),
        np.max(dat0[:, 1]),
    ]
    extents1 = [
        np.min(dat1[:, 0]),
        np.max(dat1[:, 0]),
        np.min(dat1[:, 1]),
        np.max(dat1[:, 1]),
    ]

    # Setup grid spacing parameters: dx ~ 0.04, dy ~ 0.000333375

    nx = 187
    ny = 9
    delx0 = extents0[1] - extents0[0]
    dely0 = extents0[3] - extents0[2]
    dx = delx0 / (nx - 1.0)
    dy = dely0 / (ny - 1.0)

    # Data File 0

    x0 = dat0[:, 0] - np.min(dat0[:, 0])
    y0 = dat0[:, 1] - np.min(dat0[:, 1])
    ix0 = np.round(x0 / dx).astype(int)
    iy0 = np.round(y0 / dy).astype(int)
    inx0 = np.max(ix0) + 1
    iny0 = np.max(iy0) + 1
    z0 = np.zeros((inx0, iny0), "float64")
    for i in range(dat0.shape[0]):
        z0[ix0[i]][iy0[i]] = dat0[i, 2]

    # Data File 1

    x1 = dat1[:, 0] - np.min(dat1[:, 0])
    y1 = dat1[:, 1] - np.min(dat1[:, 1])
    ix1 = np.round(x1 / dx).astype(int)
    iy1 = np.round(y1 / dy).astype(int)
    inx1 = np.max(ix1) + 1
    iny1 = np.max(iy1) + 1
    z1 = np.zeros((inx1, iny1), "float64")
    for i in range(dat1.shape[0]):
        z1[ix1[i]][iy1[i]] = dat1[i, 2]

    # print("inx1, iny1 = ", inx1, iny1)
    # print("z1min, z1max = ", z1min, z1max)

    # sys.exit(1)

    # Convolve inputs with "delta" functions for testing

    z2 = np.zeros((inx0, iny0), "float64")
    z2[inx0 // 2, iny0 // 2] = 1.0
    z0_conv_z2 = convolve2d(z0, z2, mode="same")

    z3 = np.zeros((inx1, iny1), "float64")
    # z3[inx1 // 2 - 20 : inx1 // 2 + 20, iny1 // 2 - 2 : iny1 // 2 + 2] = 1.0
    z3[inx1 // 2, iny1 // 2] = 1.0

    z1_conv_z3 = convolve2d(z1, z3, mode="same")

    # Convolve input files

    z0_conv_z1 = convolve2d(z0, z1)  # , mode="same")

    # sys.exit(1)

    # # Plotting

    fig, axs = plt.subplots(3, 3, figsize=(10 * 1.5, 8 * 1.5))

    ## ROW 1

    # Left - z0

    ax = axs[0][0]
    zdat = z0.T
    zmax = np.max(zdat)
    zdat = np.clip(zdat, 1e-16 * zmax, None)
    zdat = np.log10(zdat)

    im00 = ax.imshow(
        zdat,
        aspect="auto",
        origin="lower",
        interpolation="none",
        # extent=extents0,
    )

    fig.colorbar(im00, ax=ax)

    ax.set_ylabel("relative y-offset increment")
    ax.set_title('log $Z_0$ ("convolve_raw_0.dat")')

    # Middle - z2

    ax = axs[0][1]
    zdat = z2.T

    im01 = ax.imshow(
        zdat,
        aspect="auto",
        origin="lower",
        interpolation="none",
        # extent=extents1,
    )
    fig.colorbar(im01, ax=ax)

    ax.set_title('$Z_2$ (a "delta function")')

    # Right - z0_conv_z2

    ax = axs[0][2]
    zdat = z0_conv_z2.T
    zmax = np.max(zdat)
    zdat = np.clip(zdat, 1e-16 * zmax, None)
    zdat = np.log10(zdat)

    im02 = ax.imshow(
        zdat,
        aspect="auto",
        origin="lower",
        interpolation="none",
    )

    fig.colorbar(im02, ax=ax)
    # ax.set_xlabel("relative x-offset increment")
    ax.set_ylabel("relative y-offset increment")
    ax.set_title("log $Z_0 * Z_2$ (convolution)")

    ## ROW 2

    # Left - z1

    ax = axs[1][0]

    zdat = z1.T
    zmax = np.max(zdat)
    zdat = np.clip(zdat, 1e-16 * zmax, None)
    zdat = np.log10(zdat)

    im10 = ax.imshow(
        zdat,
        aspect="auto",
        origin="lower",
        interpolation="none",
    )
    fig.colorbar(im10, ax=ax)

    ax.set_ylabel("relative y-offset increment")
    ax.set_title('log $Z_1$ ("convolve_raw_1.dat")')

    # Middle - z3

    ax = axs[1][1]
    zdat = z3.T

    im11 = ax.imshow(
        zdat,
        aspect="auto",
        origin="lower",
        interpolation="none",
    )
    fig.colorbar(im11, ax=ax)
    ax.set_title('$Z_3$ (a "delta function")')

    # Right - z1_conv_z3

    ax = axs[1][2]

    zdat = z1_conv_z3.T
    zmax = np.max(zdat)
    zdat = np.clip(zdat, 1e-16 * zmax, None)
    zdat = np.log10(zdat)

    im12 = ax.imshow(
        zdat,
        aspect="auto",
        origin="lower",
        interpolation="none",
    )
    fig.colorbar(im12, ax=ax)

    ax.set_ylabel("relative y-offset increment")
    ax.set_title("log $Z_1 * Z_3$ (convolution)")

    ## ROW 3

    # Left - z0

    ax = axs[2][0]

    zdat = z0.T
    zmax = np.max(zdat)
    zdat = np.clip(zdat, 1e-16 * zmax, None)
    zdat = np.log10(zdat)

    im20 = ax.imshow(
        zdat,
        aspect="auto",
        origin="lower",
        interpolation="none",
    )
    fig.colorbar(im20, ax=ax)

    ax.set_xlabel("relative x-offset increment")
    ax.set_ylabel("relative y-offset increment")
    ax.set_title('log $Z_0$ ("convolve_raw_0.dat")')

    # Middle - z1
    ax = axs[2][1]

    zdat = z1.T
    zmax = np.max(zdat)
    zdat = np.clip(zdat, 1e-16 * zmax, None)
    zdat = np.log10(zdat)

    im21 = ax.imshow(
        zdat,
        aspect="auto",
        origin="lower",
        interpolation="none",
    )
    fig.colorbar(im21, ax=ax)

    ax.set_xlabel("relative x-offset increment")
    ax.set_title('log $Z_1$ ("convolve_raw_1.dat")')

    # Right - z0_conv_z1

    ax = axs[2][2]
    zdat = z0_conv_z1.T
    zmax = np.max(zdat)
    zdat = np.clip(zdat, 1e-16 * zmax, None)
    zdat = np.log10(zdat)

    im22 = ax.imshow(
        zdat,
        aspect="auto",
        origin="lower",
        interpolation="none",
    )
    fig.colorbar(im22, ax=ax)

    ax.set_xlabel("relative x-offset increment")
    ax.set_title("log $Z_0 * Z_1$ (convolution)")

    # configure, save and show plt

    plt.subplots_adjust(
        left=0.05,
        bottom=0.05,
        right=0.95,
        top=0.95,
        wspace=0.2,
        hspace=0.3,
    )

    figname = "convolve.png"
    plt.savefig(figname, dpi=300)
    # plt.show()
    plt.close()


# Execute

if __name__ == "__main__":
    main()
