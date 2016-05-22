#include <rapidjson/document.h>
#include <iostream>
#include <iomanip>
#include <sstream>

#include "Scene1b.h"
#include "Camera.h"
#include "surface.h"
#include "mkdir.h"
#include "Ray.h"
#include "Material.h"
#include "Light.h"
#include "matrix.h"
#include "cgmath.h"
#include "Intersection.h"

#include "Serialization.h"

void render(const Scene1b &scene, surface<R8G8B8A8> &output_image, const float3 &cam_eye, const float3 &cam_up,
            const float3 &cam_look_at, float w_s, float f, int sample_count);

float3 phong(const Ray &ray, const Intersection &hit, const Scene1b &scene);


Scene1b *buildScene(rapidjson::Value &json_scene);

Camera *loadCamera(rapidjson::Value &json_camera);

Light *loadLight(rapidjson::Value &json_light);

float3 loadVector3(rapidjson::Value &json_node);

float4x4 loadMatrix4(rapidjson::Value &json_node);

void renderTriangleTest(Camera *cam, Scene1b *scene, surface<R8G8B8A8> &distance_image, surface<R8G8B8A8> &bary_image);

void renderPhongTest(Scene1b *scene, surface<R8G8B8A8> &phong_image);

void renderReflectionTest(Scene1b *scene, surface<R8G8B8A8> &refl_image);

void runTestcase(rapidjson::Value &testcase) {
    const char *name = testcase["name"].GetString();
    int w = testcase["width"].GetInt();
    int h = testcase["height"].GetInt();
    const char *output_dir = testcase["output"].GetString();
    int antialiasing = 1;
    if (testcase.HasMember("antialiasing")) {
        antialiasing = testcase["antialiasing"].GetInt();
    }

    std::cout << "Running testcase " << name << std::endl;
    std::cout << "Image size " << w << "x" << h << std::endl;

    std::stringstream output_path;
    output_path << "output/" << output_dir;
    utils::mkDir(output_path.str().c_str());
    output_path << "/" << name;

    Scene1b *scene = buildScene(testcase["scene"]);
    Camera *camera = loadCamera(testcase["camera"]);
    scene->cam = camera;

    surface<R8G8B8A8> render_img(w, h, R8G8B8A8(0, 0, 0, 255));
    surface<R8G8B8A8> ray_img = surface<R8G8B8A8>(w, h, R8G8B8A8(0, 0, 0, 255));
    surface<R8G8B8A8> triangles_dist_img = surface<R8G8B8A8>(w, h, R8G8B8A8(0, 0, 0, 255));
    surface<R8G8B8A8> triangles_bary_img = surface<R8G8B8A8>(w, h, R8G8B8A8(0, 0, 0, 255));
    surface<R8G8B8A8> phong_img = surface<R8G8B8A8>(w, h, R8G8B8A8(0, 0, 0, 255));
    surface<R8G8B8A8> refl_img = surface<R8G8B8A8>(w, h, R8G8B8A8(0, 0, 0, 255));

    std::cout << "Rendering rays..." << std::endl;
    scene->ray_test = true;
    render(*scene, ray_img, camera->eye, camera->up, camera->look_at, camera->focal_length, camera->image_plane_width,
           antialiasing);
    scene->ray_test = false;
    std::cout << std::endl;

    std::stringstream ray_img_path;
    ray_img_path << output_path.str();
    ray_img_path << "_rays.png";
    std::cout << "Saving ray output to '" << ray_img_path.str() << "'." << std::endl;
    ray_img.save(ray_img_path.str().c_str());

    std::cout << "Rendering phong test..." << std::endl;
    scene->phong_test = true;
    std::vector<Light *> lights_backup = scene->lights;
    scene->lights.clear();
    Light *light = new Light();
    light->position = float3(-0.7f, 1.3f, 3.f);
    light->ambient = float3(0.25f);
    light->intensities = float3(1.f);
    scene->lights.push_back(light);
    renderPhongTest(scene, phong_img);
    delete light;
    scene->lights = lights_backup;
    scene->phong_test = false;
    std::cout << std::endl;

    std::stringstream phong_img_path;
    phong_img_path << output_path.str();
    phong_img_path << "_phong.png";
    std::cout << "Saving phong test output to '" << phong_img_path.str() << "'." << std::endl;
    phong_img.save(phong_img_path.str().c_str());

    std::cout << "Rendering reflection test..." << std::endl;
    scene->refl_test = true;
    Material mat;
    mat.reflective = true;
    scene->materials.push_back(mat);
    renderReflectionTest(scene, refl_img);
    scene->refl_test = false;
    std::cout << std::endl;

    std::stringstream refl_img_path;
    refl_img_path << output_path.str();
    refl_img_path << "_reflection.png";
    std::cout << "Saving reflection test output to '" << refl_img_path.str() << "'." << std::endl;
    refl_img.save(refl_img_path.str().c_str());

    if (!scene->empty) {
        std::cout << "Rendering triangles..." << std::endl;
        renderTriangleTest(camera, scene, triangles_dist_img, triangles_bary_img);
        std::cout << std::endl;

        std::stringstream triangles_dist_img_path;
        triangles_dist_img_path << output_path.str();
        triangles_dist_img_path << "_triangle_dist.png";
        std::cout << "Saving triangle distance output to '" << triangles_dist_img_path.str() << "'." << std::endl;
        triangles_dist_img.save(triangles_dist_img_path.str().c_str());

        std::stringstream triangles_bary_img_path;
        triangles_bary_img_path << output_path.str();
        triangles_bary_img_path << "_triangle_bary.png";
        std::cout << "Saving triangle barycentric output to '" << triangles_bary_img_path.str() << "'." << std::endl;
        triangles_bary_img.save(triangles_bary_img_path.str().c_str());

        std::cout << "Rendering..." << std::endl;
        render(*scene, render_img, camera->eye, camera->up, camera->look_at, camera->focal_length,
               camera->image_plane_width, antialiasing);
        std::cout << std::endl;

        std::stringstream render_img_path;
        render_img_path << output_path.str();
        render_img_path << ".png";
        std::cout << "Saving output to '" << render_img_path.str() << "'." << std::endl;
        render_img.save(render_img_path.str().c_str());
    }
}

Scene1b *buildScene(rapidjson::Value &json_scene) {
    Scene1b *scene = new Scene1b();

    if (json_scene.IsObject()) {
        serializeFromFile(json_scene["file"].GetString(),
                          *reinterpret_cast<Scene *>(scene));

        scene->empty = false;

        rapidjson::Value::MemberIterator i = json_scene.MemberBegin();
        while (i != json_scene.MemberEnd()) {
            std::string name = i->name.GetString();
            if (name == "light") {
                Light *light = loadLight(i->value);
                scene->lights.push_back(light);
            }

            ++i;
        }
    }

    return scene;
}

Camera *loadCamera(rapidjson::Value &json_camera) {
    float3 eye;
    std::istringstream ss(json_camera["eye"].GetString());
    ss >> eye.x >> eye.y >> eye.z;

    float3 up;
    ss.clear();
    ss.str(json_camera["up"].GetString());
    ss >> up.x >> up.y >> up.z;

    float3 look_at;
    ss.clear();
    ss.str(json_camera["lookAt"].GetString());
    ss >> look_at.x >> look_at.y >> look_at.z;

    float focal_length = static_cast<float>(
            json_camera["focalLength"].GetDouble());

    float image_plane_width = static_cast<float>(
            json_camera["imagePlaneWidth"].GetDouble());

    Camera *cam = new Camera(eye, up, look_at, focal_length, image_plane_width);
    return cam;
}

Light *loadLight(rapidjson::Value &json_light) {
    Light *light = new Light();
    float3 position = loadVector3(json_light["position"]);
    light->position = position;
    float3 intensities = loadVector3(json_light["intensities"]);
    light->intensities = intensities;
    if (json_light.HasMember("ambient")) {
        float3 ambient = loadVector3(json_light["ambient"]);
        light->ambient = ambient;
    }
    return light;
}

float3 loadVector3(rapidjson::Value &json_node) {
    std::string vec3_str = json_node.GetString();
    std::istringstream ss(vec3_str);
    float3 vec3;
    ss >> vec3.x >> vec3.y >> vec3.z;
    return vec3;
}

float4x4 loadMatrix4(rapidjson::Value &json_node) {
    std::string m_str = json_node.GetString();
    std::istringstream ss(m_str);
    float4x4 m;
    ss >> m._11 >> m._12 >> m._13 >> m._14 >>
    m._21 >> m._22 >> m._23 >> m._24 >>
    m._31 >> m._32 >> m._33 >> m._34 >>
    m._41 >> m._42 >> m._43 >> m._44;
    return m;
}

void printProgress(int y, int height) {
    static float progress = 0.0f;

    float p = std::trunc(100.0f * (y + 1) / height);
    if (p != progress) {
        progress = p;
        std::cout << "\rProgress: " << std::setw(2) << std::setfill('0') <<
        std::fixed << std::setprecision(0) << progress << "%";
    }
}

void renderTriangleTest(Camera *cam, Scene1b *scene, surface<R8G8B8A8> &distance_image, surface<R8G8B8A8> &bary_image) {
    int w = distance_image.width();
    int h = distance_image.height();
    float PI = 3.141592f;
    for (int y = 0; y < h; y++) {
        printProgress(y, h);

        float sh = sin(PI / 2 + y * PI / h);
        float ch = cos(PI / 2 + y * PI / h);
        for (int x = 0; x < w; x++) {
            float3 vec = float3(0, 0, -1);
            float s = sin(x * PI / w + PI / 2);
            float c = cos(x * PI / w + PI / 2);

            float rx = vec.x * c + vec.z * s;
            float rz = vec.z * c - vec.x * s;

            float3 tmpvec = float3(rx, vec.y, rz);

            float ry = tmpvec.y * ch + tmpvec.z * sh;
            rz = tmpvec.z * ch - tmpvec.y * sh;

            float3 ray_dir = normalize(float3(tmpvec.x, ry, rz));
            Ray ray(float3(0, 0, 5), ray_dir);


            float distance = -1.f;
            float2 bary;
            float3 intersection;
            for (BVHTree::StrongNodePtr node : scene->bvh_tree.test_leaf_nodes) {
                for (Triangle &t : node->triangles) {
                    if (t.intersectRay(ray, distance, bary)) {
                        distance_image(x, y) = R8G8B8A8(distance / 25.f);
                        bary_image(x, y) = R8G8B8A8(float3(bary, 0.f));
                        break;
                    }
                }
                if (distance != -1.f)
                    break;
            }
        }
    }
}

void renderPhongTest(Scene1b *scene, surface<R8G8B8A8> &phong_image) {
    int w = phong_image.width();
    int h = phong_image.height();
    float PI = 3.141592f;
    for (int y = 0; y < h; y++) {
        printProgress(y, h);

        float sh = sin(PI / 2 + y * PI / h);
        float ch = cos(PI / 2 + y * PI / h);
        for (int x = 0; x < w; x++) {
            float3 vec = float3(0, 0, -1);
            float s = sin(x * PI / w + PI / 2);
            float c = cos(x * PI / w + PI / 2);

            float rx = vec.x * c + vec.z * s;
            float rz = vec.z * c - vec.x * s;

            float3 tmpvec = float3(rx, vec.y, rz);

            float ry = tmpvec.y * ch + tmpvec.z * sh;
            rz = tmpvec.z * ch - tmpvec.y * sh;

            float3 ray_dir = normalize(float3(tmpvec.x, ry, rz));
            Ray ray(float3(0, 1, 3), ray_dir);

            Intersection hit;
            if (scene->intersectRay(ray, hit)) {
                float3 color = clamp(scene->phong(ray, hit));
                phong_image(x, y) = R8G8B8A8(color);
            }

        }
    }
}

void renderReflectionTest(Scene1b *scene, surface<R8G8B8A8> &refl_image) {
    int w = refl_image.width();
    int h = refl_image.height();
    float PI = 3.141592f;
    for (int y = 0; y < h; y++) {
        printProgress(y, h);

        float sh = sin(PI / 2 + y * PI / h);
        float ch = cos(PI / 2 + y * PI / h);
        for (int x = 0; x < w; x++) {
            float3 vec = float3(0, 0, -1);
            float s = sin(x * PI / w + PI / 2);
            float c = cos(x * PI / w + PI / 2);

            float rx = vec.x * c + vec.z * s;
            float rz = vec.z * c - vec.x * s;

            float3 tmpvec = float3(rx, vec.y, rz);

            float ry = tmpvec.y * ch + tmpvec.z * sh;
            rz = tmpvec.z * ch - tmpvec.y * sh;

            float3 ray_dir = normalize(float3(tmpvec.x, ry, rz));
            Ray ray(float3(10, 0, 1), ray_dir);

            float3 color = clamp(scene->traceRay(ray));
            refl_image(x, y) = R8G8B8A8(color);

        }
    }
}
