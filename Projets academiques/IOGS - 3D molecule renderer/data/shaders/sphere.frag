#version 330 core

uniform mat4 projection_matrix;

in vec3 v_color;
in vec3 v_position;

uniform float sphere_radius;
uniform vec3 sphere_center;

out vec4 out_color;

void main(void) {
    float PTP = dot(v_position,v_position);
    float PTC = dot(v_position,sphere_center);
    float delta4 = PTC*PTC - PTP*(dot(sphere_center,sphere_center)-sphere_radius*sphere_radius);

    if (delta4 < 0)
        discard;

    float alpha = (PTC-sqrt(delta4))/PTP;
    vec3 new_P = alpha*v_position;
    vec3 outColor = v_color;
    vec3 n = normalize(new_P-sphere_center);

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
    float thickness = float(dot(n, viewDir) > min(0.9,0.2*log(length(new_P)+1)/sqrt(sphere_radius)));

    out_color = vec4(outColor*thickness, outAlpha);

    vec4 P_projected = projection_matrix*vec4(new_P,1.0);
    float ndcDepth = P_projected.z/P_projected.w;
    gl_FragDepth = ((gl_DepthRange.diff * ndcDepth) + gl_DepthRange.near + gl_DepthRange.far) / 2.0;
}
