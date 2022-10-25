

#ifndef GALOBRUXO_H_INCLUDED
#define GALOBRUXO_H

#include "Galo.h"

namespace Rooster {

    class Peste : public Galo {

        Texture t;
        float legWalkAngFase = 0;
        float ArmSpinAngFase = 0;
        float Arm2SpinAngFase = 0;



    public:
        Peste(struct GaloStats _stats, int _state, bool isp1) : Galo(_stats, _state, isp1) {

            // Stats
            this->name = "Peste";



            // Creating Attacks
            this->hiKick = new Ataques(6,
                8, 0.5, HitBox{ Vector2f(0, 0), 0 },
                20, 10, -PI / 4, milliseconds(1200), ""
            );

            this->louKick = new Ataques(7,
                5, 0.5, HitBox{ Vector2f(0, 0), 0 },
                20, 10, PI / 4, milliseconds(1000), ""
            );

            this->ultimateShot = new Ataques(8,
                0.9, 0.5, HitBox{ Vector2f(0, 0), 0 },
                10, 3, 0, milliseconds(2000),
                "sounds\\awp.ogg"
            );

            Projectile* cinto = new Projectile(
                Vector2f(0, 0),
                "sprites\\Cinto.png",
                0, 0, Vector2f(1, 1),
                IntRect(0, 0, 603, 100)
            );


            atacking = NOT_ATTACK;
            projectiles.push_back(*cinto);

            Projectile* n2 = new Projectile(true);
            projectiles.push_back(*n2);





            t.loadFromFile("sprites/galoPeste.png");

            model.tex = &t;
            model.loadModel("pesteModel.txt");
            model.autoSetBounds(model.at("Body"), model.at("BackLeg"), model.at("Head"));

            HitBox* hit = new HitBox;
            for (int i = 0; i < model.allBones.size(); i++) {

                hit->center = model.at(i)->drawPos;
                hit->radius = model.at(i)->sprite.getGlobalBounds().width / 2;

                hurtBox.push_back(*hit);
            }

            delete hit;

            struct Animation agacharAnim;
            agacharAnim.init("SecondAnim.txt");
            agacharAnim.playingSpeed = 1;
            agacharAnim.connectLoop = false;
            animations.push_back(agacharAnim);


            bar = new LifeBar(maxHp, isp1, name.c_str());

        }


        void weatherAnim(int frames) {
            model.at(CORPO)->angle += 0;
            model.at(RABO)->angle = sin(frames / 200.f) * 20;
        }
        void jumpAnim() {


            ArmSpinAngFase = -(vspeed / 8) * 45;
            Arm2SpinAngFase = -(vspeed / 8) * 45;

            model.at("Hat")->offset.y += vspeed / 8;

            if (model.at("Hat")->offset.y > 0) {
                model.at("Hat")->offset.y = 0;
            }
            model.at("FrontShoe")->angle = vspeed;
            model.at("BackShoe")->angle = vspeed;

            model.at("FrontBigode")->angle += vspeed / 2;
            model.at("BackBigode")->angle += vspeed / 2;



        }
        void cairAnim() {
            model.at("Hat")->offset.y = 0;
            model.at("FrontBigode")->angle *= 0.9;
            model.at("BackBigode")->angle *= 0.9;

            model.at("Body")->angle *= 0.7;
        }
        void runAnim() {
            legWalkAngFase += hspeed;
            legWalkAngFase -= ((int)legWalkAngFase / 360) * 360;

            model.at("FrontShoe")->angle = sin(2 * PI * legWalkAngFase / 360) * 60;
            model.at("BackShoe")->angle = -sin(2 * PI * legWalkAngFase / 360) * 60;

            model.at("FrontBigode")->angle = sin(2 * PI * legWalkAngFase / 360) * 60;
            model.at("BackBigode")->angle = -sin(2 * PI * legWalkAngFase / 360) * 60;

            model.at("FrontArm")->angle += sin(2 * PI * legWalkAngFase / 360) * 60;
            model.at("BackArm")->angle += -sin(2 * PI * legWalkAngFase / 360) * 60;

            model.at("Hat")->angle += -sin(2 * PI * legWalkAngFase / 360);


        }
        void runReset() {


            model.at("FrontShoe")->angle *= 0.8;
            model.at("BackShoe")->angle *= 0.8;

            model.at("FrontArm")->angle = 0;
            model.at("BackArm")->angle = 0;

            model.at("Hat")->angle *= 0.9;

            model.at("Body")->offset.y = 0;
            model.at("BackShoe")->offset.y = 0;
            model.at("FrontShoe")->offset.y = 0;



        }

        void defend() override {
            estado = DEFENDING;
        }

        void agachadinha() {
            hspeed = 0;
        }

        void highKick() override {
            if (atacking == NOT_ATTACK) {
                atacking = HIGH_KICK;
                hiKick->init.restart();
            }

        }

        void lowKick() override {
            if (atacking == NOT_ATTACK) {
                atacking = LOW_KICK;
                louKick->init.restart();
            }
        }

        void especial() override {
            if (atacking == NOT_ATTACK) {
                atacking = SPECIAL;
                ultimateShot->init.restart();
            }

        }
        void especialAnim() {
            Time t = ultimateShot->init.getElapsedTime();

            if (t > ultimateShot->timeLapse) {
                atacking = NOT_ATTACK;
            }

            float percentage = (float)t.asMilliseconds() / (ultimateShot->timeLapse.asMilliseconds());

            int angFix = (facingRight) ? 1 : -1;
            angFix = -1;


            if (percentage < 0.5f / 3.f) {


                float thisPercentage = percentage * 3;


            }
            else if (percentage < 2.f / 3.f) {
                float thisPercentage = percentage * 3;


            }
            else if (percentage < 2.05f / 3.f) {
                ultimateShot->playSound();
            }
            else if (percentage < 2.2f / 3.f) {



                projectiles[0].setVisibility(true);


                projectiles[0].setPosition(
                    Vector2f(model.at("BackArm")->drawPos.x,
                        (model.at("BackArm")->drawPos.y - projectiles[0].getSize().y / 2)
                    )
                );

                if (facingRight) {
                    projectiles[0].setImpulse(20, 0);
                    projectiles[0].setScale(Vector2f(0.5, 0.5));
                }

                else {
                    projectiles[0].setImpulse(-20, 0);
                    projectiles[0].setScale(Vector2f(-0.5, 0.5));
                }


                ultimateShot->isAtacking = true;
            }
            else if (percentage < 2.5f / 3.f) {




            }
            else if (percentage < 2.9 / 3.f) {

            }
            else {

            }
        }

        void louKickAnim() {
            Time t = louKick->init.getElapsedTime();

            if (t > louKick->timeLapse) {
                atacking = STOPPED;
            }

            float percentage = (float)t.asMilliseconds() / (louKick->timeLapse.asMilliseconds());


            if (percentage < 1.f / 3.f) {

                float thisPercentage = percentage * 3;
                model.at("FrontArm")->angle = 45 * sin(thisPercentage * PI / 2);
                model.at("BackArm")->angle = 20 * sin(thisPercentage * PI / 2);
                model.at("BackLeg")->angle = 20 * sin(thisPercentage * PI / 2);
                model.at("Head")->angle = -20 * sin(thisPercentage * PI / 2);
                model.at("FrontEyebrow")->offset.y += 0.5;
                model.at("BackEyebrow")->offset.y += 0.5;
                model.at("FrontLeg")->offset.y = -20 * thisPercentage;
                model.at("BackLeg")->offset.y = -20 * thisPercentage;
                model.at("Biko")->offset.x = -2;
                model.at("Body")->offset.y = -20 * thisPercentage;
                model.at("Body")->angle = 45 * sin(thisPercentage * PI / 2);
            }
            else if (percentage < 2.f / 3.f) {

                model.at("Body")->angle = -75;
                model.at("FrontArm")->angle = -60;
                model.at("BackArm")->angle = -60;

                model.at("BackLeg")->angle = 20;
                model.at("Head")->angle = 45;
                model.at("Head")->offset.x = -15;

                model.at("FrontLeg")->angle = 45;
                model.at("BackLeg")->angle = 45;


            }
            else if (percentage < 2.9f / 3.f) {

                model.at("FrontArm")->angle *= 0.9;
                model.at("BackArm")->angle *= 0.9;

                model.at("BackArm")->angle *= 0.9;
                model.at("BackLeg")->angle *= 0.9;

                model.at("Head")->angle *= 0.9;
                model.at("Head")->offset.x *= 0.9;

                model.at("FrontEyebrow")->offset.y *= 0.9;
                model.at("BackEyebrow")->offset.y *= 0.9;

                model.at("FrontLeg")->angle *= 0.9;
                model.at("BackLeg")->offset.y *= 0.9;

                model.at("Body")->angle *= 0.9;

            }
            else {

                model.at("FrontArm")->angle = 0;
                model.at("BackArm")->angle = 0;

                model.at("BackArm")->angle = 0;
                model.at("BackLeg")->angle = 0;

                model.at("Head")->angle = 0;
                model.at("Head")->offset.x = 0;

                model.at("FrontEyebrow")->offset.y = 0;
                model.at("BackEyebrow")->offset.y = 0;

                model.at("FrontLeg")->angle = 0;
                model.at("BackLeg")->offset.y = 0;

                model.at("Body")->angle = 0;
            }


        }

        void highAtackAnim() {
            Time t = hiKick->init.getElapsedTime();

            if (t > hiKick->timeLapse) {
                atacking = STOPPED;
            }

            float percentage = (float)t.asMilliseconds() / (hiKick->timeLapse.asMilliseconds());

            if (percentage < 0.5 / 3.f) {

                float thisPercentage = percentage * 6;

                model.at("FrontArm")->angle = 45 * sin(thisPercentage * PI / 2);
                model.at("BackArm")->angle = -90 * sin(thisPercentage * PI / 2);
                model.at("BackLeg")->angle = 15 * sin(thisPercentage * PI / 2);
                model.at("Head")->angle = -20 * sin(thisPercentage * PI / 2);
                model.at("FrontEyebrow")->offset.y += 1;
                model.at("BackEyebrow")->offset.y += 1;
                model.at("FrontLeg")->offset.y = -20 * sin(thisPercentage * PI / 2);

            }
            else if (percentage < 1.f / 3.f) {
                float thisPercentage = percentage * 3;

                model.at("Body")->angle = -60 * sin(thisPercentage * PI / 2);
                model.at("BackLeg")->angle = 50 * sin(thisPercentage * PI / 2);

            }
            else if (percentage < 2.f / 3.f) {

                model.at("Body")->angle = 60;
                model.at("BackLeg")->angle = 50;
                model.at("FrontLeg")->angle = -45;
                model.at("BackLeg")->offset.x -= 1;
                model.at("BackLeg")->offset.y -= 1;
                model.at("FrontArm")->angle = -45;
                model.at("BackArm")->angle = 90;
            }
            else if (percentage < 2.9f / 3.f) {

                model.at("Body")->angle *= 0.9;
                model.at("BackLeg")->angle *= 0.9;
                model.at("BackLeg")->offset.x *= 0.9;
                model.at("BackLeg")->offset.y *= 0.9;
                model.at("FrontArm")->angle *= 0.9;
                model.at("BackArm")->angle *= 0.9;
                model.at("FrontLeg")->offset.y *= 0.9;
                model.at("Head")->angle *= 0.9;
            }
            else {
                model.at("Body")->angle = 0;
                model.at("BackLeg")->angle = 0;
                model.at("BackLeg")->offset.x = 0;
                model.at("BackLeg")->offset.y = 0;
                model.at("FrontArm")->angle = 0;
                model.at("BackArm")->angle = 0;
                model.at("FrontLeg")->offset.y = 0;
                model.at("Head")->angle *= 0;
                model.at("FrontEyebrow")->offset.y = 0;
                model.at("BackEyebrow")->offset.y = 0;
            }
        }

        void updateAnimations() override {
            if (estadoUpdate) {
               // model.resetToBase();
              // animations[0].playingFrame = 0;
            }

            model.at("FrontArm")->angle = ArmSpinAngFase;
            model.at("BackArm")->angle = Arm2SpinAngFase;
            if (air) {
               // jumpAnim();
            }
            else {
                //cairAnim();
            }

            if (estado == RUNNING) {
                //runAnim();
            }
            else if (estado == DEFENDING) {
               // animations[0].update();
               // if (animations[0].playingFrame > 15) {
               //     animations[0].playingFrame = 15;
               // }
               // model.updateWithAnimation(animations[0]);

            }
            else if (estado == STOPPED) {
              //  runReset();
            }



            if (atacking == HIGH_KICK) {
                // highAtackAnim();
            }
            else if (atacking == LOW_KICK) {
                // louKickAnim();
            }
            else if (atacking == SPECIAL) {
                // especialAnim();
            }

            projectiles[0].update();
        }


        
    };


}

#endif // GALOBRUXO_H_INCLUDED