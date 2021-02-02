#version 410

in vec2 LVertexPos2D;
out vec4 gl_Position;
void main()
{
    gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 );
}
