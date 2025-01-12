#include "../minirt.h"

t_vector sphere_point(t_vector center, double radius, double theta, double phi) {
    t_vector point;
    point.x = center.x + radius * sin(phi) * cos(theta);
    point.y = center.y + radius * sin(phi) * sin(theta);
    point.z = center.z + radius * cos(phi);
    return point;
}

t_triangle *triangulate_sphere(t_vector center, double radius, int slices, int stacks, int *num_triangles) {
    *num_triangles = 2 * slices * (stacks - 1);
    t_triangle *triangles = malloc(sizeof(t_triangle) * (*num_triangles));
    if (!triangles) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    int index = 0;
    int i = 0;
    while (i < stacks - 1) {
        double phi1 = M_PI * i / stacks;
        double phi2 = M_PI * (i + 1) / stacks;

        int j = 0;
        while (j < slices) {
            double theta1 = 2 * M_PI * j / slices;
            double theta2 = 2 * M_PI * (j + 1) / slices;

            t_vector p1 = sphere_point(center, radius, theta1, phi1);
            t_vector p2 = sphere_point(center, radius, theta2, phi1);
            t_vector p3 = sphere_point(center, radius, theta1, phi2);
            t_vector p4 = sphere_point(center, radius, theta2, phi2);

            triangles[index++] = (t_triangle){p1, p2, p3};
            triangles[index++] = (t_triangle){p3, p2, p4};

            j++;
        }
        i++;
    }
    return triangles;
}

// t_triangle *triangulate_plane(t_vector origin, double width, double height, int subdivisions, int *num_triangles) {
//     *num_triangles = subdivisions * subdivisions * 2;
//     t_triangle *triangles = malloc(sizeof(t_triangle) * (*num_triangles));
//     if (!triangles) {
//         perror("Memory allocation failed");
//         exit(EXIT_FAILURE);
//     }

//     double dx = width / subdivisions;
//     double dy = height / subdivisions;
//     int index = 0;
//     int i = 0;

//     while (i < subdivisions) {
//         int j = 0;
//         while (j < subdivisions) {
//             t_vector p1 = (t_vector){origin.x + i * dx, origin.y + j * dy, origin.z};
//             t_vector p2 = (t_vector){p1.x + dx, p1.y, p1.z};
//             t_vector p3 = (t_vector){p1.x, p1.y + dy, p1.z};
//             t_vector p4 = (t_vector){p2.x, p2.y + dy, p2.z};

//             triangles[index++] = (t_triangle){p1, p2, p3};
//             triangles[index++] = (t_triangle){p3, p2, p4};

//             j++;
//         }
//         i++;
//     }
//     return triangles;
// }

t_triangle *triangulate_cylinder(t_vector base, double radius, double height, int slices, int stacks, int *num_triangles) {
    *num_triangles = slices * 2 + slices * stacks * 2;
    t_triangle *triangles = malloc(sizeof(t_triangle) * (*num_triangles));
    if (!triangles) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    int index = 0;

    int i = 0;
    while (i < slices) {
        double theta1 = 2 * M_PI * i / slices;
        double theta2 = 2 * M_PI * (i + 1) / slices;

        t_vector p1 = base;
        t_vector p2 = (t_vector){base.x + radius * cos(theta1), base.y + radius * sin(theta1), base.z};
        t_vector p3 = (t_vector){base.x + radius * cos(theta2), base.y + radius * sin(theta2), base.z};

        triangles[index++] = (t_triangle){p1, p2, p3};

        t_vector top = (t_vector){base.x, base.y, base.z + height};
        t_vector p4 = (t_vector){p2.x, p2.y, top.z};
        t_vector p5 = (t_vector){p3.x, p3.y, top.z};

        triangles[index++] = (t_triangle){top, p5, p4};

        i++;
    }

    i = 0;
    while (i < slices) {
        double theta1 = 2 * M_PI * i / slices;
        double theta2 = 2 * M_PI * (i + 1) / slices;

        int j = 0;
        while (j < stacks) {
            double z1 = j * height / stacks;
            double z2 = (j + 1) * height / stacks;

            t_vector p1 = (t_vector){base.x + radius * cos(theta1), base.y + radius * sin(theta1), base.z + z1};
            t_vector p2 = (t_vector){base.x + radius * cos(theta2), base.y + radius * sin(theta2), base.z + z1};
            t_vector p3 = (t_vector){p1.x, p1.y, base.z + z2};
            t_vector p4 = (t_vector){p2.x, p2.y, base.z + z2};

            triangles[index++] = (t_triangle){p1, p2, p3};
            triangles[index++] = (t_triangle){p3, p2, p4};

            j++;
        }
        i++;
    }
    return triangles;
}
