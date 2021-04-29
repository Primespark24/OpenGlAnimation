#version 450 core   

//Incomming pieces from vertex shader
in vec2 vs_uv; 

//Texture Mapping
uniform sampler2D twoDTex; //Texture mapping for the object

out vec4 color;  
                                                                  
void main(void)                                                   
{                                    
    color =  texture(twoDTex,vs_uv);                           
}                                                                 