#include "../minirt.h"

t_vector sphere_point(t_vector center, double radius, double theta, double phi) {
    t_vector point;
    point.x = center.x + radius * sin(phi) * cos(theta);
    point.y = center.y + radius * sin(phi) * sin(theta);
    point.z = center.z + radius * cos(phi);
    return point;
}

void triangulate_sphere(t_list **triangles, t_object *object, t_vector center, double radius, int slices, int stacks) {
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

            t_triangle  *mesh = malloc(2 * sizeof(t_triangle) * 2);
            ft_memcpy(mesh, &(t_triangle){p1, p2, p3, object}, sizeof(t_triangle));
            ft_memcpy(mesh + 1, &(t_triangle){p3, p2, p4, object}, sizeof(t_triangle));
            
            t_list *new1 = ft_lstnew(mesh);
            t_list *new2 = ft_lstnew(mesh + 1);
            ft_lstadd_back(triangles, new1);    
            ft_lstadd_back(triangles, new2);
            j++;
        }
        i++;
    }
}

void    triangulate_plane(t_list **triangles, t_object *object,t_vector origin,int subdivisions) {
    int i = 0;

    while (i < subdivisions) {
        int j = 0;
        while (j < subdivisions) {
            t_vector p1 = (t_vector){origin.x + i * subdivisions, origin.y + j * subdivisions, origin.z};
            t_vector p2 = (t_vector){p1.x + subdivisions, p1.y, p1.z};
            t_vector p3 = (t_vector){p1.x, p1.y + subdivisions, p1.z};
            t_vector p4 = (t_vector){p2.x, p2.y + subdivisions, p2.z};

            t_triangle *mesh = malloc(2 * sizeof(t_triangle) * 2);
            ft_memcpy(mesh, &(t_triangle){p1, p2, p3, object}, sizeof(t_triangle));
            ft_memcpy(mesh + 1, &(t_triangle){p3, p2, p4, object}, sizeof(t_triangle));

            t_list *new1 = ft_lstnew(mesh);
            t_list *new2 = ft_lstnew(mesh + 1);
            ft_lstadd_back(triangles, new1);
            ft_lstadd_back(triangles, new2);
            j++;
        }
        i++;
    }
}

void    triangulate_cylinder(t_list **triangles, t_object *object, t_vector base, double radius, double height, int slices, int stack) {
    int i = 0;
    while (i < slices) {
        double theta1 = 2 * M_PI * i / slices;
        double theta2 = 2 * M_PI * (i + 1) / slices;

        t_vector p1 = base;
        t_vector p2 = (t_vector){base.x + radius * cos(theta1), base.y + radius * sin(theta1), base.z};
        t_vector p3 = (t_vector){base.x + radius * cos(theta2), base.y + radius * sin(theta2), base.z};

        t_triangle *mesh = malloc(2 * sizeof(t_triangle) * 2);
        ft_memcpy(mesh, &(t_triangle){p1, p2, p3, object}, sizeof(t_triangle));

        t_vector top = (t_vector){base.x, base.y, base.z + height};
        t_vector p4 = (t_vector){p2.x, p2.y, top.z};
        t_vector p5 = (t_vector){p3.x, p3.y, top.z};

        ft_memcpy(mesh + 1, &(t_triangle){top, p5, p4, object}, sizeof(t_triangle));
        t_list *new1 = ft_lstnew(mesh);
        t_list *new2 = ft_lstnew(mesh + 1);
        ft_lstadd_back(triangles, new1);
        ft_lstadd_back(triangles, new2);
        i++;
    }

    i = 0;
    while (i < slices) {
        double theta1 = 2 * M_PI * i / slices;
        double theta2 = 2 * M_PI * (i + 1) / slices;

        int j = 0;
        while (j < stack) {
            double z1 = j * height / stack;
            double z2 = (j + 1) * height / stack;

            t_vector p1 = (t_vector){base.x + radius * cos(theta1), base.y + radius * sin(theta1), base.z + z1};
            t_vector p2 = (t_vector){base.x + radius * cos(theta2), base.y + radius * sin(theta2), base.z + z1};
            t_vector p3 = (t_vector){p1.x, p1.y, base.z + z2};
            t_vector p4 = (t_vector){p2.x, p2.y, base.z + z2};

            t_triangle *mesh_cylinder = malloc(2 * sizeof(t_triangle) * 2);

            ft_memcpy(mesh_cylinder, &(t_triangle){p1, p2, p3, object}, sizeof(t_triangle));
            ft_memcpy(mesh_cylinder + 1, &(t_triangle){p3, p2, p4, object}, sizeof(t_triangle));
            t_list *new3 = ft_lstnew(mesh_cylinder);
            t_list *new4 = ft_lstnew(mesh_cylinder + 1);
            ft_lstadd_back(triangles, new3);
            ft_lstadd_back(triangles, new4);
            j++;
        }
        i++;
    }
}
