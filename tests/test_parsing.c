#include <stdio.h>

// Helper function to print t_coord
void print_coordinate(t_coord coord) {
    printf("Coordinate (x, y, z): (%lf, %lf, %lf)\n", coord.x, coord.y, coord.z);
}

// Helper function to print t_color
void print_color(t_color color) {
    printf("Color (r, g, b): (%d, %d, %d)\n", color.r, color.g, color.b);
}

// Print function for t_a
void print_A(t_a a) {
    printf("Ambient Light Ratio: %lf\n", a.ratio);
    print_color(a.color);
}

// Print function for t_c
void print_C(t_c c) {
    printf("Camera View Point:\n");
    print_coordinate(c.center);
    printf("Camera Normal:\n");
    print_coordinate(c.orientation);
    printf("Camera Field of View: %lf\n", c.fov);
}

// Print function for t_L linked list
void print_L(t_L *l) {
    while (l) {
        printf("Light Point:\n");
        print_coordinate(l->point);
        printf("Light Brightness: %lf\n", l->brightness);
        print_color(l->color);
        l = l->next;
    }
}

// Print function for t_plane
void print_plane(t_plane pl) {
    printf("Plane Point:\n");
    print_coordinate(pl.point);
    printf("Plane Normal:\n");
    print_coordinate(pl.normal);
    print_color(pl.color);
}

// Print function for t_sphere
void print_sphere(t_sphere sp) {
    printf("Sphere Center:\n");
    print_coordinate(sp.center);
    printf("Sphere Diameter: %lf\n", sp.diameter);
    print_color(sp.color);
}

// Print function for t_cylinder
void print_cylinder(t_cylinder cy) {
    printf("Cylinder Center:\n");
    print_coordinate(cy.center);
    printf("Cylinder Normal:\n");
    print_coordinate(cy.normal);
    printf("Cylinder Diameter: %lf\n", cy.diameter);
    printf("Cylinder Height: %lf\n", cy.height);
    print_color(cy.color);
}

// Print function for t_object linked list
void print_object(t_object *obj) {
    while (obj) {
        printf("Object Type: %c\n", obj->type);
        if (obj->type == 'p') {
            print_plane(obj->pl);
        } else if (obj->type == 's') {
            print_sphere(obj->sp);
        } else if (obj->type == 'c') {
            print_cylinder(obj->cy);
        }
        printf("Object Flag: %d\n", obj->flag);
        obj = obj->next;
    }
}

// Print function for t_scene
void print_scene(t_scene *scene) {
    printf("Scene Ambient Light:\n");
    print_A(scene->a);
    printf("Scene Camera:\n");
    print_C(scene->c);
    printf("Scene Lights:\n");
    print_L(scene->l);
    printf("Scene Objects:\n");
    print_object(scene->objects);
}

// Print function for t_data
void print_data(t_data *data) {
    printf("Window Width: %d, Height: %d\n", data->width, data->height);
    printf("Scene:\n");
    print_scene(data->scene);
    if (data->lines) {
        printf("Lines:\n");
        for (int i = 0; data->lines[i] != NULL; i++) {
            printf("%s\n", data->lines[i]);
        }
    }
}
