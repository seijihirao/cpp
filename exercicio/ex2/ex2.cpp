#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <memory>
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

/**
 * Spring-mass System Model class
 *
 * @author Rodrigo Seiji
 */
class SystemModel {
    private:
        double m, k, b, x, v, a;
    public:
        /**
         * Models a Spring-mass System
         *
         * @param mass - object mass
         * @param spring_constant - spring's `k` constant
         * @param absorver_constant - spring's `b` constant
         * @param initial_x - initial position
         * @param initial_v - initial speed
         */
        SystemModel(double mass, double spring_constant, double absorber_constant, double initial_x, double initial_v) {
            x = initial_x;
            v = initial_v;
            m = mass;
            k = spring_constant;
            b = absorber_constant;
            a = 0;
        }

        double getForce() {
            return -k*x -b*v;
        }

        double getAcceleration() {
            return a;
        }
        
        void setAcceleration(double a) {
            this->a = a;
        }

        double getVelocity() {
            return v;
        }

        void setVelocity(double v) {
            this->v = v;
        }

        double getPosition() {
            return x;
        }

        void setPosition(double x) {
            this->x = x;
        }

        double getMass() {
            return this->m;
        }

        void setMass(double m) {
            this->m = m;
        }

};

/**
 * Spring-mass System Controller class
 *
 * @author Rodrigo Seiji
 */
class SystemController {
    private:
        int t;
        double dt;
        shared_ptr<SystemModel> model;
    public:
        /**
         * Constrols a Spring-mass System
         *
         * @params model - system model
         * @params dt - time increase step
         */
        SystemController(shared_ptr<SystemModel> model, double dt) {
            this->model = model;
            this->dt = dt;
        }

        /**
         * Calculate next step
         */
        shared_ptr<SystemModel> next() {
            double F = model->getForce();
            model->setAcceleration(F/model->getMass());
            model->setVelocity(model->getVelocity() + model->getAcceleration() * dt);
            model->setPosition(model->getPosition() + model->getVelocity() * dt);

            return model;
        }
};

/**
 * Spring-mass System View class
 *
 * @author Rodrigo Seiji
 */
class SystemView {
    private:
        shared_ptr<SystemModel> model;

    public:
        /**
         * View for Spring-mass System
         *
         * @params model - system model
         */
        SystemView(shared_ptr<SystemModel> model) {
            this->model = model;
        }

        /**
         * Prints volume
         *
         * @returns volume
         */
        void printData() {
            cout << "\r";
            for (int i = 0; i < 100; i++) {
                int cur_x = ceil(model->getPosition()) + 50;
                if(i < cur_x) {
                    cout << "X";
                }
                else if (i == cur_x) {
                    cout << "█";
                }
                else if(i > cur_x) {
                    cout << " ";
                }
            }
            cout << flush;
        }

};

/**
 * Main class
 */
int main() {
    shared_ptr<SystemModel> model (new SystemModel(20, 20, 5, 40, 0));
    shared_ptr<SystemController> controller (new SystemController(model, 0.1f));
    shared_ptr<SystemView> view (new SystemView(model));
    unsigned int step = 10 * 1000;

    cout << "Starting Simulation" << endl;
    while(true) {
        controller->next();
        view->printData();
        usleep(step);
    }
    cout << endl;

    return 0;
}
