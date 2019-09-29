#version 330 core

uniform mat4 projection_matrix;

in vec3 v_color;
in vec3 v_position;

uniform float cylinder_radius;
uniform vec3 cylinder_bottom;
uniform vec3 cylinder_top;

out vec4 out_color;

void main(void) {
    vec3 cylinder_vector = normalize(cylinder_top - cylinder_bottom);
    float cylinder_length = length(cylinder_top - cylinder_bottom);

    float PTV = dot(v_position,cylinder_vector);
    float BTV = dot(cylinder_bottom,cylinder_vector);
    float a = dot(v_position,v_position) - PTV*PTV;
    float b2 = -dot(v_position,cylinder_bottom) + PTV*BTV;
    float c = dot(cylinder_bottom,cylinder_bottom) - BTV*BTV - cylinder_radius*cylinder_radius;
    float delta4 = b2*b2-a*c;

    if (delta4 < 0)
        discard;
    float alpha = (-b2-sqrt(delta4))/a;
    float height = alpha*PTV-BTV;
    if (height < 0 || height > cylinder_length)
        discard;
    vec3 outColor = v_color;
    vec3 new_P = alpha*v_position;
    vec3 n = normalize(new_P-cylinder_bottom-(alpha*PTV-BTV)*cylinder_vector);

    vec3 viewDir = -normalize(new_P);
    vec3 lightDir = normalize(vec3(1.0, 1.0, 1.0));
    vec3 lightColor = vec3(1.0);

    vec3 ka = vec3(0.1, 0.1, 0.1);
    vec3 kd = v_color;
    vec3 ks = vec3(0.4);
    float shininess = 10.0;

    vec3 diffuse = kd * (dot(n, lightDir)+1)*0.5;

    vec3 r = normalize(reflect(lightDir, n));
    vec3 specular = ks * pow(max(dot(n, lightDir), 0.0), shininess);

    int paliers = 5;
    float norm = floor(paliers*length(diffuse + specular))/paliers;
    outColor = ka + lightColor * norm*normalize(diffuse + specular);
    float outAlpha = min(1.0, length(new_P)/5);
    float thickness = float(dot(n, viewDir) > min(0.9,0.2*log(length(new_P)+1)/sqrt(cylinder_radius)));

    out_color = vec4(outColor*thickness, outAlpha);

    vec4 P_projected = projection_matrix*vec4(new_P,1.0);
    float ndcDepth = P_projected.z/P_projected.w;
    gl_FragDepth = ((gl_DepthRange.diff * ndcDepth) + gl_DepthRange.near + gl_DepthRange.far) / 2.0;
}
