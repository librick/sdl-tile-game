#include <vector>
#include "Sprite.cpp"

class SpriteGroup {
  private:
    std::vector <Sprite*> sprites;
    int spritesSize;
  public:
    std::vector <Sprite*> getSprites() {
      return this->sprites;
    }
    
    void add(Sprite* sprite) {
      this->sprites.push_back(sprite);
      this->spritesSize = this->sprites.size();
    }

    void remove(Sprite spriteObject) {
      for (int i = 0; i < this->spritesSize; i++) {
        if (*this->sprites[i] == spriteObject) {
          this->sprites.erase(this->sprites.begin() + i);
        }
      }
      this->spritesSize = this->sprites.size();
    }

    bool has(Sprite spriteObject) {
      for (int i = 0; i < this->spritesSize; i++) {
        if (*this->sprites[i] == spriteObject) {
          return true;
        }
      }
      return false;
    }

    void update() {
      if(!this->sprites.empty()) {
        for (int i = 0; i < this->spritesSize; i++) {
          this->sprites[i]->update();
        }
      }
    }

    void render() {
      if(!this->sprites.empty()) {
        for (int i = 0; i < this->spritesSize; i++) {
          this->sprites[i]->render();
        }
      }
    }

    void empty() {
      this->sprites.clear();
    }

    SpriteGroup copy() {
      SpriteGroup newGroup;
      for (int i = 0; i < this->spritesSize; i++) {
        newGroup.add(sprites[i]);
      }
      return newGroup;
    }
};