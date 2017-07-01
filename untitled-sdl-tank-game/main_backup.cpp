#include<iostream>

#include<SDL.h>
#include<SDL_image.h>
#include<math.h>
#include<vector>


#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4


#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT  480

#define BULLET_LIFE 50
#define FLAME_LIFE 15

using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Surface* screenSurface = NULL;

bool init(){
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        success = false;
        std::cout<<"Error: "<<SDL_GetError()<<std::endl;
    }else{
        window = SDL_CreateWindow( "Ziemniak", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

        if (window == NULL){
            success = false;
            std::cout<<"Error: "<<SDL_GetError()<<std::endl;
        }else{
            int imgFlags = IMG_INIT_PNG;

		    if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
                success = false;
                std::cout<<"Error: "<<SDL_GetError()<<std::endl;
            }else{
                renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                if (renderer == NULL){
                    success = false;
                    std::cout<<"Error: "<<SDL_GetError()<<std::endl;
                }
            }

			screenSurface = SDL_GetWindowSurface(window);
        }
    }

    return success;
}

void close(){
    SDL_FreeSurface(screenSurface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

}

class MyTexture{
    public:
        SDL_Texture* texture;

    MyTexture(){
        texture = NULL;
        std::cout<<"Empty texture created!"<<std::endl;
    }
    MyTexture(std::string fileName){

        SDL_Surface* textureSurface = NULL;

        textureSurface = IMG_Load(fileName.c_str());
        if (textureSurface == NULL){
            std::cout<<"Error: "<<SDL_GetError()<<std::endl;
        }

        SDL_SetColorKey( textureSurface, SDL_TRUE, SDL_MapRGB( textureSurface->format, 0xFF, 0x00, 0xFF ) );

        texture = SDL_CreateTextureFromSurface(renderer,textureSurface);
        if (texture == NULL){
            std::cout<<"Error: "<<SDL_GetError()<<std::endl;
        }
        SDL_FreeSurface(textureSurface);
        std::cout<<"Texture created!"<<std::endl;
    }

    ~MyTexture(){
        SDL_DestroyTexture(texture);
        std::cout<<"Destructor called!"<<std::endl;

    }


    void render(int x, int y, int mode){
        SDL_Rect rect;

        int w,h;

        SDL_QueryTexture(texture,NULL,NULL,&w,&h);

        if (mode == RENDER_IN_CENTER){
            rect.x = x - w/2;
            rect.y = y - h/2;
        }else if(mode == RENDER_IN_CORNER){
            rect.x = x;
            rect.y = y;
        }

        rect.w = w;
        rect.h = h;

        SDL_RenderCopy(renderer,texture,NULL,&rect);
    }

    void renderAnim(int x, int y, int mode,int numOfFrames, int frameIndex){
        SDL_Rect targetRect;
        SDL_Rect sourceRect;

        int w,h;


        SDL_QueryTexture(texture,NULL,NULL,&w,&h);



        int tileWidth = w/numOfFrames;

        sourceRect.x = frameIndex*tileWidth;
        sourceRect.y = 0;
        sourceRect.w = tileWidth;
        sourceRect.h = h;

        if (mode == RENDER_IN_CENTER){
            targetRect.x = x - tileWidth/2;
            targetRect.y = y - h/2;
        }else if(mode == RENDER_IN_CORNER){
            targetRect.x = x;
            targetRect.y = y;
        }

        targetRect.w = tileWidth;
        targetRect.h = h;

        SDL_RenderCopy(renderer,texture,&sourceRect,&targetRect);
    }
};


class GameObject{
    public:
        int posX;
        int posY;

        MyTexture* myTex;

        GameObject(int x, int y){
            posX = x;
            posY = y;
            myTex = NULL;
        }

        ~GameObject(){
            //delete this->myTex;
            cout<<"Destroying game object!"<<endl;
        }

        void moveObj(int direction){
            if (direction == LEFT){
                posX -=5;
            }
            if (direction == RIGHT){
                posX +=5;
            }
            if (direction == UP){
                posY -=5;
            }
            if (direction == DOWN){
                posY +=5;
            }
        }
};

class Flame : public GameObject{
    public:
        int texFrame;
        int lifeCycle;

        Flame(int x, int y) : GameObject(x,y){
            cout<<"Flame created!"<<endl;
            texFrame = 0;
            lifeCycle = 0;

        }

        void act(){


            lifeCycle += 1;

            if (lifeCycle % 3 == 0) {
                texFrame += 1;
            }

        }

};


class Player : public GameObject{
    public:
        bool bulletReady;
        int reloadingPhase;
        bool shotFired;
        bool prevShotFired;
        bool addBullet;

        Player(int x, int y):GameObject(x,y){

            posX = x;
            posY = y;
            myTex = NULL;

            bulletReady = true;
            reloadingPhase = 100;
            shotFired = false;
            prevShotFired = false;
            addBullet = false;
        }

        void handleGun(){
            if (shotFired == true && prevShotFired == false && bulletReady == true ){
                bulletReady = false;
                reloadingPhase = 0;

                addBullet = true;

            }else{
                addBullet = false;
            }

            if (bulletReady == false){
                if (reloadingPhase < 100){
                    reloadingPhase += 10;
                }
                if (reloadingPhase >= 100){
                    bulletReady = true;
                }
            }

            prevShotFired = shotFired;
        }

};

class Bullet : public GameObject{
    public:

        bool destroyed;
        int lifeCycle;
        //int posX, posY;


        Bullet(int x, int y):GameObject(x,y){
            posX = x;
            posY = y;
            lifeCycle = 0;
            destroyed = false;
            cout<<"Bullet created!"<<endl;
        }

        ~Bullet(){
            cout<<"Bullet destroyed!"<<endl;
        }

        void move(){
            lifeCycle += 1;
            if (lifeCycle > 20){
                destroyed = true;
            }
            posX += 4;
            //cout<<"bullet pos x: "<<posX<<endl;

        }


};


class Enemy : public GameObject{
    public:
        //int posX,posY;
        Enemy(int x, int y) : GameObject(x,y){
            posX = x;
            posY = y;
        }

        bool checkHit(Bullet &b){
            double distance = pow(pow(b.posX - this->posX,2) + pow(b.posY - this->posY,2) , 0.5);
            bool hit = false;
            if (distance < 25.0){
                hit = true;
            }
            return hit;
        }
};

GameObject* terrain;
Player* player;
Enemy enemyTemplate = Enemy(-10,-10);
Bullet bulletTemplate = Bullet(-10,-10);
Flame flameTemplate = Flame(-10,-10);
vector<Enemy> enemies;
vector<Bullet> bullets;
vector<Flame> flames;
GameObject* helpScreen;

bool initGame(){
    terrain = new GameObject(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    terrain->myTex = new MyTexture("data\\\gfx\\terrain.png");

    player = new Player(100,100);
    player->myTex = new MyTexture("data\\gfx\\player.png");


    enemyTemplate.myTex = new MyTexture("data\\gfx\\enemy.png");

    bulletTemplate.myTex = new MyTexture("data\\gfx\\bullet.png");

    flameTemplate.myTex = new MyTexture("data\\gfx\\flame.png");


    helpScreen = new GameObject(320,450);
    helpScreen->myTex = new MyTexture("data\\gfx\\help.png");


    Enemy e = enemyTemplate;

    e.posX = 250;
    e.posY = 400;

    enemies.push_back(e);

    e = enemyTemplate;

    e.posX = 450;
    e.posY = 100;

    enemies.push_back(e);


    //std::cout<<player->myTex.texture<<std::endl;
    std::cout<<"Game init done!"<<std::endl;
    return true;

}

bool endGame(){
    delete terrain;
    delete player;
    return true;
}

void mainLoop(){
    bool exit = false;


    while (exit != true){
        //game logic cycle
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0){

            const Uint8* state = SDL_GetKeyboardState(NULL);

            if (state[SDL_SCANCODE_UP]){
                player->moveObj(UP);
            }
            if (state[SDL_SCANCODE_DOWN]){
                player->moveObj(DOWN);
            }
            if (state[SDL_SCANCODE_LEFT]){
                player->moveObj(LEFT);
            }
            if (state[SDL_SCANCODE_RIGHT]){
                player->moveObj(RIGHT);
            }
            if (state[SDL_SCANCODE_SPACE]){
                player->shotFired = true;
            }else{
                player->shotFired = false;
            }
            if( e.type == SDL_KEYDOWN  || e.type == SDL_KEYUP) {
                    if (e.key.keysym.sym == SDLK_ESCAPE) {exit = true;}


            }
        }

        player->handleGun();

        if (player->addBullet == true){
            Bullet b = bulletTemplate;
            b.posX = player->posX;
            b.posY = player->posY;
            bullets.push_back(b);
            cout<<"bullet added!";
        }


        vector<Enemy>::iterator enemyIt;
        vector<Bullet>::iterator bulletIt;
        vector<Flame>::iterator flameIt;


        int n;
        int i;
        n = bullets.size();

        for (i = 0; i<n; i++){
            //cout<<"Entering loop..."<<"No. of elements: "<<bullets.size()<<endl;
            bullets[i].move();

            if (bullets[i].lifeCycle > BULLET_LIFE){
                bullets.erase(bullets.begin() + i);
                cout<<"Deleted"<<endl;
            }
        }

        n = enemies.size();

        for (i=0; i<n; i++){
            for (bulletIt = bullets.begin();bulletIt != bullets.end(); ++bulletIt){
                if (enemies[i].checkHit(*bulletIt) == true){
                    //add flame

                    Flame f = flameTemplate;

                    f.posX = enemies[i].posX+10;
                    f.posY = enemies[i].posY+10;

                    flames.push_back(f);

                    f = flameTemplate;

                    f.posX = enemies[i].posX-15;
                    f.posY = enemies[i].posY+3;

                    flames.push_back(f);

                    f = flameTemplate;

                    f.posX = enemies[i].posX;
                    f.posY = enemies[i].posY-7;

                    flames.push_back(f);

                    enemies.erase(enemies.begin() + i);


                }
            }
        }

        n = flames.size();

        for (i=0;i<n;i++){
            flames[i].act();

            if (flames[i].lifeCycle > 14){
                flames.erase(flames.begin() + i);
            }
        }


        //display
        SDL_RenderClear(renderer);


        terrain->myTex->render(terrain->posX,terrain->posY,RENDER_IN_CENTER);
        player->myTex->render(player->posX,player->posY,RENDER_IN_CENTER);


        for (enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt){
            (*enemyIt).myTex->render((*enemyIt).posX,(*enemyIt).posY,RENDER_IN_CENTER);
        }



        for (bulletIt = bullets.begin();bulletIt != bullets.end(); ++bulletIt){
            (*bulletIt).myTex->render((*bulletIt).posX,(*bulletIt).posY,RENDER_IN_CENTER);
        }

        for (flameIt = flames.begin();flameIt != flames.end(); ++flameIt){
            Flame &flame =  (*flameIt);
            flame.myTex->renderAnim(flame.posX,flame.posY,RENDER_IN_CENTER,5,flame.texFrame);
        }

        helpScreen->myTex->render(helpScreen->posX,helpScreen->posY,RENDER_IN_CENTER);

        SDL_RenderPresent(renderer);
        //wait
        SDL_Delay(50);
    }
}

int main(int argc,char* args[]){
    bool success = init();


    if (success == true){
        std::cout<<"Init successful!"<<std::endl;
        initGame();
        mainLoop();
        endGame();

        close();
    }


    return 0;
}




