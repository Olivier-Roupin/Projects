#version 330 core

in vec3 v_color;
in vec3 v_normal;
in vec3 v_position;

out vec4 out_color;

void main(void) {
    vec3 outColor = v_color;
    vec3 n = normalize(v_normal);
    
    vec3 viewDir = -normalize(v_position);
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
    
    out_color = vec4(outColor*float(dot(n, viewDir) > 0.2),1.0);
}
