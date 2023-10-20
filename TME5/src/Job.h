#pragma once

#include "Rayon.h"
#include "Scene.h"
#include "Color.h"
#include "Sphere.h"
#include "Barrier.h"

namespace pr {

class Job {
public:
	virtual void run () = 0;
	virtual ~Job() {};
};

class PixelJob : public Job {
private:
	// arguments
	int x;
	int y;
	Color *pixels;
	const Scene::screen_t *screen;
	Barrier *barrier;

	// calcul de la couleur
	void calcul (int x, int y, Color *pixels, const Scene::screen_t * screen) {
		// pour chaque pixel, calculer sa couleur
		// le point de l'ecran par lequel passe ce rayon
		auto & screenPoint = screen[y][x];
		// le rayon a inspecter
		Rayon  ray(scene.getCameraPos(), screenPoint);

		int targetSphere = findClosestInter(scene, ray);

		if (targetSphere == -1) {
			// keep background color
			continue ;
		} else {
			const Sphere & obj = *(scene.begin() + targetSphere);
			// pixel prend la couleur de l'objet
			Color finalcolor = computeColor(obj, ray, scene.getCameraPos(), lights);
			// le point de l'image (pixel) dont on vient de calculer la couleur
			Color & pixel = pixels[y*scene.getHeight() + x];
			// mettre a jour la couleur du pixel dans l'image finale.
			pixel = finalcolor;
		}
	}

public:
	PixelJob(int x, int y, Barrier * barrier, Color * pixels, const Scene::screen_t * screen) : x(x), y(y), barrier(barrier), pixels(pixels), screen(screen){}

	void run() {
		calcul(x, y, pixels, screen);
		b->done();
	}
	~PixelJob(){}
};

// Job concret : exemple

/**
class SleepJob : public Job {
	int calcul (int v) {
		std::cout << "Computing for arg =" << v << std::endl;
		// traiter un gros calcul
		this_thread::sleep_for(1s);
		int ret = v % 255;
		std::cout << "Obtained for arg =" << arg <<  " result " << ret << std::endl;
		return ret;
	}
	int arg;
	int * ret;
public :
	SleepJob(int arg, int * ret) : arg(arg), ret(ret) {}
	void run () {
		* ret = calcul(arg);
	}
	~SleepJob(){}
};
**/

}
