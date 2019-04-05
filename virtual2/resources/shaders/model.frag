uniform sampler2D u_tex;
uniform bool is_textured;

smooth in vec3 ex_pos;
smooth in vec2 ex_tex;
smooth in vec3 ex_normal;

in vec3 ex_norm;
in vec3 ex_lightVec;
in vec3 ex_viewVec;
in vec3 ex_objColor;

out vec4 gl_FragColor;

void main() {

    vec3 nVec = normalize(ex_norm);
    vec3 lVec = normalize(ex_lightVec);
    vec3 vVec = normalize(ex_viewVec);

    float diffuse = clamp(dot(lVec, nVec), 0.0, 1.0);
    float specular = pow(clamp(dot(reflect(-vVec, nVec), lVec), 0.0, 1.0), 32.0);

    vec4 col;
    vec3 phongCol = ex_objColor * (diffuse + 0.1) + (specular * 0.9);

    if (is_textured)
        col = texture2D(u_tex, ex_tex) + vec4(phongCol, 1.0) * 0.3;
    else
        col = vec4(phongCol, 1.0);

    gl_FragColor = col;
}
