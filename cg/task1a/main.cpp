#include <algorithm>
#include <iostream>
#include <sstream>
#include <rapidjson/document.h>
#include "surface.h"
#include "mkdir.h"
#include "Scene1a.h"
#include "Sphere.h"
#include "Plane.h"


// forward declarations
Scene1a* buildScene(rapidjson::Value& json_scene);
void saveSurface(const surface<float>& surface, const char* filename);

// functions in task1a
void render(const Scene1a& scene, surface<float>& output_image, float w_s, float f);
bool intersectRaySphere(const float3& p, const float3& d, const float3& c, float r, float& t);
bool intersectRayPlane(const float3& p, const float3& d, const float3& p_0, const float3& n, float& t);

void renderLatLongMap(Scene1a* scene, surface<float>& output_image){
    
    int w = output_image.width();
    int h = output_image.height();
    constexpr float PI = 3.14159265358979f;
    for (int y = 0; y < h; y++)
    {
        float sh = sin(PI/2+y*PI/h);
        float ch = cos(PI/2+y*PI/h);
        for (int x = 0; x < w; x++)
        {
            
            float3 vec = float3(0,0,-1);
            float s = sin(x*2*PI/w);
            float c = cos(x*2*PI/w);
            
            float rx = vec.x * c + vec.z * s;
            float rz = vec.z * c - vec.x * s;

            float3 tmpvec = float3(rx, vec.y, rz);
            
            float ry = tmpvec.y * ch + tmpvec.z * sh;
            rz = tmpvec.z * ch - tmpvec.y * sh;
            
            float3 ray = normalize(float3(tmpvec.x, ry, rz));
            
            float distance;
            bool intersected = scene->intersectWithRay(ray, distance);

            //std::cout << "is " << distance << std::endl;
            output_image(x, y) = intersected?distance:0;
        }
    }
}

void runTestcase(rapidjson::Value& testcase)
{
  const char* name = testcase["name"].GetString();
  int w = testcase["r_x"].GetInt();
  int h = testcase["r_y"].GetInt();
  float w_s = static_cast<float>(testcase["w_s"].GetDouble());
  float f = static_cast<float>(testcase["f"].GetDouble());
  const char* output_dir = testcase["output"].GetString();

  std::cout << "Running testcase " << name << std::endl;
  std::cout << "Image size " << w << "x" << h << std::endl;
  
  Scene1a* scene = buildScene(testcase["scene"]);
  
  if(testcase.HasMember("viewbox")){
    float from = static_cast<float>(testcase["viewbox"]["from"].GetDouble());
    float to = static_cast<float>(testcase["viewbox"]["to"].GetDouble());
    scene->setViewBox(from,to); 
  } else {
    std::cout << "Warning: no viewbox defined in config file!" << std::endl;
    scene->setViewBox(0,100); 
  }
  
  std::stringstream output_path;
  output_path << "output/" << output_dir;
  utils::mkDir(output_path.str().c_str());
  
  // render rays only
  Scene1a* emptyscene = new Scene1a();
  emptyscene->renderRays_ = true;
  std::stringstream output_path_rays;
  output_path_rays << output_path.str();
  output_path_rays << "/" << name << "_rays.png";
  surface<float> render_img_rays(w, h, 0.f);
  render(*emptyscene, render_img_rays, w_s, f);
  std::cout << "Saving output to '" << output_path_rays.str() << "'." << std::endl;
  saveSurface(render_img_rays, output_path_rays.str().c_str());
  
  // render globe (intersection test)
  std::stringstream output_path_is;
  output_path_is << output_path.str();
  output_path_is << "/" << name << "_globe.png";
  surface<float> render_img_is(w, h, 0.f);
  renderLatLongMap(scene, render_img_is);
  std::cout << "Saving output to '" << output_path_is.str() << "'." << std::endl;
  saveSurface(render_img_is, output_path_is.str().c_str());
  
  
  // render full scene
  surface<float> render_img(w, h, 0.f);
  render(*scene, render_img, w_s, f);

  output_path << "/" << name << ".png";

  std::cout << "Saving output to '" << output_path.str() << "'." << std::endl;
  saveSurface(render_img, output_path.str().c_str());
  std::cout << "Outputs saved." << std::endl;
}

Scene1a* buildScene(rapidjson::Value& json_scene)
{
  assert(json_scene.IsArray());
  Scene1a* scene = new Scene1a();
  scene->intersectRayWithSphere_ = *intersectRaySphere;
  scene->intersectRayWithPlane_ = *intersectRayPlane;
  
  // add objects
  for (unsigned int i = 0; i < json_scene.Size(); i++){
      if(json_scene[i].HasMember("sphere")){
          rapidjson::Value& sphere = json_scene[i]["sphere"];
          assert(sphere.HasMember("center"));
          assert(sphere.HasMember("radius"));
          rapidjson::Value& center = sphere["center"];
          
          Sphere* s = new Sphere(float3(static_cast<float>(center["x"].GetDouble()), static_cast<float>(center["y"].GetDouble()), static_cast<float>(center["z"].GetDouble())), static_cast<float>(sphere["radius"].GetDouble()));
          scene->add(s);
        
      }
      if(json_scene[i].HasMember("plane")){
          rapidjson::Value& plane = json_scene[i]["plane"];
          assert(plane.HasMember("point"));
          assert(plane.HasMember("normal"));
          rapidjson::Value& point = plane["point"];
          rapidjson::Value& normal = plane["normal"];
          
          Plane* p = new Plane(float3(static_cast<float>(point["x"].GetDouble()), static_cast<float>(point["y"].GetDouble()), static_cast<float>(point["z"].GetDouble())), normalize(float3(static_cast<float>(normal["x"].GetDouble()), static_cast<float>(normal["y"].GetDouble()), static_cast<float>(normal["z"].GetDouble()))));
          scene->add(p);
      }
  }
  
  return scene;
}

void saveSurface(const surface<float>& image, const char* filename)
{
  surface<R8G8B8A8> output(image.width(), image.height(), R8G8B8A8(0, 0, 0, 255));

  for (int pixel_y = 0; pixel_y < image.height(); pixel_y++)
  {
    for (int pixel_x = 0; pixel_x < image.width(); pixel_x++)
    {
        std::uint8_t c = static_cast<std::uint8_t>(std::min(std::max(image(pixel_x, pixel_y), 0.0f), 1.0f) * 255.0f);
        output(pixel_x, pixel_y) = R8G8B8A8(c, c, c);
    }
  }
  output.save(filename);
}
