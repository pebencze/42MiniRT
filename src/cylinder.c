
#include "../incl/minirt.h"
/* https://hugi.scene.org/online/hugi24/coding%20graphics%20chris%20dragan%20raytracing%20shapes.htm */

/* t_coord local_normal_at(t_coord point, t_object *obj, t_float m)
{
    t_coord normal;
    normal = vec_sub(point, vec_add(obj->cy.center, vec_mult(obj->cy.normal, m)));
    return vec_unit(normal);
} */

t_intersec *cylinder_intersect(t_ray ray, t_object *obj)
{
    t_float a, b, c, discriminant, t1, t2, t;
    t_coord point;
    t_intersec intersec;
    t_coord X = vec_sub(ray.origin, obj->cy.center);
    t_float D_dot_V = vec_dot(ray.direction, obj->cy.normal);
    t_float X_dot_V = vec_dot(X, obj->cy.normal);

    // Calculate the coefficients of the quadratic equation
    a = vec_dot(ray.direction, ray.direction) - D_dot_V * D_dot_V;
    b = 2 * (vec_dot(ray.direction, X) - D_dot_V * X_dot_V);
    c = vec_dot(X, X) - X_dot_V * X_dot_V - obj->cy.radius * obj->cy.radius;

    discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return NULL;

    t1 = (-b - sqrt(discriminant)) / (2.0 * a);
    t2 = (-b + sqrt(discriminant)) / (2.0 * a);

    if (t1 > t2)
    {
        t_float temp = t1;
        t1 = t2;
        t2 = temp;
    }

    // Check if the closest intersection point is within the cylinder's height
    t_float m1 = D_dot_V * t1 + X_dot_V;
    t_float m2 = D_dot_V * t2 + X_dot_V;

    if (t1 >= 0 && m1 >= 0 && m1 <= obj->cy.height)
    {
        t = t1;
    }
    else if (t2 >= 0 && m2 >= 0 && m2 <= obj->cy.height)
    {
        t = t2;
    }
    else
    {
        return NULL;
    }

    point = ray_at(ray, t);
    intersec.t = t;
    intersec.point = point;
    //intersec.normal = local_normal_at(point, obj, (t == t1) ? m1 : m2);
    intersec.color = obj->cy.color;

    obj->temp = intersec; // Store the intersection in the object's temp field
    return (&obj->temp);
}
