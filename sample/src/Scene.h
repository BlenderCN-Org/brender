#ifndef __Scene__
#define __Scene__

#include <vector>
#include <memory>
#include <string>

#define EIGEN_DONT_ALIGN_STATICALLY
#include <Eigen/Dense>

#include <BrenderManager.h>

class Cloth;
class Particle;
class MatrixStack;
class Program;
class Shape;
class Sphere;
class Brenderable;

class Scene
{
public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	
	Scene();
	virtual ~Scene();
	
	void load(const std::string &RESOURCE_DIR);
	void init();
	void tare();
	void reset();
	void step();
	
	void draw(std::shared_ptr<MatrixStack> MV, const std::shared_ptr<Program> prog) const;
	
	double getTime() const { return t; }
	
private:
	double t;
	double h;
	Eigen::Vector3d grav;
	
	std::shared_ptr<Shape> sphereShape; //this will be in sphere class
	std::shared_ptr<Cloth> cloth;
	std::shared_ptr<Sphere> the_sphere; //fix naming
	std::vector< std::shared_ptr<Particle> > spheres; // shared_ptr <sphere>

	BrenderManager *brender;
};

#endif
