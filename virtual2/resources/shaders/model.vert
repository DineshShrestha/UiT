uniform mat4 u_mvmat, u_mvpmat;
uniform mat3 u_nmat;
uniform vec3 in_lightPosition;
uniform vec3 in_objColor;

in vec4 in_vertex;
in vec4 in_normal;
in vec2 in_tex;

smooth out vec3 ex_normal;
smooth out vec3 ex_pos;
smooth out vec2 ex_tex;

out vec3 ex_norm;
out vec3 ex_lightVec;
out vec3 ex_viewVec;
out vec3 ex_objColor;

out vec4 gl_Position;

void main() {

    vec4 v_pos = u_mvmat * in_vertex;
    ex_pos = v_pos.xyz * v_pos.w;
    ex_normal = in_normal.xyz * v_pos.w;

    ex_objColor = in_objColor;
    ex_tex = in_tex;

    ex_norm = normalize(u_nmat * ex_normal);
    ex_lightVec = normalize(in_lightPosition - ex_pos);
    ex_viewVec = normalize(-ex_pos);

    gl_Position = u_mvpmat * in_vertex;
}
