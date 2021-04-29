/*
 * Based on work by Graham Sellers and OpenGL SuperBible7
 * Also: https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Load_OBJ
 *       http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/ 
 *       https://antongerdelan.net/opengl/cubemaps.html
 * 
 * Goal is to build on our skycube system to show off textures
 */

#include <sb7.h>
#include <shader.h>
#include <vmath.h>

#include <loadingFunctions.h>
#include <skybox.h>

//Needed for file loading (also vector)
#include <string>
#include <fstream>

// For error checking
#include <vector>
#include <cassert>
#define GL_CHECK_ERRORS assert(glGetError()== GL_NO_ERROR);

class test_app : public sb7::application{

    public:

    void init(){
        // Set up appropriate title
        static const char title[] = "Animation Example";
        sb7::application::init();
        memcpy(info.title, title, sizeof(title));

        info.windowWidth = 900; //Make sure things are square to start with
        info.windowHeight = 900;
    }
    
    void startup(){
        //////////////////////
        // Load Object Info //
        //////////////////////
        //Push five objects onto stack
        objects.push_back(obj_t()); 
        objects.push_back(obj_t()); 
        objects.push_back(obj_t()); 
        objects.push_back(obj_t());
        objects.push_back(obj_t());
        objects.push_back(obj_t()); 
        objects.push_back(obj_t());
        // This program is set up to load multiple *different* objects
        // If you wanted to decouple the data for objects from the transforms for object, it would be beneficial to 
        // have two cooperative structs. One would hold the vertex data, the other would reference that data with 
        // individual transform infomation.

        //Also notice this could be automated / streamlined with a list of objects to load

        //Set up info for objects

        objects[0].objFileName = ".\\bin\\media\\Windmill\\Body.obj";
        objects[0].texFileName = ".\\bin\\media\\robot\\robot_base_texture.bmp";
        objects[0].parentObj = NULL; // Base object, no parent
        objects[0].hierTrans = vmath::vec3(0.0f,-2.0f,0.0f); //Starts at origin in the hierarchy
        objects[0].rotVector = vmath::vec3(0.0f,1.0f,0.0f); //Rotating around Y
        objects[0].originalTransform = vmath::mat4::identity();

        objects[1].objFileName = ".\\bin\\media\\Windmill\\Pole.obj";
        objects[1].texFileName = ".\\bin\\media\\robot\\robot_base_texture.bmp";
        objects[1].parentObj = &objects[0]; // Base object, no parent
        objects[1].hierTrans = vmath::vec3(0.0f,-2.0f,0.0f); //Starts at origin in the hierarchy
        objects[1].rotVector = vmath::vec3(0.0f,1.0f,0.0f); //Rotating around Y
        objects[1].originalTransform = vmath::mat4::identity();

        objects[2].objFileName = ".\\bin\\media\\Windmill\\Axle.obj";
        objects[2].texFileName = ".\\bin\\media\\robot\\robot_base_texture.bmp";
        objects[2].parentObj = &objects[0]; // Base object, no parent
        objects[2].hierTrans = vmath::vec3(0.0f,-2.0f,0.0f); //Starts at origin in the hierarchy
        objects[2].rotVector = vmath::vec3(0.0f,1.0f,0.0f); //Rotating around Y
        objects[2].originalTransform = vmath::mat4::identity();

        objects[3].objFileName = ".\\bin\\media\\Windmill\\BladeDown.obj";
        objects[3].texFileName = ".\\bin\\media\\robot\\robot_base_texture.bmp";
        objects[3].parentObj = &objects[2]; // Base object, no parent
        objects[3].hierTrans = vmath::vec3(0.0f,-2.0f,0.0f); //Starts at origin in the hierarchy
        objects[3].rotVector = vmath::vec3(0.0f,1.0f,0.0f); //Rotating around Y
        objects[3].originalTransform = vmath::mat4::identity();

        objects[4].objFileName = ".\\bin\\media\\Windmill\\BladeRight.obj";
        objects[4].texFileName = ".\\bin\\media\\robot\\robot_base_texture.bmp";
        objects[4].parentObj = &objects[2]; // Base object, no parent
        objects[4].hierTrans = vmath::vec3(0.0f,-2.0f,0.0f); //Starts at origin in the hierarchy
        objects[4].rotVector = vmath::vec3(0.0f,1.0f,0.0f); //Rotating around Y
        objects[4].originalTransform = vmath::mat4::identity();

        objects[5].objFileName = ".\\bin\\media\\Windmill\\BladeLeft.obj";
        objects[5].texFileName = ".\\bin\\media\\robot\\robot_base_texture.bmp";
        objects[5].parentObj = &objects[2]; // Base object, no parent
        objects[5].hierTrans = vmath::vec3(0.0f,-2.0f,0.0f); //Starts at origin in the hierarchy
        objects[5].rotVector = vmath::vec3(0.0f,1.0f,0.0f); //Rotating around Y
        objects[5].originalTransform = vmath::mat4::identity();

        objects[6].objFileName = ".\\bin\\media\\Windmill\\BladeUp.obj";
        objects[6].texFileName = ".\\bin\\media\\robot\\robot_base_texture.bmp";
        objects[6].parentObj = &objects[2]; // Base object, no parent
        objects[6].hierTrans = vmath::vec3(0.0f,-2.0f,0.0f); //Starts at origin in the hierarchy
        objects[6].rotVector = vmath::vec3(0.0f,1.0f,0.0f); //Rotating around Y
        objects[6].originalTransform = vmath::mat4::identity();

        //start with robot base
        // objects[0].objFileName = ".\\bin\\media\\robot\\robot_base.obj";
        // objects[0].texFileName = ".\\bin\\media\\robot\\robot_base_texture.bmp";
        // objects[0].parentObj = NULL; // Base object, no parent
        // objects[0].hierTrans = vmath::vec3(0.0f,-2.0f,0.0f); //Starts at origin in the hierarchy
        // objects[0].rotVector = vmath::vec3(0.0f,1.0f,0.0f); //Rotating around Y
        // objects[0].originalTransform = vmath::mat4::identity();

        // //Load lower arm
        // objects[1].objFileName = ".\\bin\\media\\robot\\robot_lowerArm.obj";
        // objects[1].texFileName = ".\\bin\\media\\robot\\robot_lower_texture.bmp";
        // objects[1].parentObj = &objects[0]; // Points to base defined above
        // objects[1].hierTrans = vmath::vec3(0.0f,0.0f,0.0f); //Modeled at the origin in the hierarchy
        // objects[1].rotVector = vmath::vec3(1.0f,0.0f,0.0f); //Rotating around x
        // objects[1].originalTransform = vmath::mat4::identity();

        // //Load upper arm
        // objects[2].objFileName = ".\\bin\\media\\robot\\robot_upperArm.obj";
        // objects[2].texFileName = ".\\bin\\media\\robot\\robot_upper_texture.bmp";
        // objects[2].parentObj = &objects[1]; // Points to base defined above
        // objects[2].hierTrans = vmath::vec3(0.0f,1.9f,0.0f); //Modeled at the origin in the hierarchy 
        // objects[2].rotVector = vmath::vec3(1.0f,0.0f,0.0f); //Rotating around x
        // objects[2].originalTransform = vmath::mat4::identity();

        // //Load first gripper
        // objects[3].objFileName = ".\\bin\\media\\robot\\robot_gripper.obj";
        // objects[3].texFileName = ".\\bin\\media\\robot\\robot_gripper.bmp";
        // objects[3].parentObj = &objects[2]; // Points to base defined above
        // objects[3].hierTrans = vmath::vec3(0.0f,1.17f,0.0f); //Modeled at the origin in the hierarchy 
        // objects[3].rotVector = vmath::vec3(0.0f,0.0f,1.0f); //Rotating around x
        // objects[3].originalTransform = vmath::mat4::identity();

        // //Load second gripper
        // objects[4].objFileName = ".\\bin\\media\\robot\\robot_gripper.obj";
        // objects[4].texFileName = ".\\bin\\media\\robot\\robot_gripper.bmp";
        // objects[4].parentObj = &objects[2]; // Points to base defined above
        // objects[4].hierTrans = vmath::vec3(0.0f,1.17f,0.0f); //Modeled at the origin in the hierarchy 
        // objects[4].rotVector = vmath::vec3(0.0f,0.0f,1.0f); //Rotating around x
        // objects[4].originalTransform = vmath::mat4::identity() * vmath::scale(-1.0f,1.0f,1.0f); //FLIP!

        //Load objects
        for(int i = 0; i < objects.size(); i++){
            load_obj(objects[i].objFileName.c_str(), objects[i].verticies, objects[i].uv, objects[i].normals, objects[i].vertNum);
        }

        ////////////////////////////////
        //Set up Object Scene Shaders //
        ////////////////////////////////
        GLuint shaders[2];

        //Load scene rendering based shaders
        //These need to be co-located with main.cpp in src
        shaders[0] = sb7::shader::load(".\\src\\vs.glsl", GL_VERTEX_SHADER);
        compiler_error_check(shaders[0]);
        shaders[1] = sb7::shader::load(".\\src\\fs.glsl", GL_FRAGMENT_SHADER);
        compiler_error_check(shaders[1]);
        //Put together scene rendering program from the two loaded shaders
        rendering_program = sb7::program::link_from_shaders(shaders, 2, true);
        GL_CHECK_ERRORS

        /////////////////////////////////
        // Transfer Object Into OpenGL //
        /////////////////////////////////

        //Set up vao
        glUseProgram(rendering_program); //TODO:: This might not be necessary (because of the above link_from_shaders)
        glCreateVertexArrays(1,&vertex_array_object);
        glBindVertexArray(vertex_array_object);

        for(int i = 0; i < objects.size(); i++){
            //For each object in objects, set up openGL buffers
            glGenBuffers(1,&objects[i].vertices_buffer_ID); //Create the buffer id for this object
            glBindBuffer( GL_ARRAY_BUFFER, objects[i].vertices_buffer_ID);
            glBufferData( GL_ARRAY_BUFFER,
                objects[i].verticies.size() * sizeof(objects[i].verticies[0]), //Size of element * number of elements
                objects[i].verticies.data(),                                   //Actual data
                GL_STATIC_DRAW);                                               //Set to static draw (read only)  

            //Set up UV buffers
            glGenBuffers(1,&objects[i].uv_buffer_ID); //Create the buffer id for this object
            glBindBuffer( GL_ARRAY_BUFFER, objects[i].uv_buffer_ID);
            glBufferData( GL_ARRAY_BUFFER,
                objects[i].uv.size() * sizeof(objects[i].uv[0]), //Size of element * number of elements
                objects[i].uv.data(),                            //Actual data
                GL_STATIC_DRAW); 

            //Set up normals
            glGenBuffers(1,&objects[i].normals_buffer_ID); //Create the buffer id for this object
            glBindBuffer( GL_ARRAY_BUFFER, objects[i].normals_buffer_ID);
            glBufferData( GL_ARRAY_BUFFER,
                objects[i].normals.size() * sizeof(objects[i].normals[0]), //Size of element * number of elements
                objects[i].normals.data(),                                   //Actual data
                GL_STATIC_DRAW);                                               //Set to static draw (read only) 
        }
        
        GL_CHECK_ERRORS
        ////////////////////////////////////
        // Grab IDs for rendering program //
        ////////////////////////////////////
        transform_ID = glGetUniformLocation(rendering_program,"transform");
        perspec_ID = glGetUniformLocation(rendering_program,"perspective");
        toCam_ID = glGetUniformLocation(rendering_program,"toCamera");
        vertex_ID = glGetAttribLocation(rendering_program,"obj_vertex");
        uv_ID = glGetAttribLocation(rendering_program,"obj_uv");    
        normals_ID = glGetAttribLocation(rendering_program,"obj_normal");      

        ///////////////////////
        // Loading  Textures //
        ///////////////////////
        
        //Memory spaces for texture data
        unsigned char* loadedTextureData;
        unsigned int texWidth;
        unsigned int texHeight;

        for(int i = 0; i < objects.size(); i++){

            // Load texture data from bitmap file to CPU memory
            //load_BMP(".\\bin\\media\\Skycube\\sc_left.bmp",loadedTextureData,texWidth,texHeight);
            load_BMP(objects[i].texFileName,loadedTextureData,texWidth,texHeight);

            //Assign Texture from CPU memory to GPU memory
            glGenTextures(1,&objects[i].texture_ID);
            glBindTexture(GL_TEXTURE_2D, objects[i].texture_ID);
            glTexImage2D( GL_TEXTURE_2D, //What kind of texture are we loading in
                                    0, // Level of detail, 0 base level
                                GL_RGBA, // Internal (target) format of data, in this case Red, Gree, Blue, Alpha
                            texWidth, // Width of texture data (max is 1024, but maybe more)
                            texHeight, // Height of texture data
                                    0, //border (must be zero)
                                GL_RGBA, //Format of input data (in this case we added the alpha when reading in data)
                    GL_UNSIGNED_BYTE, //Type of data being passed in
                        loadedTextureData); // Finally pointer to actual data to be passed in
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            //Get rid of dynamic memory after use
            delete[] loadedTextureData;
            loadedTextureData = NULL;
            GL_CHECK_ERRORS
        }
        
        /////////////////////
        // Camera Creation //
        /////////////////////
        camera.camera_near = 0.1f; //Near Clipping Plane
        camera.camera_far = 100.0f; //Far Clipping Plane
        camera.fovy       = 67.0f; //Field of view in the y direction (x defined by aspect)
        //Initial camera details
        camera.position = vmath::vec3(0.0f, 0.0f, 5.0f); //Starting camera at position (0,0,5)
        camera.focus = vmath::vec3(0.0f, 0.0f, 0.0f); //Camera is looking at origin
        
        //Now that we have parameters set, calculate the Projection and View information for this camera
        calcProjection(camera); //Calculate the projection matrix used by this camera
        calcView(camera); //Calculate the View matrix for camera

        GL_CHECK_ERRORS

        // General openGL settings
        //src:: https://github.com/capnramses/antons_opengl_tutorials_book/tree/master/21_cube_mapping
        glEnable( GL_DEPTH_TEST );          // enable depth-testing
        glDepthFunc( GL_LESS );             // depth-testing interprets a smaller value as "closer"
        glEnable( GL_CULL_FACE );           // cull face
        glCullFace( GL_BACK );              // cull back face
        glFrontFace( GL_CCW );              // set counter-clock-wise vertex order to mean the front
        glClearColor( 0.1, 0.1, 0.1, 1.0 ); // grey background to help spot mistakes

        //End of set up check
        GL_CHECK_ERRORS
    }

    void render(double curTime){

        glViewport( 0, 0, info.windowWidth, info.windowHeight ); //Set Viewport information

        //if Auto rotate flag is set, update the position of the camera
        if(autoRotate){
            camera.position = vmath::vec3(static_cast<float>(cos(curTime/10.0) * 5.0),
                                          0.0f,
                                          static_cast<float>(sin(curTime/10.0) * 5.0) );
        }

        //If Auto Animation flag is set:
        if(autoAnimate){
            //Rotate base around
            objects[0].rotAngle = curTime*10;
            //Flip objects around
            objects[1].rotAngle = (cos(curTime/2.0) * 35.0) + 35.0; // 70 <-> 0
            objects[2].rotAngle =  cos(curTime*1.5) * 55.0; // 55 <-> -55
        }

        //Check for Gripper automation
        if(autoGrip){
            //Gripper
            objects[3].rotAngle = (cos(curTime*3)   * 20.0) - 20.0; // 40 <-> 0
        }
        //Mirrored gripper is always the opposite of other gripper
        objects[4].rotAngle = -objects[3].rotAngle; // Inverse of objects[3]

        //Update all of the object2World Matrices
        updateObject2Worlds(curTime);

        //recalculate the View matrix for camera
        calcProjection(camera);
        calcView(camera);

        //Clear output
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        runtime_error_check(1);

        //Camera and projection are both the same for all objects
        glUniformMatrix4fv(perspec_ID, 1,GL_FALSE, camera.proj_Matrix); //Load camera projection
        glUniformMatrix4fv(toCam_ID, 1,GL_FALSE, camera.view_mat); //Load in view matrix for camera

        for(int i = 0; i < objects.size(); i++ ){
            runtime_error_check(12);
            //render loop, go through each object and render it!
            glUseProgram(rendering_program); //activate the render program

            runtime_error_check(11);

            glBindVertexArray(vertex_array_object); //Select base vao
            runtime_error_check(10);
      
            glBindTexture(GL_TEXTURE_2D,objects[i].texture_ID);
            runtime_error_check(9);

            //Copy over object transforms
            glUniformMatrix4fv(transform_ID, 1,GL_FALSE, objects[i].obj2world); //Load in transform for this object
            runtime_error_check(8);

            //link to object buffer
            glEnableVertexAttribArray(vertex_ID); //Recall the vertex ID
            glBindBuffer(GL_ARRAY_BUFFER,objects[i].vertices_buffer_ID);//Link object buffer to vertex_ID
            glVertexAttribPointer( //Index into the buffer
                    vertex_ID, //Attribute in question
                    4,         //Number of elements per vertex call (vec4)
                    GL_FLOAT,  //Type of element
                    GL_FALSE,  //Normalize? Nope
                    0,         //No stride (steps between indexes)
                    0);       //initial offset
            
            runtime_error_check(7);

            //If we are using UVs in the shaders, this ID value will be set, otherwise ignore
            if(static_cast<int>(uv_ID) > 0){              
                glEnableVertexAttribArray(uv_ID); //Recall the vertex ID
                glBindBuffer(GL_ARRAY_BUFFER,objects[i].uv_buffer_ID);//Link object buffer to vertex_ID
                glVertexAttribPointer( //Index into the buffer
                        uv_ID, //Attribute in question
                        2,         //Number of elements per vertex call (vec2)
                        GL_FLOAT,  //Type of element
                        GL_FALSE,  //Normalize? Nope
                        0,         //No stride (steps between indexes)
                        0);       //initial offset

                runtime_error_check(5);
            }

            //If we are using UVs in the shaders, this ID value will be set, otherwise ignore         
            if(static_cast<int>(normals_ID) > 0){
                glEnableVertexAttribArray(normals_ID); //Recall the vertex ID
                glBindBuffer(GL_ARRAY_BUFFER,objects[i].normals_buffer_ID);//Link object buffer to vertex_ID
                glVertexAttribPointer( //Index into the buffer
                        normals_ID, //Attribute in question
                        4,         //Number of elements per vertex call (vec2)
                        GL_FLOAT,  //Type of element
                        GL_FALSE,  //Normalize? Nope
                        0,         //No stride (steps between indexes)
                        0);       //initial offset

                runtime_error_check(6);
            }

            //Draw the actual vertexes
            glDrawArrays( GL_TRIANGLES, 0, objects[i].verticies.size());
            runtime_error_check(1);
        }

        runtime_error_check(4);
    }

    void updateObject2Worlds(double curTime){
        //Set up obj->world transforms for each object (these could be modified for animation)
        for(int i = 0; i < objects.size(); i++){
            if(objects[i].parentObj != NULL){
                //Object has a parent object
                obj_t* parent = objects[i].parentObj;
                //This assumes that all children will be of a higher index than their parent
                objects[i].obj2world = parent->obj2world*
                                       vmath::translate(objects[i].hierTrans) *
                                       vmath::rotate(objects[i].rotAngle,objects[i].rotVector) * 
                                       objects[i].originalTransform; //To manage the flipping of the grippers

            } else {
                //Object is a base node
                objects[i].obj2world = vmath::mat4::identity() *
                                       vmath::translate(objects[i].hierTrans) *
                                       vmath::rotate(objects[i].rotAngle,objects[i].rotVector) * 
                                       objects[i].originalTransform;
            }
        }

    }

    void onResize(int w, int h) {
        info.windowWidth = w;
        info.windowHeight = h;
        //Recalculate the projection matrix used by camera
        calcProjection(camera); 
    }

    void onKey(int key, int action) {
        //If something did happen
        if (action) {
            switch (key) { //Select an action
                // Z - Reset to default 
                // X - Diagnostic Printout
                // C - toggle auto rotate flag
                // V - toggle auto animate
                // N/M - Rotate Base
                // Y/H - Change Lower Arm
                // U/J - Change Upper Arm Angle
                // I/K - Change Gripper Angle
                case 'N':
                    objects[0].rotAngle += 5.0;
                    break;
                case 'M':
                    objects[0].rotAngle -= 5.0;
                    break;
                case 'Y':
                    objects[1].rotAngle += 5.0;
                    break;
                case 'H':
                    objects[1].rotAngle -= 5.0;
                    break;
                case 'U':
                    objects[2].rotAngle += 5.0;
                    break;
                case 'J':
                    objects[2].rotAngle -= 5.0;
                    break;
                case 'I':
                    objects[3].rotAngle += 5.0;
                    break;
                case 'K':
                    objects[3].rotAngle -= 5.0;
                    break;
                case 'C':
                    autoRotate = !autoRotate;
                    break;
                case 'V':
                    autoAnimate = !autoAnimate;
                    break;
                case 'B':
                    autoGrip = !autoGrip;
                    break;
                case 'Z': //Reset
                    camera.position = vmath::vec3(0.0f, 0.0f, 5.0f); //Starting camera at position (0,0,5)
                    camera.focus = vmath::vec3(0.0f, 0.0f, 0.0f); //Camera is looking in the +y direction
                    autoRotate = false;
                    autoAnimate = false;
                    autoGrip = false;
                    objects[0].rotAngle = 0;
                    objects[1].rotAngle = 0;
                    objects[2].rotAngle = 0;
                    objects[3].rotAngle = 0;
                    break;
                case 'X': //Info
                    char buf2[200];
                    sprintf(buf2, "Current Hierarchy Angels: \nBase %.2f\nLower %.2f\nUpper %.2f\nGripper %.2f",objects[0].rotAngle,objects[1].rotAngle,objects[2].rotAngle,objects[3].rotAngle);
                    MessageBoxA(NULL, buf2, "Diagnostic Printout", MB_OK);
                    break;
            }
        }

    }

    void runtime_error_check(GLuint tracker = 0)
    {
        GLenum err = glGetError();
        
        if (err) {
            char buf[50];
            sprintf(buf, "Error(%d) = %x", tracker, err);
            MessageBoxA(NULL, buf, "Error running program!", MB_OK);
        }
    }

    void compiler_error_check(GLuint shader)
    {
        GLint isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> errorLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

            if(maxLength == 0){
                char buf[50];
                sprintf(buf, "Possibly shaders not found!", maxLength);
                MessageBoxA(NULL, buf, "Error in shader compilation", MB_OK);
            } else {
                // Provide the infolog in whatever manor you deem best.
                MessageBoxA(NULL, &errorLog[0], "Error in shader compilation", MB_OK);
            }

            // Exit with failure.
            glDeleteShader(shader); // Don't leak the shader.
        }
    }

    private:
        //Scene Rendering Information
        GLuint rendering_program; //Program reference for scene generation
        GLuint vertex_array_object;
        
        //Uniform attributes for Scene Render
        GLuint transform_ID; //Dynamic transform of object
        GLuint perspec_ID;   //Perspective transform
        GLuint toCam_ID;     //World to Camera transform
        GLuint vertex_ID;    //This will be mapped to different objects as we load them
        GLuint uv_ID;
        GLuint normals_ID;

        //Structure to hold all the object info
        struct obj_t{
            std::string objFileName;
            std::string texFileName;

            //Data for object loaded from file
            std::vector<vmath::vec4> verticies;
            std::vector<vmath::vec4> normals;
            std::vector<vmath::vec2> uv;
            GLuint vertNum; //This should be the same as vertivies.size()

            //Handle from OpenGL set up
            GLuint vertices_buffer_ID; 
            GLuint normals_buffer_ID; 
            GLuint uv_buffer_ID;       

            //Object to World transforms
            vmath::mat4 obj2world;

            //Texture Info
            GLuint texture_ID;

            //!!NEW!!
            //Hierarchy Space!
            obj_t* parentObj;
            vmath::vec3 hierTrans; //Translation, in object space, of this object
            float rotAngle;
            vmath::vec3 rotVector; //Used as temp angle value
            vmath::mat4 originalTransform; //Used to mirror the grippers

        };

        //Hold all of our objects
        std::vector<obj_t> objects;

        bool autoRotate = false;
        bool autoAnimate = true;
        bool autoGrip = false;

        // Camera Stuff
        struct camera_t{ //Keep all of our camera stuff together
            float camera_near;   //Near clipping mask
            float camera_far;    //Far clipping mask
            float fovy;          //Field of View in y
            float aspect;        //Aspect ratio (w/h)
            vmath::mat4 proj_Matrix; //Collection of the above

            vmath::vec3 position; //Current world coordinates of the camera
            vmath::vec3 focus; //Current world focus of the camera
            //TODO:: Maybe we just want to use euler angles here

            vmath::mat4 view_mat; //World to Camera matrix
            vmath::mat4 view_mat_no_translation; //World to Camera matrix with no translation
        } camera;

        //Utility to update project matrix and view matrix of a camera_t
        void calcProjection(camera_t &cur){
            cur.aspect = static_cast<float>(info.windowWidth) / static_cast<float>(info.windowHeight); //Maybe this will keep it updated?
            //vmath perspective
            cur.proj_Matrix = vmath::perspective(cur.fovy,cur.aspect, cur.camera_near, cur.camera_far);
        }
        void calcView(camera_t &cur){
            cur.view_mat = vmath::lookat(cur.position,cur.focus,vmath::vec3(0.0f,1.0f,0.0f)); //Based on position and focus location
            cur.view_mat_no_translation = cur.view_mat;   
            //Removing the tranlational elements for skybox         
            cur.view_mat_no_translation[3][0] = 0;
            cur.view_mat_no_translation[3][1] = 0;
            cur.view_mat_no_translation[3][2] = 0;
        }


};


DECLARE_MAIN(test_app);
