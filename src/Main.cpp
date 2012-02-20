#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <time.h>

#include "Enemy.h"
#include "Player.h"
#include "Boss.h"
#include "SpatialHash.h"
#include "Particle.h"
#include "Peak.h"
#include "EffectSystem.h"
#include "Title.h"
#include "Music.h"
#include "Credits.h"


void drawScore(sf::RenderWindow& app, Player* player, sf::String& KillCount, 
               sf::String& Timer, sf::String& HP, sf::String& Score, int running_time);

void showCredits(sf::RenderWindow& app);

//If return a reference that fail because the string is returned is new (so
//reference will be lost)
std::string operator<<(std::string& aString, std::stringstream& stream)
{
  return aString + stream.str();
}

enum GameState
{
    INTRO,
    WAVE,
    BOSS,
};

int main(int argc, char** argv) {

  sf::RenderWindow App(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32),
      "Olivier in zombie land");

  App.SetFramerateLimit(60);
  bool game_over = false;

  sf::Image BackgroundImage;
  sf::Sprite BackgroundSprite;

  if(!BackgroundImage.LoadFromFile("../resources/backgrounds/Floor.png")) {
    return EXIT_FAILURE;
  }
  BackgroundSprite.SetImage(BackgroundImage);

  sf::Image predDeathImg;
  sf::Sprite predDeathSprite;
  if(!predDeathImg.LoadFromFile("../resources/sprites/predDeath.png")) {
    return EXIT_FAILURE;
  }
  predDeathSprite.SetImage(predDeathImg);
  predDeathSprite.Resize(predDeathImg.GetWidth() * 2, predDeathImg.GetHeight() * 2);
  predDeathSprite.SetPosition(50, 300);

  std::vector<Object*> objects;

  Player *player = new Player; 
  objects.push_back(player);


  SpatialHash grid;

  sf::Font MyFont;
  if (!MyFont.LoadFromFile("../resources/fonts/comics.ttf", 50)) {
    std::cout << "Fail" << std::endl;
    return EXIT_FAILURE;
  }

  sf::Font megaFont;
  if (!megaFont.LoadFromFile("../resources/fonts/megaman_2.ttf", 50)) {
    std::cout << "Fail megaman font" << std::endl;
    return EXIT_FAILURE;
  }

  sf::String waveText;
  waveText.SetFont(megaFont);
  waveText.SetColor(sf::Color::Red);
  waveText.SetSize(75.f);
  waveText.SetPosition(225, SCREEN_HEIGHT/2 - waveText.GetSize());

  float waveTime;
  int waveNumber = 0;
  bool newWave = true;

  int numBoss = 1;
  int killPerWave = 0;
  int killThisWave = 0;

  sf::String Timer, KillCount, HP, GameOverString, Score;


  Timer.SetFont(MyFont);
  Timer.SetColor(sf::Color(0, 0, 255));
  Timer.SetSize(50.f);
  Timer.SetPosition(SCREEN_WIDTH/2 - Timer.GetSize()/2 - 75, 10.f);

  KillCount.SetFont(MyFont);
  KillCount.SetColor(sf::Color(255, 0, 0));
  KillCount.SetSize(50.f);
  KillCount.SetPosition(SCREEN_WIDTH - 250.f, 10.f);

  HP.SetFont(MyFont);
  HP.SetColor(sf::Color(0, 255, 0));
  HP.SetSize(50.f);
  HP.SetPosition(25.f, 10.f);

  float running_time = 0.0;
  float last_time = 0.0;

  std::srand(std::time(NULL));

  int spawn_rate = 1;
  float spawn_time = 0.0;

  //Title stuff
  Title title(App);

  GameState gameState = INTRO;

  
  //Title loop
  while (App.IsOpened()) {

    //Process events
    sf::Event Event;

    //Window closed
    while (App.GetEvent(Event)) 
    {
      if(Event.Type == sf::Event::Closed)
        App.Close();

      //Escape key pressed
      if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))	
        App.Close();
    }

    if (title.showTitle())
    {
      App.Clear();
      title.update();
      App.Display();
      continue;
    }
    else
    {
      gameState = WAVE;
      break;
    }
  }


  Music::GetInstance().playNormal();

  ParticleSystem particleSystem(SCREEN_WIDTH, SCREEN_HEIGHT);
  particleSystem.setDissolve( true );
  particleSystem.setDissolutionRate( 1 );
	//particleSystem.setGravity(2.0f, 1.2f );

  //Peaking
  Peak peaker(App);

  //Effect
  EffectSystem& effectSystem = EffectSystem::GetInstance();

  //Start game loop
  while (App.IsOpened()) {

    //Process events
    sf::Event Event;

    //Window closed
    while (App.GetEvent(Event)) 
    {
      if(Event.Type == sf::Event::Closed)
        App.Close();

      //Escape key pressed
      if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))	
        App.Close();

      if(Event.Key.Code == sf::Key::F1) {

        sf::Image Screen = App.Capture();
        Screen.SaveToFile("../screenshots/screenshot.jpg");
      }      
    }

    if (player->getHealth() > 0)
    {
        float ElapsedTime = App.GetFrameTime();
        running_time += ElapsedTime;


        switch (gameState)
        {
            case INTRO:
                break;
            case WAVE:
            {
                if (newWave)
                {
                  waveNumber++;
                  waveTime = running_time;
                  newWave = false;

                  std::stringstream wave;
                  wave << waveNumber;
                  waveText.SetText("Wave " + wave.str());

                  killPerWave += 1 * waveNumber;
                  killThisWave = 0;
                }

                if (killThisWave > killPerWave && gameState == WAVE)
                {
                    gameState = BOSS;

                    //Create Boss
                    for (int i = 0; i < numBoss; i++) {
                      objects.push_back(new Boss(particleSystem, sf::Randomizer::Random(200, 600), sf::Randomizer::Random(200, 500)));
                    }

                    newWave = true;
                    break;
                }

                //Increase spawn rate every 30 seconds
                if (running_time - spawn_time > 30) {
                    spawn_rate++;
                    spawn_time = running_time;
                }

                //Spawn Enemy every 2 seconds
                if (running_time - last_time > 2.0) {
                    for (int i = 0; i < spawn_rate; i++) {

                    objects.push_back(new Enemy(particleSystem, rand() % (SCREEN_WIDTH-100) + 40, rand() % (SCREEN_HEIGHT-100) + 40));
                    }
                    last_time = running_time;
                }

                grid.setup(objects);

                //Get elapsed time

                //Handle input
                player->handleInput(App, ElapsedTime, objects, grid);

                App.Draw(BackgroundSprite);

                //Draw body part over floor
                effectSystem.drawBg(App);

                drawScore(App, player, KillCount, Timer, HP, Score, static_cast<int> (running_time));

                player->update(App);
                player->draw(App);

                //Move and draw all object (except bullets)
                for (unsigned int i = 0; i < objects.size(); ++i) {

                    //Aggro is only for enemy
                    objects[i]->aggro(*player, ElapsedTime, objects, grid.getNearby(objects[i]), running_time);

                    //Don't draw player here
                    if (!objects[i]->isPlayer())
                    App.Draw(objects[i]->getSprite());
                }

                //Draw then move bullets
                for(unsigned int i = 0; i < player->bullets.size(); ++i) {
                    App.Draw(player->bullets[i]->getSprite());
                    player->bullets[i]->move(ElapsedTime, objects, grid.getNearby(player->bullets[i]), player->bullets, i);
                    player->bullets[i]->drawEdge(App);
                }

                //Check if player kill a zombie
                for(unsigned int i = 0; i < objects.size(); ++i) {
                    if (!objects[i]->alive(objects, i, running_time))
                    {
                        player->addKill();
                        killThisWave++;
                    }
                }

                break;
            }
            case BOSS:
                if (newWave)
                {
                  waveTime = running_time;
                  newWave = false;
                  waveText.SetText("BOSS");
                }

                grid.setup(objects);

                //Handle input
                player->handleInput(App, ElapsedTime, objects, grid);

                App.Draw(BackgroundSprite);

                //Draw body part over floor
                effectSystem.drawBg(App);

                drawScore(App, player, KillCount, Timer, HP, Score, static_cast<int> (running_time));

                player->update(App);
                player->draw(App);

                //Move and draw all object (except bullets)
                for (unsigned int i = 0; i < objects.size(); ++i) {

                    //Aggro is only for enemy
                    objects[i]->aggro(*player, ElapsedTime, objects, grid.getNearby(objects[i]), running_time);

                    //Don't draw player here
                    if (!objects[i]->isPlayer())
                    App.Draw(objects[i]->getSprite());
                }

                //Draw then move bullets
                for(unsigned int i = 0; i < player->bullets.size(); ++i) {
                    App.Draw(player->bullets[i]->getSprite());
                    player->bullets[i]->move(ElapsedTime, objects, grid.getNearby(player->bullets[i]), player->bullets, i);
                    player->bullets[i]->drawEdge(App);
                }
                
                //Check if player kill a zombie
                for(unsigned int i = 0; i < objects.size(); ++i) {
                    if (!objects[i]->alive(objects, i, running_time))
                    {
                        player->addKill();
                    }
                }

                //if objects contain only player
                if (objects.size() == 1)
                {
                  gameState = WAVE;
                  newWave = true;
                }

                break;
        }

        grid.clear();

        particleSystem.remove();
        particleSystem.update();
        particleSystem.render();

        effectSystem.update(App.GetFrameTime());
        effectSystem.draw(App);

        App.Draw(particleSystem.getSprite());

        //Peaking
        peaker.update();

        if (running_time - waveTime <= 1.5)
        {
          App.Draw(waveText);
        }

        //Diplay window contents on screen
        App.Display();
    }

    //Dead
    else
    {
      if (player->playDeath(App))
      {
        App.Display();
      }
      else if (game_over)  {
        App.Clear();
        App.Draw(predDeathSprite);
        App.Draw(GameOverString);
        App.Draw(Timer);
        App.Draw(KillCount);
        App.Draw(Score);
        App.Display();
      }

      else {
        game_over = true;
        Music::GetInstance().stop();

        //play game over song
        Music::GetInstance().playGameOver();

        //Stay there until credit end
        showCredits(App);

        GameOverString.SetFont(MyFont);
        GameOverString.SetColor(sf::Color(255, 255, 0));
        GameOverString.SetSize(100.f);
        GameOverString.SetPosition(SCREEN_WIDTH/2 -
            GameOverString.GetSize()/2 - 225,
            SCREEN_HEIGHT/2 - 200);

        GameOverString.SetText("Game Over");

        Timer.SetFont(MyFont);
        Timer.SetColor(sf::Color(255, 255, 0));
        Timer.SetSize(50.f);
        Timer.SetPosition(SCREEN_WIDTH/2 - Timer.GetSize()/2 - 75,
            SCREEN_HEIGHT/2);

        KillCount.SetFont(MyFont);
        KillCount.SetColor(sf::Color(255, 255, 0));
        KillCount.SetSize(50.f);
        KillCount.SetPosition(SCREEN_WIDTH/2 - KillCount.GetSize()/2 - 80,
            SCREEN_HEIGHT/2 + 100);

        Score.SetFont(MyFont);
        Score.SetColor(sf::Color(255, 255, 0));
        Score.SetSize(50.f);

        Score.SetPosition(SCREEN_WIDTH/2 - KillCount.GetSize()/2 - 80,
            SCREEN_HEIGHT/2 + 200);

      }    
    }
  }
  return 0;      
}

void showCredits(sf::RenderWindow& app)
{
  Credits credit(app);

  //Credits loop
  while (app.IsOpened()) {

    //Process events
    sf::Event Event;

    //Window closed
    while (app.GetEvent(Event)) 
    {
      if(Event.Type == sf::Event::Closed)
        app.Close();

      //Escape key pressed
      if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))	
        app.Close();
    }

    if (credit.showCredits())
    {
      app.Clear();
      credit.update();
      app.Display();
      continue;
    }
    else
    {
      break;
    }
  }
}

void drawScore(sf::RenderWindow& App, Player* player, sf::String& KillCount, 
               sf::String& Timer, sf::String& HP, sf::String& Score, int running_time)
{
    std::stringstream kill, s2, s3, s4;
    kill << player->getKill();

    KillCount.SetText("Kills: " + kill.str());
    App.Draw(KillCount);

    s2 << (int)running_time;
    std::string time_string;
    s2 >> time_string;      

    Timer.SetText("Time: " + time_string);
    App.Draw(Timer);

    s3 << player->getHealth()/100;
    std::string hp_string;
    s3 >> hp_string;

    HP.SetText("HP: " + hp_string);
    App.Draw(HP);

    s4 << player->getKill() + (int)running_time;
    std::string score_string;
    s4 >> score_string;

    Score.SetText("Score: " + score_string);
}

