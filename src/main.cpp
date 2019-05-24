#include <igl/opengl/glfw/Viewer.h>
#include <igl/readOFF.h>
#include <igl/per_vertex_normals.h>
#include <igl/per_face_normals.h>
#include <igl/per_corner_normals.h>

Eigen::MatrixXd V;
Eigen::MatrixXi F;

Eigen::MatrixXd N_vertices;
Eigen::MatrixXd N_faces;
Eigen::MatrixXd N_corners;

bool key_down(igl::opengl::glfw::Viewer& viewer, unsigned char key, int modifier) {
  switch (key) {
    case '1':
      viewer.data().set_normals(N_faces);
      return true;
    case '2':
      viewer.data().set_normals(N_vertices);
      return true;
    case '3':
      viewer.data().set_normals(N_corners);
      return true;
    default: break;
  }

  return false;
}

int main(int argc, char *argv[])
{
  std::string file_name = argv[1];
  igl::readOFF(file_name, V, F);

  igl::per_face_normals(V, F, N_faces);

  igl::per_vertex_normals(V, F, N_vertices);

  igl::per_corner_normals(V, F, 20, N_corners);

  // Plot the mesh
  igl::opengl::glfw::Viewer viewer;
  viewer.callback_key_down = &key_down;
  viewer.data().show_lines = false;
  viewer.data().set_mesh(V, F);
  viewer.data().set_normals(N_faces);

  viewer.launch();
}
