#include <stdio.h>

struct rectangular_cuboid {
    double a;
    double b;
    double c;
};

// TODO:
// Write a function called "GetSurface" that takes a RectangularCuboid
// and returns its surface

// TODO:
// Write a function called "GetVolume" that takes a RectangularCuboid
// and returns its volume

int GetSurface(struct rectangular_cuboid cube);
int GetVolume(struct rectangular_cuboid cube);

int main()
{
    struct rectangular_cuboid test_cube = {3, 2, 4};
    printf("Surface of cuboid is: %d\n", GetSurface(test_cube));
    printf("Volume of cuboid is: %d\n", GetVolume(test_cube));

    return 0;
}

int GetSurface(struct rectangular_cuboid cube)
{
    int surface = 2*(cube.a * cube.b + cube.a * cube.c + cube.b * cube.c);
    return surface;
}

int GetVolume(struct rectangular_cuboid cube)
{
    int volume = cube.a * cube.b * cube.c;
    return volume;

}
